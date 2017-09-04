#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <vector>
#include <set>

using namespace std;

int intensity_bins_ = 121;
int hasIntensityUncertainty_ = true;
bool skipheader_ = false;


// void writefootprint() {
//   FILE *foutx = fopen("footprint.bin", "wb");
//   FILE *fouty = fopen("footprint.idx", "wb");

//   int last_event_id = 0;
//   int last_areaperil_id = 0;
//   EventRow r;
//   EventIndex idx;
//   idx.event_id = 0;
//   idx.offset = 0;
//   idx.size = 0;
//   int event_id = 0;
//   int count = 0; // 11616 / 968*12
//   std::set<int> events;
//   std::set<int> areaperils;
//   fwrite(&intensity_bins_, sizeof(intensity_bins_), 1, foutx);
//   idx.offset += sizeof(intensity_bins_);
//   fwrite(&hasIntensityUncertainty_, sizeof(hasIntensityUncertainty_), 1, foutx);
//   idx.offset += sizeof(hasIntensityUncertainty_);
//   while (fgets(line, sizeof(line), stdin) != 0) {
//     lineno++;
//     if (sscanf(line, "%d,%d,%d,%f", &event_id, &r.areaperil_id, &r.intensity_bin_id, &r.probability) != 4) {
//       fprintf(stderr, "Invalid data in line %d:\n%s", lineno, line);
//       return;
//     }
//     if (event_id != last_event_id) {
//       if (events.find(event_id_vec[i]) == events.end()) {
//         events.insert(event_id_vec[i]);
//         areaperils.clear();
//         last_areaperil_id = r.areaperil_id;
//         areaperils.insert(r.areaperil_id);
//       } else {
//         fprintf(stderr, "Error (%d):Event_id %d has already been converted - all event data should be contiguous \n", lineno, event_id);
//         exit(-1);
//       }
//       if (last_event_id) {
//         idx.event_id = last_event_id;
//         idx.size = count * sizeof(EventRow);
//         fwrite(&idx, sizeof(idx), 1, fouty);
//         idx.offset += idx.size;
//       }
//       last_event_id = event_id_vec[i];
//       count = 0;
//     }
//     if (last_areaperil_id != r.areaperil_id) {
//       last_areaperil_id = r.areaperil_id;
//       if (areaperils.find(r.areaperil_id) == areaperils.end()) {
//         areaperils.insert(r.areaperil_id);
//       } else {
//         fprintf(stderr, "Error (%d): areaperil_id %d data is not contiguous "
//                         "for event_id %d \n",
//                 lineno, r.areaperil_id, event_id);
//         exit(-1);
//       }
//     }
//     fwrite(&r, sizeof(r), 1, foutx);
//     count++;
//   }
//   idx.event_id = last_event_id;
//   idx.size = count * sizeof(EventRow);
//   fwrite(&idx, sizeof(idx), 1, fouty);
//   fclose(foutx);
//   fclose(fouty);
// }

#pragma pack(push, 1)
struct EventRow
{
	int areaperil_id;
	int intensity_bin_id;
	float probability;
};

struct EventRow_doub
{
	int areaperil_id;
	int intensity_bin_id;
	double probability;
};

struct EventIndex
{
	int event_id;
	long long offset;
	long long size;
};
#pragma pack(pop)

double round_to_decimal(float f) {
    char buf[42];
    sprintf(buf, "%.7g", f); // round to 7 decimal digits
    return atof(buf);
}

void writefootprint(vector<EventRow_doub> &row_vec, vector<int> &event_id_vec) {
	FILE *foutx = fopen("../ktools/examples/static/footprint.bin", "wb");
	FILE *fouty = fopen("../ktools/examples/static/footprint.idx", "wb");

	int last_event_id = 0;
	int last_areaperil_id = 0;
	EventIndex idx;
	idx.event_id = 0;
	idx.offset = 0;
	idx.size = 0;
	int count = 0; // 11616 / 968*12
	std::set<int> events;
	std::set<int> areaperils;
	fwrite(&intensity_bins_, sizeof(intensity_bins_), 1, foutx);
	idx.offset += sizeof(intensity_bins_);
	fwrite(&hasIntensityUncertainty_, sizeof(hasIntensityUncertainty_), 1, foutx);
	idx.offset += sizeof(hasIntensityUncertainty_);

	for (int i = 0; i < row_vec.size(); i++){
		if (event_id_vec[i] != last_event_id) {
			if (events.find(event_id_vec[i]) == events.end()) {
				events.insert(event_id_vec[i]);
				areaperils.clear();
				last_areaperil_id = row_vec[i].areaperil_id;
				areaperils.insert(row_vec[i].areaperil_id);
			} else {
				fprintf(stderr, "Error (%d):Event_id %d has already been converted - all event data should be contiguous \n", i, event_id_vec[i]);
				exit(-1);
			}
			if (last_event_id) {
				idx.event_id = last_event_id;
				idx.size = count * sizeof(EventRow_doub);
				fwrite(&idx, sizeof(idx), 1, fouty);
				idx.offset += idx.size;
			}
			last_event_id = event_id_vec[i];
			count = 0;
		}
		if (last_areaperil_id != row_vec[i].areaperil_id) {
			last_areaperil_id = row_vec[i].areaperil_id;
			if (areaperils.find(row_vec[i].areaperil_id) == areaperils.end()) {
				areaperils.insert(row_vec[i].areaperil_id);
			} else {
				fprintf(stderr, "Error (%d): areaperil_id %d data is not contiguous for event_id %d \n",i, row_vec[i].areaperil_id, event_id_vec[i]);
				exit(-1);
			}
		}
		//printf("%d, %d, %lf\n",row_vec[i].areaperil_id, row_vec[i].intensity_bin_id, row_vec[i].probability);
		fwrite(&row_vec[i], sizeof(row_vec[i]), 1, foutx);
		count++;
	}
	idx.event_id = last_event_id;
	idx.size = count * sizeof(EventRow_doub);
	fwrite(&idx, sizeof(idx), 1, fouty);
	fclose(foutx);
	fclose(fouty);
}

void printrows(int event_id, FILE *finx, long long size, vector<EventRow_doub> &row_vec, vector<int> &event_id_vec)
{
	long long i=0;
	//printf("event_id = %d", event_id);
	while (i < size) {
		EventRow row;
		EventRow_doub row_doub;
		fread(&row, sizeof(row), 1,finx);
		row_doub.areaperil_id = row.areaperil_id;
		row_doub.intensity_bin_id = row.intensity_bin_id;
		row_doub.probability = static_cast<double>(row.probability);
		row_vec.push_back(row_doub);
		event_id_vec.push_back(event_id);
		i += sizeof(row);
	}
}

void readfootprint(vector<EventRow_doub> &row_vec, vector<int> &idx_vec)
{
	FILE *finx = fopen("../ktoolsSINGSPARE/examples/static/footprint.bin", "rb");
	FILE *finy = fopen("../ktoolsSINGSPARE/examples/static/footprint.idx", "rb");

	EventIndex idx;
	if (finy == nullptr) {
		fprintf(stderr, "Footprint idx open failed\n");
		exit(3);
	}
	size_t i = fread(&idx, sizeof(idx), 1, finy);
	while (i != 0) {
		fseek(finx, idx.offset, SEEK_SET);
		printrows(idx.event_id, finx, idx.size, row_vec, idx_vec);
		i = fread(&idx, sizeof(idx), 1, finy);
	}

	fclose(finx);
	fclose(finy);
}

int main(){
	auto row_vec = vector<EventRow_doub>();
	auto idx_vec = vector<int>();
	readfootprint(row_vec, idx_vec);
	writefootprint(row_vec, idx_vec);
}
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <vector>

using namespace std;
#pragma pack(push, 1)
struct damagebindictionary_doub {
        int bin_index;
        double bin_from;
        double bin_to;
        double interpolation;
        int interval_type;
};

struct damagebindictionary {
        int bin_index;
        float bin_from;
        float bin_to;
        float interpolation;
        int interval_type;
};
#pragma pack(pop)


void writebins(vector<damagebindictionary_doub> &damagebins)
{
    for (auto x:damagebins)
    {
        fwrite(&x, sizeof(x), 1, stdout);
    }
}

void getbins(vector<damagebindictionary_doub> &damagebins)
{
	damagebindictionary q;
	damagebindictionary_doub temp;
	size_t i = fread(&q, sizeof(q), 1, stdin);
    while (i != 0) {

    	temp.bin_index  = q.bin_index;
		temp.bin_from  = static_cast<double>(q.bin_from);
		temp.bin_to  = static_cast<double>(q.bin_to);
		temp.interpolation  = static_cast<double>(q.interpolation);
		temp.interval_type  = q.interval_type;

    	damagebins.push_back(temp);
        i = fread(&q, sizeof(q), 1, stdin);
    }
}

int main(){
	auto damagebins = vector<damagebindictionary_doub>();
	getbins(damagebins);
	writebins(damagebins);
}
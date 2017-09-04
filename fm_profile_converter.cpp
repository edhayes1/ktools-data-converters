#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <vector>

using namespace std;


#pragma pack(push, 1)
struct fm_profile {
	int policytc_id;
	int calcrule_id;
	int allocrule_id;
	int ccy_id;
	float deductible;
	float limits;
	float share_prop_of_lim;
	float deductible_prop_of_loss;
	float limit_prop_of_loss;
	float deductible_prop_of_tiv;
	float limit_prop_of_tiv;
	float deductible_prop_of_limit;
};

struct fm_profile_doub {
	int policytc_id;
	int calcrule_id;
	int allocrule_id;
	int ccy_id;
	double deductible;
	double limits;
	double share_prop_of_lim;
	double deductible_prop_of_loss;
	double limit_prop_of_loss;
	double deductible_prop_of_tiv;
	double limit_prop_of_tiv;
	double deductible_prop_of_limit;
};
#pragma pack(pop)

void readfm_profile(vector<fm_profile_doub> &fm_profile_vec)
{
    fm_profile q;
    fm_profile_doub qd;

    size_t i = fread(&q, sizeof(q), 1, stdin);
    while (i != 0) {

    	qd.policytc_id = q.policytc_id;
		qd.calcrule_id = q.calcrule_id;
		qd.allocrule_id = q.allocrule_id;
		qd.ccy_id = q.ccy_id;
		qd.deductible = static_cast<double>(q.deductible);
		qd.limits = static_cast<double>(q.limits);
		qd.share_prop_of_lim = static_cast<double>(q.share_prop_of_lim);
		qd.deductible_prop_of_loss = static_cast<double>(q.deductible_prop_of_loss);
		qd.limit_prop_of_loss = static_cast<double>(q.limit_prop_of_loss);
		qd.deductible_prop_of_tiv = static_cast<double>(q.deductible_prop_of_tiv);
		qd.limit_prop_of_tiv = static_cast<double>(q.limit_prop_of_tiv);
		qd.deductible_prop_of_limit = static_cast<double>(q.deductible_prop_of_limit);
		fm_profile_vec.push_back(qd);
		i = fread(&q, sizeof(q), 1, stdin);
    }
}

void writefm_profile(vector<fm_profile_doub> &fm_profile_vec)
{
	for(auto q: fm_profile_vec){
		fwrite(&q, sizeof(q), 1, stdout);
	}
}

int main(){
	auto fm_profile_vec = vector<fm_profile_doub>();
	readfm_profile(fm_profile_vec);
	writefm_profile(fm_profile_vec);
}
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <vector>

using namespace std;

void getcoverages(vector<double> &coverages)
{
    
	float tiv;
    size_t i = fread(&tiv, sizeof(tiv), 1, stdin);
    while (i != 0) {
    	coverages.push_back(static_cast<double>(tiv));
        i = fread(&tiv, sizeof(tiv), 1, stdin);
    }
}


void writecoverages(vector<double> &coverages)
{
    for(auto x:coverages)
    {
       	fwrite(&x, sizeof(x), 1, stdout);
    }
}

int main(){
	auto coverages = vector<double>();
	getcoverages(coverages);
	writecoverages(coverages);
}
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <vector>

using namespace std;

void writerands(vector<double> &rands)
{
    for(auto x: rands){
       fwrite(&x, sizeof(x), 1, stdout);
   }
}

void getrands(vector<double> &rands){
	float rand;
	while (fread(&rand, sizeof(rand), 1, stdin) == 1){
        rands.push_back(static_cast<double>(rand));
    }
}

int main(){
	auto rands = vector<double>();
	getrands(rands);
	writerands(rands);
}
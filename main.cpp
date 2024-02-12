#include <iostream>
#include <fstream>

#include "ComputedChaining.h"

using std::cout;
using std::endl;
using std::cerr;

void print_table(ComputedChaining & tbl){

	for(int i = 0; i < tbl.data_vec.size(); i++){
		cout << i << ":  " << tbl.data_vec[i].data << "  " << tbl.data_vec[i].link;
		
		if(tbl.data_vec[i].data != -1){
			cout <<"\t P(" << tbl.data_vec[i].data <<  ")    " << tbl.find_num_probes(tbl.data_vec[i].data);
		}
		
		cout << endl;
	}

}

int main(){

	std::ifstream fin("numbers");
	int number;
	int cnt = 0;

	ComputedChaining tbl(7);

	while(fin >> number){
		tbl.insert(number);
	}
	
	cout  << endl << "---Table---" <<endl;
	print_table(tbl);

	fin.close();

	return 0;
}

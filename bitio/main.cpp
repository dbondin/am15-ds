#include <iostream>
#include <fstream>


#include "BitReader.h"

int main(int argc, char **argv) {
	char c;
	std::ifstream ifs("1.txt");

	ifs>>c;

	ifs.close();

	std::cout<<"c="<<c<<std::endl;

	return 1;
}


int main2(int argc, char **argv) {

	bitio::BitReader r;

	r.attach(&std::cin);

	int count=0;
	while(true) {
		int bit = r.read_next_bit();
		if((count++ % 8) == 0) {
			std::cout<<" ";
		}
		std::cout<<bit;
	}

	return 0;
}

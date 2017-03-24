#include <string>
#include <iostream>

#include "bstree.h"

using namespace std;

int main(int argc, char **argv) {

	bstree<int, std::string> t;

	t.add(10, "Десять");
	t.add(5, "Пять");
	t.add(15, "Пятнадцать");

	std::string value;
	bool status = t.find(15, value);
	if(status == true) {
		cout<<"Нашел: "<<value<<endl;
	}
	else {
		cout<<"Не нашел"<<endl;
	}

	bstree<std::string, int> m;
	while(true) {
		string str;
		cin>>str;
		if(cin.eof()) {
			break;
		}
		int value = 1;
		if(m.find(str, value)) {
			value++;
		}
		m.add(str, value);
	}

	cout<<"Here"<<endl;

	int count = m.get_count();
	string * keys = m.get_keys();
	cout<<"Here 2"<<endl;
	for(int i=0; i<count; ++i) {
		string k = keys[i];
		int value;
		m.find(k, value);
		cout<<"key="<<k<<" value="<<value<<endl;
	}
	delete [] keys;

	return 0;
}

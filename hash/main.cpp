#include <iostream>
#include <string>
#include <iterator>

#include "HashMap.h"

using namespace std;

int main(int argc, char **argv) {

	HashMap<int, string> hms;

	hms.put(1, "Васька");
	hms.put(10, "Мурка");
	hms.put(13, "Пушок");
	hms.put(43, "Барсик");
	hms.put(67, "Бегемот");

	string x = hms.get(1);

	cout<<x<<endl;

	HashMap<int, string>::HashMapIterator i = hms.iterator();
	while(i.hasNext()) {
		HashMap<int, string>::HashMapEntry e = i.next();
		cout<<"|| "<<e.key<<" "<<e.value<<endl;
	}
	//TODO: delete i;

	return 0;
}

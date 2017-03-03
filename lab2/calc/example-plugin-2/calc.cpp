#include <string>

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif
double calc(const char * str, int * status);
#ifdef __cplusplus
}
#endif

double calc(const char * str, int * status) {

	string s(str);

	if(status != 0) {
		(*status) = 0;
	}

	if(s[0] == '2') {
		return 2.7;
	}

	return 100.0;
}




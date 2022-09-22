#ifndef APP
#include "app.h"
#endif // !APP

namespace f {

	int getNum(const char* msg) {
		if (msg != NULL) std::cout << msg;

		int res;
		std::cin >> res;

		if (msg != NULL) std::cout << std::endl;
		return res;
	}

}
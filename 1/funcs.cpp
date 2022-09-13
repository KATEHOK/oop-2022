#ifndef APP
#include "app.h"
#endif // !APP

namespace f {

	int getSumOfDigits(int number) {
		int result = 0;
		number = abs(number);

		while (number > 0) {
			result += (number % 10);
			number /= 10;
		}

		return result;
	}

	int* initArray(int count) {
		if (count <= 0) return NULL;
		int* pRes;

		try {
			pRes = new int[count];
		}
		catch (...) {
			return NULL;
		}

		return pRes;
	}

};
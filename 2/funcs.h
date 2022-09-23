#pragma once

namespace f {

	template <typename T>
	T inputNum(const char* msg) {
		if (msg != NULL) std::cout << msg;

		T res;
		std::cin >> res;

		if (msg != NULL) std::cout << std::endl;
		return res;
	}

}
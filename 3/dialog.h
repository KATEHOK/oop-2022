#pragma once

#ifndef APP
#include "app.h"
#endif

using namespace sequence;

namespace dialog {

	typedef bool (*func)(Sequence&);

	template<typename T>
	int getNum(T* pNum) {
		if (pNum == nullptr) throw std::invalid_argument("pNum == nullptr in getNum()");
		int status = FAIL;

		std::cin >> *pNum;
		if (std::cin.good()) status = SUCCESS;
		else std::cin.clear();

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return status;
	}

	int askNum(const std::string fMsg, const std::string sMsg);
	bool confirm();

	bool exit(Sequence& seq);
	bool initFree(Sequence& seq);
	bool initOne(Sequence& seq);
	bool initByArray(Sequence& seq);

	bool printSize(Sequence& seq);
	bool printMaxSize(Sequence& seq);

	bool printElement(Sequence& seq);

	bool input(Sequence& seq);
	bool output(Sequence& seq);

	bool plus(Sequence& seq);
	bool findMonotonicity(Sequence& seq);

	bool insert(Sequence& seq);
	bool printGroupsCount(Sequence& seq);
	bool printSameCount(Sequence& seq);

	void printVars(std::vector<std::string> vars);
	int getChoice(const int mCount);
};

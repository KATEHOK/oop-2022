#pragma once

#ifndef APP
#include "app.h"
#endif

using namespace sequence;

namespace dialog {

	int getNum(int* pNum = nullptr);
	int getNum(const char* pFMsg = nullptr, const char* pSMsg = nullptr);
	int confirm();

	int exit(Sequence* pS = nullptr);
	int initFree(Sequence* pS = nullptr);
	int initOne(Sequence* pS = nullptr);
	int initByArray(Sequence* pS = nullptr);

	int printSize(Sequence* pS = nullptr);
	int printMaxSize(Sequence* pS = nullptr);

	int printElement(Sequence* pS = nullptr);
	int makeClone(Sequence* pS = nullptr);

	int input(Sequence* pS = nullptr);
	int output(Sequence* pS = nullptr);

	int plus(Sequence* pS = nullptr);
	int findMonotonicity(Sequence* pS = nullptr);

	int insert(Sequence* pS = nullptr);
	int printGroupsCount(Sequence* pS = nullptr);
	int printSameCount(Sequence* pS = nullptr);
};

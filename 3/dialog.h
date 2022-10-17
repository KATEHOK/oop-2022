#pragma once

#ifndef APP
#include "app.h"
#endif

using namespace sequence;

namespace dialog {

	int getNum(int* pNum = NULL);
	int getNum(const char* pFMsg = NULL, const char* pSMsg = NULL);
	int confirm();

	int exit(Sequence* pS = NULL);
	int initFree(Sequence* pS = NULL);
	int initOne(Sequence* pS = NULL);
	int initByArray(Sequence* pS = NULL);

	int printSize(Sequence* pS = NULL);
	int printMaxSize(Sequence* pS = NULL);

	int printElement(Sequence* pS = NULL);
	int makeClone(Sequence* pS = NULL);

	int input(Sequence* pS = NULL);
	int output(Sequence* pS = NULL);

	int plus(Sequence* pS = NULL);
	int findMonotonicity(Sequence* pS = NULL);

	int insert(Sequence* pS = NULL);
	int printGroupsCount(Sequence* pS = NULL);
	int printSameCount(Sequence* pS = NULL);
};

#pragma once

#ifndef APP
#include "app.h"
#endif

using namespace sequence;

namespace dialog {

	int getNum(int* pNum = NULL);
	int getNum(const char* pFMsg = NULL, const char* pSMsg = NULL);
	int confirm();

	int exit(Sequence** ppS = NULL);
	int initFree(Sequence** ppS = NULL);
	int initOne(Sequence** ppS = NULL);
	int initByArray(Sequence** ppS = NULL);

	int printSize(Sequence** ppS = NULL);
	int printMaxSize(Sequence** ppS = NULL);

	int printElement(Sequence** ppS = NULL);
	int makeClone(Sequence** ppS = NULL);

	int input(Sequence** ppS = NULL);
	int output(Sequence** ppS = NULL);

	int plus(Sequence** ppS = NULL);
	int findMonotonicity(Sequence** ppS = NULL);

	int insert(Sequence** ppS = NULL);
	int printGroupsCount(Sequence** ppS = NULL);
	int printSameCount(Sequence** ppS = NULL);
};

#ifndef APP
#include "app.h"
#endif // !APP

using namespace matr;

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	char stop = '\0';
	while (stop != 'F') {

		int rowsCount, colsCount, numsCount;


		// input
		std::cout << "Print count of rows: ";
		std::cin >> rowsCount;

		std::cout << std::endl << "Print count of columns: ";
		std::cin >> colsCount;

		std::cout << std::endl << "Print count of numbers: ";
		std::cin >> numsCount;

		std::cout << std::endl << "Print A to use autofilling the matrix: ";
		std::cin >> stop;
		std::cout << std::endl;


		// filling
		Matrix* pMatrix = initM(rowsCount, colsCount);
		if (pMatrix == NULL) continue;

		if (stop == 'A') fill(pMatrix, numsCount);
		else for (int i = 0; i < numsCount; i++) {
			int rowId, colId, value;
			std::cout << "(" << i + 1 << ") Print row id, column id and value separated by a space: ";

			std::cin >> rowId;
			std::cin >> colId;
			std::cin >> value;

			if (insert(pMatrix, rowId, colId, value) == SUCCESS)
				std::cout << std::endl << "Success!" << std::endl;

			else
				std::cout << std::endl << "Fail!" << std::endl;
		}


		// main task
		int* pArray = f::initArray(rowsCount);
		if (pArray == NULL) {
			deleteM(pMatrix);
			break;
		}

		int counter = 0;
		int curSum;
		int firstSum;
		int totalSum;
		Line* pLine = pMatrix->pTop;
		Item* pItem;

		while (pLine != NULL) {
			for (counter = counter; counter < pLine->id; counter++) pArray[counter] = 0;
			pItem = pLine->pItem;

			if (pItem->id > 0) pArray[counter] = 0;

			else {
				firstSum = f::getSumOfDigits(pItem->value);
				totalSum = 0;

				pItem = pItem->pNext;

				while (pItem != NULL) {
					curSum = f::getSumOfDigits(pItem->value);
					if (curSum == firstSum) totalSum += pItem->value;

					pItem = pItem->pNext;
				}

				pArray[counter] = totalSum;
			}
			
			counter++;
			pLine = pLine->pNext;
		}
		for (counter = counter; counter < rowsCount; counter++) pArray[counter] = 0;


		// output
		std::cout << "Matrix:" << std::endl;
		print(pMatrix);
		
		std::cout << std::endl << "Vector:" << std::endl;
		for (int i = 0; i < rowsCount; i++)	std::cout << "[" << i << "] " << pArray[i] << std::endl;


		delete[] pArray;
		deleteM(pMatrix);

		std::cout << std::endl << std::endl << "Print F to stop the program: ";
		std::cin >> stop;
		std::cout << std::endl << std::endl;
	}

	return SUCCESS;
}
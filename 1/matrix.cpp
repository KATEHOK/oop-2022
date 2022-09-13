#ifndef APP
#include "app.h"
#endif // !APP

namespace matr {
	Matrix* initM(int maxRowsCount, int maxColsCount) {
		if (maxColsCount <= 0 || maxRowsCount <= 0) return NULL;
		Matrix* pMatrix;

		try {
			pMatrix = new Matrix;
		}
		catch (...) {
			return NULL;
		}

		pMatrix->pTop = NULL;
		pMatrix->maxRowsCount = maxRowsCount;
		pMatrix->maxColsCount = maxColsCount;

		return pMatrix;
	}

	Line* initL(int id, Item* pItem, Line* pNext) {
		if (id < 0) return NULL;
		Line* pLine;

		try {
			pLine = new Line;
		}
		catch (...) {
			return NULL;
		}

		pLine->id = id;
		pLine->pItem = pItem;
		pLine->pNext = pNext;

		return pLine;
	}

	Item* initI(int id, int value, Item* pNext) {
		if (id < 0) return NULL;
		Item* pItem;

		try {
			pItem = new Item;
		}
		catch (...) {
			return NULL;
		}

		pItem->id = id;
		pItem->value = value;
		pItem->pNext = pNext;

		return pItem;
	}

	void deleteM(Matrix* pMatrix) {
		if (pMatrix == NULL) return;

		deleteLs(pMatrix->pTop);
		delete pMatrix;
	}

	void deleteLs(Line* pLine) {
		if (pLine == NULL) return;

		while (pLine != NULL) {
			Line* pCopy = pLine;
			pLine = pLine->pNext;

			deleteIs(pCopy->pItem);
			delete pCopy;
		}
	}

	void deleteIs(Item* pItem) {
		if (pItem == NULL) return;

		while (pItem != NULL) {
			Item* pCopy = pItem;
			pItem = pItem->pNext;
			delete pCopy;
		}
	}

	template<typename T>
	T searchInList(T pCur, int id) {
		if (pCur == NULL || id < 0 || pCur->id > id) return NULL;
		
		while (pCur != NULL && pCur->id != id) {
			if (pCur->id > id) return NULL;
			pCur = pCur->pNext;
		}

		return pCur;
	}

	template<typename T>
	T searchPrevInList(T pCur, int id) {
		if (pCur == NULL || id < 0 || pCur->id >= id) return NULL;

		while (pCur->pNext != NULL && pCur->pNext->id < id) pCur = pCur->pNext;
		return pCur;
	}

	Item* search(Matrix* pMatrix, int rowId, int colId) {
		if (pMatrix == NULL || rowId < 0 || colId < 0) return NULL;

		Line* pLine = searchInList(pMatrix->pTop, rowId);
		if (pLine == NULL) return NULL;

		return searchInList(pLine->pItem, colId);
	}

	int insert(Matrix* pMatrix, int rowId, int colId, int value) {
		if (pMatrix == NULL || rowId < 0 || colId < 0 ||
			colId >= pMatrix->maxColsCount ||
			rowId >= pMatrix->maxRowsCount) return WRONG_PARAMS;

		if (value == 0) return updateToZero(pMatrix, rowId, colId);

		// Элемент уже существует
		Item* pItem = search(pMatrix, rowId, colId);
		if (pItem != NULL) {
			pItem->value = value;
			return SUCCESS;
		}

		Line* pPrevLine = searchPrevInList(pMatrix->pTop, rowId);
		Line* pLine;

		// Строка уже существует
		if (pPrevLine != NULL && pPrevLine->pNext != NULL && pPrevLine->pNext->id == rowId) // не первая
			pLine = pPrevLine->pNext;
		else if (pMatrix->pTop != NULL && pMatrix->pTop->id == rowId) // первая
			pLine = pMatrix->pTop;

		// Матрица пуста или вставляем в первую позицию
		else if (pPrevLine == NULL) {
			pLine = initL(rowId, NULL, pMatrix->pTop);
			if (pLine == NULL) return MEMERROR;

			pMatrix->pTop = pLine;
		}

		// в середину или в конец новый
		else {
			pLine = initL(rowId, NULL, pPrevLine->pNext);
			if (pLine == NULL) return MEMERROR;

			pPrevLine->pNext = pLine;
		}


		Item* pPrevItem = searchPrevInList(pLine->pItem, colId);

		// Строка пуста или вставляем в первую позицию
		if (pPrevItem == NULL) {
			pItem = initI(colId, value, pLine->pItem);
			if (pItem == NULL) return MEMERROR;

			pLine->pItem = pItem;
		}

		// в середину или в конец
		else {
			pItem = initI(colId, value, pPrevItem->pNext);
			if (pItem == NULL) return MEMERROR;

			pPrevItem->pNext = pItem;
		}

		return SUCCESS;
	}

	int updateToZero(Matrix* pMatrix, int rowId, int colId) {
		if (pMatrix == NULL || rowId < 0 || colId < 0) return WRONG_PARAMS;

		Item* pItem = search(pMatrix, rowId, colId);
		if (pItem == NULL) return NOT_FOUND;

		Line* pPrevLine = searchPrevInList(pMatrix->pTop);
		Line* pLine;

		if (pPrevLine == NULL) pLine = pMatrix->pTop;
		else pLine = pPrevLine->pNext;

		Item* pPrevItem = searchPrevInList(pLine->pItem, colId);

		if (pPrevItem == NULL) pLine->pItem = pItem->pNext;
		else pPrevItem->pNext = pItem->pNext;

		delete pItem;

		if (pLine->pItem != NULL) return SUCCESS;

		if (pPrevLine == NULL) pMatrix->pTop = pLine->pNext;
		else pPrevLine->pNext = pLine->pNext;

		delete pLine;

		return SUCCESS;
	}

	int print(Matrix* pMatrix) {
		if (pMatrix == NULL) return WRONG_PARAMS;

		Line* pLine = pMatrix->pTop;
		Item* pItem;

		if (pLine == NULL) std::cout << "All items is equal 0!" << std::endl;

		else {
			while (pLine != NULL) {
				std::cout << "{" << pLine->id << "} ";
				pItem = pLine->pItem;

				while (pItem != NULL) {
					std::cout << " " << pItem->id << ":" << pItem->value;
					pItem = pItem->pNext;
				}

				std::cout << std::endl;
				pLine = pLine->pNext;
			}
		}

		return SUCCESS;
	}

	int fill(Matrix* pMatrix, int count, int maxValue) {

		if (pMatrix == NULL || count <= 0) return WRONG_PARAMS;
		srand(time(NULL));

		for (int i = 0; i < count; i++) {

			if (insert(pMatrix,
				(rand() * rand()) % pMatrix->maxRowsCount,
				(rand() * rand()) % pMatrix->maxColsCount,
				(rand() * rand()) % maxValue + 1) == MEMERROR) return MEMERROR;
		}

		return SUCCESS;
	}

	int checkCollision(Matrix* pMatrix) {
		if (pMatrix == NULL) return WRONG_PARAMS;

		Line* pLine = pMatrix->pTop;
		int *pArr, *pArr2;

		try {
			pArr = new int[pMatrix->maxColsCount];
			pArr2 = new int[pMatrix->maxRowsCount];
		}
		catch (...) {
			return MEMERROR;
		}

		for (int i = 0; i < pMatrix->maxColsCount; i++) pArr2[i] = 0;

		while (pLine != NULL) {

			Item* pItem = pLine->pItem;
			for (int i = 0; i < pMatrix->maxColsCount; i++) pArr[i] = 0;

			while (pItem != NULL) {
				pArr[pItem->id]++;
				if (pArr[pItem->id] > 1) return FAIL;

				pItem = pItem->pNext;
			}

			pArr2[pLine->id]++;
			if (pArr2[pLine->id] > 1) return FAIL;

			pLine = pLine->pNext;
		}

		delete[] pArr;
		delete[] pArr2;

		return SUCCESS;
	}
};
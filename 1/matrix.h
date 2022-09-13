#pragma once

namespace matr {
	typedef struct Item {
		int id;
		int value;

		struct Item* pNext;
	} Item;

	typedef struct Line {
		int id;
		Item* pItem;

		struct Line* pNext;
	} Line;

	typedef struct Matrix {
		int maxRowsCount;
		int maxColsCount;

		Line* pTop;
	} Matrix;

	/*
	* Инициализирует матрицу:
	*/
	Matrix* initM(int rowsCount = 0, int colsCount = 0);

	/*
	* Инициализирует строку матрицы:
	*/
	Line* initL(int id = -1, Item* pItem = NULL, Line* pNext = NULL);

	/*
	* Инициализирует элемент матрицы:
	*/
	Item* initI(int id = -1, int value = 0, Item* pNext = NULL);

	/*
	* Удаляет матрицу:
	*/
	void deleteM(Matrix* pMatrix = NULL);

	/*
	* Удаляет список строк:
	*/
	void deleteLs(Line* pLine = NULL);

	/*
	* Удаляет список элементов:
	*/
	void deleteIs(Item* pItem = NULL);

	template<typename T>
	/*
	* Выполняет поиск элемента в списке по id:
	*/
	T searchInList(T pCur = NULL, int id = -1);

	template<typename T>
	/*
	* Выполняет поиск элемента в списке максимального среди меньших по id:
	*/
	T searchPrevInList(T pCur = NULL, int id = -1);

	/*
	* Ищет элемент матрицы по координатам:
	*/
	Item* search(Matrix* pMatrix = NULL, int rowId = -1, int colId = -1);

	/*
	* Вставляет значение в матрицу:
	*/
	int insert(Matrix* pMatrix = NULL, int rowId = -1, int colId = -1, int value = 0);

	/*
	* Очищает память по координатам (обновляет значение на 0)
	*/
	int updateToZero(Matrix* pMatrix = NULL, int rowId = -1, int colId = -1);

	/*
	* Печатает матрицу:
	*/
	int print(Matrix* pMatrix = NULL);

	/*
	* Заполняет матрицу рандомными числами:
	*/
	int fill(Matrix* pMatrix = NULL, int count = -1, int maxValue = INT_MAX);

	/*
	* Проверяет пары координат на наличие коллизии
	*/
	int checkCollision(Matrix* pMatrix = NULL);
}
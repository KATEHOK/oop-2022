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
	* �������������� �������:
	*/
	Matrix* initM(int rowsCount = 0, int colsCount = 0);

	/*
	* �������������� ������ �������:
	*/
	Line* initL(int id = -1, Item* pItem = NULL, Line* pNext = NULL);

	/*
	* �������������� ������� �������:
	*/
	Item* initI(int id = -1, int value = 0, Item* pNext = NULL);

	/*
	* ������� �������:
	*/
	void deleteM(Matrix* pMatrix = NULL);

	/*
	* ������� ������ �����:
	*/
	void deleteLs(Line* pLine = NULL);

	/*
	* ������� ������ ���������:
	*/
	void deleteIs(Item* pItem = NULL);

	template<typename T>
	/*
	* ��������� ����� �������� � ������ �� id:
	*/
	T searchInList(T pCur = NULL, int id = -1);

	template<typename T>
	/*
	* ��������� ����� �������� � ������ ������������� ����� ������� �� id:
	*/
	T searchPrevInList(T pCur = NULL, int id = -1);

	/*
	* ���� ������� ������� �� �����������:
	*/
	Item* search(Matrix* pMatrix = NULL, int rowId = -1, int colId = -1);

	/*
	* ��������� �������� � �������:
	*/
	int insert(Matrix* pMatrix = NULL, int rowId = -1, int colId = -1, int value = 0);

	/*
	* ������� ������ �� ����������� (��������� �������� �� 0)
	*/
	int updateToZero(Matrix* pMatrix = NULL, int rowId = -1, int colId = -1);

	/*
	* �������� �������:
	*/
	int print(Matrix* pMatrix = NULL);

	/*
	* ��������� ������� ���������� �������:
	*/
	int fill(Matrix* pMatrix = NULL, int count = -1, int maxValue = INT_MAX);

	/*
	* ��������� ���� ��������� �� ������� ��������
	*/
	int checkCollision(Matrix* pMatrix = NULL);
}
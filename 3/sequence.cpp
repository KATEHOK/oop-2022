#ifndef SEQUENCE_H
#include "sequence.h"
#endif

namespace sequence {

	Sequence::Sequence() {}
	Sequence::Sequence(const int item) { this->insert(item); }
	Sequence::Sequence(const int size, const int* pData) {
		if (pData == NULL) return;
		for (int i = 0; i < size; i++) this->insert(pData[i]);
	}

	int Sequence::getSize() const { return this->size; }
	int Sequence::getMaxSize() const { return this->maxSize; }
	int Sequence::getElement(const int id) const {
		if (id >= 0 && id < this->size) return this->pNums[id];
		return INT_MAX;
	}
	Sequence* Sequence::makeClone() const {
		Sequence* pResult = NULL;
		try { pResult = new Sequence(this->size, this->pNums); }
		catch (...) { return NULL; }
		return pResult;
	}

	void Sequence::input() {
		int value;

		while (this->size < this->maxSize) { 
			std::cin >> value;
			if (!std::cin.good()) {// если ошибка ввода
				std::cin.clear(); // возвращаем "нормальный" режим работы
				break;
			}
			if (this->insert(value) != 0) break; // ловим переполнение
		}
		// очищаем буфер ввода
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	void Sequence::output() const {
		std::cout << "{";
		for (int i = 0; i < this->size; i++) {
			std::cout << this->pNums[i];
			if (i < this->size - 1) std::cout << ", ";
		}
		std::cout << "}";
	}
	
	Sequence* Sequence::plus(const Sequence* pOther) const {
		if (pOther == NULL) return NULL;
		Sequence* pResult = this->makeClone();

		if (pResult == NULL) return NULL;
		int i = 0;

		while (pResult->size < this->maxSize && i < pOther->size) {
			pResult->insert(pOther->pNums[i]);
			i++;
		}

		return pResult;
	}

	Sequence* Sequence::findMonotonicity(const int order) const {
		Sequence* pResult;

		try { pResult = new Sequence; }
		catch (...) { return NULL; }

		int last = this->pNums[0];
		int startId = 0;

		for (int counter = 1; counter < this->size; counter++) {

			if (this->pNums[counter] <= last && order == 0 || 
				this->pNums[counter] >= last && order != 0) {
				// прерывание монотонности из 1 или 2 элементов (продолжаем)
				if (counter - startId <= 2) {
					last = this->pNums[counter];
					startId = counter;
					continue;
				}
				// прерывание монотонности НЕ меньше, чем из трех элементов (завершаем)
				break;
			}
			// монотонность короче 3 элементов
			if (counter - startId < 2) {
				last = this->pNums[counter];
				continue;
			}
			// найдена монотонность из 3 элементов
			if (counter - startId == 2) {
				pResult->insert(this->pNums[startId]);
				pResult->insert(this->pNums[startId + 1]);
			}
			// продолжение монотонности длинее 2 элементов
			last = this->pNums[counter];
			pResult->insert(this->pNums[counter]);
		}

		return pResult;
	}

	int Sequence::insert(const int value) {
		if (this->size == this->maxSize) return OVERSIZE;
		if (value == INT_MAX) return WRONG_PARAMS;
		this->pNums[this->size] = value;
		this->size++;
		return SUCCESS;
	}

	int Sequence::getGroupsCount() const {
		int* pCash;
		if (this->size == 0) return 0;

		try { pCash = new int[this->size * 2]; }
		catch (...) { return -MEMORY_ERROR; }

		int i, j, k;
		for (i = 1; i < this->size * 2; i += 2) pCash[i] = 0;

		pCash[0] = this->pNums[0];
		pCash[1] = 1;

		for (i = 1; i < this->size; i++) {
			for (j = 0; j < this->size * 2; j += 2) {
				if (pCash[j + 1] == 0 || this->pNums[i] == pCash[j]) {
					pCash[j] = this->pNums[i];
					pCash[j + 1]++;
					break;
				}
			}
		}

		j = 0;
		for (i = 1; i < this->size * 2; i += 2) {
			if (pCash[i] == 0) break;
			j++;
		}

		delete[] pCash;
		return j;
	}

	int Sequence::getSameCount(const int value) const {
		int result = 0;
		for (int i = 0; i < this->size; i++)
			if (this->pNums[i] == value) result++;
		return result;
	}
}
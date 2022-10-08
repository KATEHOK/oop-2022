#ifndef SEQUENCE_H
#include "sequence.h"
#endif

namespace sequence {

	Sequence::Sequence() {} // done
	Sequence::Sequence(const int item) { this->insert(item); }
	// done
	Sequence::Sequence(const int size, const int* pData) {
		for (int i = 0; i < size; i++) this->insert(pData[i]);
	}
	// done

	int Sequence::getSize() const { return this->size; }
	int Sequence::getMaxSize() const { return this->maxSize; }
	int Sequence::getElement(const int id) const { return this->pNums[id]; }
	Sequence* Sequence::makeClone() const {
		Sequence* pResult = NULL;

		try { pResult = new Sequence(this->getSize(), this->pNums); }
		catch (...) { return NULL; }

		return pResult;
	}

	void Sequence::input() {
		int value;

		while (this->getSize() < this->getMaxSize()) { // и пока нет ошибки ввода
			std::cin >> value;
			this->insert(value);
		}
	}
	void Sequence::output() const {
		std::cout << "{";
		for (int i = 0; i < this->getSize(); i++) {
			std::cout << this->getElement(i);
			if (i < this->getSize()) std::cout << ", ";
		}
		std::cout << "}";
	}
	// done
	
	Sequence* Sequence::plus(const Sequence* pOther) const {
		if (pOther == NULL) return NULL;
		Sequence* pResult = this->makeClone();

		if (pResult == NULL) return NULL;
		int i = 0;

		while (pResult->getSize() < this->getMaxSize() && i < pOther->getSize()) {
			pResult->insert(pOther->getElement(i));
			i++;
		}

		return pResult;
	}
	// done

	Sequence* Sequence::findMonotonicity(const int order) const {
		Sequence* pResult;

		try { pResult = new Sequence; }
		catch (...) { return NULL; }

		int last = this->getElement(0);
		int startId = 0;

		for (int counter = 1; counter < this->getSize(); counter++) {
			if ((this->getElement(counter) <= last && order == 0 || 
				this->getElement(counter) >= last && order != 0) &&
				counter - startId <= 2) {

				last = this->getElement(counter);
				startId = counter;
				continue;
			}

			if (counter - startId == 2) {
				pResult->insert(this->getElement(startId));
				pResult->insert(this->getElement(startId + 1));
				pResult->insert(this->getElement(startId + 2));
				continue;
			}

			if (this->getElement(counter) <= last && order == 0 ||
				this->getElement(counter) >= last && order != 0) break;

			pResult->insert(this->getElement(counter));
		}

		return pResult;
	}
	// done

	int Sequence::insert(const int value) {
		if (this->getSize() == this->getMaxSize()) return OVERSIZE;
		this->pNums[this->getSize()] = value;
		this->size++;
		return SUCCESS;
	}
	// done

	int Sequence::getGroupsCount() const {
		int* pCash;

		try { pCash = new int [this->getSize() * 2]; }
		catch (...) { return -MEMORY_ERROR; }

		int i, j, k;
		for (i = 1; i < this->getSize() * 2; i += 2) pCash[i] = 0;

		if (this->getSize() > 0) {
			pCash[0] = this->getElement(0);
			pCash[1] = 1;
		}

		for (i = 1; i < this->getSize(); i++) {
			k = 0;

			for (j = 0; k < i; j += 2) {
				if (pCash[j + 1] == 0 || this->getElement(i) == pCash[j]) {
					pCash[j] = this->getElement(i);
					pCash[j + 1]++;
					break;
				}

				k += pCash[j + 1];
			}
		}

		j = 0;
		for (i = 1; i < this->getSize() * 2; i += 2) {
			if (pCash[i] == 0) break;
			j++;
		}

		delete[] pCash;
		return j;
	}
	// done

	int Sequence::getSameCount(const int value) const {
		int result = 0;
		for (int i = 0; i < this->getSize(); i++)
			if (this->getElement(i) == value) result++;
		return result;
	}
	// done
}
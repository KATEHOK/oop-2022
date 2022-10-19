#ifndef SEQUENCE_H
#include "sequence.h"
#endif

namespace sequence {

	Sequence::Sequence() {}
	Sequence::Sequence(const int item) {
		this->insert(item);
	}
	Sequence::Sequence(const int size, const int* pData) {
		if (pData == nullptr)
			throw std::invalid_argument("pData == nullptr in Sequence::Sequence()");
		for (int i = 0; i < size; i++) this->insert(pData[i]);
	}
	Sequence::Sequence(const int* pData) {
		if (pData == nullptr)
			throw std::invalid_argument("pData == nullptr in Sequence::Sequence()");
		int i = 0;
		try { while (this->insert(pData[i]) == SUCCESS) i++; }
		catch (...) { throw std::invalid_argument("pData can not be Sequence");}
	}
	Sequence::Sequence(const Sequence& other) {
		(*this) = Sequence(other.size, other.pNums);
	}

	int Sequence::getSize() const {
		return this->size;
	}
	int Sequence::getMaxSize() const {
		return this->maxSize;
	}
	int Sequence::getElement(const int id) const {
		if (id >= 0 && id < this->size) return this->pNums[id];
		return INT_MAX;
	}

	Sequence& Sequence::makeClone() const {
		Sequence result(this->size, this->pNums);
		return result;
	}

	void Sequence::input(std::istream& in) {
		int value;

		while (this->size < this->maxSize) { 
			in >> value;
			if (!in.good()) {// если ошибка ввода
				in.clear(); // возвращаем "нормальный" режим работы
				break;
			}
			if (this->insert(value) != SUCCESS) break; // ловим переполнение
		}
		// очищаем буфер ввода
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	void Sequence::output(std::ostream& out) const {
		out << "{";
		for (int i = 0; i < this->size; i++) {
			out << this->pNums[i];
			if (i < this->size - 1) out << ", ";
		}
		out << "}";
	}
	
	Sequence& Sequence::plus(const Sequence& other) const {
		Sequence result = this->makeClone();

		int i = 0;

		while (result.size < result.maxSize && i < other.size) {
			result.insert(other.pNums[i]);
			i++;
		}

		return result;
	}
	Sequence& Sequence::minus(const Sequence& other) const {
		Sequence res;
		for (int i = 0; i < other.size; i++) res = res.minusNum(other.pNums[i]);
		return res;
	}
	Sequence& Sequence::minusNum(const int other) const {
		int id = this->findBack(other);
		Sequence res = this->makeClone();

		if (id != INT_MAX) {
			for (int i = id; i < res.size - 1; i++) res.pNums[i] = res.pNums[i + 1];
			res.size--;
		}
		return res;
	}

	Sequence& Sequence::findMonotonicity(const int order) const {
		Sequence res;

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
				res += this->pNums[startId];
				res += this->pNums[startId + 1];
			}
			// продолжение монотонности длинее 2 элементов
			last = this->pNums[counter];
			res += this->pNums[counter];
		}

		return res;
	}

	int Sequence::insert(const int value) {
		if (this->size == this->maxSize) return OVERSIZE;
		if (value == INT_MAX) return WRONG_PARAMS;

		this->pNums[this->size] = value;
		this->size++;
		return SUCCESS;
	}

	int Sequence::getGroupsCount() const {
		if (this->size == 0) return 0;
		int* pCash = new int[this->size];
		int count = 0, j;

		for (int i = 0; i < this->size; i++) {
			j = 0;
			for (j = 0; j < count; j++)
				if (this->pNums[i] == pCash[j]) j = count;

			if (j == count + 1) continue;
			pCash[count] = this->pNums[i];
			count++;
		}

		delete[] pCash;
		return count;
	}

	int Sequence::getSameCount(const int value) const {
		int result = 0;
		for (int i = 0; i < this->size; i++)
			if (this->pNums[i] == value) result++;
		return result;
	}

	int Sequence::findBack(const int value) const {
		for (int i = this->size - 1; i >= 0; i--) if (this->pNums[i] == value) return i;
		return INT_MAX;
	}

	// operators
	bool Sequence::operator== (const Sequence& other) const {
		if (this->size != other.size) return false;
		for (int i = 0; i < this->size; i++)
			if (this->pNums[i] != other.pNums[i]) return false;
		return true;
	}
	bool Sequence::operator!= (const Sequence& other) const {
		return !(*this == other);
	}
	bool Sequence::operator> (const Sequence& other) const {
		return this->size > other.size;
	}
	bool Sequence::operator< (const Sequence& other) const {
		return this->size < other.size;
	}
	bool Sequence::operator>= (const Sequence& other) const {
		return this->size >= other.size;
	}
	bool Sequence::operator<= (const Sequence& other) const {
		return this->size <= other.size;
	}

	Sequence& Sequence::operator= (const Sequence& src) {
		this->size = src.size;
		memcpy(this->pNums, src.pNums, src.size * sizeof(int));
		return *this;
	}

	Sequence& Sequence::operator+ (const Sequence& other) const { 
		return this->plus(other);
	}
	Sequence& Sequence::operator+= (const Sequence& other) {
		(*this) = this->plus(other);
		return (*this);
	}

	Sequence& Sequence::operator- (const Sequence& other) const {
		return this->minus(other);
	}
	Sequence& Sequence::operator-= (const Sequence& other) {
		(*this) = this->minus(other);
		return (*this);
	}

	int Sequence::operator[] (const int id) const {	return this->getElement(id); }

	// friends
	std::ostream& operator<< (std::ostream& out, const Sequence& seq) {
		seq.output(out);
		return out;
	}
	std::istream& operator>> (std::istream& in, Sequence& seq) {
		seq.input(in);
		return in;
	}
}
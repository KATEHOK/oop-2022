#ifndef SEQUENCE_H
#include "sequence.h"
#endif

namespace sequence {

	Sequence::Sequence() {}
	Sequence::Sequence(const int item) {
		*this += item;
	}
	Sequence::Sequence(const int size, const int* pData) {
		if (pData == NULL)
			throw std::invalid_argument("pData == NULL in Sequence::Sequence()");
		for (int i = 0; i < size; i++) *this += pData[i];
	}
	Sequence::Sequence(const int* pData) {
		if (pData == NULL)
			throw std::invalid_argument("pData == NULL in Sequence::Sequence()");
		int i = 0;
		while (this->insert(pData[i]) == SUCCESS) i++;
	}

	int Sequence::getSize() const {
		return this->size;
	}
	int Sequence::getMaxSize() const {
		return this->maxSize;
	}
	int Sequence::getElement(const int id) const {
		if (id >= 0 && id < (*this)) return this->pNums[id];
		return INT_MAX;
	}

	Sequence& Sequence::makeClone() const {
		Sequence result(this->size, this->pNums);
		return result;
	}

	void Sequence::input(std::istream& in) {
		int value;

		while ((*this) < this->maxSize) { 
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
		for (int i = 0; i < (*this); i++) {
			out << (*this)[i];
			if (i < (*this) - 1) out << ", ";
		}
		out << "}";
	}
	
	Sequence& Sequence::plus(const Sequence& other) const {
		Sequence result = (*this);
		int i = 0;

		while (result < this->maxSize && i < other) {
			result += other[i];
			i++;
		}

		return result;
	}

	Sequence& Sequence::findMonotonicity(const int order) const {
		Sequence res;

		int last = (*this)[0];
		int startId = 0;

		for (int counter = 1; counter < (*this); counter++) {

			if ((*this)[counter] <= last && order == 0 || 
				(*this)[counter] >= last && order != 0) {
				// прерывание монотонности из 1 или 2 элементов (продолжаем)
				if (counter - startId <= 2) {
					last = (*this)[counter];
					startId = counter;
					continue;
				}
				// прерывание монотонности НЕ меньше, чем из трех элементов (завершаем)
				break;
			}
			// монотонность короче 3 элементов
			if (counter - startId < 2) {
				last = (*this)[counter];
				continue;
			}
			// найдена монотонность из 3 элементов
			if (counter - startId == 2) {
				res += (*this)[startId];
				res += (*this)[startId + 1];
			}
			// продолжение монотонности длинее 2 элементов
			last = (*this)[counter];
			res += (*this)[counter];
		}

		return res;
	}

	int Sequence::insert(const int value) {
		if ((*this) == this->maxSize) return OVERSIZE;
		if (value == INT_MAX) return WRONG_PARAMS;
		this->pNums[this->size] = value;
		this->size++;
		return SUCCESS;
	}

	int Sequence::getGroupsCount() const {
		if ((*this) == 0) return 0;
		int* pCash = new int[this->size];
		int count = 0, j;

		for (int i = 0; i < (*this); i++) {
			j = 0;
			for (j = 0; j < count; j++)
				if ((*this)[i] == pCash[j]) j = count;

			if (j == count + 1) continue;
			pCash[count] = (*this)[i];
			count++;
		}

		delete[] pCash;
		return count;
	}

	int Sequence::getSameCount(const int value) const {
		int result = 0;
		for (int i = 0; i < (*this); i++)
			if ((*this)[i] == value) result++;
		return result;
	}

	// operators

	bool Sequence::operator== (const Sequence& other) const {
		if (this->size != other.size) return false;
		for (int i = 0; i < this->size; i++)
			if ((*this)[i] != other[i]) return false;
		return true;
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

	bool Sequence::operator== (const int other) const {
		return this->size == other;
	}
	bool Sequence::operator> (const int other) const {
		return this->size > other;
	}
	bool Sequence::operator< (const int other) const {
		return this->size < other;
	}
	bool Sequence::operator>= (const int other) const {
		return this->size >= other;
	}
	bool Sequence::operator<= (const int other) const {
		return this->size <= other;
	}

	Sequence& Sequence::operator=(const Sequence& src) {
		this->size = src.size;
		memcpy(this->pNums, src.pNums, src * sizeof(int));
		return *this;
	}
	Sequence& Sequence::operator= (const int src) {
		Sequence res(src);
		return res;
	}
	Sequence& Sequence::operator= (const int* pSrc) {
		if (pSrc == NULL)
			throw std::invalid_argument("pSrc == NULL in Sequence::operator=");
		Sequence res(pSrc);
		return res;
	}

	Sequence& Sequence::operator+ (const Sequence& other) const { 
		return this->plus(other);
	}
	Sequence& Sequence::operator+ (const int value) const {
		return this->makeClone() += value;
	}
	Sequence& Sequence::operator+= (const int value) {
		this->insert(value);
		return *this;
	}

	int Sequence::operator[] (const int id) const {	return this->getElement(id); }

	int Sequence::operator- (const int other) const {
		return this->size - other;
	}
	int Sequence::operator* (const int other) const {
		return this->size * other;
	}
	int Sequence::operator/ (const int other) const {
		return this->size / other;
	}
	int Sequence::operator% (const int other) const {
		return this->size % other;
	}

	// friends

	bool operator== (const int other, const Sequence& cur) {
		return other == cur.size;
	}
	bool operator> (const int other, const Sequence& cur) {
		return other > cur.size;
	}
	bool operator< (const int other, const Sequence& cur) {
		return other < cur.size;
	}
	bool operator>= (const int other, const Sequence& cur) {
		return other >= cur.size;
	}
	bool operator<= (const int other, const Sequence& cur) {
		return other <= cur.size;
	}

	int operator- (const int other, const Sequence& cur) {
		return other - cur.size;
	}
	int operator* (const int other, const Sequence& cur) {
		return other * cur.size;
	}
	int operator/ (const int other, const Sequence& cur) {
		return other / cur.size;
	}
	int operator% (const int other, const Sequence& cur) {
		return other % cur.size;
	}
	int operator-= (int other, const Sequence& cur) {
		return other -= cur.size;
	}
	int operator*= (int other, const Sequence& cur) {
		return other *= cur.size;
	}
	int operator/= (int other, const Sequence& cur) {
		return other /= cur.size;
	}
	int operator%= (int other, const Sequence& cur) {
		return other %= cur.size;
	}

	std::ostream& operator<<(std::ostream& out, const Sequence& seq) {
		seq.output(out);
		return out;
	}
	std::istream& operator>>(std::istream& in, Sequence& seq) {
		seq.input(in);
		return in;
	}
}
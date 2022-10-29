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
		this->reinit(other.maxSize);
		this->size = other.size;
		if (this->pNums != nullptr) memcpy(this->pNums, other.pNums, other.size * sizeof(int));
	}
	Sequence::Sequence(Sequence&& other) noexcept {
		*this = std::move(other);
	}
	Sequence::~Sequence() {
		this->reinit(0);
	}

	int Sequence::getSize() const {
		return this->size;
	}
	int Sequence::getMaxSize() const {
		return this->maxSize;
	}

	void Sequence::input(std::istream& in) {
		int value;

		while (true) { 
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

	Sequence Sequence::findMonotonicity(const int order) const {
		Sequence res;
		if (this->size == 0) return res;

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
				res.insert(this->pNums[startId]);
				res.insert(this->pNums[startId + 1]);
			}
			// продолжение монотонности длинее 2 элементов
			last = this->pNums[counter];
			res.insert(this->pNums[counter]);
		}
		return res;
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

	int Sequence::insert(const int value) {
		if (value == INT_MAX) return WRONG_PARAMS;
		if (this->size == this->maxSize) this->addBlock();

		this->pNums[this->size] = value;
		this->size++;
		return SUCCESS;
	}
	int Sequence::remove(const int value) {
		int id = this->findBack(value);
		if (id == INT_MAX) return NOT_FOUND;

		for (int i = id; i < this->size - 1; i++) this->pNums[i] = this->pNums[i + 1];
		this->size--;

		if (this->maxSize - this->size >= this->BLOCK_SIZE) this->removeBlock();
		return SUCCESS;
	}

	Sequence& Sequence::plusEqual(const Sequence& other) {
		for (int i = 0; i < other.size; i++) if (this->insert(other.pNums[i]) != SUCCESS)
			throw std::invalid_argument("other is invalid in Sequence::plusEqual()");
		return *this;
	}
	Sequence& Sequence::minusEqual(const Sequence& other) {
		for (int i = 0; i < other.size; i++) this->remove(other.pNums[i]);
		return *this;
	}

	int Sequence::findBack(const int value) const {
		for (int i = this->size - 1; i >= 0; i--) if (this->pNums[i] == value) return i;
		return INT_MAX;
	}

	void Sequence::reinit(const int blockSize) {
		if (blockSize <= 0) {
			if (this->pNums != nullptr) delete[] this->pNums;
			this->pNums = nullptr;
			this->size = 0;
			this->maxSize = 0;
			return;
		}

		int minSize;
		int* pNew = new int[blockSize];

		blockSize < this->size ? minSize = blockSize : minSize = this->size;
		memcpy(pNew, this->pNums, minSize * sizeof(int));

		delete[] this->pNums;
		this->pNums = pNew;
		this->size = minSize;
		this->maxSize = blockSize;
	}
	void Sequence::addBlock() {
		this->reinit(this->maxSize + this->BLOCK_SIZE);
	}
	void Sequence::removeBlock() {
		this->reinit(this->maxSize - this->BLOCK_SIZE);
	}

	// operators
	bool Sequence::operator== (const Sequence& other) const {
		if (this->size != other.size) return false;
		for (int i = 0; i < this->size; i++)
			if (this->pNums[i] != other.pNums[i]) return false;
		return true;
	}
	bool Sequence::operator!= (const Sequence& other) const {
		if (this->size != other.size) return true;
		for (int i = 0; i < this->size; i++) if (this->pNums[i] != other.pNums[i]) return true;
		return false;
	}
	bool Sequence::operator> (const Sequence& other) const {
		return this->size > other.size;
	}
	bool Sequence::operator< (const Sequence& other) const {
		return this->size < other.size;
	}

	Sequence& Sequence::operator= (const Sequence& src) {
		this->reinit(src.maxSize);
		this->size = src.size;
		if (this->size > 0) memcpy(this->pNums, src.pNums, src.size * sizeof(int));

		std::cout << "Copy!" << std::endl;

		return *this;
	}
	Sequence& Sequence::operator= (Sequence&& src) noexcept {
		if (this != &src) {
			this->reinit(0);

			this->size = src.size;
			this->maxSize = src.maxSize;
			this->pNums = src.pNums;

			src.size = 0;
			src.maxSize = 0;
			src.pNums = nullptr;
		}

		std::cout << "Transfer!" << std::endl;

		return *this;
	}

	Sequence Sequence::operator+ (const Sequence& other) const {
		Sequence result(*this);
		result.plusEqual(other);
		return result;
	}
	Sequence& Sequence::operator+= (const Sequence& other) {
		this->plusEqual(other);
		return *this;
	}

	Sequence Sequence::operator- (const Sequence& other) const {
		Sequence result(*this);
		result.minusEqual(other);
		return result;
	}
	Sequence& Sequence::operator-= (const Sequence& other) {
		this->minusEqual(other);
		return *this;
	}

	int Sequence::operator[] (const int id) const {
		if (id >= 0 && id < this->size) return this->pNums[id];
		return INT_MAX;
	}

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
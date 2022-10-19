#pragma once

#define SEQUENCE_H

#ifndef APP

#include <iostream>
#include <limits>
#include <exception>

enum status {
	SUCCESS = 0,
	FAIL,
	OVERSIZE,
	MEMORY_ERROR,
	NOT_FOUND,
	WRONG_PARAMS,
};

#endif

namespace sequence {

	/*
	* INT_MAX - служебное значение
	*/
	class Sequence {

		// friends
		friend std::ostream& operator<<(std::ostream& out, const Sequence& seq);
		friend std::istream& operator>>(std::istream& in, Sequence& seq);

	public:

		Sequence();
		Sequence(const int item);
		Sequence(const int size, const int* pData);
		Sequence(const int* pData); // обязательно терминальное значение INT_MAX
		Sequence(const Sequence& other);
		~Sequence();

		int getSize() const;
		int getMaxSize() const;
		/*
		* В случае переполнения вернет INT_MAX
		*/
		int getElement(const int id) const;

		/*
		* Чтобы завершить ввод, необходимо ввести NaN
		*/
		void input(std::istream& in);
		void output(std::ostream& out) const;

		Sequence& plus(const Sequence& other) const;
		Sequence& minus(const Sequence& other) const;

		/*
		* Ищет монотонную подпоследовательность
		*/
		Sequence& findMonotonicity(const int order) const;

		int insert(const int value);
		int remove(const int value);

		/*
		* Считает количество групп
		*/
		int getGroupsCount() const;

		/*
		* Считает количество двойников для данного элемента
		*/
		int getSameCount(const int value) const;

		// operators
		bool operator== (const Sequence& other) const; // полное совпадение
		bool operator!= (const Sequence& other) const; // хотя бы частичное несовпадение
		bool operator> (const Sequence& other) const; // размер
		bool operator< (const Sequence& other) const; // размер

		Sequence& operator= (const Sequence& src);
		
		Sequence& operator+ (const Sequence& other) const;
		Sequence& operator+= (const Sequence& other);

		Sequence& operator- (const Sequence& other) const;
		Sequence& operator-= (const Sequence& other);

		int operator[] (const int id) const;

	private:

		const int BLOCK_SIZE = 10;
		int size = 0;
		int maxSize = 0;
		int* pNums = nullptr;

		/*
		* Ищет индекс последнего вхождения элемента
		*/
		int findBack(const int value) const;

		void realloc(const int blockSize = 0);
		void addBlock();
		void removeBlock();

	};
}

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

	// INT_MAX - служебное значение
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

		// Чтобы завершить ввод, необходимо ввести NaN
		void input(std::istream& in);
		void output(std::ostream& out) const;

		// Ищет монотонную подпоследовательность
		Sequence findMonotonicity(const int order) const;

		// Считает количество групп
		int getGroupsCount() const;

		// Считает количество двойников для данного элемента		
		int getSameCount(const int value) const;

		// operators
		bool operator== (const Sequence& other) const; // полное совпадение
		bool operator!= (const Sequence& other) const; // хотя бы частичное несовпадение
		bool operator> (const Sequence& other) const; // размер
		bool operator< (const Sequence& other) const; // размер

		Sequence& operator= (const Sequence& src);
		
		// работают, как объединение
		Sequence operator+ (const Sequence& other) const;
		Sequence& operator+= (const Sequence& other);

		// работают, как с множествами, только с конца
		Sequence operator- (const Sequence& other) const;
		Sequence& operator-= (const Sequence& other); 

		// В случае отсутствия вернет INT_MAX
		int operator[] (const int id) const;

	private:

		static const int BLOCK_SIZE = 10;
		int size = 0;
		int maxSize = 0;
		int* pNums = nullptr;

		int insert(const int value);
		int remove(const int value);

		Sequence& plusEqual(const Sequence& other);
		Sequence& minusEqual(const Sequence& other);

		// Ищет индекс последнего вхождения элемента
		int findBack(const int value) const;

		void reinit(const int blockSize = 0);
		void addBlock();
		void removeBlock();

	};
}

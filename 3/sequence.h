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
	const int MAX_SIZE = 100;

	/*
	* INT_MAX - служебное значение
	*/
	class Sequence {

		// friends
		friend bool operator== (const int other, const Sequence& cur);
		friend bool operator> (const int other, const Sequence& cur);
		friend bool operator< (const int other, const Sequence& cur);
		friend bool operator>= (const int other, const Sequence& cur);
		friend bool operator<= (const int other, const Sequence& cur);

		friend int operator- (const int other, const Sequence& cur);
		friend int operator-= (const int other, const Sequence& cur);
		friend int operator* (const int other, const Sequence& cur);
		friend int operator*= (const int other, const Sequence& cur);
		friend int operator/ (const int other, const Sequence& cur);
		friend int operator/= (const int other, const Sequence& cur);
		friend int operator% (const int other, const Sequence& cur);
		friend int operator%= (const int other, const Sequence& cur);

	public:

		Sequence();
		Sequence(const int item);
		Sequence(const int size, const int* pData);
		Sequence(const int* pData); // обязательно терминальное значение INT_MAX

		int getSize() const;
		int getMaxSize() const;
		/*
		* В случае переполнения вернет INT_MAX
		*/
		int getElement(const int id) const;
		/*
		* Клонирует экземпляр
		*/
		Sequence& makeClone() const;

		/*
		* Чтобы завершить ввод, необходимо ввести NaN
		*/
		void input();
		void output() const;

		Sequence& plus(const Sequence& other) const;

		/*
		* Ищет монотонную подпоследовательность
		*/
		Sequence& findMonotonicity(const int order) const;

		int insert(const int value);

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
		bool operator> (const Sequence& other) const; // размер
		bool operator< (const Sequence& other) const; // размер
		bool operator>= (const Sequence& other) const; // размер
		bool operator<= (const Sequence& other) const; // размер

		bool operator== (const int other) const; // размер
		bool operator> (const int other) const; // размер
		bool operator< (const int other) const; // размер
		bool operator>= (const int other) const; // размер
		bool operator<= (const int other) const; // размер

		Sequence& operator= (const Sequence& src);
		Sequence& operator= (const int src);
		Sequence& operator= (const int* pSrc); // обязательно терминальное значение INT_MAX
		
		Sequence& operator+ (const Sequence& other) const;
		Sequence& operator+ (const int value) const;
		Sequence& operator+= (const int value);

		int operator[] (const int id) const;

		int operator- (const int other) const;
		int operator* (const int other) const;
		int operator/ (const int other) const;
		int operator% (const int other) const;

	private:

		const int maxSize = MAX_SIZE;
		int pNums[MAX_SIZE];
		int size = 0;

	};
}

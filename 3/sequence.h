#pragma once

#define SEQUENCE_H

#ifndef MAX_SIZE
#define MAX_SIZE 100
#endif

#ifndef APP

#include <iostream>
#include <limits>

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

	public:

		Sequence();
		Sequence(const int item);
		Sequence(const int size, const int* pData);

		int getSize() const;
		int getMaxSize() const;
		/*
		* В случае переполнения вернет INT_MAX
		*/
		int getElement(const int id) const;
		Sequence* makeClone() const;

		/*
		* Not a number character is required after the last num
		*/
		void input();
		void output() const;

		Sequence* plus(const Sequence* pOther) const;

		Sequence* findMonotonicity(const int order) const;

		int insert(const int value);

		int getGroupsCount() const;

		int getSameCount(const int value) const;

	private:

		const int maxSize = MAX_SIZE;
		int pNums[MAX_SIZE];
		int size = 0;

	};

}

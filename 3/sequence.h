#pragma once

#define SEQUENCE_H

#ifndef MAX_SIZE
#define MAX_SIZE 100
#endif

#ifndef APP

#include <iostream>

enum status {
	SUCCESS = 0,
	FAIL,
	OVERSIZE,
	MEMORY_ERROR,
};

#endif

namespace sequence {

	class Sequence {

	public:

		Sequence();
		Sequence(const int item);
		Sequence(const int size, const int* pData);

		int getSize() const;
		int getMaxSize() const;
		int getElement(const int id) const;
		Sequence* makeClone() const;

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

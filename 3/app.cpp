﻿#ifndef APP
#include "app.h"
#endif

using namespace sequence;

int main() {

	/*
	const int count = 120;
	int data[count];
	for (int i = 0; i < count; i++) data[i] = i;
	*/

	/*
	Sequence f(count, data);
	std::cout << f.getSize() << std::endl << std::endl;
	for (int i = 0; i < count; i++)
		std::cout << f.getElement(i) << " " << i << std::endl;
	*/

	/*
	Sequence a;
	std::cout << "Enter integer nums via space: ";
	a.input();
	a.output();
	std::cout << std::endl << a.getSize();
	*/

	/*const int count = 100;
	int data[count] = { 777, 777, 0, 56, 45, 78, 120, 45, -989, 0, 1, 986,
						-89, -4562, -98651, 45, 45, 89, 456, 1236, 7889, 10000, 78953, 0 };*/

	/*Sequence bbb(3, data);
	Sequence* pBBB = bbb.findMonotonicity(0);
	Sequence* ppBBB = bbb.findMonotonicity(1);
	std::cout << pBBB->getSize() << ' ' << 0 << std::endl;
	std::cout << ppBBB->getSize() << ' ' << 0 << std::endl << std::endl;
	ppBBB->output();*/

	/*Sequence c(24, data);
	Sequence* pC = c.findMonotonicity(0);
	Sequence* ppC = c.findMonotonicity(1);
	std::cout << ppC->getSize() << ' ' << 3 << std::endl << std::endl;
	ppC->output();*/

	/*int* pCash = new int[2 * 2];
	for (int i = 1; i < 2 * 2; i += 2) pCash[i] = 0;
	for (int i = 0; i < 4; i++) std::cout << pCash[i] << std::endl;
	std::cout << std::endl;*/

	/*int data[6] = { 213, 213, 213, 0, 8, 213 };
	Sequence d(4, &(data[2]));
	std::cout << d.getGroupsCount() << ' ' << 3 << std::endl << std::endl;
	d.output();*/

	return SUCCESS;
}
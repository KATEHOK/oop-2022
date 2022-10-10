#ifndef APP
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


	const int count = 100;
	int data[count] = { 777, 777, 0, 56, 45, 78, 120, 45, -989, 0, 1, 986,
						-89, -4562, -98651, 45, 45, 89, 456, 1236, 7889, 10000, 78953, 0 };

	/*Sequence bbb(3, data);
	Sequence* pBBB = bbb.findMonotonicity(0);
	Sequence* ppBBB = bbb.findMonotonicity(1);
	std::cout << pBBB->getSize() << ' ' << 0 << std::endl;
	std::cout << ppBBB->getSize() << ' ' << 0 << std::endl << std::endl;
	ppBBB->output();*/
	//Assert::IsTrue(pBBB->getSize() == 0, L"bbb(0) (size)");
	//Assert::IsTrue(ppBBB->getSize() == 0, L"bbb(1) (size)");
	//Assert::IsTrue(pBBB->getElement(0) == INT_MAX, L"bbb(0) (pBBB[0])");
	//Assert::IsTrue(pBBB->getElement(1) == INT_MAX, L"bbb(0) (pBBB[1])");
	//Assert::IsTrue(ppBBB->getElement(0) == INT_MAX, L"bbb(1) (ppBBB[0])");
	//Assert::IsTrue(ppBBB->getElement(1) == INT_MAX, L"bbb(1) (ppBBB[1])");

	/*Sequence c(24, data);
	Sequence* pC = c.findMonotonicity(0);
	Sequence* ppC = c.findMonotonicity(1);
	std::cout << ppC->getSize() << ' ' << 3 << std::endl << std::endl;
	ppC->output();*/
	//Assert::IsTrue(pC->getSize() == 3, L"c(0) (size)");
	//Assert::IsTrue(ppC->getSize() == 3, L"c(1) (size)");
	//Assert::IsTrue(pC->getElement(0) == 45, L"c(0) (pC[0])");

	return SUCCESS;
}
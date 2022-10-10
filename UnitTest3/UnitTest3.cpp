#include "CppUnitTest.h"
#include "../3/sequence.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace sequence;

namespace UnitTest3
{
	TEST_CLASS(UnitTest3)
	{
	public:
		
		TEST_METHOD(Constructor_GetSize_GetMaxSize_GetElement_Insert)
		{
			Sequence a;
			Assert::IsTrue(a.getSize() == 0, L"Default");

			Sequence b(777);
			Assert::IsTrue(b.getSize() == 1, L"Single-size (777)");
			Assert::IsTrue(b.getElement(0) == 777, L"Single-element (777)");

			Sequence c(-985);
			Assert::IsTrue(c.getSize() == 1, L"Single-size (-985)");
			Assert::IsTrue(c.getElement(0) == -985, L"Single-element (-985)");

			const int count = 120;
			int data[count];
			for (int i = 0; i < count; i++) data[i] = i;

			Sequence d(100, data);
			Assert::IsTrue(d.getSize() == 100, L"100-size");
			for (int i = 0; i < 100; i++)
				Assert::IsTrue(d.getElement(i) == i, L"100 0..99");

			Sequence e(20, &(data[100]));
			Assert::IsTrue(e.getSize() == 20, L"20-size");
			for (int i = 100; i < count; i++)
				Assert::IsTrue(e.getElement(i - 100) == i, L"20 100..119");

			Sequence f(120, data);
			Assert::IsTrue(f.getSize() == 100, L"120-size");
			for (int i = 0; i < count; i++) {
				if (i < f.getSize()) Assert::IsTrue(f.getElement(i) == i, L"120 0..99");
				else Assert::IsTrue(f.getElement(i) == INT_MAX, L"120 0..99"); // код ошибки
			}
		}

		TEST_METHOD(MakeClone)
		{
			Sequence a;
			Sequence* pA = a.makeClone();
			Assert::IsTrue(pA->getSize() == 0, L"Default");

			Sequence b(777);
			Sequence* pB = b.makeClone();
			Assert::IsTrue(pB->getSize() == 1, L"Single-size (777)");
			Assert::IsTrue(pB->getElement(0) == 777, L"Single-element (777)");

			Sequence c(-985);
			Sequence* pC = c.makeClone();
			Assert::IsTrue(pC->getSize() == 1, L"Single-size (-985)");
			Assert::IsTrue(pC->getElement(0) == -985, L"Single-element (-985)");

			const int count = 120;
			int data[count];
			for (int i = 0; i < count; i++) data[i] = i;

			Sequence d(100, data);
			Sequence* pD = d.makeClone();
			Assert::IsTrue(pD->getSize() == 100, L"100-size");
			for (int i = 0; i < 100; i++)
				Assert::IsTrue(pD->getElement(i) == i, L"100 0..99");

			Sequence e(20, &(data[100]));
			Sequence* pE = e.makeClone();
			Assert::IsTrue(pE->getSize() == 20, L"20-size");
			for (int i = 100; i < count; i++)
				Assert::IsTrue(pE->getElement(i - 100) == i, L"20 100..119");

			Sequence f(120, data);
			Sequence* pF = f.makeClone();
			Assert::IsTrue(pF->getSize() == 100, L"120-size");
			for (int i = 0; i < count; i++) {
				if (i < pF->getSize()) Assert::IsTrue(pF->getElement(i) == i, L"120 0..99");
				else Assert::IsTrue(pF->getElement(i) == INT_MAX, L"120 0..99"); // код ошибки
			}
		}

		TEST_METHOD(Plus)
		{
			Sequence a;
			Sequence* pA = a.plus(&a);
			Assert::IsTrue(pA->getSize() == 0, L"a+a (size)");
			Assert::IsTrue(pA->getElement(0) == INT_MAX, L"a+a (pA[0])");
			Assert::IsTrue(pA->getElement(1) == INT_MAX, L"a+a (pA[1])");

			Sequence b(777);
			Sequence c(-985);
			Sequence* pB = b.plus(&c);
			Sequence* pC = c.plus(&b);
			Assert::IsTrue(pB->getSize() == 2, L"b+c (size");
			Assert::IsTrue(pB->getElement(0) == 777, L"b+c (777)");
			Assert::IsTrue(pB->getElement(1) == -985, L"b+c (-985)");
			Assert::IsTrue(pC->getSize() == 2, L"c+b (size");
			Assert::IsTrue(pC->getElement(0) == -985, L"c+b (-985)");
			Assert::IsTrue(pC->getElement(1) == 777, L"c+b (777)");

			Sequence* pAB = a.plus(&b);
			Sequence* pBA = b.plus(&a);
			Assert::IsTrue(pAB->getSize() == 1, L"a+b (size)");
			Assert::IsTrue(pAB->getElement(0) == 777, L"a+b (777)");
			Assert::IsTrue(pAB->getElement(1) == INT_MAX, L"a+b (pAB[1])");
			Assert::IsTrue(pBA->getSize() == 1, L"b+a (size");
			Assert::IsTrue(pBA->getElement(0) == 777, L"b+a (777)");
			Assert::IsTrue(pBA->getElement(1) == INT_MAX, L"b+a (pBA[1])");

			const int count = 100;
			int data[count];
			for (int i = 0; i < count; i++) data[i] = i;

			Sequence d(100, data);
			Sequence e(20, data);
			Sequence* pDE = d.plus(&e);
			Sequence* pED = e.plus(&d);
			Sequence* pEE = e.plus(&e);
			Assert::IsTrue(pDE->getSize() == 100, L"d+e (size)");
			Assert::IsTrue(pED->getSize() == 100, L"e+d (size)");
			Assert::IsTrue(pEE->getSize() == 40, L"e+e (size)");
			for (int i = 0; i < 200; i++) {
				if (i < pDE->getSize()) Assert::IsTrue(pDE->getElement(i) == i, L"d+e (0..99)");
				else Assert::IsTrue(pDE->getElement(i) == INT_MAX, L"d+e (pDE[i])");

				if (i < pED->getSize()) {
					if (i < 20) Assert::IsTrue(pED->getElement(i) == i, L"e+d (0..19)");
					else Assert::IsTrue(pED->getElement(i) == i - 20, L"e+d (20..99)");
				}
				else Assert::IsTrue(pED->getElement(i) == INT_MAX, L"e+d (pED[i])");

				if (i < 20) Assert::IsTrue(pEE->getElement(i) == i, L"e+e (pEE[0..19])");
				else if (i < 40) Assert::IsTrue(pEE->getElement(i) == i - 20, L"e+e (pEE[20..39])");
				else Assert::IsTrue(pEE->getElement(i) == INT_MAX, L"e+e (pEE[i])");
			}
		}

		TEST_METHOD(FindMonotonicity)
		{
			Sequence a;
			Sequence* pA = a.findMonotonicity(0);
			Sequence* ppA = a.findMonotonicity(1);
			Assert::IsTrue(pA->getSize() == 0, L"a(0) (size)");
			Assert::IsTrue(ppA->getSize() == 0, L"a(1) (size)");
			Assert::IsTrue(pA->getElement(0) == INT_MAX, L"a(0) (pA[0])");
			Assert::IsTrue(pA->getElement(1) == INT_MAX, L"a(0) (pA[1])");
			Assert::IsTrue(ppA->getElement(0) == INT_MAX, L"a(1) (ppA[0])");
			Assert::IsTrue(ppA->getElement(1) == INT_MAX, L"a(1) (ppA[1])");

			Sequence b(777);
			Sequence* pB = b.findMonotonicity(0);
			Sequence* ppB = b.findMonotonicity(1);
			Assert::IsTrue(pB->getSize() == 0, L"b(0) (size)");
			Assert::IsTrue(ppB->getSize() == 0, L"b(1) (size)");
			Assert::IsTrue(pB->getElement(0) == INT_MAX, L"b(0) (pB[0])");
			Assert::IsTrue(pB->getElement(1) == INT_MAX, L"b(0) (pB[1])");
			Assert::IsTrue(ppB->getElement(0) == INT_MAX, L"b(1) (ppB[0])");
			Assert::IsTrue(ppB->getElement(1) == INT_MAX, L"b(1) (ppB[1])");

			const int count = 100;
			int data[count] = { 777, 777, 0, 56, 45, 78, 120, 45, -989, 0, 1, 986,
								-89, -4562, -98651, 45, 45, 89, 456, 1236, 7889, 10000, 78953, 0};

			Sequence bb(2, data);
			Sequence* pBB = bb.findMonotonicity(0);
			Sequence* ppBB = bb.findMonotonicity(1);
			Assert::IsTrue(pBB->getSize() == 0, L"bb(0) (size)");
			Assert::IsTrue(ppBB->getSize() == 0, L"bb(1) (size)");
			Assert::IsTrue(pBB->getElement(0) == INT_MAX, L"bb(0) (pBB[0])");
			Assert::IsTrue(pBB->getElement(1) == INT_MAX, L"bb(0) (pBB[1])");
			Assert::IsTrue(ppBB->getElement(0) == INT_MAX, L"bb(1) (ppBB[0])");
			Assert::IsTrue(ppBB->getElement(1) == INT_MAX, L"bb(1) (ppBB[1])");

			Sequence bbb(3, data);
			Sequence* pBBB = bbb.findMonotonicity(0);
			Sequence* ppBBB = bbb.findMonotonicity(1);
			Assert::IsTrue(pBBB->getSize() == 0, L"bbb(0) (size)");
			Assert::IsTrue(ppBBB->getSize() == 0, L"bbb(1) (size)");
			Assert::IsTrue(pBBB->getElement(0) == INT_MAX, L"bbb(0) (pBBB[0])");
			Assert::IsTrue(pBBB->getElement(1) == INT_MAX, L"bbb(0) (pBBB[1])");
			Assert::IsTrue(ppBBB->getElement(0) == INT_MAX, L"bbb(1) (ppBBB[0])");
			Assert::IsTrue(ppBBB->getElement(1) == INT_MAX, L"bbb(1) (ppBBB[1])");

			// { 777, 777, 0, 56, 45, 78, 120, 45, -989, 0, 1, 986, -89, 
			// -4562, -98651, 45, 45, 89, 456, 1236, 7889, 10000, 78953, 0 };

			Sequence c(24, data);
			Sequence* pC = c.findMonotonicity(0);
			Sequence* ppC = c.findMonotonicity(1);
			Assert::IsTrue(pC->getSize() == 3, L"c(0) (size)");
			Assert::IsTrue(ppC->getSize() == 3, L"c(1) (size)");
			Assert::IsTrue(pC->getElement(0) == 45, L"c(0) (pC[0])");
			Assert::IsTrue(pC->getElement(1) == 78, L"c(0) (pC[1])");
			Assert::IsTrue(pC->getElement(2) == 120, L"c(0) (pC[2])");
			Assert::IsTrue(pC->getElement(3) == INT_MAX, L"c(0) (pC[3])");
			Assert::IsTrue(ppC->getElement(0) == 120, L"c(1) (ppC[0])");
			Assert::IsTrue(ppC->getElement(1) == 45, L"c(1) (ppC[1])");
			Assert::IsTrue(ppC->getElement(2) == -989, L"c(1) (ppC[2])");
			Assert::IsTrue(ppC->getElement(3) == INT_MAX, L"c(1) (ppC[3])");

			Sequence d(17, &(data[7]));
			Sequence* pD = d.findMonotonicity(0);
			Sequence* ppD = d.findMonotonicity(1);
			Assert::IsTrue(pD->getSize() == 4, L"d(0) (size)");
			Assert::IsTrue(ppD->getSize() == 4, L"d(1) (size)");
			Assert::IsTrue(pD->getElement(0) == -989, L"d(0) (pD[0])");
			Assert::IsTrue(pD->getElement(1) == 0, L"d(0) (pD[1])");
			Assert::IsTrue(pD->getElement(2) == 1, L"d(0) (pD[2])");
			Assert::IsTrue(pD->getElement(3) == 986, L"d(0) (pD[3])");
			Assert::IsTrue(pD->getElement(4) == INT_MAX, L"d(0) (pD[4])");
			Assert::IsTrue(ppD->getElement(0) == 986, L"d(1) (ppD[0])");
			Assert::IsTrue(ppD->getElement(1) == -89, L"d(1) (ppD[1])");
			Assert::IsTrue(ppD->getElement(2) == -4562, L"d(1) (ppD[2])");
			Assert::IsTrue(ppD->getElement(3) == -98651, L"d(1) (ppD[3])");
			Assert::IsTrue(ppD->getElement(4) == INT_MAX, L"d(1) (ppD[4])");
			
			int pArray[100];
			for (int i = 0; i < 100; i++) {
				if (i < 50) pArray[i] = i;
				else pArray[i] = 99 - i;
			}

			Sequence e(100, pArray);
			Sequence* pE = e.findMonotonicity(0);
			Sequence* ppE = e.findMonotonicity(1);
			Assert::IsTrue(pE->getSize() == 50, L"e(0) (size)");
			Assert::IsTrue(ppE->getSize() == 50, L"e(1) (size)");
			for (int i = 0; i < 100; i++) {

				if (i < 50) {
					Assert::IsTrue(pE->getElement(i) == i, L"e(0) (pE[0..49])");
					Assert::IsTrue(ppE->getElement(i) == 49 - i, L"e(1) (ppE[0..49])");
				}
				else {
					Assert::IsTrue(pE->getElement(i) == INT_MAX, L"e(0) (pE[i])");
					Assert::IsTrue(ppE->getElement(i) == INT_MAX, L"e(1) (ppE[i])");
				}
			}
		}
	};
}

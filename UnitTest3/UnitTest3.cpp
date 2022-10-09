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

		/*TEST_METHOD(MakeClone)
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
		}*/
	};
}

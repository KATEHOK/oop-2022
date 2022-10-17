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
			Sequence pa = a.makeClone();
			Assert::IsTrue(pa.getSize() == 0, L"Default");

			Sequence b(777);
			Sequence pb = b.makeClone();
			Assert::IsTrue(pb.getSize() == 1, L"Single-size (777)");
			Assert::IsTrue(pb.getElement(0) == 777, L"Single-element (777)");

			Sequence c(-985);
			Sequence pc = c.makeClone();
			Assert::IsTrue(pc.getSize() == 1, L"Single-size (-985)");
			Assert::IsTrue(pc.getElement(0) == -985, L"Single-element (-985)");

			const int count = 120;
			int data[count];
			for (int i = 0; i < count; i++) data[i] = i;

			Sequence d(100, data);
			Sequence pd = d.makeClone();
			Assert::IsTrue(pd.getSize() == 100, L"100-size");
			for (int i = 0; i < 100; i++)
				Assert::IsTrue(pd.getElement(i) == i, L"100 0..99");

			Sequence e(20, &(data[100]));
			Sequence pe = e.makeClone();
			Assert::IsTrue(pe.getSize() == 20, L"20-size");
			for (int i = 100; i < count; i++)
				Assert::IsTrue(pe.getElement(i - 100) == i, L"20 100..119");

			Sequence f(120, data);
			Sequence pf = f.makeClone();
			Assert::IsTrue(pf.getSize() == 100, L"120-size");
			for (int i = 0; i < count; i++) {
				if (i < pf.getSize()) Assert::IsTrue(pf.getElement(i) == i, L"120 0..99");
				else Assert::IsTrue(pf.getElement(i) == INT_MAX, L"120 0..99"); // код ошибки
			}
		}

		TEST_METHOD(Plus)
		{
			Sequence a;
			Sequence pa = a.plus(a);
			Assert::IsTrue(pa.getSize() == 0, L"a+a (size)");
			Assert::IsTrue(pa.getElement(0) == INT_MAX, L"a+a (pA[0])");
			Assert::IsTrue(pa.getElement(1) == INT_MAX, L"a+a (pA[1])");

			Sequence b(777);
			Sequence c(-985);
			Sequence pb = b.plus(c);
			Sequence pc = c.plus(b);
			Assert::IsTrue(pb.getSize() == 2, L"b+c (size");
			Assert::IsTrue(pb.getElement(0) == 777, L"b+c (777)");
			Assert::IsTrue(pb.getElement(1) == -985, L"b+c (-985)");
			Assert::IsTrue(pc.getSize() == 2, L"c+b (size");
			Assert::IsTrue(pc.getElement(0) == -985, L"c+b (-985)");
			Assert::IsTrue(pc.getElement(1) == 777, L"c+b (777)");

			Sequence pab = a.plus(b);
			Sequence pba = b.plus(a);
			Assert::IsTrue(pab.getSize() == 1, L"a+b (size)");
			Assert::IsTrue(pab.getElement(0) == 777, L"a+b (777)");
			Assert::IsTrue(pab.getElement(1) == INT_MAX, L"a+b (pAB[1])");
			Assert::IsTrue(pba.getSize() == 1, L"b+a (size");
			Assert::IsTrue(pba.getElement(0) == 777, L"b+a (777)");
			Assert::IsTrue(pba.getElement(1) == INT_MAX, L"b+a (pBA[1])");

			const int count = 100;
			int data[count];
			for (int i = 0; i < count; i++) data[i] = i;

			Sequence d(100, data);
			Sequence e(20, data);
			Sequence pde = d.plus(e);
			Sequence ped = e.plus(d);
			Sequence pee = e.plus(e);
			Assert::IsTrue(pde.getSize() == 100, L"d+e (size)");
			Assert::IsTrue(ped.getSize() == 100, L"e+d (size)");
			Assert::IsTrue(pee.getSize() == 40, L"e+e (size)");
			for (int i = 0; i < 200; i++) {
				if (i < pde.getSize()) Assert::IsTrue(pde.getElement(i) == i, L"d+e (0..99)");
				else Assert::IsTrue(pde.getElement(i) == INT_MAX, L"d+e (pDE[i])");

				if (i < ped.getSize()) {
					if (i < 20) Assert::IsTrue(ped.getElement(i) == i, L"e+d (0..19)");
					else Assert::IsTrue(ped.getElement(i) == i - 20, L"e+d (20..99)");
				}
				else Assert::IsTrue(ped.getElement(i) == INT_MAX, L"e+d (pED[i])");

				if (i < 20) Assert::IsTrue(pee.getElement(i) == i, L"e+e (pEE[0..19])");
				else if (i < 40) Assert::IsTrue(pee.getElement(i) == i - 20, L"e+e (pEE[20..39])");
				else Assert::IsTrue(pee.getElement(i) == INT_MAX, L"e+e (pEE[i])");
			}
		}

		TEST_METHOD(FindMonotonicity)
		{
			Sequence a;
			Sequence pa = a.findMonotonicity(0);
			Sequence ppa = a.findMonotonicity(1);
			Assert::IsTrue(pa.getSize() == 0, L"a(0) (size)");
			Assert::IsTrue(ppa.getSize() == 0, L"a(1) (size)");
			Assert::IsTrue(pa.getElement(0) == INT_MAX, L"a(0) (pA[0])");
			Assert::IsTrue(pa.getElement(1) == INT_MAX, L"a(0) (pA[1])");
			Assert::IsTrue(ppa.getElement(0) == INT_MAX, L"a(1) (ppA[0])");
			Assert::IsTrue(ppa.getElement(1) == INT_MAX, L"a(1) (ppA[1])");

			Sequence b(777);
			Sequence pb = b.findMonotonicity(0);
			Sequence ppb = b.findMonotonicity(1);
			Assert::IsTrue(pb.getSize() == 0, L"b(0) (size)");
			Assert::IsTrue(ppb.getSize() == 0, L"b(1) (size)");
			Assert::IsTrue(pb.getElement(0) == INT_MAX, L"b(0) (pB[0])");
			Assert::IsTrue(pb.getElement(1) == INT_MAX, L"b(0) (pB[1])");
			Assert::IsTrue(ppb.getElement(0) == INT_MAX, L"b(1) (ppB[0])");
			Assert::IsTrue(ppb.getElement(1) == INT_MAX, L"b(1) (ppB[1])");

			const int count = 100;
			int data[count] = { 777, 777, 0, 56, 45, 78, 120, 45, -989, 0, 1, 986,
								-89, -4562, -98651, 45, 45, 89, 456, 1236, 7889, 10000, 78953, 0};

			Sequence bb(2, data);
			Sequence pbb = bb.findMonotonicity(0);
			Sequence ppbb = bb.findMonotonicity(1);
			Assert::IsTrue(pbb.getSize() == 0, L"bb(0) (size)");
			Assert::IsTrue(ppbb.getSize() == 0, L"bb(1) (size)");
			Assert::IsTrue(pbb.getElement(0) == INT_MAX, L"bb(0) (pBB[0])");
			Assert::IsTrue(pbb.getElement(1) == INT_MAX, L"bb(0) (pBB[1])");
			Assert::IsTrue(ppbb.getElement(0) == INT_MAX, L"bb(1) (ppBB[0])");
			Assert::IsTrue(ppbb.getElement(1) == INT_MAX, L"bb(1) (ppBB[1])");

			Sequence bbb(3, data);
			Sequence pbbb = bbb.findMonotonicity(0);
			Sequence ppbbb = bbb.findMonotonicity(1);
			Assert::IsTrue(pbbb.getSize() == 0, L"bbb(0) (size)");
			Assert::IsTrue(ppbbb.getSize() == 0, L"bbb(1) (size)");
			Assert::IsTrue(pbbb.getElement(0) == INT_MAX, L"bbb(0) (pBBB[0])");
			Assert::IsTrue(pbbb.getElement(1) == INT_MAX, L"bbb(0) (pBBB[1])");
			Assert::IsTrue(ppbbb.getElement(0) == INT_MAX, L"bbb(1) (ppBBB[0])");
			Assert::IsTrue(ppbbb.getElement(1) == INT_MAX, L"bbb(1) (ppBBB[1])");

			// { 777, 777, 0, 56, 45, 78, 120, 45, -989, 0, 1, 986, -89, 
			// -4562, -98651, 45, 45, 89, 456, 1236, 7889, 10000, 78953, 0 };

			Sequence c(24, data);
			Sequence pc = c.findMonotonicity(0);
			Sequence ppc = c.findMonotonicity(1);
			Assert::IsTrue(pc.getSize() == 3, L"c(0) (size)");
			Assert::IsTrue(ppc.getSize() == 3, L"c(1) (size)");
			Assert::IsTrue(pc.getElement(0) == 45, L"c(0) (pC[0])");
			Assert::IsTrue(pc.getElement(1) == 78, L"c(0) (pC[1])");
			Assert::IsTrue(pc.getElement(2) == 120, L"c(0) (pC[2])");
			Assert::IsTrue(pc.getElement(3) == INT_MAX, L"c(0) (pC[3])");
			Assert::IsTrue(ppc.getElement(0) == 120, L"c(1) (ppC[0])");
			Assert::IsTrue(ppc.getElement(1) == 45, L"c(1) (ppC[1])");
			Assert::IsTrue(ppc.getElement(2) == -989, L"c(1) (ppC[2])");
			Assert::IsTrue(ppc.getElement(3) == INT_MAX, L"c(1) (ppC[3])");

			Sequence d(17, &(data[7]));
			Sequence pd = d.findMonotonicity(0);
			Sequence ppd = d.findMonotonicity(1);
			Assert::IsTrue(pd.getSize() == 4, L"d(0) (size)");
			Assert::IsTrue(ppd.getSize() == 4, L"d(1) (size)");
			Assert::IsTrue(pd.getElement(0) == -989, L"d(0) (pD[0])");
			Assert::IsTrue(pd.getElement(1) == 0, L"d(0) (pD[1])");
			Assert::IsTrue(pd.getElement(2) == 1, L"d(0) (pD[2])");
			Assert::IsTrue(pd.getElement(3) == 986, L"d(0) (pD[3])");
			Assert::IsTrue(pd.getElement(4) == INT_MAX, L"d(0) (pD[4])");
			Assert::IsTrue(ppd.getElement(0) == 986, L"d(1) (ppD[0])");
			Assert::IsTrue(ppd.getElement(1) == -89, L"d(1) (ppD[1])");
			Assert::IsTrue(ppd.getElement(2) == -4562, L"d(1) (ppD[2])");
			Assert::IsTrue(ppd.getElement(3) == -98651, L"d(1) (ppD[3])");
			Assert::IsTrue(ppd.getElement(4) == INT_MAX, L"d(1) (ppD[4])");
			
			int pArray[100];
			for (int i = 0; i < 100; i++) {
				if (i < 50) pArray[i] = i;
				else pArray[i] = 99 - i;
			}

			Sequence e(100, pArray);
			Sequence pe = e.findMonotonicity(0);
			Sequence ppe = e.findMonotonicity(1);
			Assert::IsTrue(pe.getSize() == 50, L"e(0) (size)");
			Assert::IsTrue(ppe.getSize() == 50, L"e(1) (size)");
			for (int i = 0; i < 100; i++) {

				if (i < 50) {
					Assert::IsTrue(pe.getElement(i) == i, L"e(0) (pE[0..49])");
					Assert::IsTrue(ppe.getElement(i) == 49 - i, L"e(1) (ppE[0..49])");
				}
				else {
					Assert::IsTrue(pe.getElement(i) == INT_MAX, L"e(0) (pE[i])");
					Assert::IsTrue(ppe.getElement(i) == INT_MAX, L"e(1) (ppE[i])");
				}
			}
		}

		TEST_METHOD(GetGroupsCount)
		{
			Sequence a;
			Assert::IsTrue(a.getGroupsCount() == 0, L"a");

			Sequence b(789);
			Assert::IsTrue(b.getGroupsCount() == 1, L"b");

			int data[6] = { 213, 213, 213, 0, 8, 213 };
			Sequence c(3, data);
			Assert::IsTrue(c.getGroupsCount() == 1, L"c");

			Sequence d(4, &(data[2]));
			Assert::IsTrue(d.getGroupsCount() == 3, L"d");
		}

		TEST_METHOD(GetSameCount)
		{
			Sequence a;
			Assert::IsTrue(a.getSameCount(78) == 0, L"a(78)");

			Sequence b(789);
			Assert::IsTrue(b.getSameCount(789) == 1, L"b(789)");
			Assert::IsTrue(b.getSameCount(78) == 0, L"b(78)");

			int data[6] = { 213, 213, 213, 0, 8, 213 };
			Sequence c(3, data);
			Assert::IsTrue(c.getSameCount(213) == 3, L"c(213)");
			Assert::IsTrue(c.getSameCount(-89) == 0, L"c(-89)");

			Sequence d(4, &(data[2]));
			Assert::IsTrue(d.getSameCount(213) == 2, L"d(213)");
			Assert::IsTrue(d.getSameCount(0) == 1, L"d(0)");
			Assert::IsTrue(d.getSameCount(8) == 1, L"d(8)");
			Assert::IsTrue(d.getSameCount(789) == 0, L"d(789)");
		}
	};
}

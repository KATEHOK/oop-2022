//#include "pch.h"
#include "CppUnitTest.h"

#ifndef APP
#define CLASS_ONLY
#include "../2/app.h"
#endif

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace strophoid;

bool isDoubleEqual(double a = 0.0, double b = 0.0) { return fabs(a - b) < 0.0005; }

namespace UnitTest2
{
	TEST_CLASS(UnitTest2)
	{
	public:

		TEST_METHOD(TestConstructor)
		{
			Strophoid line;
			Assert::IsTrue(line.getA() == 1.0, L"Default");

			Strophoid line1(10.0);
			Assert::IsTrue(line1.getA() == 10.0, L"10.0");

			Strophoid line2(999.0);
			Assert::IsTrue(isDoubleEqual(line2.getA(), 999.0), L"999.0");
		}
		TEST_METHOD(TestGetY)
		{
			Strophoid line(10.0);

			Assert::IsTrue(line.getY(-10.0) == 0.0, L"-10");

			Assert::IsTrue(line.getY(0.0) == 0.0, L"0");
		}
		TEST_METHOD(TestGetRadius)
		{
			Strophoid line(10.0);

			Assert::IsTrue(isDoubleEqual(line.getRadius(0.0), 0.0), L"0");

			Assert::IsTrue(isDoubleEqual(line.getRadius(30.0), 0.0), L"30");

			Assert::IsTrue(isDoubleEqual(line.getRadius(45.0), 0.0), L"45");

			Assert::IsTrue(isDoubleEqual(line.getRadius(60.0), 10.0), L"60");

			Assert::IsTrue(isDoubleEqual(line.getRadius(90.0), 0.0), L"90");

			Assert::IsTrue(isDoubleEqual(line.getRadius(120.0), 0.0), L"120");

			Assert::IsTrue(isDoubleEqual(line.getRadius(135.0), 0.0), L"135");

			Assert::IsTrue(isDoubleEqual(line.getRadius(180.0), 10.0), L"180");

			Assert::IsTrue(isDoubleEqual(line.getRadius(225.0), 0.0), L"225");

			Assert::IsTrue(isDoubleEqual(line.getRadius(240.0), 0.0), L"240");

			Assert::IsTrue(isDoubleEqual(line.getRadius(270.0), 0.0), L"270");

			Assert::IsTrue(isDoubleEqual(line.getRadius(300.0), 10.0), L"300");

			Assert::IsTrue(isDoubleEqual(line.getRadius(315.0), 0.0), L"315");

			Assert::IsTrue(isDoubleEqual(line.getRadius(330.0), 0.0), L"330");

			Assert::IsTrue(isDoubleEqual(line.getRadius(360.0), 0.0), L"360");

			Assert::IsTrue(isDoubleEqual(line.getRadius(390.0), 0.0), L"390");

			Assert::IsTrue(isDoubleEqual(line.getRadius(405.0), 0.0), L"405");

			Assert::IsTrue(isDoubleEqual(line.getRadius(420.0), 10.0), L"420");

			Assert::IsTrue(isDoubleEqual(line.getRadius(450.0), 0.0), L"450");

			Assert::IsTrue(isDoubleEqual(line.getRadius(480.0), 0.0), L"480");

			Assert::IsTrue(isDoubleEqual(line.getRadius(495.0), 0.0), L"495");

			Assert::IsTrue(isDoubleEqual(line.getRadius(540.0), 10.0), L"540");

			Assert::IsTrue(isDoubleEqual(line.getRadius(585.0), 0.0), L"585");

			Assert::IsTrue(isDoubleEqual(line.getRadius(600.0), 0.0), L"600");

			Assert::IsTrue(isDoubleEqual(line.getRadius(630.0), 0.0), L"630");

			Assert::IsTrue(isDoubleEqual(line.getRadius(660.0), 10.0), L"660");

			Assert::IsTrue(isDoubleEqual(line.getRadius(675.0), 0.0), L"675");

			Assert::IsTrue(isDoubleEqual(line.getRadius(690.0), 0.0), L"690");

			Assert::IsTrue(isDoubleEqual(line.getRadius(720.0), 0.0), L"720");

			Assert::IsTrue(isDoubleEqual(line.getRadius(-0.0), 0.0), L"-0");

			Assert::IsTrue(isDoubleEqual(line.getRadius(-30.0), 0.0), L"-30");

			Assert::IsTrue(isDoubleEqual(line.getRadius(-45.0), 0.0), L"-45");

			Assert::IsTrue(isDoubleEqual(line.getRadius(-60.0), 10.0), L"-60");

			Assert::IsTrue(isDoubleEqual(line.getRadius(-90.0), 0.0), L"-90");

			Assert::IsTrue(isDoubleEqual(line.getRadius(-120.0), 0.0), L"-120");

			Assert::IsTrue(isDoubleEqual(line.getRadius(-135.0), 0.0), L"-135");

			Assert::IsTrue(isDoubleEqual(line.getRadius(-180.0), 10.0), L"-180");

			Assert::IsTrue(isDoubleEqual(line.getRadius(-225.0), 0.0), L"-225");

			Assert::IsTrue(isDoubleEqual(line.getRadius(-240.0), 0.0), L"-240");

			Assert::IsTrue(isDoubleEqual(line.getRadius(-270.0), 0.0), L"-270");

			Assert::IsTrue(isDoubleEqual(line.getRadius(-300.0), 10.0), L"-300");

			Assert::IsTrue(isDoubleEqual(line.getRadius(-315.0), 0.0), L"-315");

			Assert::IsTrue(isDoubleEqual(line.getRadius(-330.0), 0.0), L"-330");

			Assert::IsTrue(isDoubleEqual(line.getRadius(-360.0), 0.0), L"-360");

			Assert::IsTrue(isDoubleEqual(line.getRadius(-390.0), 0.0), L"-390");

			Assert::IsTrue(isDoubleEqual(line.getRadius(-405.0), 0.0), L"-405");

			Assert::IsTrue(isDoubleEqual(line.getRadius(-420.0), 10.0), L"-420");

			Assert::IsTrue(isDoubleEqual(line.getRadius(-450.0), 0.0), L"-450");

			Assert::IsTrue(isDoubleEqual(line.getRadius(-480.0), 0.0), L"-480");

			Assert::IsTrue(isDoubleEqual(line.getRadius(-495.0), 0.0), L"-495");

			Assert::IsTrue(isDoubleEqual(line.getRadius(-540.0), 10.0), L"-540");

			Assert::IsTrue(isDoubleEqual(line.getRadius(-585.0), 0.0), L"-585");

			Assert::IsTrue(isDoubleEqual(line.getRadius(-600.0), 0.0), L"-600");

			Assert::IsTrue(isDoubleEqual(line.getRadius(-630.0), 0.0), L"-630");

			Assert::IsTrue(isDoubleEqual(line.getRadius(-660.0), 10.0), L"-660");

			Assert::IsTrue(isDoubleEqual(line.getRadius(-675.0), 0.0), L"-675");

			Assert::IsTrue(isDoubleEqual(line.getRadius(-690.0), 0.0), L"-690");

			Assert::IsTrue(isDoubleEqual(line.getRadius(-720.0), 0.0), L"-720");
		}
		TEST_METHOD(TestGetgetRadiusOfCurvature)
		{
			Strophoid line(10.0);
			Assert::IsTrue(isDoubleEqual(line.getRadiusOfCurvature(), 14.1421), L"10");

			Strophoid line1(1.0);
			Assert::IsTrue(isDoubleEqual(line1.getRadiusOfCurvature(), 1.41421), L"1");
		}
		TEST_METHOD(TestGetLoopArea)
		{
			Strophoid line(10.0);
			Assert::IsTrue(isDoubleEqual(line.getLoopArea(), 42.9204), L"10");

			Strophoid line1(1.0);
			Assert::IsTrue(isDoubleEqual(line1.getLoopArea(), 0.429204), L"1");
		}
		TEST_METHOD(TestGetLoopVolume)
		{
			Strophoid line(10.0);
			Assert::IsTrue(isDoubleEqual(line.getLoopVolume(), 1213.58), L"10");

			Strophoid line1(1.0);
			Assert::IsTrue(isDoubleEqual(line1.getLoopVolume(), 1.21358), L"1");
		}
		TEST_METHOD(TestGetMiddleBranchesArea)
		{
			Strophoid line(10.0);
			Assert::IsTrue(isDoubleEqual(line.getMiddleBranchesArea(), 357.08), L"10");

			Strophoid line1(1.0);
			Assert::IsTrue(isDoubleEqual(line1.getMiddleBranchesArea(), 3.5708), L"1");
		}
	};
}

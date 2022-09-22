#include "pch.h"
#include "CppUnitTest.h"
#include "../2/app.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{
	TEST_CLASS(UnitTest2)
	{
	public:
		
		TEST_METHOD(TestMethod)
		{
			strophoid::Strophoid line(10.0);
			Assert::IsTrue(line.getA() == 10.0, L"getA");

			Assert::IsTrue(line.getY(-10.0) == 0.0, L"getY(-10)");

			Assert::IsTrue(line.getY(0.0) == 0.0, L"getY(0)");

			Assert::IsTrue(line.getRadius(0.0) == 0.0, L"getRadius(0)");

			Assert::IsTrue(line.getRadius(30.0) == 0.0, L"getRadius(30)");

			Assert::IsTrue(line.getRadius(45.0) == 0.0, L"getRadius(45)");

			Assert::IsTrue(line.getRadius(60.0) == 10.0, L"getRadius(60)");

			Assert::IsTrue(line.getRadius(90.0) == 0.0, L"getRadius(90)");

			Assert::IsTrue(line.getRadius(120.0) == 0.0, L"getRadius(120)");

			Assert::IsTrue(line.getRadius(135.0) == 0.0, L"getRadius(135)");

			Assert::IsTrue(line.getRadius(180.0) == 10.0, L"getRadius(180)");

			Assert::IsTrue(line.getRadius(225.0) == 0.0, L"getRadius(225)");

			Assert::IsTrue(line.getRadius(240.0) == 0.0, L"getRadius(240)");

			Assert::IsTrue(line.getRadius(270.0) == 0.0, L"getRadius(270)");

			Assert::IsTrue(line.getRadius(300.0) == 10.0, L"getRadius(300)");

			Assert::IsTrue(line.getRadius(315.0) == 0.0, L"getRadius(315)");

			Assert::IsTrue(line.getRadius(330.0) == 0.0, L"getRadius(330)");
		}
	};
}

#include "CppUnitTest.h"
#include "../../4/src/department.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace department;

namespace departmenttests
{
	TEST_CLASS(departmenttests)
	{
	public:
		
		TEST_METHOD(department_constructor_and_getters)
		{
			// Default
			Department d1;
			Assert::IsTrue(d1.id() == 0 && d1.name() == "", L"Default");
			Department d2[3];
			for (auto i : d2) Assert::IsTrue(i.id() == 0 && i.name() == "", L"Default array");

			// Fields values
			int id = 777;
			std::string name = "icis";
			Department d3(id, name);
			Assert::IsTrue(d3.id() == id && d3.name() == name, L"Fields values");

			// Copy
			Department d4(d1);
			Assert::IsTrue(d4.id() == 0 && d4.name() == "", L"Copy-1");
			Department d5(d3);
			Assert::IsTrue(d5.id() == id && d5.name() == name, L"Copy-2");

			// Transfer
			/*Department d4(d1);
			Assert::IsTrue(d4.id() == 0 && d4.name() == "", L"Transfer-1");
			Department d5(d3);
			Assert::IsTrue(d5.id() == id && d5.name() == name, L"Transfer-2");*/
		}

		TEST_METHOD(department_operators)
		{
			int id = 777;
			std::string name = "icis";
			Department d1;
			Department d2(id, name);

			// =
			Department d3 = d1;
			Department d4 = d2;
			Assert::IsTrue(d3.id() == 0 && d3.name() == "",		L"= - 1");
			Assert::IsTrue(d4.id() == id && d4.name() == name,	L"= - 2");

			// ==
			Department d5(0, name), d6(id, "");
			Assert::IsTrue(d1 == d3, L"== - 1");
			Assert::IsTrue(d1 == d5, L"== - 2");
			Assert::IsTrue(d1 == d6, L"== - 3");
			Assert::IsTrue(d5 == d4, L"== - 4");
			Assert::IsTrue(d6 == d4, L"== - 5");
			Assert::IsTrue(d2 == d4, L"== - 6");

			// !=
			Assert::IsTrue(d1 != d2, L"!= - 1");
			Assert::IsTrue(d5 != d6, L"!= - 2");
			Assert::IsTrue(d3 != d4, L"!= - 3");
		}

		TEST_METHOD(departments_table_constructor_and_getters_and_operators)
		{
			// Default
			DepartmentsTable dt1;
			Assert::IsTrue(dt1.size() == 0, L"Default");
			DepartmentsTable dt2[3];
			for (auto i : dt2) Assert::IsTrue(i.size() == 0, L"Default array");

			int id = 777;
			std::string name = "icis";
			Department d1, d2(id, name);

			// By department
			DepartmentsTable dt3(d1), dt4(d2);
			Assert::IsTrue(dt3.size() == 1 && dt4.size() == 1,	L"By department - size");
			Assert::IsTrue(dt3[0] == d1 && dt4[id] == d2,		L"By department - item by id");
			Assert::IsTrue(dt3[""] == d1 && dt4[name] == d2,	L"By department - item by name");

			// Copy
			DepartmentsTable dt5(dt3), dt6(dt4);
			Assert::IsTrue(dt5.size() == 1 && dt6.size() == 1,	L"Copy - size");
			Assert::IsTrue(dt5[0] == d1 && dt6[id] == d2,		L"Copy - item by id");
			Assert::IsTrue(dt5[""] == d1 && dt6[name] == d2,	L"Copy - item by name");

			// =
			DepartmentsTable dt7 = dt3, dt8 = dt4;
			Assert::IsTrue(dt7.size() == 1 && dt8.size() == 1,	L"= - size");
			Assert::IsTrue(dt7[0] == d1 && dt8[id] == d2,		L"= - item by id");
			Assert::IsTrue(dt7[""] == d1 && dt8[name] == d2,	L"= - item by name");

			// Transfer
			/*Department d4(d1);
			Assert::IsTrue(d4.id() == 0 && d4.name() == "", L"Transfer-1");
			Department d5(d3);
			Assert::IsTrue(d5.id() == id && d5.name() == name, L"Transfer-2");*/
		}

		TEST_METHOD(departments_table_funcs)
		{
			int id = 777;
			std::string name = "icis";
			Department d1, d2(id, name);

			// push_back
			DepartmentsTable dt1, dt2;
			for (int i = 0; i < 10; ++i) {
				dt1.push_back(d1);
				dt1.push_back(d2);
				dt2.push_back(d2);
				dt2.push_back(d1);
			}
			Assert::IsTrue(dt1.size() == 2 && dt2.size() == 2,	L"push_back - size");
			Assert::IsTrue(dt1[0] == d1 && dt1[id] == d2,		L"push_back - dt1 with id");
			Assert::IsTrue(dt1[""] == d1 && dt1[name] == d2,	L"push_back - dt1 with name");
			Assert::IsTrue(dt2[0] == d1 && dt2[id] == d2,		L"push_back - dt2 with id");
			Assert::IsTrue(dt2[""] == d1 && dt2[name] == d2,	L"push_back - dt2 with name");

			// find
			Assert::IsTrue(dt1.find(0) == 0 && dt2.find(0) == 1,			L"find - d1 by id");
			Assert::IsTrue(dt1.find(id) == 1 && dt2.find(id) == 0,			L"find - d2 by id");
			Assert::IsTrue(dt1.find("") == 0 && dt2.find("") == 1,			L"find - d1 by name");
			Assert::IsTrue(dt1.find(name) == 1 && dt2.find(name) == 0,		L"find - d2 by name");
			Assert::IsTrue(dt1.find(d1) == 0 && dt2.find(d1) == 1,			L"find - by d1");
			Assert::IsTrue(dt1.find(d2) == 1 && dt2.find(d2) == 0,			L"find - by d2");
			Assert::IsTrue(dt1.find(1) == -1 && dt2.find(1) == -1,			L"find - d1 by fake id");
			Assert::IsTrue(dt1.find("name") == -1 && dt2.find("name") == -1,L"find - d2 by fake name");

			// erase
			dt1.erase(1);
			dt2.erase(1);
			dt1.erase("name");
			dt2.erase("name");
			Assert::IsTrue(dt1.size() == 2 && dt2.size() == 2, L"erase - fake id");
			Assert::IsTrue(dt1.size() == 2 && dt2.size() == 2, L"erase - fake name");
			dt1.erase(0);
			dt2.erase("");
			Assert::IsTrue(dt1.size() == 1, L"erase - real 0");
			Assert::IsTrue(dt2.size() == 1, L"erase - real \"\"");
			dt1.erase(id);
			dt2.erase(name);
			Assert::IsTrue(dt1.size() == 0, L"erase - real id");
			Assert::IsTrue(dt2.size() == 0, L"erase - real name");
			dt1.erase(id);
			dt2.erase(name);
			Assert::IsTrue(dt1.size() == 0 && dt2.size() == 0, L"erase - from free");

		}
	};
}

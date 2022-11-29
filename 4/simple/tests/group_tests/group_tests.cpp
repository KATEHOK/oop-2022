#include "../../4/src/group.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace group;

namespace grouptests
{
	TEST_CLASS(grouptests)
	{
	public:
		
		TEST_METHOD(group)
		{

			// Default
			Group g1, g2[10];
			Assert::IsTrue(g1.id() == 0 && g1.size() == 0 && g1.study_duration() == 0 && g1.department_id() == 0, L"Default");
			for (auto i : g2) Assert::IsTrue(
				i.id() == 0 &&
				i.size() == 0 &&
				i.study_duration() == 0 &&
				i.department_id() == 0, L"Default");

			// By fields values
			int id = 777, size = 777, study_duration = 777, department_id = 777;
			Group g3(id, size, department_id, study_duration);
			Assert::IsTrue(
				g3.id() == id &&
				g3.size() == size &&
				g3.study_duration() == study_duration &&
				g3.department_id() == department_id, L"By fields values");

			// size - setter
			Assert::IsTrue(g1.size(size) == size, L"size - setter");
		}
	};
}

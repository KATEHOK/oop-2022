#include "../../4/src/groups_table.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace group;

namespace groupstabletests
{
	TEST_CLASS(groupstabletests)
	{
	public:
		
		TEST_METHOD(groups_table_item_constuctors_getters)
		{

			// Default
			GroupsTableItem gti1, gti2[10];
			Assert::IsTrue(gti1.group_id() == 0 && gti1.group_ptr() == nullptr, L"Default");
			for (auto i : gti2)	Assert::IsTrue(i.group_id() == 0 && i.group_ptr() == nullptr, L"Default array");

			int id = 1, size = 1, department_id = 1, study_duration = 1, fellows_amount = 1;
			float stipend = 1;
			std::string specialization = "Cyber security engineer";
			DayGroup
				*pG1 = new DayGroup,
				*pG2 = new DayGroup(id, size, department_id, study_duration, specialization, stipend, fellows_amount);
			std::shared_ptr<DayGroup> spG1(pG1), spG2(pG2);

			// By fields values
			GroupsTableItem
				//gti3(0, pG1), // err
				//gti4(id, pG2), // err
				gti5(0, spG1),
				gti6(id, spG2);
			Assert::IsTrue(
			//	gti3.group_id() == 0 && gti3.group_ptr() == spG1 &&
			//	gti4.group_id() == id && gti4.group_ptr() == spG2 &&
				gti5.group_id() == 0 && gti5.group_ptr() == spG1 &&
				gti6.group_id() == id && gti6.group_ptr() == spG2,	L"By fields values");

			// By group - err
			/*GroupsTableItem	gti7(*pG1), gti8(*pG2);
			Assert::IsTrue(
				gti7.group_id() == 0 && gti7.group_ptr() == spG1 &&
				gti8.group_id() == id && gti8.group_ptr() == spG2,	L"By group");*/

			// Copy
			GroupsTableItem	gti9(gti5), gti10(gti6);
			Assert::IsTrue(
				gti9.group_id() == 0 && gti9.group_ptr() == spG1 &&
				gti10.group_id() == id && gti10.group_ptr() == spG2, L"Copy");

		}
	};
}

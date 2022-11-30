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
				gti5(0, spG1),
				gti6(id, spG2);
			Assert::IsTrue(
				gti5.group_id() == 0 && gti5.group_ptr() == spG1 &&
				gti6.group_id() == id && gti6.group_ptr() == spG2,	L"By fields values");

			// By group
			DayGroup
				*pG3 = new DayGroup,
				*pG4 = new DayGroup(id, size, department_id, study_duration, specialization, stipend, fellows_amount);
			GroupsTableItem	gti7(*pG3), gti8(*pG4);
			Assert::IsTrue(
				gti7.group_id() == 0 && gti7.group_ptr().get() == pG3 &&
				gti8.group_id() == id && gti8.group_ptr().get() == pG4, L"By group");

			// Copy
			GroupsTableItem	gti9(gti5), gti10(gti6);
			Assert::IsTrue(
				gti9.group_id() == 0 && gti9.group_ptr() == spG1 &&
				gti10.group_id() == id && gti10.group_ptr() == spG2, L"Copy");

		}

		TEST_METHOD(groups_table_item_operators)
		{

			int id = 1, size = 1, department_id = 1, study_duration = 1, fellows_amount = 1;
			float stipend = 1;
			std::string specialization = "Cyber security engineer";
			std::shared_ptr<DayGroup>
				spG1(new DayGroup),
				spG2(new DayGroup(id, size, department_id, study_duration, specialization, stipend, fellows_amount));
			GroupsTableItem
				gti1(0, spG1),
				gti2(id, spG2);

			// =
			GroupsTableItem	gti3 = gti1, gti4 = gti2;
			Assert::IsTrue(
				gti3.group_id() == 0 && gti3.group_ptr() == spG1 &&
				gti4.group_id() == id && gti4.group_ptr() == spG2, L"=");

			// ==
			Assert::IsTrue(
				gti3 == 0 && gti3 == spG1 &&
				gti4 == id && gti4 == spG2, L"==");

			// !=
			Assert::IsTrue(
				gti3 != id && gti3 != spG2 &&
				gti4 != 0 && gti4 != spG1, L"!=");

		}

		TEST_METHOD(groups_table_constructors_size)
		{

			// Default
			GroupsTable gt1, gt2[10];
			Assert::IsTrue(gt1.size() == 0, L"Default");
			for (auto i : gt2)	Assert::IsTrue(i.size() == 0, L"Default array");

			int id = 1, size = 1, department_id = 1, study_duration = 1, fellows_amount = 1;
			float stipend = 1;
			std::string specialization = "Cyber security engineer";
			std::shared_ptr<DayGroup>
				spG1(new DayGroup),
				spG2(new DayGroup(id, size, department_id, study_duration, specialization, stipend, fellows_amount));
			GroupsTableItem
				gti1(0, spG1),
				gti2(id, spG2);

			// By groups fields values
			GroupsTable
				gt3(0, std::shared_ptr<DayGroup>(new DayGroup)),
				gt4(0, std::shared_ptr<DayGroup>(new DayGroup(
					id, size, department_id,
					study_duration, specialization,
					stipend, fellows_amount)));
			Assert::IsTrue(gt3.size() == 1 && gt4.size() == 1, L"By item fields values");

			// By group
			GroupsTable
				gt5(*(new DayGroup)),
				gt6(*(new DayGroup(
					id, size, department_id,
					study_duration, specialization,
					stipend, fellows_amount)));
			Assert::IsTrue(gt5.size() == 1 && gt6.size() == 1, L"By group");

			// By item
			GroupsTable gt7(gti1), gt8(gti2);
			Assert::IsTrue(gt7.size() == 1 && gt8.size() == 1, L"By item");

			// Copy
			GroupsTable gt9(gt7), gt10(gt8);
			Assert::IsTrue(gt9.size() == 1 && gt10.size() == 1, L"Copy");

		}

		TEST_METHOD(groups_table_other)
		{

			int id = 1, size = 1, department_id = 1, study_duration = 1, fellows_amount = 1;
			float stipend = 1;
			std::string specialization = "Cyber security engineer";
			std::shared_ptr<DayGroup>
				spG1(new DayGroup),
				spG2(new DayGroup(id, size, department_id, study_duration, specialization, stipend, fellows_amount));
			GroupsTableItem
				gti1(0, spG1),
				gti2(id, spG2);
			GroupsTable gt1(gti1), gt2(gti2);

			// =
			GroupsTable gt3 = gt1, gt4 = gt2;
			Assert::IsTrue(gt3.size() == 1 && gt4.size() == 1, L"=");

			// insert by group
			gt3.insert(*(new DayGroup));
			gt4.insert(*(new DayGroup(
				id, size, department_id,
				study_duration, specialization,
				stipend, fellows_amount)));
			Assert::IsTrue(gt3.size() == 1 && gt4.size() == 1, L"insert by group - already exist");
			gt3.insert(*(new DayGroup(
				id, size, department_id,
				study_duration, specialization,
				stipend, fellows_amount)));
			gt4.insert(*(new DayGroup));
			Assert::IsTrue(gt3.size() == 2 && gt4.size() == 2, L"insert by group - unique");

			// insert by item
			gt1.insert(gti1);
			gt2.insert(gti2);
			Assert::IsTrue(gt1.size() == 1 && gt2.size() == 1, L"insert by item - already exist");
			gt1.insert(gti2);
			gt2.insert(gti1);
			Assert::IsTrue(gt1.size() == 2 && gt2.size() == 2, L"insert by item - unique");

			// insert by groups fields values
			gt1.insert(0, spG1);
			gt2.insert(id, spG2);
			Assert::IsTrue(gt1.size() == 2 && gt2.size() == 2, L"insert by groups fields values - already exist");
			gt1.insert(7, std::shared_ptr<DayGroup>(
				new DayGroup(7, size, department_id, study_duration, specialization, stipend, fellows_amount)));
			DayGroup* pg = new DayGroup(7, size, department_id, study_duration, specialization, stipend, fellows_amount);
			gt2.insert(7, std::shared_ptr<DayGroup>(pg));
			Assert::IsTrue(gt1.size() == 3 && gt2.size() == 3, L"insert by groups fields values - unique");

			// find - was tested with insert

			// erase
			DayGroup g;
			gt1.erase(9);
			gt2.erase(&g);
			Assert::IsTrue(gt1.size() == 3 && gt2.size() == 3, L"erase - fake arguments");
			gt1.erase(7);
			gt2.erase(pg);
			Assert::IsTrue(gt1.size() == 2 && gt2.size() == 2, L"erase - real arguments");

			// []
			Assert::IsTrue(
				gt1[0].group_id() == 0 &&
				gt1[0].group_ptr() == spG1 &&
				gt1[spG1].group_id() == 0 &&
				gt1[spG1].group_ptr() == spG1 &&
				gt1[id].group_id() == id &&
				gt1[id].group_ptr() == spG2 &&
				gt1[spG2].group_id() == id &&
				gt1[spG2].group_ptr() == spG2, L"[]"
			);
		}
	};
}

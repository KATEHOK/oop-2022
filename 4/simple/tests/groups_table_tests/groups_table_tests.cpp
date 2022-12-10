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
			GroupsTable gt3 = std::move(gt1), gt4 = std::move(gt2);
			Assert::IsTrue(gt3.size() == 1 && gt4.size() == 1, L"=");

			// insert by group
			DayGroup* p1 = new DayGroup;
			DayGroup* p2 = new DayGroup(
				id, size, department_id,
				study_duration, specialization,
				stipend, fellows_amount);
			DayGroup* p3 = new DayGroup(
				id, size, department_id,
				study_duration, specialization,
				stipend, fellows_amount);
			DayGroup* p4 = new DayGroup;
			gt3.insert(*p1);
			gt4.insert(*p2);
			Assert::IsTrue(gt3.size() == 1 && gt4.size() == 1, L"insert by group - already exist");
			gt3.insert(*p3);
			gt4.insert(*p4);
			Assert::IsTrue(gt3.size() == 2 && gt4.size() == 2, L"insert by group - unique");

			GroupsTableItem gti3(*(new DayGroup));
			GroupsTableItem gti4(*(new DayGroup));
			GroupsTableItem gti5(*(new DayGroup(
				id, size, department_id,
				study_duration, specialization,
				stipend, fellows_amount
			)));
			GroupsTableItem gti6(*(new DayGroup(
				id, size, department_id,
				study_duration, specialization,
				stipend, fellows_amount
			)));
			GroupsTable gt5(gti3);
			GroupsTable gt6(gti5);

			// insert by item
			gt5.insert(gti4);
			gt6.insert(gti6);
			Assert::IsTrue(gt5.size() == 1 && gt6.size() == 1, L"insert by item - already exist");
			gt5.insert(gti6);
			gt6.insert(gti4);
			Assert::IsTrue(gt5.size() == 2 && gt6.size() == 2, L"insert by item - unique");

			// insert by groups fields values
			gt5.insert(0, spG1);
			gt6.insert(id, spG2);
			Assert::IsTrue(gt5.size() == 2 && gt6.size() == 2, L"insert by groups fields values - already exist");
			gt5.insert(7, std::shared_ptr<DayGroup>(
				new DayGroup(7, size, department_id, study_duration, specialization, stipend, fellows_amount)));
			DayGroup* pg = new DayGroup(7, size, department_id, study_duration, specialization, stipend, fellows_amount);
			gt6.insert(7, std::shared_ptr<DayGroup>(pg));
			Assert::IsTrue(gt5.size() == 3 && gt6.size() == 3, L"insert by groups fields values - unique");

			// find - was tested with insert

			// []
			Assert::IsTrue(
				gt6[0].group_id() == 0 &&
				gt6[7].group_ptr().get() == pg &&
				gt6[pg].group_id() == 7 &&
				gt6[pg].group_ptr().get() == pg, L"[]"
			);

			// erase
			DayGroup g;
			gt5.erase(9);
			gt6.erase(&g);
			Assert::IsTrue(gt5.size() == 3 && gt6.size() == 3, L"erase - fake arguments");
			gt5.erase(7);
			gt6.erase(pg);
			Assert::IsTrue(gt5.size() == 2 && gt6.size() == 2, L"erase - real arguments");
		}
	};
}

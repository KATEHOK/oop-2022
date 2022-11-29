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
				i.department_id() == 0, L"Default array");

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

		TEST_METHOD(day_group)
		{

			// Default
			DayGroup g1, g2[10];
			Assert::IsTrue(
				g1.id() == 0 && 
				g1.size() == 0 && 
				g1.study_duration() == 0 && 
				g1.department_id() == 0 &&
				g1.specialization() == "" &&
				g1.stipend() == 0 &&
				g1.fellows_amount() == 0, L"Default");
			for (auto i : g2) Assert::IsTrue(
				i.id() == 0 &&
				i.size() == 0 &&
				i.study_duration() == 0 &&
				i.department_id() == 0 &&
				i.specialization() == "" &&
				i.stipend() == 0 &&
				i.fellows_amount() == 0, L"Default array");

			// By fields values
			int id = 777, size = 777, study_duration = 777, department_id = 777, fellows_amount = 777;
			float stipend = 777;
			std::string specialization = "Cyber security engineer";
			DayGroup g3(id, size, department_id, study_duration, specialization, stipend, fellows_amount);
			Assert::IsTrue(
				g3.id() == id &&
				g3.size() == size &&
				g3.study_duration() == study_duration &&
				g3.department_id() == department_id &&
				g3.specialization() == specialization &&
				g3.stipend() == stipend &&
				g3.fellows_amount() == fellows_amount, L"By fields values");

			// Copy
			DayGroup g4(g3);
			Assert::IsTrue(
				g4.id() == id &&
				g4.size() == size &&
				g4.study_duration() == study_duration &&
				g4.department_id() == department_id &&
				g4.specialization() == specialization &&
				g4.stipend() == stipend &&
				g4.fellows_amount() == fellows_amount, L"Copy");

			// =
			DayGroup g5 = g4;
			Assert::IsTrue(
				g5.id() == id &&
				g5.size() == size &&
				g5.study_duration() == study_duration &&
				g5.department_id() == department_id &&
				g5.specialization() == specialization &&
				g5.stipend() == stipend &&
				g5.fellows_amount() == fellows_amount, L"=");

			// setters
			Assert::IsTrue(g1.stipend(stipend) == stipend &&
				g1.fellows_amount(fellows_amount) == fellows_amount, L"setters");
		}

		TEST_METHOD(evening_group)
		{

			// Default
			EveningGroup g1, g2[10];
			Assert::IsTrue(
				g1.id() == 0 &&
				g1.size() == 0 &&
				g1.study_duration() == 0 &&
				g1.department_id() == 0 &&
				g1.contingent() == "" &&
				g1.qualification() == "", L"Default");
			for (auto i : g2) Assert::IsTrue(
				i.id() == 0 &&
				i.size() == 0 &&
				i.study_duration() == 0 &&
				i.department_id() == 0 &&
				i.department_id() == 0 &&
				i.contingent() == "" &&
				i.qualification() == "", L"Default array");

			// By fields values
			int id = 777, size = 777, study_duration = 777, department_id = 777;
			std::string contingent = "Sbrod", qualification = "bulbasaur";
			EveningGroup g3(id, size, department_id, study_duration, contingent, qualification);
			Assert::IsTrue(
				g3.id() == id &&
				g3.size() == size &&
				g3.study_duration() == study_duration &&
				g3.department_id() == department_id &&
				g3.contingent() == contingent &&
				g3.qualification() == qualification, L"By fields values");

			// Copy
			EveningGroup g4(g3);
			Assert::IsTrue(
				g4.id() == id &&
				g4.size() == size &&
				g4.study_duration() == study_duration &&
				g4.department_id() == department_id &&
				g4.contingent() == contingent &&
				g4.qualification() == qualification, L"Copy");

			// =
			EveningGroup g5 = g4;
			Assert::IsTrue(
				g5.id() == id &&
				g5.size() == size &&
				g5.study_duration() == study_duration &&
				g5.department_id() == department_id &&
				g4.contingent() == contingent &&
				g4.qualification() == qualification, L"=");

		}

		TEST_METHOD(paid_group)
		{

			// Default
			PaidGroup g1, g2[10];
			Assert::IsTrue(
				g1.id() == 0 &&
				g1.size() == 0 &&
				g1.study_duration() == 0 &&
				g1.department_id() == 0 &&
				g1.contract_id() == 0 &&
				g1.payment_size() == 0, L"Default");
			for (auto i : g2) Assert::IsTrue(
				i.id() == 0 &&
				i.size() == 0 &&
				i.study_duration() == 0 &&
				i.department_id() == 0 &&
				i.contract_id() == 0 &&
				i.payment_size() == 0, L"Default array");

			// By fields values
			int id = 777, size = 777, study_duration = 777, department_id = 777, contract_id = 777;
			float payment_size = 777;
			PaidGroup g3(id, size, department_id, study_duration, contract_id, payment_size);
			Assert::IsTrue(
				g3.id() == id &&
				g3.size() == size &&
				g3.study_duration() == study_duration &&
				g3.department_id() == department_id &&
				g3.contract_id() == contract_id &&
				g3.payment_size() == payment_size, L"By fields values");

			// Copy
			PaidGroup g4(g3);
			Assert::IsTrue(
				g4.id() == id &&
				g4.size() == size &&
				g4.study_duration() == study_duration &&
				g4.department_id() == department_id &&
				g4.contract_id() == contract_id &&
				g4.payment_size() == payment_size, L"Copy");

			// =
			PaidGroup g5 = g4;
			Assert::IsTrue(
				g5.id() == id &&
				g5.size() == size &&
				g5.study_duration() == study_duration &&
				g5.department_id() == department_id &&
				g5.contract_id() == contract_id &&
				g5.payment_size() == payment_size, L"=");

			// payment_size - setter
			Assert::IsTrue(g1.payment_size(payment_size) == payment_size, L"payment_size - setter");
		}
	};
}

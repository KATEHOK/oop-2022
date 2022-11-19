#pragma once

#ifndef SAME
#include "same.h"
#endif // !SAME

#define GROUP

namespace group {

	class Group {

		friend class GroupsTableItem;
		friend class GroupsTable;

	protected:
		int _id; // уникален в рамках одной таблицы
		int _size; // количество студентов
		int _department_id;
		int _study_duration; // срок обучения

		void output(std::ostream& out) const;

	public:
		Group(int id, int size, int department_id, int study_duration) :
			_id(id),
			_size(size),
			_department_id(department_id),
			_study_duration(study_duration) {}

		Group(const Group& src) :
			_id(src._id),
			_size(src._size),
			_department_id(src._department_id),
			_study_duration(src._study_duration) {}

		int id() const;

		int size() const;

		int size(int size);

		int department_id() const;

		int study_duration() const;
	};

	class DayGroup : public Group {
	private:
		std::string _specialization;
		float _stipend; // размер стипендии
		int _fellows_amount; // количество стипендиатов

	public:
		DayGroup(int id, int size, int department_id, int study_duration,
			std::string specialization, float stipend, int fellows_amount) :
			Group(id, size, department_id, study_duration),
			_specialization(specialization),
			_stipend(stipend),
			_fellows_amount(fellows_amount) {}

		DayGroup(const DayGroup& src) :
			Group(src),
			_specialization(src._specialization),
			_stipend(src._stipend),
			_fellows_amount(src._fellows_amount) {}

		DayGroup(DayGroup&& src) :
			Group(src),
			_specialization(src._specialization),
			_stipend(src._stipend),
			_fellows_amount(src._fellows_amount) {
			if (this != &src) src._specialization.clear();
		}

		DayGroup& operator= (const DayGroup& src);

		DayGroup& operator= (DayGroup&& src);

		std::string specialization() const;

		float stipend() const;

		float stipend(float stipend);

		int fellows_amount() const;

		int fellows_amount(int amount);

		friend std::ostream& operator<< (std::ostream& out, const DayGroup& dg);
	};

	class EveningGroup : public Group {
	private:
		std::string _contingent;
		std::string _qualification;

	public:
		EveningGroup(int id, int size, int department_id, int study_duration,
			std::string contingent, std::string qualification) :
			Group(id, size, department_id, study_duration),
			_contingent(contingent),
			_qualification(qualification) {}

		EveningGroup(const EveningGroup& src) :
			Group(src),
			_contingent(src._contingent),
			_qualification(src._qualification) {}

		EveningGroup(EveningGroup&& src) :
			Group(src),
			_contingent(src._contingent),
			_qualification(src._qualification) {
			if (this != &src) {
				src._contingent.clear();
				src._qualification.clear();
			}
		}

		EveningGroup& operator= (const EveningGroup& src);

		EveningGroup& operator= (EveningGroup&& src);

		std::string contingent() const;

		std::string qualification() const;

		friend std::ostream& operator<< (std::ostream& out, const EveningGroup& eg);
	};

	class PaidGroup : public Group {
	private:
		int _contract_id;
		float _payment_size;

	public:
		PaidGroup(int id, int size, int department_id, int study_duration,
			int contract_id, float payment_size) :
			Group(id, size, department_id, study_duration),
			_contract_id(contract_id),
			_payment_size(payment_size) {}

		PaidGroup(const PaidGroup& src) :
			Group(src),
			_contract_id(src._contract_id),
			_payment_size(src._payment_size) {}

		PaidGroup(PaidGroup&& src) :
			Group(src),
			_contract_id(src._contract_id),
			_payment_size(src._payment_size) {}

		PaidGroup& operator= (const PaidGroup& src);

		PaidGroup& operator= (PaidGroup&& src);

		int contract_id() const;

		float payment_size() const;

		float payment_size(float payment_size);

		friend std::ostream& operator<< (std::ostream& out, const PaidGroup& pg);
	};
}

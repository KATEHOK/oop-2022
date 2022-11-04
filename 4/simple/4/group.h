#pragma once

#ifndef PRECOMPILED
#include "precompiled.h"
#endif // !PRECOMPILED

#define GROUP

namespace group {

	class Group {
	protected:
		int _id;
		int _size; // количество студентов
		int _department_id;
		int _study_duration; // срок обучения

	public:
		Group(int id, int size, int department_id, int study_duration) :
			_id(id), _size(size),
			_department_id(department_id),
			_study_duration(study_duration) {}

		Group(const Group& src) :
			_id(src._id), _size(src._size),
			_department_id(src._department_id),
			_study_duration(src._study_duration) {}

		// нужно ли в данном случае делать конструктор перемещения?

		~Group() {}

		int id() const
		{
			return _id;
		}

		int size() const
		{
			return _size;
		}

		int size(int size)
		{
			_size = size;
			return _size;
		}

		int department_id() const
		{
			return _department_id;
		}

		void output(std::ostream& out) const
		{
			out << '{' << _id << ", " << _size << ", "
				<< _department_id << ", " << _study_duration << '}';
		}
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
			Group(src._id, src._size, src._department_id, src._study_duration),
			_specialization(src._specialization),
			_stipend(src._stipend),
			_fellows_amount(src._fellows_amount) {}

		DayGroup(DayGroup&& src) noexcept :
			Group(src._id, src._size, src._department_id, src._study_duration),
			_specialization(src._specialization),
			_stipend(src._stipend),
			_fellows_amount(src._fellows_amount)
		{
			if (this != &src) src._specialization.clear();
		}

		~DayGroup()
		{
			_specialization.clear();
		}

		std::string specialization() const
		{
			return _specialization;
		}

		float stipend() const
		{
			return _stipend;
		}

		float stipend(float stipend)
		{
			if (stipend >= 0) _stipend = stipend;
			return _stipend;
		}

		int fellows_amount() const
		{
			return _fellows_amount;
		}

		int fellows_amount(int amount)
		{
			_fellows_amount = amount;
			return _fellows_amount;
		}
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
			Group(src._id, src._size, src._department_id, src._study_duration),
			_contingent(src._contingent),
			_qualification(src._qualification){}

		EveningGroup(EveningGroup&& src) noexcept :
			Group(src._id, src._size, src._department_id, src._study_duration),
			_contingent(src._contingent),
			_qualification(src._qualification)
		{
			if (this != &src) {
				src._contingent.clear();
				src._qualification.clear();
			}
		}

		~EveningGroup()
		{
			_contingent.clear();
			_qualification.clear();
		}

		std::string contingent() const
		{
			return _contingent;
		}

		std::string qualification() const
		{
			return _qualification;
		}
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
			Group(src._id, src._size, src._department_id, src._study_duration),
			_contract_id(src._contract_id),
			_payment_size(src._payment_size) {}

		float payment_size() const
		{
			return _payment_size;
		}

		float payment_size(float payment_size)
		{
			if (payment_size >= 0) _payment_size = payment_size;
			return _payment_size;
		}
	};
}

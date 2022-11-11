#pragma once

#ifndef SAME
#include "same.h"
#endif // !SAME

#define GROUP

namespace group {

	class Group {
	protected:
		int _id;
		int _size; // количество студентов
		int _department_id;
		int _study_duration; // срок обучения

	public:
		Group(int id, int size, int department_id, int study_duration);

		Group(const Group& src);

		// нужно ли в данном случае делать конструктор перемещения?

		~Group() {}

		int id() const;

		int size() const;

		int size(int size);

		int department_id() const;

		friend std::ostream& operator<< (std::ostream& out, const Group& g);
	};

	class DayGroup : public Group {
	private:
		std::string _specialization;
		float _stipend; // размер стипендии
		int _fellows_amount; // количество стипендиатов

	public:
		DayGroup(int id, int size, int department_id, int study_duration,
			std::string specialization, float stipend, int fellows_amount);

		DayGroup(const DayGroup& src);

		DayGroup(DayGroup&& src);

		~DayGroup();

		std::string specialization() const;

		float stipend() const;

		float stipend(float stipend);

		int fellows_amount() const;

		int fellows_amount(int amount);
	};

	class EveningGroup : public Group {
	private:
		std::string _contingent;
		std::string _qualification;

	public:
		EveningGroup(int id, int size, int department_id, int study_duration,
			std::string contingent, std::string qualification);

		EveningGroup(const EveningGroup& src);

		EveningGroup(EveningGroup&& src);

		~EveningGroup();

		std::string contingent() const;

		std::string qualification() const;
	};

	class PaidGroup : public Group {
	private:
		int _contract_id;
		float _payment_size;

	public:
		PaidGroup(int id, int size, int department_id, int study_duration,
			int contract_id, float payment_size);

		PaidGroup(const PaidGroup& src);

		float payment_size() const;

		float payment_size(float payment_size);
	};
}

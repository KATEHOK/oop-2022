#ifndef GROUP
#include "group.h"
#endif // !GROUP

namespace group {
	
	// class Group

	int Group::id() const {
		return _id;
	}

	int Group::size() const {
		return _size;
	}

	int Group::size(int size) {
		_size = size;
		return _size;
	}

	int Group::department_id() const {
		return _department_id;
	}

	int Group::study_duration() const {
		return _study_duration;
	}

	void Group::output(std::ostream& out) const {
		out << _id << ", " << _size << ", " << _department_id << ", " << _study_duration;
	}

	// class DayGroup

	DayGroup::~DayGroup() {
		_specialization.clear();
	}

	DayGroup& DayGroup::operator= (const DayGroup& src) {
		_specialization.clear();
		_size = src._size;
		_department_id = src._department_id;
		_study_duration = src._study_duration;

		_specialization = src._specialization;
		_stipend = src._stipend;
		_fellows_amount = src._fellows_amount;
		return *this;
	}

	DayGroup& DayGroup::operator= (DayGroup&& src) {
		if (this == &src) return *this;

		_specialization.clear();
		_size = src._size;
		_department_id = src._department_id;
		_study_duration = src._study_duration;

		_specialization = src._specialization;
		_stipend = src._stipend;
		_fellows_amount = src._fellows_amount;

		src._specialization.clear();
		return *this;
	}

	std::string DayGroup::specialization() const {
		return _specialization;
	}

	float DayGroup::stipend() const {
		return _stipend;
	}

	float DayGroup::stipend(float stipend) {
		if (stipend >= 0) _stipend = stipend;
		return _stipend;
	}

	int DayGroup::fellows_amount() const {
		return _fellows_amount;
	}

	int DayGroup::fellows_amount(int amount) {
		if (amount >= 0) _fellows_amount = amount;
		return _fellows_amount;
	}

	std::ostream& operator<< (std::ostream& out, const DayGroup& dg) {
		out << '[';
		dg.output(out); 
		out << ", " << dg._specialization
			<< ", "	<< dg._stipend
			<< ", "	<< dg._fellows_amount
			<< ']';
		return out;
	}

	// class EveningGroup

	EveningGroup::~EveningGroup() {
		_contingent.clear();
		_qualification.clear();
	}

	EveningGroup& EveningGroup::operator= (const EveningGroup& src) {
		_contingent.clear();
		_qualification.clear();

		_size = src._size;
		_department_id = src._department_id;
		_study_duration = src._study_duration;

		_contingent = src._contingent;
		_qualification = src._qualification;

		return *this;
	}

	EveningGroup& EveningGroup::operator= (EveningGroup&& src) {
		if (this == &src) return *this;

		_contingent.clear();
		_qualification.clear();

		_size = src._size;
		_department_id = src._department_id;
		_study_duration = src._study_duration;

		_contingent = src._contingent;
		_qualification = src._qualification;

		src._contingent.clear();
		src._qualification.clear();

		return *this;
	}

	std::string EveningGroup::contingent() const {
		return _contingent;
	}

	std::string EveningGroup::qualification() const {
		return _qualification;
	}

	std::ostream& operator<< (std::ostream& out, const EveningGroup& eg) {
		out << '[';
		eg.output(out);
		out << ", " << eg._contingent
			<< ", " << eg._qualification
			<< ']';
		return out;
	}

	// class PaidGroup

	PaidGroup& PaidGroup::operator= (const PaidGroup& src) {
		_size = src._size;
		_department_id = src._department_id;
		_study_duration = src._study_duration;

		_contract_id = src._contract_id;
		_payment_size = src._payment_size;
		return *this;
	}

	PaidGroup& PaidGroup::operator= (PaidGroup&& src) {
		if (this == &src) return *this;

		_size = src._size;
		_department_id = src._department_id;
		_study_duration = src._study_duration;

		_contract_id = src._contract_id;
		_payment_size = src._payment_size;
		return *this;
	}

	int PaidGroup::contract_id() const {
		return _contract_id;
	}

	float PaidGroup::payment_size() const {
		return _payment_size;
	}

	float PaidGroup::payment_size(float payment_size) {
		_payment_size = payment_size;
		return _payment_size;
	}

	std::ostream& operator<< (std::ostream& out, const PaidGroup& pg) {
		out << '[';
		pg.output(out);
		out << ", " << pg._contract_id
			<< ", " << pg._payment_size
			<< ']';
		return out;
	}

}
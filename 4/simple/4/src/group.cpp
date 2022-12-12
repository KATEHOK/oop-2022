#ifndef GROUP
#include "group.h"
#endif // !GROUP

namespace group {
	
	// class Group

	Group::Group(const Group& src) {
		copy_from(src);
	}

	Group::Group(Group&& src) {
		move_from(std::move(src));
	}

	int Group::id() const {
		return _id;
	}

	size_t Group::size() const {
		return _size;
	}

	size_t Group::size(size_t size) {
		_size = size;
		return _size;
	}

	int Group::department_id() const {
		return _department_id;
	}

	int Group::study_duration() const {
		return _study_duration;
	}

	void Group::out(std::ostream& out) const {
		out << _id << ", " << _size << ", " << _department_id << ", " << _study_duration;
	}

	void Group::copy_from(const Group& src) {
		_id = src._id;
		_size = src._size;
		_department_id = src._department_id;
		_study_duration = src._study_duration;
	}

	void Group::move_from(Group&& src) {
		if (this == &src) return;
		copy_from(src);
		src._id = 0;
		src._size = 0;
		src._department_id = 0;
		src._study_duration = 0;
	}

	std::ostream& operator<< (std::ostream& out, const Group& group)
	{
		group.output();
		return out;
	}

	// class DayGroup

	DayGroup::DayGroup(const DayGroup& src) {
		this->copy_from(src);
	}

	DayGroup::DayGroup(DayGroup&& src) {
		this->move_from(std::move(src));
	}

	DayGroup& DayGroup::operator= (const DayGroup& src) {
		this->copy_from(src);
		return *this;
	}

	DayGroup& DayGroup::operator= (DayGroup&& src) {
		this->move_from(std::move(src));
		return *this;
	}

	void DayGroup::copy_from(const DayGroup& src) {
		Group::copy_from(src);
		this->_specialization = src._specialization;
		this->_stipend = src._stipend;
		this->_fellows_amount = src._fellows_amount;
	}

	void DayGroup::move_from(DayGroup&& src) {
		if (this == &src) return;
		Group::copy_from(src);

		this->_specialization = std::move(src._specialization);
		this->_stipend = src._stipend;
		this->_fellows_amount = src._fellows_amount;

		src._stipend = 0;
		src._fellows_amount = 0;
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
		dg.out(out);
		out << ", " << dg._specialization
			<< ", "	<< dg._stipend
			<< ", "	<< dg._fellows_amount
			<< ']';
		return out;
	}

	// class EveningGroup

	EveningGroup::EveningGroup(const EveningGroup& src) {
		this->copy_from(src);
	}

	EveningGroup::EveningGroup(EveningGroup&& src) {
		this->move_from(std::move(src));
	}

	EveningGroup& EveningGroup::operator= (const EveningGroup& src) {
		this->copy_from(src);
		return *this;
	}

	EveningGroup& EveningGroup::operator= (EveningGroup&& src) {
		this->move_from(std::move(src));
		return *this;
	}

	void EveningGroup::copy_from(const EveningGroup& src) {
		Group::copy_from(src);
		this->_contingent = src._contingent;
		this->_qualification = src._qualification;
	}

	void EveningGroup::move_from(EveningGroup&& src) {
		if (this == &src) return;
		Group::copy_from(src);

		this->_contingent = std::move(src._contingent);
		this->_qualification = std::move(src._qualification);
	}

	std::string EveningGroup::contingent() const {
		return _contingent;
	}

	std::string EveningGroup::qualification() const {
		return _qualification;
	}

	std::ostream& operator<< (std::ostream& out, const EveningGroup& eg) {
		out << '[';
		eg.out(out);
		out << ", " << eg._contingent
			<< ", " << eg._qualification
			<< ']';
		return out;
	}

	// class PaidGroup

	PaidGroup::PaidGroup(const PaidGroup& src) {
		this->copy_from(src);
	}

	PaidGroup::PaidGroup(PaidGroup&& src) {
		this->move_from(std::move(src));
	}

	PaidGroup& PaidGroup::operator= (const PaidGroup& src) {
		this->copy_from(src);
		return *this;
	}

	PaidGroup& PaidGroup::operator= (PaidGroup&& src) {
		this->move_from(std::move(src));
		return *this;
	}

	void PaidGroup::copy_from(const PaidGroup& src) {
		Group::copy_from(src);
		this->_contract_id = src._contract_id;
		this->_payment_size = src._payment_size;
	}

	void PaidGroup::move_from(PaidGroup&& src) {
		if (this == &src) return;
		Group::copy_from(src);

		this->_contract_id = src._contract_id;
		this->_payment_size = src._payment_size;

		src._contract_id = 0;
		src._payment_size = 0;
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
		pg.out(out);
		out << ", " << pg._contract_id
			<< ", " << pg._payment_size
			<< ']';
		return out;
	}

}
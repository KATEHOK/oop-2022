#ifndef DEPARTMENT
#include "department.h"
#endif // !DEPARTMENT

namespace department {

	// class Department

	Department::Department(Department&& src) {
		if (this != &src) {
			_id = src._id;
			_name = src._name;
			src._name.clear();
		}
	}

	int Department::id() const {
		return _id;
	}

	Department& Department::operator= (const Department& src) {
		_id = src._id;
		_name = src._name;
		return *this;
	}

	Department& Department::operator= (Department&& src) {
		if (this != &src) {
			_id = src._id;
			_name = src._name;
			src._name.clear();
		}
		return *this;
	}

	std::string Department::name() const {
		return _name;
	}

	bool operator== (const Department& left, const Department& right) {
		return (left._id == right._id || left._name == right._name);
	}

	bool operator!= (const Department& left, const Department& right) {
		return !(left == right);
	}

	std::ostream& operator<< (std::ostream& out, const Department& d) {
		out << '[' << d._id << ", " << d._name << ']';
		return out;
	}

	// class DepartmentsTable

	DepartmentsTable::DepartmentsTable(const Department& src) {
		_departments.push_back(src);
	}

	DepartmentsTable::DepartmentsTable(Department&& src) {
		_departments.push_back(src);
		src._name.clear();
	}

	DepartmentsTable::DepartmentsTable(const DepartmentsTable& src) {
		for (auto i : src._departments) _departments.push_back(i);
	}

	DepartmentsTable::DepartmentsTable(DepartmentsTable&& src) {
		if (this != &src) {
			for (auto i : src._departments) _departments.push_back(i);
			src._departments.clear();
		}
	}

	DepartmentsTable& DepartmentsTable::operator= (const DepartmentsTable& src) {
		_departments = src._departments;
		return *this;
	}

	DepartmentsTable& DepartmentsTable::operator= (DepartmentsTable&& src) {
		if (this != &src) {
			_departments = src._departments;
			src._departments.clear();
		}
		return *this;
	}

	void DepartmentsTable::push_back(Department& department) {
		if (find(department._id) >= 0 || find(department._name) >= 0) return;
		_departments.push_back(department);
	}

	int DepartmentsTable::find(int department_id) const {
		for (int i = 0; i < _departments.size(); ++i)
			if (_departments[i]._id == department_id) return i;
		return -1;
	}

	int DepartmentsTable::find(const std::string department_name) const {
		for (int i = 0; i < _departments.size(); ++i)
			if (_departments[i]._name == department_name) return i;
		return -1;
	}

	int DepartmentsTable::find(const Department& d) const {
		for (int i = 0; i < _departments.size(); ++i)
			if (_departments[i] == d) return i;
		return -1;
	}

	int DepartmentsTable::size() const {
		return _departments.size();
	}

	std::ostream& operator<< (std::ostream& out, const DepartmentsTable& dt) {
		out << '{';
		for (auto it = dt._departments.cbegin(); it < dt._departments.cend(); ++it) {
			out << *it;
			if (it < --dt._departments.cend()) out << ", ";
		}
		out << '}';
		return out;
	}

}
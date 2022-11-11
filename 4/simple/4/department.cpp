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

	Department::~Department() {
		_name.clear();
	}

	int Department::id() const {
		return _id;
	}

	std::string Department::name() const {
		return _name;
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

	DepartmentsTable::~DepartmentsTable() {
		_departments.clear();
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

	int DepartmentsTable::find(std::string department_name) const {
		for (int i = 0; i < _departments.size(); ++i)
			if (_departments[i]._name == department_name) return i;
		return -1;
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
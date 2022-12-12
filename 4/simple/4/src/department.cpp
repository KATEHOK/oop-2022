#ifndef DEPARTMENT
#include "department.h"
#endif // !DEPARTMENT

namespace department {

	// class Department

	Department::Department(Department&& src) {
		if (this != &src) {
			_id = src._id;
			_name = std::move(src._name);
		}
	}

	Department& Department::operator= (const Department& src) {
		_id = src._id;
		_name = src._name;
		return *this;
	}

	Department& Department::operator= (Department&& src) {
		if (this != &src) {
			_id = src._id;
			_name = std::move(src._name);
		}
		return *this;
	}

	int Department::id() const {
		return _id;
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
		_departments.push_back(std::move(src));
	}

	DepartmentsTable::DepartmentsTable(const DepartmentsTable& src) {
		for (auto i : src._departments) _departments.push_back(i);
	}

	DepartmentsTable::DepartmentsTable(DepartmentsTable&& src) {
		if (this != &src) _departments = std::move(src._departments);
	}

	DepartmentsTable& DepartmentsTable::operator= (const DepartmentsTable& src) {
		_departments = src._departments;
		return *this;
	}

	DepartmentsTable& DepartmentsTable::operator= (DepartmentsTable&& src) {
		if (this != &src) _departments = std::move(src._departments);
		return *this;
	}

	bool DepartmentsTable::push_back(const Department& department) {
		if (find(department._id) >= 0 || find(department._name) >= 0) return false;
		_departments.push_back(department);
		return true;
	}

	bool DepartmentsTable::push_back(Department&& department) {
		if (find(department._id) >= 0 || find(department._name) >= 0) return false;
		_departments.push_back(std::move(department));
		return true;
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

	void DepartmentsTable::clear() {
		_departments.clear();
	}

	size_t DepartmentsTable::size() const {
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

	void DepartmentsTable::output() const {
		int len_name = 0, len_id = 0, len_num, copy_id;
		for (auto i : _departments) {

			len_num = 0, copy_id = i._id;
			while (copy_id > 0) {
				copy_id /= 10;
				++len_num;
			}

			if (len_num > len_id) len_id = len_num;
			if (i._name.size() > len_name) len_name = i._name.size();
		}
		if (len_id + len_name == 0) len_id = 16;
		else len_id += 8 - len_id % 8;
		    		
		for (int i = 0; i < len_id + len_name; ++i) std::cout << '=';
		std::cout << std::endl;

		for (auto i : _departments) std::cout << i._id << '\t' << i._name << std::endl;

		for (int i = 0; i < len_id + len_name; ++i) std::cout << '=';
		std::cout << std::endl;
	}

}
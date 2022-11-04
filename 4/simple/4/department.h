#pragma once

#ifndef PRECOMPILED
#include "precompiled.h"
#endif // !PRECOMPILED

#define DEPARTMENT

namespace department {

	class Department {
		friend class DepartmentsTable;

	private:
		int _id;
		std::string _name;

	public:
		Department(int id, std::string name) : _id(id), _name(name) {}

		Department(const Department& src) : _id(src._id), _name(src._name) {}

		Department(Department&& src) noexcept : _id(src._id), _name(src._name)
		{
			if (this != &src) {
				src._id = -1;
				src._name.clear();
			}
		}

		~Department()
		{
			_id = -1;
			_name.clear();
		}

		int id() const
		{
			return _id;
		}

		std::string name() const
		{
			return _name;
		}

		void output(std::ostream& out) const
		{
			out << '{' << _id << ", " << _name << '}';
		}
	};

	class DepartmentsTable {
	private:
		std::vector<Department> _departments;

	public:
		DepartmentsTable() {}

		DepartmentsTable(const Department& src)
		{
			_departments.clear();
			_departments.push_back(src);
		}

		DepartmentsTable(Department&& src)
		{
			_departments.clear();
			_departments.push_back(src);

			src._id = -1;
			src._name.clear();
		}

		DepartmentsTable(const DepartmentsTable& src)
		{
			_departments.clear();
			for (auto it = src._departments.cbegin(); it != src._departments.cend(); ++it) {
				_departments.push_back(*it);
			}
		}

		DepartmentsTable(DepartmentsTable&& src) noexcept
		{
			if (this != &src) _departments.clear();
			for (auto it = src._departments.begin(); it != src._departments.end(); ++it) {
				_departments.push_back(*it);

				if (this != &src) {
					(*it)._id = -1;
					(*it)._name.clear();
				}
			}
			if (this != &src) src._departments.clear();
		}

		~DepartmentsTable()
		{
			for (auto it = _departments.begin(); it != _departments.end(); ++it) {
				(*it).~Department();
			}
			_departments.clear();
		}

		void insert(Department& department)
		{
			_departments.push_back(department);
		}

		int find(int department_id) const; // индекс в векторе

		int find(std::string department_name) const; // индекс в векторе

		void erase(int department_id);

		void erase(std::string department_name);

		void output(std::ostream& out) const
		{
			for (auto it = _departments.cbegin(); it != _departments.cend(); ++it)
			{
				(*it).output(out);
				out << std::endl;
			}
		}
	};
}

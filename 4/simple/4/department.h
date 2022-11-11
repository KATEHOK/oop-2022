#pragma once

#ifndef SAME
#include "same.h"
#endif // !SAME

#define DEPARTMENT

namespace department {

	class Department {
		friend class DepartmentsTable;

	private:
		int _id;
		std::string _name;

	public:
		Department(int id, std::string name);

		Department(const Department& src);

		Department(Department&& src);

		~Department();

		int id() const;

		std::string name() const;

		friend std::ostream& operator<< (std::ostream& out, Department& d);
	};

	class DepartmentsTable {
	private:
		std::vector<Department> _departments;

	public:
		DepartmentsTable();

		DepartmentsTable(const Department& src);

		DepartmentsTable(Department&& src);

		DepartmentsTable(const DepartmentsTable& src);

		DepartmentsTable(DepartmentsTable&& src);

		~DepartmentsTable();

		void insert(Department& department);

		int find(int department_id) const; // индекс в векторе

		int find(std::string department_name) const; // индекс в векторе

		void erase(int department_id);

		void erase(std::string department_name);

		friend std::ostream& operator<< (std::ostream& out, DepartmentsTable& dt);
	};
}

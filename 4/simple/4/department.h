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
		Department(int id, const std::string name) : _id(id), _name(name) {}

		Department(const Department& src) : _id(src._id), _name(src._name) {}

		Department(Department&& src);

		~Department();

		int id() const;

		std::string name() const;

		friend std::ostream& operator<< (std::ostream& out, const Department& d);
	};

	class DepartmentsTable {
	private:
		std::vector<Department> _departments; // имя и индекс - уникальны

	public:
		DepartmentsTable() {}

		DepartmentsTable(const Department& src);

		DepartmentsTable(Department&& src);

		DepartmentsTable(const DepartmentsTable& src);

		DepartmentsTable(DepartmentsTable&& src);

		~DepartmentsTable();

		void push_back(Department& department); // не добавит дублирующиеся имена и индексы

		int find(int department_id) const; // индекс в векторе (не найдено - 0)

		int find(std::string department_name) const; // индекс в векторе (не найдено - 0)

		// по имени или индексу департамента (НЕ по индексу вектора!)
		template<typename T>
		void erase(T id_or_name) { 
			int id = find(id_or_name);
			if (id < 0) return;

			auto it = _departments.begin() + id;
			_departments.erase(it);
		}

		friend std::ostream& operator<< (std::ostream& out, const DepartmentsTable& dt);
	};
}

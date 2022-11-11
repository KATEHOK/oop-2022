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
		Department() {}

		Department(int id, const std::string name) : _id(id), _name(name) {}

		Department(const Department& src) : _id(src._id), _name(src._name) {}

		Department(Department&& src);

		~Department();

		Department& operator= (const Department& src);

		Department& operator= (Department&& src);

		int id() const;

		std::string name() const;

		// достаточно равенства одного из двух полей
		friend bool operator== (const Department& left, const Department& right);

		// полное несовпадение полей
		friend bool operator!= (const Department& left, const Department& right);

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

		DepartmentsTable& operator= (const DepartmentsTable& src);

		DepartmentsTable& operator= (DepartmentsTable&& src);

		void push_back(Department& department); // не добавит дублирующиеся имена и индексы

		int find(int department_id) const; // индекс в векторе (не найдено - 0)

		int find(const std::string department_name) const; // индекс в векторе (не найдено - 0)

		int find(const Department& d) const; // индекс в векторе (не найдено - 0)

		int size() const;

		// по департаменту или по имени или по индексу департамента (НЕ по индексу вектора!)
		template<typename T>
		void erase(T id_or_name_or_obj) { 
			int id = find(id_or_name_or_obj);
			if (id < 0) return;

			auto it = _departments.begin() + id;
			_departments.erase(it);
		}

		// по имени или индексу департамента (НЕ по индексу вектора!)
		template<typename T>
		Department operator[] (T id_or_name) const {
			int id = find(id_or_name);
			if (id < 0) throw std::out_of_range("Table has not this item");
			return _departments[id];
		}

		friend std::ostream& operator<< (std::ostream& out, const DepartmentsTable& dt);
	};
}

#pragma once

#ifndef SAME
#include "same.h"
#endif // !SAME

#define DEPARTMENT

namespace department {

	/**
	* @brief Класс, описывающий кафедру
	*/
	class Department {
		friend class DepartmentsTable;

	private:
		//! @brief Номер кафедры (уникален в рамках одной таблицы)
		int _id = 0;
		//! @brief Наименование кафедры (уникально в рамках одной таблицы)
		std::string _name;

	public:
		/**
		* @brief Конструктор по умолчанию
		*/
		Department() {}

		/**
		* @brief Конструктор
		* @param id Номер кафедры
		* @param name Наименование кафедры
		*/
		Department(int id, const std::string name) : _id(id), _name(name) {}

		/**
		* @brief Копирующий конструктор
		* @param src Копируемый объект
		*/
		Department(const Department& src) : _id(src._id), _name(src._name) {}

		/**
		* @brief Перемещающий конструктор
		* @param src Перемещаемый объект
		*/
		Department(Department&& src);

		/**
		* @brief Копирующий оператор присваивания
		* @param src Ссыдка на копируемый объект
		* @return Ссылка на объект класса Department
		*/
		Department& operator= (const Department& src);

		/**
		* @brief Перемещающий оператор присваивания
		* @param src Ссыдка на перемещаемый объект
		* @return Ссылка на объект класса Department
		*/
		Department& operator= (Department&& src);

		/**
		* @brief Геттер номера кафедры
		* @return Номер кафедры
		*/
		int id() const;

		/**
		* @brief Геттер наименования кафедры
		* @return Наименование кафедры
		*/
		std::string name() const;

		/**
		* @brief Дружественный оператор равенства
		* @param left Ссыдка на левый операнд
		* @param right Ссыдка на правый операнд
		* @return true в случае совпадения хотя бы одного из полей, иначе false
		*/
		friend bool operator== (const Department& left, const Department& right);

		/**
		* @brief Дружественный оператор неравенства
		* @param left Ссыдка на левый операнд
		* @param right Ссыдка на правый операнд
		* @return false в случае совпадения хотя бы одного из полей, иначе true
		*/
		friend bool operator!= (const Department& left, const Department& right);

		/**
		* @brief Дружественный оператор вывода на стандартный поток вывода
		* @param out Ссылка на стандартный поток вывода
		* @param d Ссыдка на выводимую кафедру
		* @return Ссылка на стандартный поток вывода
		*/
		friend std::ostream& operator<< (std::ostream& out, const Department& d);
	};

	/**
	* @brief Класс, описывающий таблицу кафедр
	*/
	class DepartmentsTable {
	private:
		//! @brief Вектор из кафедр
		std::vector<Department> _departments;

	public:

		/**
		* @brief Конструктор по умолчанию
		*/
		DepartmentsTable() {}

		/**
		* @brief Конструктор на основе копируемой кафедры
		* @param src Ссылка на копируемый объект кафедры
		*/
		DepartmentsTable(const Department& src);

		/**
		* @brief Конструктор на основе перемещаемой кафедры
		* @param src Ссылка на перемещаемый объект кафедры
		*/
		DepartmentsTable(Department&& src);

		/**
		* @brief Копирующий конструктор
		* @param src Ссылка на копируемый объект таблицы
		*/
		DepartmentsTable(const DepartmentsTable& src);

		/**
		* @brief Перемещающий конструктор
		* @param src Ссылка на перемещаемый объект таблицы
		*/
		DepartmentsTable(DepartmentsTable&& src);

		/**
		* @brief Копирующий оператор присваивания
		* @param src Ссылка на копируемый объект таблицы
		* @return Ссылка на скопированный объект таблицы
		*/
		DepartmentsTable& operator= (const DepartmentsTable& src);

		/**
		* @brief Перемещающий оператор присваивания
		* @param src Ссылка на перемещаемый объект таблицы
		* @return Ссылка на перемещенный объект таблицы 
		*/
		DepartmentsTable& operator= (DepartmentsTable&& src);

		/**
		* @brief Функция, добавляющая уникальный объект кафедры в конец таблицы
		* @param department Ссылка на добавляемый объект кафедры
		*/
		void push_back(Department& department);

		/**
		* @brief Функция поиска объекта кафедры в таблице по номеру кафедры
		* @param department_id Номер искомой кафедры
		* @return Индекс внутри вектора (или -1 при отсутствии)
		*/
		int find(int department_id) const;

		/**
		* @brief Функция поиска объекта кафедры в таблице по наименованию кафедры
		* @param department_name Наименование искомой кафедры
		* @return Индекс внутри вектора (или -1 при отсутствии)
		*/
		int find(const std::string department_name) const;

		/**
		* @brief Функция поиска объекта кафедры в таблице по самому объекту
		* @param d Ссылка на искомый объект кафедры
		* @return Индекс внутри вектора (или -1 при отсутствии)
		*/
		int find(const Department& d) const;

		/**
		* @brief Геттер размера таблицы
		* @return Количество элементов таблицы
		*/
		int size() const;

		/**
		* @brief Шаблон функции удаления объекта кафедры из таблицы
		* @param id_or_name_or_obj Номер, наименование кафедры или ссылка на объект кафедры
		*/
		template<typename T>
		void erase(T id_or_name_or_obj) { 
			int id = find(id_or_name_or_obj);
			if (id < 0) return;

			auto it = _departments.begin() + id;
			_departments.erase(it);
		}

		/**
		* @brief Шаблон оператора индексирования (присвоение по индексу может нарушить логику!)
		* @param id_or_name Номер или наименование кафедры
		* @param Ссылка на найденный объект кафедры
		*/
		template<typename T>
		Department operator[] (T id_or_name) const {
			int id = find(id_or_name);
			if (id < 0) throw std::out_of_range("Table has not this item");
			return _departments[id];
		}

		/**
		* @brief Оператор вывода таблицы на стандартный поток вывода
		* @param out Ссылка на стандартный поток вывода
		* @param dt Ссылка выводимый объект таблицы
		* @return Ссылка на стандартный поток вывода
		*/
		friend std::ostream& operator<< (std::ostream& out, const DepartmentsTable& dt);
	};
}

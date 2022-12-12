#pragma once

#define DIALOG

#include "department.h"		// классы кафедры и таблицы кафедр, <string>, <iostream>, (мой) шаблон вектора 
#include "groups_table.h"	// классы групп и таблицы групп

#include <limits>			// для нормализации стандартного потока ввода

using namespace my_template;
using namespace department;
using namespace group;

#define MAX_INT 9999999		// Чтобы вывод табличек смотрелся красиво

namespace dialog {

	/**
	* @brief Тип указателя на функцию,
	* принимающую GroupsTable& и DepartmentsTable&
	* и возвращающую bool
	*/
	typedef bool (*func)(GroupsTable&, DepartmentsTable&);

	/**
	* @brief Шаблон функции ожидает ввод любого типа через стандартный поток ввода
	* @param result Ссылка, куда в случае успеха запишется введенное значение
	* @return true - в случае успеха, иначе - false
	*/
	template<typename T>
	bool ask_input(T& result) {
		bool status = false;
		T draft;

		std::cin >> draft;
		if (std::cin.good())
		{
			status = true;
			result = draft;
		}
		else std::cin.clear();

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return status;
	}

	/**
	* @brief Шаблон функции запрашивает (настойчиво) ввод положительного числа через стандартный поток ввода
	* @param result Ссылка, куда в случае успеха запишется введенное число
	* @param param_name Строка - название поля группы
	* @return true - в случае успеха, иначе - false
	*/
	template<typename T>
	void ask_positive_groups_param(T& result, const std::string param_name)
	{
		std::cout << "Enter " << param_name << " of new group: ";
		while (!ask_input(result) || result < 0 || result > MAX_INT)
			std::cout << "Something went wrong! Enter " << param_name << " of new group: ";
	}

	/**
	* @brief Функция запрашивает подтверждение (ожидает Y или N - Yes/No)
	* @return true, если ввели Y, false, если ввели N
	*/
	bool confirm();

	/**
	* @brief Выводит приветственное сообщение
	*/
	void print_greeting();

	/**
	* @brief Выводит прощальное сообщение
	*/
	void print_farewell();

	/**
	* @brief Функция выводит список доступных действий
	* @param options Ссылка на вектор строк, описывающих действия
	*/
	void print_options(const vector<std::string>& options);

	/**
	* @brief Функция (настойчиво) просит выбрать действие
	* @param choice Ссылка по которому надо записать выбор
	* @param count Количество возможных действий
	*/
	void ask_choice(int& choice, size_t count);

	// departments_table

	/**
	* @brief Функция запрашивает ввод одного из параметров кафедры
	* @param department_id Ссылка, куда записать номер кафедры
	* @param department_name Ссылка, куда записать имя кафедры
	* @return false - если пользоваткль выбрал выход, иначе - true
	*/
	bool ask_input_departments_param(int& department_id, std::string& department_name);

	/**
	* @brief Запрашивает данные и инициализует кафедру
	* @param Ссылка на таблицу групп
	* @param departments_table Ссылка на таблицу кафедр
	* @return true - если можно продолжить, false - если необходимо завершить выполнение программы
	*/
	bool add_department(GroupsTable&, DepartmentsTable& departments_table);

	/**
	* @brief Запрашивает данные, находит кафедру и выводит информацию о ее группах
	* @param groups_table Ссылка на таблицу групп
	* @param departments_table Ссылка на таблицу кафедр
	* @return true - если можно продолжить, false - если необходимо завершить выполнение программы
	*/
	bool output_groups_by_department(GroupsTable& groups_table, DepartmentsTable& departments_table);

	/**
	* @brief Запрашивает данные и удаляет кафедру и все связанные с ней группы
	* @param groups_table Ссылка на таблицу групп
	* @param departments_table Ссылка на таблицу кафедр
	* @return true - если можно продолжить, false - если необходимо завершить выполнение программы
	*/
	bool erase_department(GroupsTable& groups_table, DepartmentsTable& departments_table);

	/**
	* @brief Выводит таблицу кафедр
	* @param Ссылка на таблицу групп
	* @param departments_table Ссылка на таблицу кафедр
	* @return true - если можно продолжить, false - если необходимо завершить выполнение программы
	*/
	bool output_departments_table(GroupsTable&, DepartmentsTable& departments_table);

	/**
	* @brief Очищает таблицу кафедр и таблицу групп
	* @param groups_table Ссылка на таблицу групп
	* @param departments_table Ссылка на таблицу кафедр
	* @return true - если можно продолжить, false - если необходимо завершить выполнение программы
	*/
	bool clear_departments_table(GroupsTable& groups_table, DepartmentsTable& departments_table);

	// groups_table

	/**
	* @brief Функция запрашивает необходимые данные и находит элемент таблицы
	* @param result Ссылка, куда надо записать результат
	* @param groups_table Ссылка на таблицу групп
	* @return true - если элемент найден, false - если элемент не найден
	*/
	bool find_item(GroupsTableItem& result, const GroupsTable& groups_table);

	/**
	* @brief Функция запрашивает необходимые данные и в клучае корректности их инициализирует новую группу
	* @param groups_table Ссылка на таблицу групп
	* @param departments_table Ссылка на таблицу кафедр
	* @return true - если можно продолжить, false - если необходимо завершить выполнение программы
	*/
	bool add_group(GroupsTable& groups_table, DepartmentsTable& departments_table);

	/**
	* @brief Функция запрашивает необходимые данные и выводит информацию о элементе таблицы
	* @param groups_table Ссылка на таблицу групп
	* @param departments_table Ссылка на таблицу кафедр
	* @return true - если можно продолжить, false - если необходимо завершить выполнение программы
	*/
	bool find_item(GroupsTable& groups_table, DepartmentsTable&);

	/**
	* @brief Функция запрашивает необходимые данные и выводит информацию о группе
	* @param groups_table Ссылка на таблицу групп
	* @param departments_table Ссылка на таблицу кафедр
	* @return true - если можно продолжить, false - если необходимо завершить выполнение программы
	*/
	bool output_group(GroupsTable& groups_table, DepartmentsTable&);

	bool change_group(GroupsTable& groups_table, DepartmentsTable&);

	/**
	* @brief Функция запрашивает необходимые данные и удаляет группу
	* @param groups_table Ссылка на таблицу групп
	* @param departments_table Ссылка на таблицу кафедр
	* @return true - если можно продолжить, false - если необходимо завершить выполнение программы
	*/
	bool erase_group(GroupsTable& groups_table, DepartmentsTable&);

	/**
	* @brief Выводит таблицу групп
	* @param Ссылка на таблицу групп
	* @param departments_table Ссылка на таблицу кафедр
	* @return true - если можно продолжить, false - если необходимо завершить выполнение программы
	*/
	bool output_groups_table(GroupsTable& groups_table, DepartmentsTable&);

	/**
	* @brief Функция удаляет все группы
	* @param groups_table Ссылка на таблицу групп
	* @param departments_table Ссылка на таблицу кафедр
	* @return true - если можно продолжить, false - если необходимо завершить выполнение программы
	*/
	bool clear_groups_table(GroupsTable& groups_table, DepartmentsTable&);

	//



}
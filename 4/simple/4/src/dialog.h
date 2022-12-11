#pragma once

#define DIALOG

#include "department.h"		// классы кафедры и таблицы кафедр, <string>, <iostream>, (мой) шаблон вектора 
#include "groups_table.h"	// классы групп и таблицы групп

#include <limits>			// для нормализации стандартного потока ввода

using namespace my_template;
using namespace department;
using namespace group;

namespace dialog {

	/**
	* @brief Тип указателя на функцию,
	* принимающую GroupsTable& и DepartmentsTable&
	* и возвращающую bool
	*/
	typedef bool (*func)(GroupsTable&, DepartmentsTable&);

	/**
	* @brief Шаблон функции запрашивает число любого типа
	* @param num Ссылка, куда в случае успеха запишется число
	* @return true - в случае успеха, иначе - false
	*/
	template<typename T>
	bool ask_num(T& num) {
		bool status = false;
		T draft;

		std::cin >> draft;
		if (std::cin.good())
		{
			status = true;
			num = draft;
		}
		else std::cin.clear();

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return status;
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

}
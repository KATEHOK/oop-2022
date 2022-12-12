#define DEBUG

#ifdef DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif

#ifndef DIALOG
#include "dialog.h"	// диалоговые функции
#endif // !DIALOG

using namespace my_template;
using namespace department;
using namespace group;
using namespace dialog;

int main()
{

#ifdef DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	int choice = 0;
	GroupsTable groups_table;
	DepartmentsTable department_table;

	// Вектор наименований доступных действий
	const vector<std::string> options = {
		"Quit",

		"Add new department",
		"Delete existing department",
		"Output groups table of department",
		"Output departments table",
		"Delete all departments",

		"Add new group",
		"Find groups table item by group id and output it",
		"Find group by id and output it",
		"Find and change group",
		"Delete group by id",
		"Output groups table",
		"Delete all groups"
	};

	// Вектор указателей на доступные действия
	const vector<func> actions = {
		[](GroupsTable&, DepartmentsTable&) { return false; },

		add_department,
		erase_department,
		output_groups_by_department,
		output_departments_table,
		clear_departments_table,

		add_group,
		find_item,
		output_group,
		change_group,
		erase_group,
		output_groups_table,
		clear_groups_table,
	};

	print_greeting();
	std::cout << "Do you want to start? ";
	bool status = confirm();

	while (status)
	{
		std::cout << std::endl << "Menu" << std::endl;
		print_options(options);
		ask_choice(choice, options.size());
		std::cout << std::endl;

		try { status = actions[choice](groups_table, department_table); }
		catch (std::exception& err)
		{
#ifdef DEBUG
			std::cout << "Exception: " << err.what() << std::endl;
#else
			std::cout << "Sorry, something went wrong:(" << std::endl;
#endif
			status = false;
		}
	}

	print_farewell();
	return 0;
}
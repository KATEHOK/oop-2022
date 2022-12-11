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
	};

	// Вектор указателей на доступные действия
	const vector<func> actions = {
		[](GroupsTable&, DepartmentsTable&) { return false; }
	};

	print_greeting();
	std::cout << "Do you want to start? ";
	bool status = confirm();

	while (status)
	{
		print_options(options);
		ask_choice(choice, options.size());

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
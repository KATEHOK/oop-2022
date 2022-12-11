#ifndef DIALOG
#include "dialog.h"
#endif // !DIALOG

using namespace my_template;
using namespace department;
using namespace group;

namespace dialog {


	bool confirm()
	{
		char choice = '\0';
		std::cout << "Enter Y or N: ";
		std::cin >> choice;

		while ((choice != 'Y' && choice != 'N') || !std::cin.good()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << std::endl << "Enter Y or N: ";
			std::cin >> choice;
		}

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		if (choice == 'N') return false;
		return true;
	}

	void print_greeting()
	{
		std::cout <<
			"Hello world!"
			<< std::endl;
	}

	void print_farewell()
	{
		std::cout <<
			"Good bye world!"
			<< std::endl;
	}

	void print_options(const vector<std::string>& options)
	{
		std::cout << "======================" << std::endl;
		for (auto it = options.cbegin(); it < options.cend(); ++it)
		{
			std::cout << it.id() << ")\t" << *it << std::endl;
		}
		std::cout << "======================" << std::endl;
	}

	void ask_choice(int& choice, size_t count)
	{
		std::cout << "Make choice: ";
		while (!ask_num(choice) || choice < 0 || choice >= count)
			std::cout << "Something went wrong:(" << std::endl << "Make choice: ";
		std::cout << std::endl;
	}
}
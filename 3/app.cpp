#ifndef APP
#include "app.h"
#endif

using namespace dialog;

int main() {
	// Для выявления утечек памяти
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	int choice;
	const int mCount = 14;
	sequence::Sequence seq;

	const std::vector<std::string> vars = {
		"Exit", "Init free", "Init one", "Init by array",
		"Print size", "Print max size",
		"Find element by ID", "Input", "Output",
		"Add other", "Find monotonicity",
		"Insert value", "Get groups count", "Get same count"
	};

	int (*operations[mCount])(sequence::Sequence*) = {
		exit, initFree, initOne, initByArray,
		printSize, printMaxSize,
		printElement, input, output,
		plus, findMonotonicity,
		insert, printGroupsCount, printSameCount
	};

	std::cout << "Enter any integer to start or something else to stop: ";
	int status = getNum(&choice);

	while (status == SUCCESS) {
		// вывод возможностей
		std::cout << std::endl;

		for (auto it = vars.begin(); it != vars.end(); ++it)
			std::cout << " " << (it - vars.begin()) << ") " << *it << std::endl;

		// запрос выбора
		std::cout << std::endl << "Choose point: ";
		while (getNum(&choice) == FAIL || choice < 0 || choice > mCount)
			std::cout << std::endl << "Wrong value! Choose point: ";
		std::cout << std::endl;
		
		// исполнение выбора
		try { status = operations[choice](&seq); }
		catch (std::exception& err) {
			std::cout << "Exception: " << err.what() << std::endl;
			status = FAIL;
		}
	}

	return SUCCESS;
}
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
		"Get element by ID", "Input", "Output",
		"Add other", "Find monotonicity",
		"Insert value", "Get groups count", "Get same count"
	};

	std::vector<func> functions = {
		exit, initFree, initOne, initByArray,
		printSize, printMaxSize,
		printElement, input, output,
		plus, findMonotonicity,
		insert, printGroupsCount, printSameCount
	};

	std::cout << "Do you want to start? ";
	bool status = confirm();

	while (status) {
		printVars(vars); // вывод возможностей

		choice = getChoice(mCount); // запрос выбора
		
		// исполнение выбора
		try { status = functions[choice](seq); }
		catch (std::exception& err) {
			std::cout << "Exception: " << err.what() << std::endl;
			status = false;
		}
	}

	return SUCCESS;
}
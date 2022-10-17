#ifndef APP
#include "app.h"
#endif

using namespace dialog;

int main() {
	// Для выявления утечек памяти
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	int choice;
	const int mCount = 15;
	sequence::Sequence seq;

	const char* ppVars[mCount] = {
		"Exit", "Init free", "Init one", "Init by array",
		"Print size", "Print max size",
		"Find element by ID", "Clone",
		"Input", "Output",
		"Add other", "Find monotonicity",
		"Insert value", "Get groups count", "Get same count"
	};

	int (*operations[mCount])(sequence::Sequence*) = {
		exit, initFree, initOne, initByArray,
		printSize, printMaxSize,
		printElement, makeClone,
		input, output,
		plus, findMonotonicity,
		insert, printGroupsCount, printSameCount
	};

	std::cout << "Enter any integer to start or something else to stop: ";
	int status = getNum(&choice);

	while (status == SUCCESS) {
		std::cout << std::endl;
		for (int i = 0; i < mCount; i++)
			std::cout << " " << i << ") " << ppVars[i] << std::endl;

		std::cout << std::endl << "Choose point: ";
		while (getNum(&choice) == FAIL || choice < 0 || choice > mCount)
			std::cout << std::endl << "Wrong value! Choose point: ";
		std::cout << std::endl;
		
		status = operations[choice](&seq);
	}

	std::cout << "Code: " << status << std::endl;
	return SUCCESS;
}
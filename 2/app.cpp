#ifndef APP
#include "app.h"
#endif // !APP

using namespace strophoid;

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	char stop = '\0';
	while (stop != 'F') {

		long double val[7];
		val[0] = f::getNum<long double>("Enter A: ");

		Strophoid line(val[0]);

		val[1] = line.getRadius();
		val[2] = line.getY();
		val[3] = line.getRadiusOfCurvature();
		val[4] = line.getLoopArea();
		val[5] = line.getLoopVolume();
		val[6] = line.getMiddleBranchesVolume();

		for (int i = 0; i < 7; i++) std::cout << val[i] << std::endl;

		std::cout << std::endl << std::endl << "Print F to stop the program: ";
		std::cin >> stop;
		std::cout << std::endl << std::endl;
	}

	return SUCCESS;
}
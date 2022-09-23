#ifndef APP
#include "app.h"
#endif // !APP

using namespace strophoid;

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	long double value = 0.0;
	int code = f::inputNum<int>("Print 0 to start the program or something else to stop: ");

	if (code != 0) return SUCCESS;
	Strophoid line;

	while (code == 0) {
		std::string vars[8] = { "Set X of A-point", "Print X of A-point", "Print X by X",
			"Print radius by angle",  "Print radius of curvature", "Print area of loop",
			"Print volume of loop rotation", "Print area between branches and asymptotes"
		};

		for (int i = 0; i < 8; i++) std::cout << " " << i << ") " << vars[i] << std::endl;
		std::cout << " 8) Stop the program" << std::endl;
		code = f::inputNum<int>("Choose point: ");

		if (code >= 0 && code <= 7) {
			long double res = 0.0;

			switch (code) {
			case 0:
				value = f::inputNum<long double>("Print X of A-point: ");
				line.setA(value);
				break;

			case 1:
				res = line.getA();
				break;

			case 2:
				value = f::inputNum<long double>("Print X: ");
				res = line.getY(value);
				break;

			case 3:
				value = f::inputNum<long double>("Print angle in degrees: ");
				res = line.getRadius(value);
				break;

			case 4:
				res = line.getRadiusOfCurvature();
				break;

			case 5:
				res = line.getLoopArea();
				break;

			case 6:
				res = line.getLoopVolume();
				break;

			case 7:
				res = line.getMiddleBranchesArea();
				break;
			}

			std::cout << res << std::endl;
			code = 0;
		}

		std::cout << std::endl;
	}

	return SUCCESS;
}
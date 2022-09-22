#ifndef APP
#include "app.h"
#endif // !APP

using namespace strophoid;

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	int code = f::getNum("Print 0 to start the program or something else to stop: ");

	if (code != 0) return SUCCESS;
	Strophoid line;

	while (code == 0) {
		std::string vars[8] = { "Set X of A-point", "Print X of A-point", "Print X by X",
			"Print radius by angle",  "Print radius of curvature", "Print area of loop",
			"Print volume of loop rotation", "Print area between branches and asymptotes"
		};

		for (int i = 0; i < 8; i++) std::cout << " " << i << ") " << vars[i] << std::endl;
		std::cout << " 8) Stop the program" << std::endl;
		int code = f::getNum("Choose point: ");

		if (code == 0) line.setA();
		else code = line.print(code);

		std::cout << std::endl;
	}

	return SUCCESS;
}
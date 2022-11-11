#include "department.h"

int main() {

	std::string s = "IX";

	department::Department d(9, s);

	department::DepartmentsTable dt(d);

	dt.push_back(d);
	dt.push_back(d);
	dt.push_back(d);
	dt.push_back(d);

	std::cout << std::endl << dt << std::endl;

	return 0;
}
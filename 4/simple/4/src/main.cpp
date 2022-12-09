#include "../../my_vector/src/vector.h"
#include <iostream>

using namespace my_template;

template<typename T, size_t N>
size_t array_size(T(&arr)[N])
{
	return N;
}

int main() {

	int a[] = {0, 1, 2, 3, 4};

	vector<int> b = a;

	std::cout << b.begin().id() << ' ' << b.end().id() << std::endl;
	std::cout << b.cbegin().id() << ' ' << b.cend().id() << std::endl << std::endl;

	for (int i = 0; i < b.size(); ++i) std::cout << b[i] << ' ';
	std::cout << std::endl << std::endl;

	for (auto it = b.cbegin(); it < b.cend(); ++it) std::cout << *it << ", ";
	std::cout << std::endl;

	for (auto it = b.begin(); it < b.end(); ++it) std::cout << *it << ", ";
	std::cout << std::endl << std::endl;

	for (auto it = b.cbegin(); it < b.cend(); it++) std::cout << *it << ", ";
	std::cout << std::endl;

	for (auto it = b.begin(); it < b.end(); it++) std::cout << *it << ", ";
	std::cout << std::endl << std::endl;

	for (auto it = b.cbegin(); it < b.cend(); it += 1) std::cout << *it << ", ";
	std::cout << std::endl;

	for (auto it = b.begin(); it < b.end(); it += 1) std::cout << *it << ", ";
	std::cout << std::endl << std::endl;

	for (auto it = b.cbegin(); it < b.cend(); it = it + 1) std::cout << *it << ' ';
	std::cout << std::endl;

	for (auto it = b.begin(); it < b.end(); it = it + 1) std::cout << *it << ' ';
	std::cout << std::endl << std::endl;

	auto it1 = b.cbegin();
	auto it2 = b.cend();
	it2 = it2 - 2;
	std::cout << it2.id() << ' ' << (++it2).id() << ' ' << (it2).id() << std::endl;
	std::cout << (it2).id() << ' ' << (it2++).id() << ' ' << (it2).id() << std::endl << std::endl;

	for (auto i : b) std::cout << i << ' ';
	std::cout << std::endl;

	return 0;
}
#include "vector.h"

using namespace my_vector;

int main() {

	int arr[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	vector vec1(10, arr), vec2, vec3, vec4;

	std::cin >> vec2;
	vec2.sort();

	std::cout << vec1 << ' ' << vec1.size() << ' ' << vec1.quantity() << std::endl;
	std::cout << vec2 << ' ' << vec2.size() << ' ' << vec2.quantity() << std::endl;
	std::cout << vec3 << ' ' << vec3.size() << ' ' << vec3.quantity() << std::endl;
	std::cout << vec4 << ' ' << vec4.size() << ' ' << vec4.quantity() << std::endl;

	return 0;
}
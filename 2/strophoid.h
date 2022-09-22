#pragma once

namespace strophoid {

	class Strophoid {

	public:

		Strophoid(long double A = 0);

		void setA(long double A = 0); // 0

		int print(int code = 0);

		long double getNum(const char* msg);

		long double getA(); // 1

#ifdef TEST
		long double getY(long double X); // 2

		long double getRadius(long double angle);
#else
		long double getY(); // 2

		long double getRadius(); // 3
#endif

		long double getRadiusOfCurvature(); // 4

		long double getLoopArea(); // 5

		long double getLoopVolume(); // 6

		long double getMiddleBranchesArea(); // 7

	private:

		long double A;

	};
}
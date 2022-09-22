#pragma once

namespace strophoid {

	class Strophoid {

	public:

		Strophoid(long double A = 0);

		void setA(long double A = 0); // 0

		int print(int code = 0);

	private:

		long double A;

		long double getNum(const char* msg);

		long double getA(); // 1

		long double getY(); // 2

		long double getRadius(); // 3

		long double getRadiusOfCurvature(); // 4

		long double getLoopArea(); // 5

		long double getLoopVolume(); // 6

		long double getMiddleBranchesArea(); // 7

	};
}
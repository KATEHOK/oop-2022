#pragma once

namespace strophoid {

	class Strophoid {

	public:

		Strophoid(long double A = 0);

		void setA(long double A = 0);

		long double getY(); // 3

		long double getRadius(); // 4

		long double getRadiusOfCurvature(); // 5

		long double getLoopArea(); // 6

		long double getLoopVolume(); // 7

		long double getMiddleBranchesVolume(); // 8

	private:

		long double A;

	};
}
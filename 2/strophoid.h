#pragma once

namespace strophoid {

	class Strophoid {

	public:

		Strophoid(const long double A = 1.0);

		void setA(const long double A = 1.0);
		
		long double getA() const;
		long double getY(const long double X = 0) const;
		long double getRadius(long double angle = 0) const;
		long double getRadiusOfCurvature() const;
		long double getLoopArea() const;
		long double getLoopVolume() const;
		long double getMiddleBranchesArea() const;

	private:

		long double A;

	};
}
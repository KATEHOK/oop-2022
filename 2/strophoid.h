#pragma once

namespace strophoid {

	class Strophoid {

	public:

		Strophoid(const double A = 1.0);

		void setA(const double A = 1.0);
		
		double getA() const;
		double getY(const double X = 0) const;
		double getRadius(double angle = 0) const;
		double getRadiusOfCurvature() const;
		double getLoopArea() const;
		double getLoopVolume() const;
		double getMiddleBranchesArea() const;

	private:

		double A;

	};
}
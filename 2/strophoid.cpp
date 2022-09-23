#ifndef APP
#include "app.h"
#endif // !APP

namespace strophoid {
	/*
	https://www.fxyz.ru/%D1%84%D0%BE%D1%80%D0%BC%D1%83%D0%BB%D1%8B_%D0%BF%D0%BE_%D0%BC%D0%B0%D1%82%D0%B5%D0%BC%D0%B0%D1%82%D0%B8%D0%BA%D0%B5/%D1%84%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D0%B8_%D0%B8_%D0%B3%D1%80%D0%B0%D1%84%D0%B8%D0%BA%D0%B8/%D1%81%D1%82%D1%80%D0%BE%D1%84%D0%BE%D0%B8%D0%B4%D0%B0/
	*/

	Strophoid::Strophoid(const double A) { setA(A); }

	void Strophoid::setA(const double A) { this->A = A; }

	double Strophoid::getA() const { return this->A; }

	double Strophoid::getY(const double X) const {
		return abs(X) * sqrt( abs( (this->A + X) / (this->A - X) ) );
	}

	double Strophoid::getRadius(double angle) const {
		if (angle >= 360) angle -= 360 * floor(angle / 360);
		else if (angle < 0) angle += 360 * ceil(abs(angle) / 360);

		if (angle >= 0 && angle <= 45 || angle >= 90 && angle <= 135 ||
			angle >= 225 && angle <= 270 || angle >= 315) return 0.0;

		double angleRad = angle / 180.0 * M_PI;
		double radius = -(this->A * cos(2 * angleRad)) / cos(angleRad);
		
		if (radius <= 0) radius = 0.0;
		return radius;
	}

	double Strophoid::getRadiusOfCurvature() const { return this->A * sqrt(2); }

	double Strophoid::getLoopArea() const {	return pow(this->A, 2) * (2 - 0.5 * M_PI); }

	double Strophoid::getLoopVolume() const {
		return M_PI * pow(this->A, 3) * (2 * log(2) - 4 / 3);
	}

	double Strophoid::getMiddleBranchesArea() const {
		return pow(this->A, 2) * ( 2 + 0.5 * M_PI);
	}
}
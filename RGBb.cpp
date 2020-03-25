#include "pch.h"

#include "RGBb.h"

namespace brightland {

	RGBb::RGBb(double r, double g, double b) : r(r), g(g), b(b) {



	}

	RGBb operator-(const RGBb& first, const RGBb& second) {

		return RGBb(first.r - second.r, first.g - second.g, first.b - second.b);

	}



}
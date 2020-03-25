#ifndef RGBb_H_
#define RGBb_H_


namespace brightland {

	struct RGBb
	{

		double r;
		double g;
		double b;

		RGBb(double r, double g, double b);


	};

	RGBb operator-(const RGBb& first, const RGBb& second);
}


#endif
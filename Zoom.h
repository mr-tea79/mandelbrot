#ifndef ZOOM_H_
#define ZOOM_H_

namespace brightland {


	//struct has all members public by default, class has all members private by default.
	struct Zoom
	{
		int x{ 0 };
		int y{ 0 };
		double scale{ 0 };
		Zoom(int x, int y, double scale) : x(x), y(y), scale(scale) {};

	};
}
#endif

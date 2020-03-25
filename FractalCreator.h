#ifndef FRACTALCREATOR_H_
#define FRACTALCREATOR_H_

#include <memory>
#include <math.h>
#include <cstdint>
#include <string>
#include <vector>
#include "Zoom.h"
#include "ZoomList.h"
#include "Mandelbrot.h"
#include "Bitmap.h"
#include "RGBb.h"

using namespace std;


namespace brightland {

	class FractalCreator
	{
	private:
		int m_width;
		int m_height;
		Bitmap m_bitmap;
		ZoomList m_zoomList;
		int m_total{ 0 };

		unique_ptr<int[]> m_histogram;

		unique_ptr<int[]> m_fractal;

		vector<int> m_ranges;
		vector<RGBb> m_colors;
		vector<int> m_rangeTotals;

		bool m_bGotFirstRange{ false };


	private:
		void calculateIteration();
		void calculateTotalIterations();
		void calculateRangeTotals();
		void drawFractal();

		void writeBitmap(string name);

	public:
		FractalCreator(int width, int height);
		void addRange(double rangeEnd, const RGBb& rgb);
		void addZoom(const Zoom& zoom);

		int getRange(int iterations) const;
		virtual ~FractalCreator();

		void run(string name);

	};

}

#endif
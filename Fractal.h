#include <iostream>
#include "FractalCreator.h"
#include "RGBb.h"
#include "Zoom.h"

using namespace std;
using namespace brightland;

int Fractal()
{
    //   RGB rgb1(4, 5, 6);
     //  RGB rgb2(1, 2, 3);

       //RGB rgb3 = rgb1 - rgb2;

       //std::cout << rgb3.r << ", " << rgb3.g << ", " << rgb3.b << endl;

    FractalCreator m_fractalCreator(800, 600);

    //Need error checking on GUI min and max range 0.0 - 1.0
    m_fractalCreator.addRange(0.0, RGBb(0, 0, 0));
    m_fractalCreator.addRange(0.3, RGBb(255, 0, 0));
    m_fractalCreator.addRange(0.5, RGBb(255, 255, 0));
    m_fractalCreator.addRange(1.0, RGBb(255, 255, 255));

    std::cout << "Range: " << m_fractalCreator.getRange(200) << endl;

    m_fractalCreator.addZoom(Zoom(295, 202, 0.1));
    m_fractalCreator.addZoom(Zoom(312, 304, 0.1));

    m_fractalCreator.run("test.bmp");


    std::cout << "Finished" << endl;
    return 0;
}


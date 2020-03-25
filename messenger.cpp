#include "pch.h"
#include "framework.h"
#include "Mandelbrot Experiment.h"
#include "Mandelbrot ExperimentDlg.h"
#include "afxdialogex.h"
#include <Afxwin.h>
#include "time.h"
#include <string>

using namespace std;
using namespace brightland;


void CMandelbrotExperimentDlg::messenger(string s) {


	//m_Console = "test";
	m_output = s.c_str();

	//UpdateData(FALSE);


}


// Mandelbrot ExperimentDlg.cpp : implementation file
//Last update was on 26th of March 2020
//

#include "pch.h"
#include "framework.h"
#include "Mandelbrot Experiment.h"
#include "Mandelbrot ExperimentDlg.h"
#include "afxdialogex.h"
#include "FractalCreator.h"
#include "CStaticSubclass.h"
#include <Windows.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define _AFXDLL //<<===notice this

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace brightland;

int currValue;
int maxValue;
BOOL stopNow;



// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
	enum { IDD = IDD_MANDELBROTEXPERIMENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	CString m_console;
	CString m_output;
	CString text1;
//	CString red_value;	
//	CEdit r_edit1;
};


CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
, m_console(_T(""))
, text1(_T(""))
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);	
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_HSCROLL()
	ON_WM_HSCROLL()
END_MESSAGE_MAP()

// CMandelbrotExperimentDlg dialog

CMandelbrotExperimentDlg::CMandelbrotExperimentDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MANDELBROTEXPERIMENT_DIALOG, pParent)
	, m_output(_T(""))
//	, red_value(_T(""))
{	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMandelbrotExperimentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_OUTPUT, m_output);
	DDX_Control(pDX, IDC_BMP, m_pic);	
}

BEGIN_MESSAGE_MAP(CMandelbrotExperimentDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTNCOMPILE, &CMandelbrotExperimentDlg::OnBnClickedBtnCompile) //Start Monitoring Button
	//ON_BN_CLICKED(IDC_BUTTON1, &CMandelbrotExperimentDlg::OnBnClickedBtnTest) //Start Monitoring Button
	ON_WM_MOUSEMOVE(OnMouseMove)
	//ON_WM_MBUTTONDBLCLK(OnMButtonDblClk)
	ON_WM_LBUTTONDBLCLK(OnLButtonDblClk)

END_MESSAGE_MAP()


// CMandelbrotExperimentDlg message handlers

BOOL CMandelbrotExperimentDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	//LPCTSTR str = _T("test.bmp");

	//This adds the minimize and close controls to the dialog box.
	ModifyStyle(0, WS_MINIMIZEBOX, TRUE);
	ModifyStyle(0, WS_POPUP, TRUE);
	ModifyStyle(0, WS_BORDER, TRUE);
	ModifyStyle(0, WS_SYSMENU, TRUE);
	ModifyStyle(0, WS_CAPTION, TRUE);

	//Set Range 1 default values
	m_output = "0";
	SetDlgItemText(IDC_EDIT2, m_output);
	m_output = "0";
	SetDlgItemText(IDC_EDIT3, m_output);
	m_output = "0";
	SetDlgItemText(IDC_EDIT4, m_output);

	//Set Range 2 default values
	m_output = "255";
	SetDlgItemText(IDC_EDIT5, m_output);
	m_output = "0";
	SetDlgItemText(IDC_EDIT6, m_output);
	m_output = "0";
	SetDlgItemText(IDC_EDIT7, m_output);

	//Set Range 3 default values
	m_output = "255";
	SetDlgItemText(IDC_EDIT8, m_output);
	m_output = "255";
	SetDlgItemText(IDC_EDIT9, m_output);
	m_output = "0";
	SetDlgItemText(IDC_EDIT10, m_output);

	//Set Range 4 default values
	m_output = "255";
	SetDlgItemText(IDC_EDIT11, m_output);
	m_output = "255";
	SetDlgItemText(IDC_EDIT12, m_output);
	m_output = "255";
	SetDlgItemText(IDC_EDIT13, m_output);

	//Set Coordindates
	m_output = "295";
	SetDlgItemText(IDC_EDIT14, m_output);
	m_output = "202";
	SetDlgItemText(IDC_EDIT15, m_output);

	m_output = "312";
	SetDlgItemText(IDC_EDIT16, m_output);
	m_output = "304";
	SetDlgItemText(IDC_EDIT17, m_output);

	//Set Magnification
	m_output = "1.0";
	SetDlgItemText(IDC_EDIT18, m_output);

	m_output = "1.0";
	SetDlgItemText(IDC_EDIT19, m_output);

	// Add "About..." menu item to system menu.
	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMandelbrotExperimentDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CMandelbrotExperimentDlg::ChangeStaticCtrl(LPCTSTR lpszImagePath, // path to imageg source
	UINT nCtrlID) // ID of static control
{
	HBITMAP hBitmap = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
		lpszImagePath, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	if (hBitmap != NULL) // we are OK, image load correctly
	{
		if (bmp.m_hObject != NULL) // make sure we remove last image
			bmp.DeleteObject();

		bmp.Attach(hBitmap); // attach new image to it
		CStatic* pCtrl = (CStatic*)GetDlgItem(nCtrlID);
		pCtrl->SetBitmap((HBITMAP)bmp);
	}
}


//OnTimer is important because it gives your program the ability to update the controls from a separate thread.
void CMandelbrotExperimentDlg::OnTimer(UINT_PTR nIDEvent) {
	// TODO: Add your message handler code here and/or call default

	//m_ctrlStatus.SetWindowText(sStatusMsg);
	CDialogEx::OnTimer(nIDEvent);
	UpdateData(FALSE);
}

//Just for testing
void CMandelbrotExperimentDlg::OnBnClickedBtnTest() {
	stopNow = 1;
	m_output = "test";

	UpdateData(false);
}

//This updates the image with the preview.
void CMandelbrotExperimentDlg::updateImage(LPCTSTR str) {

	CImage img1;
	int dimx = 400, dimy = 300;
	
	img1.Load((LPCTSTR)(str));
	//filename = path on local system to the bitmap

	CDC* screenDC = GetDC();
	CDC mDC;
	mDC.CreateCompatibleDC(screenDC);
	CBitmap b;
	b.CreateCompatibleBitmap(screenDC, dimx, dimy);

	CBitmap* pob = mDC.SelectObject(&b);
	mDC.SetStretchBltMode(HALFTONE);
	img1.StretchBlt(mDC.m_hDC, 0, 0, dimx, dimy, 0, 0, img1.GetWidth(), img1.GetHeight(), SRCCOPY);
	mDC.SelectObject(pob);

	m_pic.SetBitmap((HBITMAP)b.Detach());
	ReleaseDC(screenDC);
}

//This creates a new thread to allow the GUI to still function.
void CMandelbrotExperimentDlg::OnBnClickedBtnCompile()
{
	//Disable button to prevent multiple threads being started (Crash might occur).
	CWnd* okbtn = GetDlgItem(IDC_BTNCOMPILE);
	if (okbtn) {
		okbtn->EnableWindow(FALSE);
	}
	//Begin the new thread.
	stopNow = 0;
	SetTimer(1234, 333, 0); // 3 times per second
	
	m_output = "Bulding Fractal, please wait..";
	
	AfxBeginThread(compileMandelbrot, this);
	UpdateData(false);	
}

//Notifies the user that the mandelbrot has finished compiling.
int CMandelbrotExperimentDlg::finishUp() {

	string output = "Fractal Completed!";
	messenger(output);

	return 0;
}

//This is used to check if the fields contain a number.
bool CMandelbrotExperimentDlg::isNumber(string s)
{
	for (int i = 0; i < s.length(); i++) {
		if (isdigit(s[i]) == false && s[i] != '.')
			return false;	
	}

	int b = atoi(s.c_str());  //Convert to integer and test if it is greater than 255 or less than 0
	if (b > 255 || b < 0)
		return false;

	if (s == "")
		return false;

	return true;
}

//This is where the mandelbrot is compiled.
UINT CMandelbrotExperimentDlg::compileMandelbrot(LPVOID pParam) {

	CMandelbrotExperimentDlg* pObject = (CMandelbrotExperimentDlg*)pParam;
	
	//Set hue values
	CString red1;
	
	//Get the values from the textboxes and convert them into required format.
	pObject->GetDlgItemText(IDC_EDIT2, red1);

	std::string r1 = std::string(CStringA(red1));
	double red1d = _ttoi(red1);

	CString green1;
	pObject->GetDlgItemText(IDC_EDIT3, green1);
	std::string g1 = std::string(CStringA(green1));
	double green1d = _ttoi(green1);

	CString blue1;
	pObject->GetDlgItemText(IDC_EDIT4, blue1);
	std::string b1 = std::string(CStringA(blue1));
	double blue1d = _ttoi(blue1);

	CString red2;
	pObject->GetDlgItemText(IDC_EDIT5, red2);
	std::string r2 = std::string(CStringA(red2));
	double red2d = _ttoi(red2);

	CString green2;
	pObject->GetDlgItemText(IDC_EDIT6, green2);
	std::string g2 = std::string(CStringA(green2));
	double green2d = _ttoi(green2);

	CString blue2;
	pObject->GetDlgItemText(IDC_EDIT7, blue2);
	std::string b2 = std::string(CStringA(blue2));
	double blue2d = _ttoi(blue2);

	CString red3;
	pObject->GetDlgItemText(IDC_EDIT8, red3);
	std::string r3 = std::string(CStringA(red3));
	double red3d = _ttoi(red3);

	CString green3;
	pObject->GetDlgItemText(IDC_EDIT9, green3);
	std::string g3 = std::string(CStringA(green3));
	double green3d = _ttoi(green3);

	CString blue3;
	pObject->GetDlgItemText(IDC_EDIT10, blue3);
	std::string b3 = std::string(CStringA(blue3));
	double blue3d = _ttoi(blue3);

	CString red4;
	pObject->GetDlgItemText(IDC_EDIT11, red4);
	std::string r4 = std::string(CStringA(red4));
	double red4d = _ttoi(red4);

	CString green4;
	pObject->GetDlgItemText(IDC_EDIT12, green4);
	std::string g4 = std::string(CStringA(green4));	
	double green4d = _ttoi(green4);

	CString blue4;
	pObject->GetDlgItemText(IDC_EDIT13, blue4);
	std::string b4 = std::string(CStringA(blue4));
	double blue4d = _ttoi(blue4);

	//Zoom Coordinates
	CString zoom1s1;
	pObject->GetDlgItemText(IDC_EDIT14, zoom1s1);
	int zoom1int1 = _ttoi(zoom1s1);
	std::string z1int = std::string(CStringA(zoom1s1));

	CString zoom1s2;
	pObject->GetDlgItemText(IDC_EDIT15, zoom1s2);
	int zoom1int2 = _ttoi(zoom1s2);
	std::string z1int2 = std::string(CStringA(zoom1s2));

	CString zoom2s1;
	pObject->GetDlgItemText(IDC_EDIT16, zoom2s1);
	int zoom2int1 = _ttoi(zoom2s1);
	std::string z2int = std::string(CStringA(zoom2s1));

	CString zoom2s2;
	pObject->GetDlgItemText(IDC_EDIT17, zoom2s2);
	int zoom2int2 = _ttoi(zoom2s2);
	std::string z2int2 = std::string(CStringA(zoom2s2));

	//Validation
	if (pObject->isNumber(b4) == false || pObject->isNumber(g4) == false || pObject->isNumber(r1) == false) {
		pObject->m_output = "You need to enter a valid number between 0 - 255 !";
		pObject->SetDlgItemText(IDC_OUTPUT, pObject->m_output);
		CWnd* okbtn = pObject->GetDlgItem(IDC_BTNCOMPILE);
		if (okbtn) {
			okbtn->EnableWindow(TRUE);
		}
		stopNow = TRUE;
		//Stop the application Thread.
		pObject->KillTimer(1234);
		return 0;
	}

	if (pObject->isNumber(b3) == false || pObject->isNumber(g3) == false || pObject->isNumber(r3) == false) {
		pObject->m_output = "You need to enter a valid number between 0 - 255 !";
		pObject->SetDlgItemText(IDC_OUTPUT, pObject->m_output);
		CWnd* okbtn = pObject->GetDlgItem(IDC_BTNCOMPILE);
		if (okbtn) {
			okbtn->EnableWindow(TRUE);
		}
		stopNow = TRUE;
		//Stop the application Thread.
		pObject->KillTimer(1234);
		return 0;
	}

	if (pObject->isNumber(b2) == false || pObject->isNumber(g2) == false || pObject->isNumber(r2) == false) {
		pObject->m_output = "You need to enter a valid number between 0 - 255 !";
		pObject->SetDlgItemText(IDC_OUTPUT, pObject->m_output);
		CWnd* okbtn = pObject->GetDlgItem(IDC_BTNCOMPILE);
		if (okbtn) {
			okbtn->EnableWindow(TRUE);
		}
		stopNow = TRUE;
		//Stop the application Thread.
		pObject->KillTimer(1234);
		return 0;
	}

	if (pObject->isNumber(b1) == false || pObject->isNumber(g1) == false || pObject->isNumber(r1) == false) {
		pObject->m_output = "You need to enter a valid number between 0 - 255 !";
		pObject->SetDlgItemText(IDC_OUTPUT, pObject->m_output);
		CWnd* okbtn = pObject->GetDlgItem(IDC_BTNCOMPILE);
		if (okbtn) {
			okbtn->EnableWindow(TRUE);
		}
		stopNow = TRUE;
		//Stop the application Thread.
		pObject->KillTimer(1234);
		return 0;
	}

	CString magnification1;
	pObject->GetDlgItemText(IDC_EDIT18, magnification1);
	CString magnification2;
	pObject->GetDlgItemTextW(IDC_EDIT19, magnification2);
	
	double mag1 = _tstof(magnification1);
	double mag2 = _tstof(magnification2);
	
	CString zoomint1;
	pObject->GetDlgItemText(IDC_EDIT14, zoomint1);
	CString zoomint2;
	pObject->GetDlgItemText(IDC_EDIT15, zoomint2);
	CString zoomint3;
	pObject->GetDlgItemText(IDC_EDIT16, zoomint3);
	CString zoomint4;
	pObject->GetDlgItemText(IDC_EDIT17, zoomint4);
	
	if (zoomint1 != "295" && zoomint2 !="202") {			
		//Convert int to CString!
		std::string outputString = std::to_string(zoom1int1);
		CString cstr(outputString.c_str());
		
		//pObject->m_output = cstr;
		//pObject->SetDlgItemText(IDC_OUTPUT, pObject->m_output);
	}
	if (zoomint3 != "312" && zoomint4 != "304") {
		//Convert int to CString!
		std::string outputString = std::to_string(zoom1int2);
		CString cstr(outputString.c_str());

		//pObject->m_output = cstr;
		//pObject->SetDlgItemText(IDC_OUTPUT, pObject->m_output);
	}
	

	FractalCreator m_fractalCreator(800, 600);

	//Need error checking on GUI min and max range 0.0 - 1.0
	m_fractalCreator.addRange(0.0, RGBb(red1d, green1d, blue1d));
	m_fractalCreator.addRange(0.3, RGBb(red2d, green2d, blue2d));
	m_fractalCreator.addRange(0.5, RGBb(red3d, green3d, blue3d));
	m_fractalCreator.addRange(1.0, RGBb(red4d, green4d, blue4d));

	m_fractalCreator.addZoom(Zoom(zoom1int1, zoom1int2, mag1));
	m_fractalCreator.addZoom(Zoom(zoom2int1, zoom2int2, mag2));

	//Get file path and fix it with extra slashes etc..
	CString cpath;
	pObject->GetDlgItemText(IDC_EDIT1, cpath);
	std::string path = std::string(CStringA(cpath));
	if (path == "") {
			path = "fractal.bmp";
	}
	else {
			for (auto pos = path.find('\\'); pos != string::npos; pos = path.find('\\', ++pos))
				path.insert(++pos, 1, '\\');

			path.append("\\Fractal.bmp");
	}

	//Make filepath for LPCTSTR
	CA2T lpath(path.c_str());
	LPCTSTR str = lpath;

	if (GetFileAttributes(lpath) == INVALID_FILE_ATTRIBUTES) {
		pObject->m_output = "Directory Doesn't exist! Please check your path.";
		pObject->SetDlgItemText(IDC_OUTPUT, pObject->m_output);
		stopNow = TRUE;
		//Stop the application Thread.
		pObject->KillTimer(1234);
			
		CWnd* okbtn = pObject->GetDlgItem(IDC_BTNCOMPILE);
		if (okbtn) {
				okbtn->EnableWindow(TRUE);
		}
	}
		else {
			m_fractalCreator.run(path);			
			stopNow = TRUE;
			//Stop the application Thread.
			pObject->KillTimer(1234);
			pObject->m_output = "Fractal Completed!";
			pObject->SetDlgItemText(IDC_OUTPUT, pObject->m_output);
			pObject->ChangeStaticCtrl(str, IDC_BMP);

			CWnd* okbtn = pObject->GetDlgItem(IDC_BTNCOMPILE);
			if (okbtn) {
				okbtn->EnableWindow(TRUE);
			}

			pObject->updateImage(str);

			return 0;


		}	
}


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMandelbrotExperimentDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMandelbrotExperimentDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//Hover handler to display coordinates when moving the mouse over the preview image.
void brightland::CMandelbrotExperimentDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	//Get the Picture Control's Rect To check
	CRect rect;
	m_pic.GetWindowRect(rect);
	ScreenToClient(&rect);

	//Store The Cursor Position
	CPoint pt;
	GetCursorPos(&pt);

	//Make it as LPARAM and send it
	LPARAM lp = MAKELPARAM(pt.x, pt.y);
	if (rect.PtInRect(point))
	{
		m_pic.SendMessage(WM_MOUSEMOVE, 0, lp);
	}

	CDialog::OnMouseMove(nFlags, point);
}

//Click Handler for when the user double clicks within the preview window.
void brightland::CMandelbrotExperimentDlg::OnMButtonDblClk(UINT nFlags, CPoint point)
{
	//Get the Picture Control's Rect To check
	CRect rect;
	m_pic.GetWindowRect(rect);
	ScreenToClient(&rect);

	//Store The Cursor Position
	CPoint pt;
	GetCursorPos(&pt);

	//Make it as LPARAM and send it
	LPARAM lp = MAKELPARAM(pt.x, pt.y);
	if (rect.PtInRect(point))
	{
		m_output = "Double Click";
		SetDlgItemText(IDC_OUTPUT, m_output);
		m_pic.SendMessage(WM_MBUTTONDBLCLK, 0, lp);
	}

	//Do it again!
	CDialog::OnMButtonDblClk(nFlags, point);	
}

void brightland::CMandelbrotExperimentDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	//Get the Picture Control's Rect To check
	CRect rect;
	m_pic.GetWindowRect(rect);
	ScreenToClient(&rect);

	//Store The Cursor Position
	CPoint pt;
	GetCursorPos(&pt);

	//Make it as LPARAM and send it
	LPARAM lp = MAKELPARAM(pt.x, pt.y);
	if (rect.PtInRect(point))
	{
		//m_output = "Double Click";
		SetDlgItemText(IDC_OUTPUT, m_output);
		m_pic.SendMessage(WM_LBUTTONDBLCLK, 0, lp);
	}

	CDialog::OnLButtonDblClk(nFlags, point);
}
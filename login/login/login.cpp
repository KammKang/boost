// login.cpp : main source file for login.exe
//

#include "stdafx.h"

#include "resource.h"

#include "MainDlg.h"
#include "MainFrm.h"
CAppModule _Module;



int Run(LPSTR lpCmdLine = NULL, int nCmdShow = SW_SHOWDEFAULT)
{
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	CMDIFrame wndMain;

	if (wndMain.CreateEx() == NULL)
	{
		ATLTRACE(_T("Main window creation failed!\n"));
		return 0;
	}

	wndMain.ShowWindow(nCmdShow);

	int nRet = theLoop.Run();

	_Module.RemoveMessageLoop();
	return nRet;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR lpCmdLine, int nCmdShow)
{
	HRESULT hRes = ::CoInitialize(NULL);
	ATLASSERT(SUCCEEDED(hRes));

	AtlInitCommonControls(ICC_BAR_CLASSES);	// add flags to support other controls

	hRes = _Module.Init(NULL, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	// login moudle;
	int nRet = 0;
	// BLOCK: Run application
	{
		CMainDlg dlgMain;
		nRet = (int)dlgMain.DoModal();
	}

	if(nRet )
	{
		//WinMain.run();
		Run(lpCmdLine, nCmdShow);
		
	}
	
	_Module.Term();
	::CoUninitialize();

	return nRet;
}

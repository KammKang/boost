#pragma once

#include <atlctrls.h>
#include <atlctrlw.h>
#include "stdafx.h"

#include "../../../../Samples/MDIDocVw/resource.h"

class CHelloView : public CWindowImpl<CHelloView>
{
public:
	COLORREF m_clrText;

	//state of color buttons
	BOOL m_bBlack;
	BOOL m_bRed;
	BOOL m_bBlue;
	BOOL m_bGreen;
	BOOL m_bWhite;
	BOOL m_bCustom;

	CUpdateUIBase* m_pUpdateUI;

	CHelloView(CUpdateUIBase* pUpdateUI) : m_clrText(RGB(0, 0, 0)),
		m_bBlack(TRUE),
		m_bRed(FALSE),
		m_bBlue(FALSE),
		m_bGreen(FALSE),
		m_bWhite(FALSE),
		m_bCustom(FALSE),
		m_pUpdateUI(pUpdateUI)
	{ }

	DECLARE_WND_CLASS(NULL)

	void ClearAllColors()
	{
		m_bBlack = m_bBlue = m_bRed = FALSE;
		m_bWhite = m_bGreen = FALSE;
	}


	

	virtual void OnFinalMessage(HWND /*hWnd*/)
	{
		delete this;
	}

	BEGIN_MSG_MAP(CHelloView)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
	END_MSG_MAP()

	LRESULT OnPaint(UINT, WPARAM, LPARAM, BOOL&)
	{
		CPaintDC dc(m_hWnd);

		RECT rect;
		GetClientRect(&rect);
		dc.SetTextColor(m_clrText);
		dc.SetBkColor(::GetSysColor(COLOR_WINDOW));
		dc.DrawText(_T("Hello, ATL"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

		return 0;
	}



};
class CHelloWnd : public CMDIChildWindowImpl<CHelloWnd>
{
public:
	CHelloView* m_pView;
	CUpdateUIBase* m_pUpdateUI;


	CHelloWnd(CUpdateUIBase* pUpdateUI) : m_pView(NULL), m_pUpdateUI(pUpdateUI)
	{ }
	DECLARE_FRAME_WND_CLASS(NULL, IDR_HELLOTYPE)

	virtual void OnFinalMessage(HWND /*hWnd*/)
	{
		delete this;
	}

	BEGIN_MSG_MAP(CHelloWnd)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		CHAIN_CLIENT_COMMANDS()
		CHAIN_MSG_MAP(CMDIChildWindowImpl<CHelloWnd>)
	END_MSG_MAP()

	LRESULT OnCreate(UINT, WPARAM, LPARAM lParam, BOOL& bHandled)
	{
		m_pView = new CHelloView(m_pUpdateUI);
		RECT rect = { 0, 0, 1, 1 };
		// m_hWndClient = 当前客户区窗口
		m_hWndClient = m_pView->Create(m_hWnd, rect, NULL, WS_CHILD | WS_VISIBLE, WS_EX_CLIENTEDGE);

		bHandled = FALSE;
		return 1;
	}
};
class CMDIFrame : public CMDIFrameWindowImpl<CMDIFrame>, CUpdateUI<CMDIFrame>,
	public CMessageFilter, public CIdleHandler
{
public:
	CMDICommandBarCtrl m_CmdBar;
	//DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)

	CMDIFrame():m_wnd_h_hello_wnd_1((CUpdateUIBase*)this), m_wnd_h_hello_wnd_2((CUpdateUIBase*)this), m_wnd_h_hello_wnd_3((CUpdateUIBase*)this)
	{
		
	};
	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		return CMDIFrameWindowImpl<CMDIFrame>::PreTranslateMessage(pMsg);
	}

	virtual BOOL OnIdle()
	{
		UIUpdateToolBar();
		return FALSE;
	}
	
	BEGIN_MSG_MAP(CMDIFrame)
		MESSAGE_HANDLER(WM_CREATE,OnCreate)
	END_MSG_MAP()
	BEGIN_UPDATE_UI_MAP(CMainFrame)
	END_UPDATE_UI_MAP()
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		CreateMDIClient();

		HWND hWndCmdBar = m_CmdBar.Create(m_hWnd, rcDefault, NULL, ATL_SIMPLE_CMDBAR_PANE_STYLE);
		m_CmdBar.Create(m_hWnd, rcDefault, NULL, ATL_SIMPLE_CMDBAR_PANE_STYLE);
		m_CmdBar.SetMDIClient(m_hWndClient);
		m_CmdBar.AttachMenu(GetMenu());
		SetMenu(NULL);

		// Create Toolbar
		HWND hWndToolBar = CreateSimpleToolBarCtrl(m_hWnd, IDR_MAINFRAME, FALSE, ATL_SIMPLE_TOOLBAR_PANE_STYLE);
			CreateSimpleReBar(ATL_SIMPLE_REBAR_NOBORDER_STYLE);
		AddSimpleReBarBand(m_CmdBar);
		AddSimpleReBarBand(hWndToolBar, NULL, TRUE);

		UIAddToolBar(hWndToolBar);

		// Create Rebar
	
		

		m_wnd_h_hello_wnd_1.CreateEx(m_hWndClient, NULL, _T("Hello"));
		CMessageLoop* pLoop = _Module.GetMessageLoop();
		pLoop->AddMessageFilter(this);
		pLoop->AddIdleHandler(this);
		
		return 0;
	};
	
	
private:
	CHelloWnd m_wnd_h_hello_wnd_1;
	CHelloWnd m_wnd_h_hello_wnd_2;

	CHelloWnd m_wnd_h_hello_wnd_3;

};

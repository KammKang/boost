// ChildFrm.cpp : implementation of the CChildFrame class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "View.h"
#include "ChildFrm.h"

void CChildFrame::OnFinalMessage(HWND /*hWnd*/)
{
	delete this;
}
BOOL CChildFrame::PreTranslateMessage(MSG* pMsg)
{
	if (CMDIChildWindowImpl<CChildFrame>::PreTranslateMessage(pMsg))
		return TRUE;

	HWND hWnd = MDIGetActive();
	if (hWnd != NULL)
		return (BOOL)::SendMessage(hWnd, WM_FORWARDMSG, 0, (LPARAM)pMsg);

	return FALSE;
}

BOOL CChildFrame::OnIdle()
{
	return FALSE;
}

LRESULT CChildFrame::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{

	bHandled = FALSE;
	
	return 1;
}
LRESULT CChildFrame::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	m_hWndClient = m_view.Create(m_hWndClient, rcDefault, NULL, 
		WS_CHILD | /*WS_CLIPSIBLINGS | WS_CLIPCHILDREN| */WS_MINIMIZE| WS_HSCROLL| WS_VSCROLL,
		WS_EX_CLIENTEDGE);

	bHandled = FALSE;
	return 1;
}


LRESULT CChildFrame::OnForwardMsg(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& /*bHandled*/)
{
	LPMSG pMsg = (LPMSG)lParam;

	if(CMDIChildWindowImpl<CChildFrame>::PreTranslateMessage(pMsg))
		return TRUE;

	return m_view.PreTranslateMessage(pMsg);
}

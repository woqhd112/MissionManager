// MissionTimer.cpp: 구현 파일
//

#include "pch.h"
#include "MissionManager.h"
#include "MissionTimer.h"
#include "afxdialogex.h"


// MissionTimer 대화 상자

IMPLEMENT_DYNAMIC(MissionTimer, CDialogEx)

MissionTimer::MissionTimer(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MISSION_TIMER_DIALOG, pParent)
{
	this->pParent = pParent;
	bStart = true;
	bThread = false;
	bSoundThread = false;
}

MissionTimer::~MissionTimer()
{
	PlaySound(NULL, AfxGetInstanceHandle(), NULL);
	if (bThread)
	{
		bThread = false;
		DWORD nExitCode = NULL;
		DWORD nExitSoundCode = NULL;
		if (bSoundThread)
		{
			bSoundThread = false;
			GetExitCodeThread(m_soundThread->m_hThread, &nExitSoundCode);
			if (TerminateThread(m_soundThread->m_hThread, nExitSoundCode) != 0)
			{
				delete m_soundThread;
				m_soundThread = nullptr;
			}
		}

		GetExitCodeThread(m_thread->m_hThread, &nExitCode);
		if (TerminateThread(m_thread->m_hThread, nExitCode) != 0)
		{
			delete m_thread;
			m_thread = nullptr;
		}
	}

}

void MissionTimer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TIMER_PICTURE, m_stt_picture);
	DDX_Control(pDX, IDC_EDIT_TIMER_MINUTE, m_edit_minute);
	DDX_Control(pDX, IDC_EDIT_TIMER_SECOND, m_edit_second);
	DDX_Control(pDX, IDC_STATIC_TIMER_EQUAL, m_stt_equal);
	DDX_Control(pDX, IDC_BUTTON_TIMER_START, m_btn_start);
	DDX_Control(pDX, IDC_BUTTON_TIMER_RESET, m_btn_reset);
}


BEGIN_MESSAGE_MAP(MissionTimer, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_TIMER_START, &MissionTimer::OnBnClickedButtonTimerStart)
	ON_BN_CLICKED(IDC_BUTTON_TIMER_RESET, &MissionTimer::OnBnClickedButtonTimerReset)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// MissionTimer 메시지 처리기


BOOL MissionTimer::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_backBrush.CreateSolidBrush(RGB(0, 0, 0));

	this->SetWindowPos(NULL, 0, 0, 260, 210, SWP_NOMOVE);

	m_stt_picture.MoveWindow(20, 20, 200, 90);
	drawBorderRect = { 19, 19, 202 + 19, 92 + 19 };

	m_edit_minute.MoveWindow(25, 25, 80, 80);
	m_stt_equal.MoveWindow(110, 25, 20, 80);
	m_edit_second.MoveWindow(135, 25, 80, 80);

	m_btn_start.MoveWindow(20, 120, 95, 30);
	m_btn_reset.MoveWindow(125, 120, 95, 30);

	m_btn_start.Initialize(RGB(220, 220, 220), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("Tahoma"), 15, FW_BOLD);
	m_btn_reset.Initialize(RGB(220, 220, 220), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("Tahoma"), 15, FW_BOLD);

	m_edit_minute.Initialize(55, _T("DS-Digital"));
	m_edit_second.Initialize(55, _T("DS-Digital"));

	m_stt_equal.Initialize(55, _T("DS-Digital"));

	m_stt_picture.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_equal.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_edit_minute.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_edit_second.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);

	m_stt_equal.BringWindowToTop();
	m_edit_minute.BringWindowToTop();
	m_edit_second.BringWindowToTop();

	m_edit_minute.SetWindowTextW(_T("00"));
	m_edit_second.SetWindowTextW(_T("00"));
	m_btn_start.SetFocus();

	m_edit_minute.LimitText(2);
	m_edit_second.LimitText(2);

	return FALSE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void MissionTimer::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}


BOOL MissionTimer::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			if (pMsg->hwnd == m_edit_minute.m_hWnd)
			{
				m_edit_minute.HideCaret();
			}
			else if (pMsg->hwnd == m_edit_second.m_hWnd)
			{
				m_edit_second.HideCaret();
			}
		}
		else if (pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void MissionTimer::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnClose();
}


HBRUSH MissionTimer::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		if (pWnd->GetDlgCtrlID() == IDC_STATIC_TIMER_PICTURE)
		{
			CRect rect;
			GetClientRect(&rect);

			CDC* pDC = m_stt_picture.GetWindowDC();
			CBrush *pOld = pDC->SelectObject(&m_backBrush);
			pDC->PatBlt(0, 0, rect.Width(), rect.Height(), PATCOPY);
			pDC->SelectObject(pOld);
			hbr = (HBRUSH)m_backBrush;
		}
		else if (pWnd->GetDlgCtrlID() == IDC_STATIC_TIMER_EQUAL)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkColor(RGB(0, 0, 0));
			hbr = (HBRUSH)m_backBrush;
		}
		else if (pWnd->GetDlgCtrlID() == IDC_EDIT_TIMER_MINUTE)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkColor(RGB(0, 0, 0));
			hbr = (HBRUSH)m_backBrush;
		}
		else if (pWnd->GetDlgCtrlID() == IDC_EDIT_TIMER_SECOND)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkColor(RGB(0, 0, 0));
			hbr = (HBRUSH)m_backBrush;
		}
	}
	else if (nCtlColor == CTLCOLOR_EDIT)
	{
		if (pWnd->GetDlgCtrlID() == IDC_EDIT_TIMER_MINUTE)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkColor(RGB(0, 0, 0));
			hbr = (HBRUSH)m_backBrush;
		}
		else if (pWnd->GetDlgCtrlID() == IDC_EDIT_TIMER_SECOND)
		{
			pDC->SetTextColor(RGB(255, 255, 255));
			pDC->SetBkColor(RGB(0, 0, 0));
			hbr = (HBRUSH)m_backBrush;
		}
	}
	else
	{
		hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void MissionTimer::OnBnClickedButtonTimerStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (bStart)
	{
		bStart = false;
		bThread = true;
		m_btn_start.SetWindowTextW(_T("정지"));
		m_btn_reset.EnableWindow(FALSE);
		m_edit_minute.EnableWindow(FALSE);
		m_edit_second.EnableWindow(FALSE);
		m_thread = AfxBeginThread(thrBaseTimer, this);
	}
	else
	{
		ResetDefaultValue();
		DeleteMainThread();
	}
}


void MissionTimer::OnBnClickedButtonTimerReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_edit_minute.SetWindowTextW(_T("00"));
	m_edit_second.SetWindowTextW(_T("00"));
}

UINT MissionTimer::thrBaseTimer(LPVOID method)
{
	MissionTimer* timer = (MissionTimer*)method;
	timer->StartBaseTimer();

	return 0;
}

UINT MissionTimer::thrLoadSound(LPVOID method)
{
	MissionTimer* timer = (MissionTimer*)method;
	timer->StartSound(IDR_WAVE_ALARM);

	return 0;
}

void MissionTimer::StartSound(int nSoundResourceID)
{
	PlaySound(MAKEINTRESOURCE(nSoundResourceID), AfxGetInstanceHandle(), SND_ASYNC | SND_RESOURCE);
	bSoundThread = false;
}

void MissionTimer::ResetDefaultValue()
{
	bStart = true;
	bThread = false;
	m_btn_start.SetWindowTextW(_T("시작"));
	m_btn_reset.EnableWindow(TRUE);
	m_edit_minute.EnableWindow(TRUE);
	m_edit_second.EnableWindow(TRUE);
}

void MissionTimer::StartBaseTimer()
{
	while (bThread)
	{
		clock_t start, finish;
		double duration;

		start = clock();

		CString strM, strS;
		m_edit_minute.GetWindowTextW(strM);
		m_edit_second.GetWindowTextW(strS);
		int m = _ttoi(strM);
		int s = _ttoi(strS);

		if (m <= 0 && s <= 0)
		{
			ResetDefaultValue();
			break;
		}
		else if (m > 0 && s <= 0)
		{
			m--;
			s = 59;
		}
		else if (s > 0)
		{
			s--;
		}

		if (m <= 0 && s <= 0)
		{
			// 종료 소리 실행 함수
			// func
			bSoundThread = true;
			m_edit_minute.SetWindowTextW(_T("00"));
			m_edit_second.SetWindowTextW(_T("00"));
			for (int i = 0; i < 20; i++)
			{
				m_soundThread = AfxBeginThread(thrLoadSound, this);
				Sleep(6000);
			}
			ResetDefaultValue();
			break;
		}

		strM.Format(_T("%02d"), m);
		strS.Format(_T("%02d"), s);
		m_edit_minute.SetWindowTextW(strM);
		m_edit_second.SetWindowTextW(strS);

		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		Sleep((1000 - (duration * 1000) <= 0) ? DWORD(0) : DWORD(1000 - (duration * 1000)));
	}
}

bool MissionTimer::DeleteMainThread()
{
	PlaySound(NULL, AfxGetInstanceHandle(), NULL);
	DWORD nExitCode = NULL;

	GetExitCodeThread(m_thread->m_hThread, &nExitCode);
	if (TerminateThread(m_thread->m_hThread, nExitCode) != 0)
	{
		delete m_thread;
		m_thread = nullptr;
		return true;
	}
	return false;
}


void MissionTimer::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	dc.Draw3dRect(drawBorderRect, RGB(0,0,0), RGB(0,0,0));

	CBrush *pOld = dc.SelectObject(&m_backBrush);
	dc.PatBlt(drawBorderRect.left + 1, drawBorderRect.top + 1, drawBorderRect.Width() - 2, drawBorderRect.Height() - 2, PATCOPY);
	dc.SelectObject(pOld);
}

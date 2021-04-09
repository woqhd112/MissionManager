// MissionCountSetting.cpp: 구현 파일
//

#include "pch.h"
#include "MissionManager.h"
#include "MissionCountSetting.h"
#include "afxdialogex.h"


// MissionCountSetting 대화 상자

IMPLEMENT_DYNAMIC(MissionCountSetting, CDialogEx)

MissionCountSetting::MissionCountSetting(int* nOut, int* nSheild, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MISSION_COUNT_SETTING_DIALOG, pParent)
{
	this->nOut = nOut;
	this->nSheild = nSheild;
	this->pParent = pParent;
}

MissionCountSetting::~MissionCountSetting()
{
}

void MissionCountSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_COUNT_GROUP, m_stt_group_count);
	DDX_Control(pDX, IDC_STATIC_COUNT_OUT, m_stt_out);
	DDX_Control(pDX, IDC_STATIC_COUNT_SHEILD, m_stt_sheild);
	DDX_Control(pDX, IDC_EDIT_COUNT_OUT, m_edit_out);
	DDX_Control(pDX, IDC_EDIT_COUNT_SHEILD, m_edit_sheild);
	DDX_Control(pDX, IDC_BUTTON_COUNT_SAVE, m_btn_save_close);
}


BEGIN_MESSAGE_MAP(MissionCountSetting, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_COUNT_SAVE, &MissionCountSetting::OnBnClickedButtonCountSave)
END_MESSAGE_MAP()


// MissionCountSetting 메시지 처리기


BOOL MissionCountSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	this->SetWindowPos(NULL, 0, 0, 200, 250, SWP_NOMOVE);

	m_stt_group_count.MoveWindow(10, 10, 160, 150);
	m_stt_out.MoveWindow(30, 50, 30, 30);
	m_stt_sheild.MoveWindow(30, 100, 30, 30);
	m_edit_out.MoveWindow(80, 45, 70, 25);
	m_edit_sheild.MoveWindow(80, 95, 70, 25);
	m_btn_save_close.MoveWindow(70, 170, 100, 30);

	m_btn_save_close.Initialize(RGB(220, 220, 220), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("Tahoma"), 15, FW_BOLD);
	m_stt_out.Initialize(15, _T("Tahoma"));
	m_stt_sheild.Initialize(15, _T("Tahoma"));
	m_edit_out.Initialize(20, _T("Tahoma"));
	m_edit_sheild.Initialize(20, _T("Tahoma"));

	CString strOut, strSheild;
	strOut.Format(_T("%d"), *nOut);
	strSheild.Format(_T("%d"), *nSheild);

	m_edit_out.SetWindowTextW(strOut);
	m_edit_sheild.SetWindowTextW(strSheild);

	m_edit_out.LimitText(3);
	m_edit_sheild.LimitText(3);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void MissionCountSetting::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}


BOOL MissionCountSetting::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN) // ENTER키 눌릴 시
			return TRUE;
		else if (pMsg->wParam == VK_ESCAPE) // ESC키 눌릴 시
			return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void MissionCountSetting::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnOK();
	//CDialogEx::OnClose();
}


HBRUSH MissionCountSetting::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void MissionCountSetting::OnBnClickedButtonCountSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString strOutCount, strSheildCount;

	m_edit_out.GetWindowTextW(strOutCount);
	m_edit_sheild.GetWindowTextW(strSheildCount);

	*nOut = _ttoi(strOutCount);
	*nSheild = _ttoi(strSheildCount);

	PostMessage(WM_CLOSE);
}

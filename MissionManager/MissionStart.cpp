// MissionStart.cpp: 구현 파일
//

#include "pch.h"
#include "MissionManager.h"
#include "MissionStart.h"
#include "RandomProcess.h"
#include "afxdialogex.h"


// MissionStart 대화 상자

IMPLEMENT_DYNAMIC(MissionStart, CDialogEx)

MissionStart::MissionStart(MissionVersionItem* currentMissionVersionItem, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MISSION_START_DIALOG, pParent)
{
	this->currentMissionVersionItem = currentMissionVersionItem;
	this->pParent = pParent;

	curentMissionList = currentMissionVersionItem->GetMission();
	nMissionCount = 0;
}

MissionStart::~MissionStart()
{
	if (missionListCtrl)
	{
		delete missionListCtrl;
		missionListCtrl = nullptr;
	}
}

void MissionStart::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_START_EXTRACT, m_btn_mission_extract);
	DDX_Control(pDX, IDC_STATIC_MISSION_PERFORMER, m_stt_mission_performer);
	DDX_Control(pDX, IDC_EDIT_MISSION_PERFORMER, m_edit_mission_performer);
	DDX_Control(pDX, IDC_BUTTON_TIMER, m_btn_timer);
	DDX_Control(pDX, IDC_STATIC_HAVING_MISSION, m_stt_having_mission);
	DDX_Control(pDX, IDC_STATIC_HAVING_SHEILD, m_stt_having_sheild);
	DDX_Control(pDX, IDC_BUTTON_SHEILD_EXTRACT, m_btn_sheild_extract);
}


BEGIN_MESSAGE_MAP(MissionStart, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_START_EXTRACT, &MissionStart::OnBnClickedButtonStartExtract)
	ON_BN_CLICKED(IDC_BUTTON_SHEILD_EXTRACT, &MissionStart::OnBnClickedButtonSheildExtract)
END_MESSAGE_MAP()


// MissionStart 메시지 처리기


BOOL MissionStart::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	this->SetWindowPos(NULL, 0, 0, 500, 700, SWP_NOMOVE);

	m_stt_having_mission.MoveWindow(10, 80, 230, 20);
	m_stt_having_sheild.MoveWindow(240, 80, 230, 20);

	missionListCtrl = new MissionListCtrl(curentMissionList, this);
	missionListCtrl->Create(IDD_MISSIONLIST_DIALOG, this);
	missionListCtrl->ShowWindow(SW_SHOW);
	missionListCtrl->MoveWindow(10, 100, 460, 314);

	m_btn_mission_extract.MoveWindow(20, 430, 100, 30);
	m_btn_sheild_extract.MoveWindow(140, 430, 100, 30);
	m_btn_timer.MoveWindow(260, 430, 100, 30);
	m_stt_mission_performer.MoveWindow(20, 480, 100, 20);
	m_edit_mission_performer.MoveWindow(120, 475, 200, 25);

	m_btn_mission_extract.Initialize(RGB(220, 220, 220), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("Tahoma"), 15, FW_BOLD);
	m_btn_sheild_extract.Initialize(RGB(220, 220, 220), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("Tahoma"), 15, FW_BOLD);
	m_btn_timer.Initialize(RGB(220, 220, 220), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("Tahoma"), 15, FW_BOLD);
	m_stt_mission_performer.Initialize(15, _T("Tahoma"));
	m_edit_mission_performer.Initialize(20, _T("Tahoma"));

	m_stt_having_mission.SetWindowTextW(_T("보유중인 미션 : 0"));
	m_stt_having_sheild.SetWindowTextW(_T("보유중인 실드 : 0"));

	missionManager = (CMissionManagerDlg*)pParent;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void MissionStart::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}


BOOL MissionStart::PreTranslateMessage(MSG* pMsg)
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


void MissionStart::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnClose();
}


HBRUSH MissionStart::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void MissionStart::OnBnClickedButtonStartExtract()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


	CString strMissionUserName;

	m_edit_mission_performer.GetWindowTextW(strMissionUserName);

	if (strMissionUserName.IsEmpty())
	{
		AfxMessageBox(_T("수행자를 입력 해 주세요."), MB_OK | MB_ICONSTOP);
		m_edit_mission_performer.SetFocus();
		return;
	}

	// 랜덤 함수 
	RandomProcess random;
	int nRandomValue = random.Random(0, curentMissionList.size() - 1);

	// 우선 테스트용으로 첫번째 값으로 설정
	MissionItem* extractMission = curentMissionList.at(nRandomValue);

	if (extractMission->GetEvent()->GetEventType() == 3)
	{
		CString strSheild;
		int nSheildCount = sheildList.size();
		strSheild.Format(_T("%d"), nSheildCount + 1);
		m_stt_having_sheild.SetWindowTextW(_T("보유중인 실드 : ") + strSheild);
		sheildList.push_back(extractMission);

		return;
	}

	missionListCtrl->InsertItem(extractMission, strMissionUserName);
	nMissionCount++;
	CString strMissionCount;
	strMissionCount.Format(_T("보유중인 미션 : %d"), nMissionCount);
	m_stt_having_mission.SetWindowTextW(strMissionCount);
}


void MissionStart::OnBnClickedButtonSheildExtract()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (sheildList.size() == 0)
	{
		AfxMessageBox(_T("뽑은 실드가 없습니다."), MB_OK | MB_ICONSTOP);
		return;
	} 

	// 랜덤 함수 

	// 임의로 설정함
	int nSheildIndex = 0;

	sheildList.erase(sheildList.begin() + nSheildIndex);

	CString strSheild;
	int nSheildCount = sheildList.size();
	strSheild.Format(_T("%d"), nSheildCount);
	m_stt_having_sheild.SetWindowTextW(_T("보유중인 실드 : ") + strSheild);
}

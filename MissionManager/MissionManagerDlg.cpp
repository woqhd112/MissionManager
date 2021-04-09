
// MissionManagerDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MissionManager.h"
#include "MissionManagerDlg.h"
#include "AllVersionListDlg.h"
#include "MissionManage.h"
#include "MissionStart.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMissionManagerDlg 대화 상자



CMissionManagerDlg::CMissionManagerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MISSIONMANAGER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CMissionManagerDlg::~CMissionManagerDlg()
{
	for (int i = 0; i < (int)cVersionList.size(); i++)
	{
		MissionVersionItem* deleteVersionItem = cVersionList.at(i);
		delete deleteVersionItem;
		deleteVersionItem = nullptr;
	}
}

void CMissionManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_MAIN_MISSION_START, m_btn_mission_start);
	DDX_Control(pDX, IDC_BUTTON_MAIN_MISSION_MANAGE, m_btn_mission_manage);
	DDX_Control(pDX, IDC_BUTTON_MAIN_VERSION_SELECT, m_btn_version_select);
	DDX_Control(pDX, IDC_STATIC_VERSION_NAME, m_stt_version_name);
	DDX_Control(pDX, IDC_LIST_MAIN_MISSION_LIST, m_list_mission_list);
}

BEGIN_MESSAGE_MAP(CMissionManagerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_MAIN_VERSION_SELECT, &CMissionManagerDlg::OnBnClickedButtonMainVersionSelect)
	ON_BN_CLICKED(IDC_BUTTON_MAIN_MISSION_MANAGE, &CMissionManagerDlg::OnBnClickedButtonMainMissionManage)
	ON_BN_CLICKED(IDC_BUTTON_MAIN_MISSION_START, &CMissionManagerDlg::OnBnClickedButtonMainMissionStart)
END_MESSAGE_MAP()


// CMissionManagerDlg 메시지 처리기

BOOL CMissionManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	this->SetWindowPos(NULL, 0, 0, 400, 600, SWP_NOMOVE);
	//this->SetBackgroundColor(RGB(0, 0, 0));

	m_btn_mission_start.Initialize(RGB(220, 220, 220), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("Tahoma"), 15, FW_BOLD);
	m_btn_mission_manage.Initialize(RGB(220, 220, 220), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("Tahoma"), 15, FW_BOLD);
	m_btn_version_select.Initialize(RGB(220, 220, 220), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("Tahoma"), 15, FW_BOLD);
	m_stt_version_name.Initialize(20, _T("Tahoma"));
	InitList();

	m_btn_mission_start.MoveWindow(20, 20, 100, 30);
	m_btn_mission_manage.MoveWindow(140, 20, 100, 30);
	m_btn_version_select.MoveWindow(260, 20, 100, 30);
	m_stt_version_name.MoveWindow(20, 70, 300, 20);
	m_list_mission_list.MoveWindow(20, 100, 340, 400);

	// 버전 로드
	LoadVersionList();

	CString strDefaultVersionName = _T("버전 이름");
	if (!cVersionList.empty())
	{
		strDefaultVersionName = cVersionList.at(0)->GetVersionName();
	}
	m_stt_version_name.SetWindowTextW(strDefaultVersionName);

	ViewVersion(cVersionList.at(0));

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMissionManagerDlg::InitList()
{
	CImageList imgGap;
	imgGap.Create(1, 30, ILC_COLORDDB, 1, 0);
	m_list_mission_list.SetImageList(&imgGap, LVSIL_SMALL);

	m_list_mission_list.InsertColumn(0, _T("번호"), LVCFMT_CENTER, 50);
	m_list_mission_list.InsertColumn(1, _T("미션명"), LVCFMT_LEFT, 300);

	m_list_mission_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER | LVS_EX_GRIDLINES);
}

void CMissionManagerDlg::ViewVersion(MissionVersionItem* cVersion)
{
	MissionList missionList = cVersion->GetMission();
	cCurrentMissionVersionItem = cVersion;
	m_list_mission_list.DeleteAllItems();
	if (!missionList.empty())
	{
		for (int i = 0; i < (int)missionList.size(); i++)
		{
			CString strSeq;
			strSeq.Format(_T("%d"), missionList.at(i)->GetMissionSequence());
			m_list_mission_list.InsertItem(i, strSeq);
			m_list_mission_list.SetItemText(i, 1, missionList.at(i)->GetMissionName());
		}


		CString strDefaultVersionName;
		strDefaultVersionName = cVersion->GetVersionName();
		m_stt_version_name.SetWindowTextW(strDefaultVersionName);
	}
}

void CMissionManagerDlg::LoadVersionList()
{
	// 첫번째 버전 하나 테스트로 생성
	MissionVersionItem* newVersion = new MissionVersionItem;
	newVersion->SetVersionName(_T("테스트 버전"));
	MissionList missionList;
	for (int i = 0; i < 100; i++)
	{
		MissionItem* newMission = new MissionItem;

		EventItem* newEvent = new EventItem;
		newEvent->SetEventType(EventItem::EVENT_RANDOM_PRESET);

		RandomTextList newRandomTextList;
		newRandomTextList.push_back(_T("1"));
		newRandomTextList.push_back(_T("2"));
		newRandomTextList.push_back(_T("3"));
		newRandomTextList.push_back(_T("4"));
		newRandomTextList.push_back(_T("5"));

		newEvent->SetRandomTextList(newRandomTextList);

		CString strVersionName;
		strVersionName.Format(_T("테스트%d"), i + 1);
		newMission->SetMissionGrade(1);
		newMission->SetMissionName(strVersionName);
		newMission->SetMissionSequence(i + 1);
		newMission->SetEvent(newEvent);

		missionList.push_back(newMission);
	}
	newVersion->SetMission(missionList);

	cVersionList.push_back(newVersion);



	newVersion = new MissionVersionItem;
	newVersion->SetVersionName(_T("실험 버전"));
	MissionList missionList1;
	for (int i = 0; i < 100; i++)
	{
		MissionItem* newMission = new MissionItem;

		EventItem* newEvent = new EventItem;
		newEvent->SetEventType(EventItem::EVENT_NONE);
		newEvent->SetUsingEvent(false);

		CString strVersionName;
		strVersionName.Format(_T("실험%d"), i + 1);
		newMission->SetMissionGrade(1);
		newMission->SetMissionName(strVersionName);
		newMission->SetMissionSequence(i + 1);
		newMission->SetEvent(newEvent);

		missionList1.push_back(newMission);
	}
	newVersion->SetMission(missionList1);

	cVersionList.push_back(newVersion);
}

void CMissionManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMissionManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMissionManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



HBRUSH CMissionManagerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		if (pWnd->m_hWnd == m_stt_version_name.m_hWnd)
		{
			//pDC->SetTextColor(RGB(255, 255, 255));
		}
	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void CMissionManagerDlg::OnBnClickedButtonMainVersionSelect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CRect thisPos;
	GetWindowRect(thisPos);

	AllVersionListDlg allVersionListDlg(cVersionList, thisPos, this);
	allVersionListDlg.DoModal();
}


void CMissionManagerDlg::OnBnClickedButtonMainMissionManage()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CRect thisPos;
	GetWindowRect(thisPos);

	MissionManage missionManage(cCurrentMissionVersionItem, thisPos, this);
	missionManage.DoModal();
}


BOOL CMissionManagerDlg::PreTranslateMessage(MSG* pMsg)
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


void CMissionManagerDlg::OnBnClickedButtonMainMissionStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	MissionStart missionStart(cCurrentMissionVersionItem, this);
	missionStart.DoModal();
}

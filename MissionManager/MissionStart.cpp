// MissionStart.cpp: 구현 파일
//

#include "pch.h"
#include "MissionManager.h"
#include "MissionStart.h"
#include "RandomProcess.h"
#include "MissionCountSetting.h"
#include "MissionTimer.h"
#include "afxdialogex.h"


// MissionStart 대화 상자

IMPLEMENT_DYNAMIC(MissionStart, CDialogEx)

MissionStart::MissionStart(MissionVersionItem* currentMissionVersionItem, ProgressingMissionStartingData* pmsd /*=nullptr*/, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MISSION_START_DIALOG, pParent)
{
	this->currentMissionVersionItem = currentMissionVersionItem;
	this->pParent = pParent;
	this->pmsd = pmsd;

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

	if (pmsd)
	{
		delete pmsd;
		pmsd = nullptr;
	}

	for (int i = 0; i < (int)curentMissionList.size(); i++)
	{
		curentMissionList.at(i)->SetMissionPerformer(_T(""));
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
	DDX_Control(pDX, IDC_STATIC_MISSION_START_MISSION_VIEW, m_stt_mission_view_picture);
	DDX_Control(pDX, IDC_STATIC_MISSION_START_MISSION_VIEW_STATIC, m_stt_mission_view_static);
	DDX_Control(pDX, IDC_STATIC_START_GROUP_COUNT, m_stt_group_count);
	DDX_Control(pDX, IDC_STATIC_START_OUT_COUNT, m_stt_out_count);
	DDX_Control(pDX, IDC_STATIC_START_SHEILD_COUNT, m_stt_sheild_count);
	DDX_Control(pDX, IDC_STATIC_START_OUT_COUNT_VIEW, m_stt_out_count_view);
	DDX_Control(pDX, IDC_STATIC_START_SHEILD_COUNT_VIEW, m_stt_sheild_count_view);
	DDX_Control(pDX, IDC_BUTTON_START_COUNT_SET, m_btn_count_setting);
	DDX_Control(pDX, IDC_BUTTON_START_OUT_COUNT_UP, m_btn_out_count_up);
	DDX_Control(pDX, IDC_BUTTON_START_OUT_COUNT_DOWN, m_btn_out_count_down);
	DDX_Control(pDX, IDC_BUTTON_START_SHEILD_COUNT_UP, m_btn_sheild_count_up);
	DDX_Control(pDX, IDC_BUTTON_START_SHEILD_COUNT_DOWN, m_btn_sheild_count_down);
	DDX_Control(pDX, IDC_BUTTON_START_SHEILD_UP, m_btn_sheild_up);
}


BEGIN_MESSAGE_MAP(MissionStart, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_START_EXTRACT, &MissionStart::OnBnClickedButtonStartExtract)
	ON_BN_CLICKED(IDC_BUTTON_SHEILD_EXTRACT, &MissionStart::OnBnClickedButtonSheildExtract)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_START_COUNT_SET, &MissionStart::OnBnClickedButtonStartCountSet)
	ON_BN_CLICKED(IDC_BUTTON_START_OUT_COUNT_UP, &MissionStart::OnBnClickedButtonStartOutCountUp)
	ON_BN_CLICKED(IDC_BUTTON_START_OUT_COUNT_DOWN, &MissionStart::OnBnClickedButtonStartOutCountDown)
	ON_BN_CLICKED(IDC_BUTTON_START_SHEILD_COUNT_UP, &MissionStart::OnBnClickedButtonStartSheildCountUp)
	ON_BN_CLICKED(IDC_BUTTON_START_SHEILD_COUNT_DOWN, &MissionStart::OnBnClickedButtonStartSheildCountDown)
	ON_BN_CLICKED(IDC_BUTTON_START_SHEILD_UP, &MissionStart::OnBnClickedButtonStartSheildUp)
	ON_BN_CLICKED(IDC_BUTTON_TIMER, &MissionStart::OnBnClickedButtonTimer)
END_MESSAGE_MAP()


// MissionStart 메시지 처리기


BOOL MissionStart::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_backBrush.CreateSolidBrush(RGB(0, 0, 0));
	currentColor = RGB(255, 255, 255);

	this->SetWindowPos(NULL, 0, 0, 500, 700, SWP_NOMOVE);

	m_stt_group_count.MoveWindow(10, 10, 460, 60);
	m_stt_out_count.MoveWindow(30, 35, 30, 20);
	m_stt_sheild_count.MoveWindow(230, 35, 30, 20);
	m_stt_out_count_view.MoveWindow(60, 35, 100, 20);
	m_stt_sheild_count_view.MoveWindow(260, 35, 100, 20);
	m_btn_count_setting.MoveWindow(430, 25, 30, 30);

	m_btn_out_count_up.MoveWindow(160, 23, 20, 20);
	m_btn_out_count_down.MoveWindow(160, 44, 20, 20);
	m_btn_sheild_count_up.MoveWindow(360, 23, 20, 20);
	m_btn_sheild_count_down.MoveWindow(360, 44, 20, 20);

	m_stt_having_mission.MoveWindow(10, 80, 230, 20);
	m_stt_having_sheild.MoveWindow(240, 80, 230, 20);
	m_btn_sheild_up.MoveWindow(400, 76, 20, 20);

	missionListCtrl = new MissionListCtrl(curentMissionList, this);
	missionListCtrl->Create(IDD_MISSIONLIST_DIALOG, this);
	missionListCtrl->ShowWindow(SW_SHOW);
	missionListCtrl->MoveWindow(10, 100, 460, 314);

	m_btn_mission_extract.MoveWindow(20, 430, 100, 30);
	m_btn_sheild_extract.MoveWindow(140, 430, 100, 30);
	m_btn_timer.MoveWindow(260, 430, 100, 30);
	m_stt_mission_performer.MoveWindow(20, 480, 100, 20);
	m_edit_mission_performer.MoveWindow(120, 475, 200, 25);
	m_stt_mission_view_picture.MoveWindow(10, 510, 460, 120);
	m_stt_mission_view_static.MoveWindow(30, 550, 420, 70);
	viewRect = { 10, 510, 460 + 10, 120 + 510 };

	m_btn_mission_extract.Initialize(RGB(220, 220, 220), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("Tahoma"), 15, FW_BOLD);
	m_btn_sheild_extract.Initialize(RGB(220, 220, 220), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("Tahoma"), 15, FW_BOLD);
	m_btn_count_setting.Initialize(RGB(220, 220, 220), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("Tahoma"), 15, FW_BOLD);
	m_btn_out_count_up.Initialize(RGB(220, 220, 220), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("Tahoma"), 15, FW_BOLD);
	m_btn_out_count_down.Initialize(RGB(220, 220, 220), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("Tahoma"), 15, FW_BOLD);
	m_btn_sheild_count_up.Initialize(RGB(220, 220, 220), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("Tahoma"), 15, FW_BOLD);
	m_btn_sheild_count_down.Initialize(RGB(220, 220, 220), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("Tahoma"), 15, FW_BOLD);
	m_btn_sheild_up.Initialize(RGB(220, 220, 220), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("Tahoma"), 15, FW_BOLD);
	m_btn_timer.Initialize(RGB(220, 220, 220), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("Tahoma"), 15, FW_BOLD);
	m_stt_mission_performer.Initialize(15, _T("Tahoma"));
	m_stt_having_mission.Initialize(15, _T("Tahoma"));
	m_stt_having_sheild.Initialize(15, _T("Tahoma"));
	m_edit_mission_performer.Initialize(20, _T("Tahoma"));
	m_stt_mission_view_static.Initialize(25, _T("Tahoma"));

	m_stt_out_count.Initialize(15, _T("Tahoma"));
	m_stt_sheild_count.Initialize(15, _T("Tahoma"));
	m_stt_out_count_view.Initialize(15, _T("Tahoma"));
	m_stt_sheild_count_view.Initialize(15, _T("Tahoma"));

	m_btn_sheild_up.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_stt_having_sheild.ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	m_btn_sheild_up.BringWindowToTop();

	m_stt_mission_view_static.SetWindowTextW(_T(""));

	m_stt_having_mission.SetWindowTextW(_T("보유중인 미션 : 0"));
	m_stt_having_sheild.SetWindowTextW(_T("보유중인 실드 : 0"));

	m_edit_mission_performer.LimitText(6);

	missionManager = (CMissionManagerDlg*)pParent;


	LoadProgressingMissionData();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void MissionStart::LoadProgressingMissionData()
{
	if (pmsd != nullptr)
	{

	}
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
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		if (pWnd->m_hWnd == m_stt_mission_view_static.m_hWnd)
		{
			pDC->SetBkColor(RGB(0, 0, 0));
			pDC->SetTextColor(currentColor);

			hbr = m_backBrush;
		}
	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void MissionStart::OnBnClickedButtonStartExtract()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (curentMissionList.empty())
	{
		AfxMessageBox(_T("등록된 미션이 없습니다."), MB_OK | MB_ICONSTOP);
		return;
	}

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
	int nRandomValue = 0;

	while (true)
	{
		bool bSameFind = false;
		nRandomValue = random.Random(0, (int)curentMissionList.size() - 1);
		for (int i = 0; i < missionListCtrl->GetItemCount(); i++)
		{
			if (missionListCtrl->GetItem(i)->GetMissionSequence() == nRandomValue)
			{
				bSameFind = true;
				break;
			}
		}

		if (bSameFind)
		{
			continue;
		}
		else
		{
			break;
		}
	}

	MissionItem* extractMission = curentMissionList.at(nRandomValue);
	//MissionItem* extractMission = curentMissionList.at(1);

	CString strFormatView;
	strFormatView.Format(_T("%d. %s"), extractMission->GetMissionSequence(), extractMission->GetMissionName());

	m_stt_mission_view_static.SetWindowTextW(strFormatView);

	if (extractMission->GetMissionGrade() == 1)
	{
		currentColor = RGB(255, 255, 255);
	}
	else if (extractMission->GetMissionGrade() == 2)
	{
		currentColor = RGB(255, 201, 14);
	}
	else if (extractMission->GetMissionGrade() == 3)
	{
		currentColor = RGB(237, 28, 36);
	}
	Invalidate();

	if (extractMission->GetEvent()->GetEventType() == 4)
	{ 
		sheildList.push_back(extractMission);

		CString strSheild;
		int nSheildCount = (int)sheildList.size();
		strSheild.Format(_T("%d"), nSheildCount);
		m_stt_having_sheild.SetWindowTextW(_T("보유중인 실드 : ") + strSheild);

		return;
	}
	extractMission->SetMissionPerformer(strMissionUserName);
	missionListCtrl->InsertItem(extractMission, strMissionUserName);
	nMissionCount++;
	CString strMissionCount;
	strMissionCount.Format(_T("보유중인 미션 : %d"), nMissionCount);
	m_stt_having_mission.SetWindowTextW(strMissionCount);
}


void MissionStart::OnBnClickedButtonSheildExtract()
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

	if (sheildList.size() == 0)
	{
		AfxMessageBox(_T("보유중인 실드가 없습니다."), MB_OK | MB_ICONSTOP);
		return;
	} 

	// 랜덤 함수 
	RandomProcess random;
	int nRandomValue = random.Random(0, (int)curentMissionList.size() - 1);

	MissionItem* extractSheild = curentMissionList.at(nRandomValue);

	CString strFormatView;
	strFormatView.Format(_T("%d. %s"), extractSheild->GetMissionSequence(), extractSheild->GetMissionName());

	m_stt_mission_view_static.SetWindowTextW(strFormatView);

	int nSheildIndex = 0;

	sheildList.erase(sheildList.begin() + nSheildIndex);

	extractSheild->SetMissionPerformer(strMissionUserName);

	CString strSheild;
	int nSheildCount = (int)sheildList.size();
	strSheild.Format(_T("%d"), nSheildCount);
	m_stt_having_sheild.SetWindowTextW(_T("보유중인 실드 : ") + strSheild);
}


void MissionStart::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.

	dc.Draw3dRect(viewRect, RGB(0, 0, 0), RGB(0, 0, 0));

	CBrush *pOld = dc.SelectObject(&m_backBrush);
	dc.PatBlt(viewRect.left, viewRect.top, viewRect.Width(), viewRect.Height(), PATCOPY);
	dc.SelectObject(pOld);
}


void MissionStart::OnBnClickedButtonStartCountSet()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString strOutCount, strOutPrefix, strOutSuffix;
	CString strSheildCount, strSheildPrefix, strSheildSuffix;

	m_stt_out_count_view.GetWindowTextW(strOutCount);
	m_stt_sheild_count_view.GetWindowTextW(strSheildCount);

	AfxExtractSubString(strOutPrefix, strOutCount, 0, '/');
	AfxExtractSubString(strOutSuffix, strOutCount, 1, '/');
	AfxExtractSubString(strSheildPrefix, strSheildCount, 0, '/');
	AfxExtractSubString(strSheildSuffix, strSheildCount, 1, '/');

	strOutPrefix = strOutPrefix.Trim();
	strOutSuffix = strOutSuffix.Trim();
	strSheildPrefix = strSheildPrefix.Trim();
	strSheildSuffix = strSheildSuffix.Trim();

	int nOutSuffixCount, nSheildSuffixCount, nOutPrefixCount, nSheildPrefixCount;
	nOutSuffixCount = _ttoi(strOutSuffix);
	nSheildSuffixCount = _ttoi(strSheildSuffix);
	nOutPrefixCount = _ttoi(strOutPrefix);
	nSheildPrefixCount = _ttoi(strSheildPrefix);

	MissionCountSetting countSet(&nOutSuffixCount, &nSheildSuffixCount, this);

	if (countSet.DoModal() == IDOK)
	{
		if (nOutPrefixCount > nOutSuffixCount)
			nOutPrefixCount = nOutSuffixCount;

		if (nSheildPrefixCount > nSheildSuffixCount)
			nSheildPrefixCount = nSheildSuffixCount;

		strOutCount.Format(_T("%d / %d"), nOutPrefixCount, nOutSuffixCount);
		strSheildCount.Format(_T("%d / %d"), nSheildPrefixCount, nSheildSuffixCount);

		m_stt_out_count_view.SetWindowTextW(strOutCount);
		m_stt_sheild_count_view.SetWindowTextW(strSheildCount);
	}
}


void MissionStart::OnBnClickedButtonStartOutCountUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString strOutCount, strOutPrefix, strOutSuffix;
	m_stt_out_count_view.GetWindowTextW(strOutCount);

	AfxExtractSubString(strOutPrefix, strOutCount, 0, '/');
	AfxExtractSubString(strOutSuffix, strOutCount, 1, '/');

	strOutPrefix = strOutPrefix.Trim();
	strOutSuffix = strOutSuffix.Trim();

	int nPrefixCount = _ttoi(strOutPrefix);
	int nSuffixCount = _ttoi(strOutSuffix);

	nPrefixCount++;

	if (nPrefixCount > nSuffixCount)
		return;

	strOutCount.Format(_T("%d / %d"), nPrefixCount, nSuffixCount);

	m_stt_out_count_view.SetWindowTextW(strOutCount);
}


void MissionStart::OnBnClickedButtonStartOutCountDown()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString strOutCount, strOutPrefix, strOutSuffix;
	m_stt_out_count_view.GetWindowTextW(strOutCount);

	AfxExtractSubString(strOutPrefix, strOutCount, 0, '/');
	AfxExtractSubString(strOutSuffix, strOutCount, 1, '/');

	strOutPrefix = strOutPrefix.Trim();
	strOutSuffix = strOutSuffix.Trim();

	int nPrefixCount = _ttoi(strOutPrefix);
	int nSuffixCount = _ttoi(strOutSuffix);

	nPrefixCount--;

	if (nPrefixCount < 0)
		return;

	strOutCount.Format(_T("%d / %d"), nPrefixCount, nSuffixCount);

	m_stt_out_count_view.SetWindowTextW(strOutCount);
}


void MissionStart::OnBnClickedButtonStartSheildCountUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString strSheildCount, strSheildPrefix, strSheildSuffix;
	m_stt_sheild_count_view.GetWindowTextW(strSheildCount);

	AfxExtractSubString(strSheildPrefix, strSheildCount, 0, '/');
	AfxExtractSubString(strSheildSuffix, strSheildCount, 1, '/');

	strSheildPrefix = strSheildPrefix.Trim();
	strSheildSuffix = strSheildSuffix.Trim();

	int nPrefixCount = _ttoi(strSheildPrefix);
	int nSuffixCount = _ttoi(strSheildSuffix);

	nPrefixCount++;

	if (nPrefixCount > nSuffixCount)
		return;

	strSheildCount.Format(_T("%d / %d"), nPrefixCount, nSuffixCount);

	m_stt_sheild_count_view.SetWindowTextW(strSheildCount);
}


void MissionStart::OnBnClickedButtonStartSheildCountDown()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString strSheildCount, strSheildPrefix, strSheildSuffix;
	m_stt_sheild_count_view.GetWindowTextW(strSheildCount);

	AfxExtractSubString(strSheildPrefix, strSheildCount, 0, '/');
	AfxExtractSubString(strSheildSuffix, strSheildCount, 1, '/');

	strSheildPrefix = strSheildPrefix.Trim();
	strSheildSuffix = strSheildSuffix.Trim();

	int nPrefixCount = _ttoi(strSheildPrefix);
	int nSuffixCount = _ttoi(strSheildSuffix);

	nPrefixCount--;

	if (nPrefixCount < 0)
		return;

	strSheildCount.Format(_T("%d / %d"), nPrefixCount, nSuffixCount);

	m_stt_sheild_count_view.SetWindowTextW(strSheildCount);
}


void MissionStart::OnBnClickedButtonStartSheildUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	MissionItem* findSheildItem;
	bool bFindSheild = false;
	for (int i = 0; i < (int)curentMissionList.size(); i++)
	{
		if (curentMissionList.at(i)->GetEvent()->GetEventType() == 4)
		{
			findSheildItem = curentMissionList.at(i);
			bFindSheild = true;
		}
	}

	if (!bFindSheild)
	{
		AfxMessageBox(_T("현재 미션에 등록된 실드가 없습니다."), MB_OK | MB_ICONSTOP);
		return;
	}

	sheildList.push_back(findSheildItem);

	CString strSheild;
	int nSheildCount = (int)sheildList.size();
	strSheild.Format(_T("%d"), nSheildCount);
	m_stt_having_sheild.SetWindowTextW(_T("보유중인 실드 : ") + strSheild);
}


void MissionStart::OnBnClickedButtonTimer()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	MissionTimer timer(this);

	timer.DoModal();
}

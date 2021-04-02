// MissionManage.cpp: 구현 파일
//

#include "pch.h"
#include "MissionManager.h"
#include "MissionManage.h"
#include "MissionAdd.h"
#include "afxdialogex.h"


// MissionManage 대화 상자

IMPLEMENT_DYNAMIC(MissionManage, CDialogEx)

MissionManage::MissionManage(MissionVersionItem* cMissionVersionItem, CRect parentRect, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MISSIONMANAGE_DIALOG, pParent)
{
	this->cMissionVersionItem = cMissionVersionItem;
	m_cMissionList = cMissionVersionItem->GetMission();
	this->parentRect = parentRect;
	this->pParent = pParent;
	bRandomListClickChange = false;
	nRandomListClickRow = -1;
}

MissionManage::~MissionManage()
{
	for (int i = 0; i < (int)m_cNewMissionList.size(); i++)
	{
		MissionItem* deleteMission = m_cNewMissionList.at(i);
		delete deleteMission;
		deleteMission = nullptr;
	}
}

void MissionManage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MISSION_MANAGE, m_list_mission_manage);
	DDX_Control(pDX, IDC_BUTTON_MANAGE_MISSION_ADD, m_btn_mission_add);
	DDX_Control(pDX, IDC_BUTTON_MANAGE_SAVE, m_btn_mission_save);
	DDX_Control(pDX, IDC_BUTTON_MANAGE_CLOSE, m_btn_close);
	DDX_Control(pDX, IDC_STATIC_INPUT_GROUP, m_stt_input_group);
	DDX_Control(pDX, IDC_STATIC_MISSION_NAME, m_stt_mission_name);
	DDX_Control(pDX, IDC_STATIC_EVENT_TYPE, m_stt_event_type);
	DDX_Control(pDX, IDC_STATIC_RANDOM_OUTPUT, m_stt_random_output);
	DDX_Control(pDX, IDC_EDIT_MISSION_NAME, m_edit_mission_name);
	DDX_Control(pDX, IDC_EDIT_RANDOM_OUTPUT, m_edit_random_output);
	DDX_Control(pDX, IDC_LIST_RANDOM_OUTPUT_LIST, m_list_random_output);
	DDX_Control(pDX, IDC_COMBO_EVENT_TYPE, m_combo_event_type);
	DDX_Control(pDX, IDC_STATIC_RANDOM_VALUE_INPUT, m_stt_random_value_input);
	DDX_Control(pDX, IDC_STATIC_MANAGE_VERSION_NAME, m_stt_version_name);
	DDX_Control(pDX, IDC_EDIT_MANAGE_VERSION_NAME, m_edit_version_name);
}


BEGIN_MESSAGE_MAP(MissionManage, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_CLICK, IDC_LIST_MISSION_MANAGE, &MissionManage::OnNMClickListMissionManage)
	ON_CBN_SELCHANGE(IDC_COMBO_EVENT_TYPE, &MissionManage::OnCbnSelchangeComboEventType)
	ON_EN_CHANGE(IDC_EDIT_MISSION_NAME, &MissionManage::OnEnChangeEditMissionName)
	ON_BN_CLICKED(IDC_BUTTON_MANAGE_SAVE, &MissionManage::OnBnClickedButtonManageSave)
	ON_BN_CLICKED(IDC_BUTTON_MANAGE_CLOSE, &MissionManage::OnBnClickedButtonManageClose)
	ON_BN_CLICKED(IDC_BUTTON_MANAGE_MISSION_ADD, &MissionManage::OnBnClickedButtonManageMissionAdd)
	ON_NOTIFY(NM_CLICK, IDC_LIST_RANDOM_OUTPUT_LIST, &MissionManage::OnNMClickListRandomOutputList)
END_MESSAGE_MAP()


// MissionManage 메시지 처리기


BOOL MissionManage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	this->MoveWindow(parentRect.right, parentRect.top, 450, 720);

	m_stt_version_name.MoveWindow(10, 20, 50, 20);
	m_edit_version_name.MoveWindow(60, 15, 360, 25);
	m_list_mission_manage.MoveWindow(10, 50, 410, 300);

	m_stt_input_group.MoveWindow(10, 360, 410, 250);
	m_stt_mission_name.MoveWindow(30, 390, 50, 20);
	m_edit_mission_name.MoveWindow(90, 385, 320, 25);
	m_stt_event_type.MoveWindow(30, 420, 100 ,20);
	m_combo_event_type.MoveWindow(30, 440, 150, 20);
	m_stt_random_output.MoveWindow(200, 420, 100, 20);
	m_list_random_output.MoveWindow(200, 440, 210, 130);
	m_stt_random_value_input.MoveWindow(200, 580, 70, 20);
	m_edit_random_output.MoveWindow(270, 575, 140, 25);

	m_btn_mission_add.MoveWindow(40, 620, 100, 30);
	m_btn_mission_save.MoveWindow(170, 620, 100, 30);
	m_btn_close.MoveWindow(300, 620, 100, 30);

	m_btn_mission_add.Initialize(RGB(220, 220, 220), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("Tahoma"), 15, FW_BOLD);
	m_btn_mission_save.Initialize(RGB(220, 220, 220), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("Tahoma"), 15, FW_BOLD);
	m_btn_close.Initialize(RGB(220, 220, 220), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("Tahoma"), 15, FW_BOLD);

	m_edit_mission_name.Initialize(20, _T("Tahoma"));
	m_edit_random_output.Initialize(20, _T("Tahoma"));
	m_edit_version_name.Initialize(20, _T("Tahoma"));

	missionManager = (CMissionManagerDlg*)pParent;

	InitList();
	LoadMissionList();
	m_edit_random_output.LimitText(10);

	m_list_random_output.EnableWindow(FALSE);
	m_edit_random_output.EnableWindow(FALSE);
	m_edit_mission_name.EnableWindow(FALSE);
	m_combo_event_type.EnableWindow(FALSE);

	m_combo_event_type.InsertString(0, _T("없음"));
	m_combo_event_type.InsertString(1, _T("랜덤 뽑기"));
	m_combo_event_type.InsertString(2, _T("텍스트 입력"));
	m_combo_event_type.InsertString(3, _T("실드"));
	m_combo_event_type.InsertString(4, _T("직접말하기"));

	m_combo_event_type.SetCurSel(0);
	m_edit_version_name.SetWindowTextW(cMissionVersionItem->GetVersionName());

	HWND h_wnd = ::FindWindowEx(m_combo_event_type.m_hWnd, NULL, _T("Edit"), NULL);
	if (h_wnd != NULL)
		((CEdit*)CWnd::FromHandle(h_wnd))->SetReadOnly(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void MissionManage::InitList()
{
	CImageList imgGap;
	imgGap.Create(1, 20, ILC_COLORDDB, 1, 0);
	m_list_mission_manage.SetImageList(&imgGap, LVSIL_SMALL);

	m_list_mission_manage.InsertColumn(0, _T("번호"), LVCFMT_CENTER, 50);
	m_list_mission_manage.InsertColumn(1, _T("미션명"), LVCFMT_LEFT, 335);

	m_list_mission_manage.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER | LVS_EX_GRIDLINES);

	m_list_random_output.SetImageList(&imgGap, LVSIL_SMALL);
	m_list_random_output.InsertColumn(0, _T("랜덤 값"), LVCFMT_LEFT, 200);
	m_list_random_output.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER | LVS_EX_GRIDLINES);
}

void MissionManage::LoadMissionList()
{
	for (int i = 0; i < (int)m_cMissionList.size(); i++)
	{
		MissionItem* newMission = new MissionItem;
		EventItem* newEvent = new EventItem;
		newEvent->SetEventType(m_cMissionList.at(i)->GetEvent()->GetEventType());
		newEvent->SetRandomTextList(m_cMissionList.at(i)->GetEvent()->GetRandomTextList());

		newMission->SetMissionSequence(m_cMissionList.at(i)->GetMissionSequence());
		newMission->SetMissionName(m_cMissionList.at(i)->GetMissionName());
		newMission->SetEvent(newEvent);
		m_cNewMissionList.push_back(newMission);
	}


	for (int i = 0; i < (int)m_cNewMissionList.size(); i++)
	{
		MissionItem* currentMission = m_cNewMissionList.at(i);
		CString strSeq;
		strSeq.Format(_T("%d"), currentMission->GetMissionSequence());
		m_list_mission_manage.InsertItem(i, strSeq);
		m_list_mission_manage.SetItemText(i, 1, currentMission->GetMissionName());
	}
}

void MissionManage::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}


BOOL MissionManage::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->hwnd == m_edit_mission_name)
		{
			if (m_list_mission_manage.GetSelectionMark() == -1)
			{
				return TRUE;
			}
		}

		if (pMsg->wParam == VK_RETURN)
		{
			if (pMsg->hwnd == m_edit_random_output.m_hWnd)
			{
				CString strInputText;
				m_edit_random_output.GetWindowTextW(strInputText);

				if (strInputText.IsEmpty())
					return TRUE;

				EventItem* eventItem = currentMission->GetEvent();
				RandomTextList randomTextList = eventItem->GetRandomTextList();
				if (bRandomListClickChange)
				{
					m_list_random_output.SetItemText(nRandomListClickRow, 0, strInputText);

					RandomTextList newTextList;
					for (int i = 0; i < nRandomListClickRow; i++)
					{
						newTextList.push_back(randomTextList.at(i));
					}
					newTextList.push_back(strInputText);
					for (int i = nRandomListClickRow + 1; i < (int)randomTextList.size(); i++)
					{
						newTextList.push_back(randomTextList.at(i));
					}

					eventItem->SetRandomTextList(newTextList);

					nRandomListClickRow = -1;
					bRandomListClickChange = false;
				}
				else
				{
					m_list_random_output.InsertItem(m_list_random_output.GetItemCount(), strInputText);
					
					randomTextList.push_back(strInputText);

					eventItem->SetRandomTextList(randomTextList);
				}

				currentMission->SetEvent(eventItem);
				ExecuteMission();
				m_edit_random_output.SetWindowTextW(_T(""));
			}
		}
		else if (pMsg->wParam == VK_ESCAPE) // ESC키 눌릴 시
			return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void MissionManage::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnClose();
}


HBRUSH MissionManage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void MissionManage::OnNMClickListMissionManage(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int row = pNMItemActivate->iItem;	// 세로 행
	int col = pNMItemActivate->iSubItem;	// 가로 칼럼

	// 행 선택 되었을 때
	if (row > -1)
	{
		m_list_random_output.EnableWindow(FALSE);
		m_edit_random_output.EnableWindow(FALSE); 
		m_edit_mission_name.EnableWindow(TRUE);
		m_combo_event_type.EnableWindow(TRUE);

		m_list_random_output.DeleteAllItems();
		m_edit_random_output.SetWindowTextW(_T(""));

		MissionItem* selectMission = m_cNewMissionList.at(row);
		currentMission = selectMission;
		EventItem* selectEvent = selectMission->GetEvent();
		// 아래 인풋그룹에 추가
		m_edit_mission_name.SetWindowTextW(selectMission->GetMissionName());
		EventItem::EventType eventType = selectEvent->GetEventType();
		m_combo_event_type.SetCurSel((int)eventType);

		if (eventType == EventItem::EVENT_RANDOM)
		{
			m_list_random_output.EnableWindow(TRUE);
			m_edit_random_output.EnableWindow(TRUE);

			RandomTextList randomTextList = selectEvent->GetRandomTextList();

			
			for (int i = 0; i < (int)randomTextList.size(); i++)
			{
				m_list_random_output.InsertItem(i, randomTextList.at(i));
			}
		}
	}
	else
	{
		m_list_random_output.EnableWindow(FALSE);
		m_edit_random_output.EnableWindow(FALSE);
		m_edit_mission_name.EnableWindow(FALSE);
		m_combo_event_type.EnableWindow(FALSE);
		m_list_mission_manage.SetSelectionMark(-1);
		m_edit_mission_name.SetWindowTextW(_T(""));
		m_combo_event_type.SetCurSel(0);
		m_list_random_output.DeleteAllItems();
	}

	*pResult = 0;
}


void MissionManage::OnCbnSelchangeComboEventType()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (m_list_mission_manage.GetSelectionMark() == -1)
	{
		AfxMessageBox(_T("미션을 선택해 주세요."), MB_OK | MB_ICONSTOP);
		m_combo_event_type.SetCurSel(0);
		return;
	}

	EventItem* selectEvent = currentMission->GetEvent();

	if (m_combo_event_type.GetCurSel() == 1)
	{
		m_list_random_output.EnableWindow(TRUE);
		m_edit_random_output.EnableWindow(TRUE);

		RandomTextList randomTextList = selectEvent->GetRandomTextList();

		m_list_random_output.DeleteAllItems();
		m_edit_random_output.SetWindowTextW(_T(""));
		for (int i = 0; i < (int)randomTextList.size(); i++)
		{
			m_list_random_output.InsertItem(i, randomTextList.at(i));
		}
	}
	else
	{
		m_list_random_output.EnableWindow(FALSE);
		m_edit_random_output.EnableWindow(FALSE);

		m_list_random_output.DeleteAllItems();
		m_edit_random_output.SetWindowTextW(_T(""));
	}

	selectEvent->SetEventType(m_combo_event_type.GetCurSel());
	currentMission->SetEvent(selectEvent);

	ExecuteMission();
}


void MissionManage::OnEnChangeEditMissionName()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (m_list_mission_manage.GetSelectionMark() == -1)
	{
		return;
	}

	CString strText;
	m_edit_mission_name.GetWindowTextW(strText);

	currentMission->SetMissionName(strText);

	m_list_mission_manage.SetItemText(m_list_mission_manage.GetSelectionMark(), 1, strText);

	ExecuteMission();
}

void MissionManage::ExecuteMission()
{
	for (int i = 0; i < (int)m_cNewMissionList.size(); i++)
	{
		MissionItem* missionItem = m_cNewMissionList.at(i);
		if (missionItem->GetMissionSequence() == currentMission->GetMissionSequence())
		{
			missionItem = currentMission;
			break;
		}
	}
}


void MissionManage::OnBnClickedButtonManageSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//m_cMissionList = m_cNewMissionList;
	for (int i = 0; i < (int)m_cMissionList.size(); i++)
	{
		MissionItem* deleteMission = m_cMissionList.at(i);
		delete deleteMission;
		deleteMission = nullptr;
	}
	m_cMissionList.clear();

	for (int i = 0; i < (int)m_cNewMissionList.size(); i++)
	{
		MissionItem* assignMission = m_cNewMissionList.at(i);
		EventItem* assignEvent = assignMission->GetEvent();
		MissionItem* createMission = new MissionItem;
		EventItem* createEvent = new EventItem;

		createEvent->SetEventType(assignEvent->GetEventType());
		createEvent->SetRandomTextList(assignEvent->GetRandomTextList());
		createMission->SetEvent(createEvent);
		createMission->SetMissionName(assignMission->GetMissionName());
		createMission->SetMissionSequence(assignMission->GetMissionSequence());
		m_cMissionList.push_back(createMission);
	}

	CString strChangeVersionName;
	m_edit_version_name.GetWindowTextW(strChangeVersionName);

	cMissionVersionItem->SetVersionName(strChangeVersionName);
	cMissionVersionItem->SetMission(m_cMissionList);

	missionManager->ViewVersion(cMissionVersionItem);
}


void MissionManage::OnBnClickedButtonManageClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	PostMessage(WM_CLOSE);
}


void MissionManage::OnBnClickedButtonManageMissionAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int nMissionListSize = (int)m_cNewMissionList.size() + 1;
	MissionAdd missionAddDlg(nMissionListSize, this);
	missionAddDlg.DoModal();

}


void MissionManage::OnNMClickListRandomOutputList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int row = pNMItemActivate->iItem;	// 세로 행
	int col = pNMItemActivate->iSubItem;	// 가로 칼럼
	
	// 행 선택 되었을 때
	if (row > -1)
	{
		CString strRandomText = m_list_random_output.GetItemText(row, col);
		m_edit_random_output.SetWindowTextW(strRandomText);
		nRandomListClickRow = row;
		bRandomListClickChange = true;
	}
	else
	{
		nRandomListClickRow = -1;
		bRandomListClickChange = false;
	}

	*pResult = 0;
}

// MissionAdd.cpp: 구현 파일
//

#include "pch.h"
#include "MissionManager.h"
#include "MissionAdd.h"
#include "afxdialogex.h"


// MissionAdd 대화 상자

IMPLEMENT_DYNAMIC(MissionAdd, CDialogEx)

MissionAdd::MissionAdd(int nMissionListSize, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MISSION_ADD_DIALOG, pParent)
{
	this->pParent = pParent;
	this->nMissionListSize = nMissionListSize;

	bRandomListClickChange = false;
	nRandomListClickRow = -1;
}

MissionAdd::~MissionAdd()
{
}

void MissionAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_ADD_MISSION_NAME, m_stt_mission_name);
	DDX_Control(pDX, IDC_EDIT_ADD_MISSION_NAME, m_edit_mission_name);
	DDX_Control(pDX, IDC_STATIC_ADD_MISSION_EVENT_TYPE, m_stt_event_type);
	DDX_Control(pDX, IDC_COMBO_ADD_EVENT_TYPE, m_combo_event_type);
	DDX_Control(pDX, IDC_STATIC_ADD_RANDOM_INPUT_LIST, m_stt_random_input_list);
	DDX_Control(pDX, IDC_LIST_ADD_RANDOM_INPUT_LIST, m_list_random_input_list);
	DDX_Control(pDX, IDC_STATIC_ADD_RANDOM_VALUE_INPUT, m_stt_random_value_input);
	DDX_Control(pDX, IDC_EDIT_ADD_RANDOM_VALUE_INPUT, m_edit_random_value_input);
	DDX_Control(pDX, IDC_BUTTON_ADD_SAVE, m_btn_save);
	DDX_Control(pDX, IDC_BUTTON_ADD_CLOSE, m_btn_close);
	DDX_Control(pDX, IDC_STATIC_ADD_MISSION_GRADE, m_stt_mission_grade);
	DDX_Control(pDX, IDC_RADIO_ADD_MISSION_LEVEL_EASY, m_radio_level_easy);
	DDX_Control(pDX, IDC_RADIO_ADD_MISSION_LEVEL_NORMAL, m_radio_level_normal);
	DDX_Control(pDX, IDC_RADIO_ADD_MISSION_LEVEL_HARD, m_radio_level_hard);
}


BEGIN_MESSAGE_MAP(MissionAdd, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_ADD_CLOSE, &MissionAdd::OnBnClickedButtonAddClose)
	ON_BN_CLICKED(IDC_BUTTON_ADD_SAVE, &MissionAdd::OnBnClickedButtonAddSave)
	ON_CBN_SELCHANGE(IDC_COMBO_ADD_EVENT_TYPE, &MissionAdd::OnCbnSelchangeComboAddEventType)
	ON_NOTIFY(NM_CLICK, IDC_LIST_ADD_RANDOM_INPUT_LIST, &MissionAdd::OnNMClickListAddRandomInputList)
END_MESSAGE_MAP()


// MissionAdd 메시지 처리기


BOOL MissionAdd::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	this->SetWindowPos(NULL, 0, 0, 400, 460, SWP_NOMOVE);

	m_stt_mission_name.MoveWindow(20, 20, 50, 20);
	m_edit_mission_name.MoveWindow(130, 15, 230, 25);
	m_stt_event_type.MoveWindow(20, 50, 100, 20);
	m_combo_event_type.MoveWindow(130, 50, 150, 20);
	m_stt_random_input_list.MoveWindow(20, 80, 100, 20);
	m_list_random_input_list.MoveWindow(130, 80, 230, 200);
	m_stt_random_value_input.MoveWindow(20, 290, 100, 20);
	m_edit_random_value_input.MoveWindow(130, 285, 230, 25);

	m_stt_mission_grade.MoveWindow(20, 330, 50, 20);
	m_radio_level_easy.MoveWindow(130, 325, 50, 25);
	m_radio_level_normal.MoveWindow(190, 325, 50, 25);
	m_radio_level_hard.MoveWindow(250, 325, 50, 25);

	m_btn_save.MoveWindow(150, 360, 100, 30);
	m_btn_close.MoveWindow(260, 360, 100, 30);

	m_btn_save.Initialize(RGB(220, 220, 220), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("Tahoma"), 15, FW_BOLD);
	m_btn_close.Initialize(RGB(220, 220, 220), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("Tahoma"), 15, FW_BOLD);
	m_edit_mission_name.Initialize(20, _T("Tahoma"));
	m_edit_random_value_input.Initialize(20, _T("Tahoma"));

	//CImageList imgGap;
	//imgGap.Create(1, 20, ILC_COLORDDB, 1, 0);
	//m_list_random_input_list.SetImageList(&imgGap, LVSIL_SMALL);

	m_list_random_input_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_list_random_input_list.InsertColumn(0, _T("랜덤 값"), LVCFMT_LEFT, 225);
	m_list_random_input_list.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);

	m_combo_event_type.InsertString(0, _T("없음"));
	m_combo_event_type.InsertString(1, _T("랜덤 뽑기 사전 설정"));
	m_combo_event_type.InsertString(2, _T("랜덤 뽑기 사후 설정"));
	m_combo_event_type.InsertString(3, _T("텍스트 입력"));
	m_combo_event_type.InsertString(4, _T("실드"));
	m_combo_event_type.InsertString(5, _T("직접말하기"));

	m_combo_event_type.SetCurSel(0);
	m_radio_level_easy.SetCheck(TRUE);

	HWND h_wnd = ::FindWindowEx(m_combo_event_type.m_hWnd, NULL, _T("Edit"), NULL);
	if (h_wnd != NULL)
		((CEdit*)CWnd::FromHandle(h_wnd))->SetReadOnly(TRUE);

	m_list_random_input_list.EnableWindow(FALSE);
	m_edit_random_value_input.EnableWindow(FALSE);

	manage = (MissionManage*)pParent;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void MissionAdd::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}


BOOL MissionAdd::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN)
		{
			if (pMsg->hwnd == m_edit_random_value_input.m_hWnd)
			{
				CString strInputText;
				m_edit_random_value_input.GetWindowTextW(strInputText);

				if (strInputText.IsEmpty())
					return TRUE;

				if (bRandomListClickChange)
				{
					m_list_random_input_list.SetItemText(nRandomListClickRow, 0, strInputText);

					RandomTextList newTextList;
					for (int i = 0; i < nRandomListClickRow; i++)
					{
						newTextList.push_back(inputRandomTextList.at(i));
					}
					newTextList.push_back(strInputText);
					for (int i = nRandomListClickRow + 1; i < (int)inputRandomTextList.size(); i++)
					{
						newTextList.push_back(inputRandomTextList.at(i));
					}
					inputRandomTextList = newTextList;

					nRandomListClickRow = -1;
					bRandomListClickChange = false;
				}
				else
				{
					m_list_random_input_list.InsertItem(m_list_random_input_list.GetItemCount(), strInputText);
					inputRandomTextList.push_back(strInputText);
				}
				

				m_edit_random_value_input.SetWindowTextW(_T(""));
			}
		}
		else if (pMsg->wParam == VK_ESCAPE) // ESC키 눌릴 시
			return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void MissionAdd::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnClose();
}


HBRUSH MissionAdd::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void MissionAdd::OnBnClickedButtonAddClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	PostMessage(WM_CLOSE);
}


void MissionAdd::OnBnClickedButtonAddSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString strInputMissionName;
	m_edit_mission_name.GetWindowTextW(strInputMissionName);

	int nEventTypeIndex = m_combo_event_type.GetCurSel();

	if (strInputMissionName.IsEmpty())
	{
		AfxMessageBox(_T("미션 명을 입력해 주세요."), MB_OK | MB_ICONSTOP);
		return;
	}

	int nGrade = 0;
	if (m_radio_level_easy.GetCheck())
	{
		nGrade = 1;
	}
	else if (m_radio_level_normal.GetCheck())
	{
		nGrade = 2;
	}
	else if (m_radio_level_hard.GetCheck())
	{
		nGrade = 3;
	}

	MissionItem* newMission = new MissionItem;
	EventItem* newEventItem = new EventItem;

	newMission->SetMissionName(strInputMissionName);
	newMission->SetMissionSequence(nMissionListSize);
	newMission->SetMissionGrade(nGrade);
	newEventItem->SetEventType(nEventTypeIndex);
	newEventItem->SetRandomTextList(inputRandomTextList);
	newMission->SetEvent(newEventItem);

	CString strSequence;
	strSequence.Format(_T("%d"), newMission->GetMissionSequence());
	int nItemCount = manage->m_list_mission_manage.GetItemCount();
	manage->m_list_mission_manage.InsertItem(nItemCount, strSequence);
	manage->m_list_mission_manage.SetItemText(nItemCount, 1, newMission->GetMissionName());
	manage->m_cNewMissionList.push_back(newMission);

	manage->m_list_mission_manage.SetItemState(nItemCount, LVIS_SELECTED, LVIS_SELECTED);
	manage->m_list_mission_manage.EnsureVisible(nItemCount, FALSE);
	manage->m_list_mission_manage.SetSelectionMark(nItemCount);
	manage->m_list_mission_manage.SetFocus();

	nMissionListSize++;

	m_edit_mission_name.SetWindowTextW(_T(""));
	m_edit_random_value_input.SetWindowTextW(_T(""));
	m_combo_event_type.SetCurSel(0);
	m_list_random_input_list.DeleteAllItems();
	inputRandomTextList.clear();
	m_list_random_input_list.EnableWindow(FALSE);
	m_edit_random_value_input.EnableWindow(FALSE);
	m_radio_level_easy.SetCheck(TRUE);
	m_radio_level_normal.SetCheck(FALSE);
	m_radio_level_hard.SetCheck(FALSE);
}


void MissionAdd::OnCbnSelchangeComboAddEventType()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (m_combo_event_type.GetCurSel() == 1)
	{
		m_list_random_input_list.EnableWindow(TRUE);
		m_edit_random_value_input.EnableWindow(TRUE);
	}
	else
	{
		m_list_random_input_list.EnableWindow(FALSE);
		m_edit_random_value_input.EnableWindow(FALSE);

		m_list_random_input_list.DeleteAllItems();
		inputRandomTextList.clear();
		m_edit_random_value_input.SetWindowTextW(_T(""));
	}
}


void MissionAdd::OnNMClickListAddRandomInputList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int row = pNMItemActivate->iItem;	// 세로 행
	int col = pNMItemActivate->iSubItem;	// 가로 칼럼

	// 행 선택 되었을 때
	if (row > -1)
	{
		CString strRandomText = m_list_random_input_list.GetItemText(row, col);
		m_edit_random_value_input.SetWindowTextW(strRandomText);
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

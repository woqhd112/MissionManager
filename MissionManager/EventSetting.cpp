// EventSetting.cpp: 구현 파일
//

#include "pch.h"
#include "MissionManager.h"
#include "EventSetting.h"
#include "RandomProcess.h"
#include "afxdialogex.h"


// EventSetting 대화 상자

IMPLEMENT_DYNAMIC(EventSetting, CDialogEx)

EventSetting::EventSetting(MissionList curentMissionList, MissionListItem* inputMission, CString* outputText, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETTING_EVENT_DIALOG, pParent)
{
	this->curentMissionList = curentMissionList;
	this->inputMission = inputMission;
	this->pParent = pParent;
	this->outputText = outputText;
	nSelectMission = 0;
}

EventSetting::~EventSetting()
{
}

void EventSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_GROUP_EVENT, m_stt_group_event);
	DDX_Control(pDX, IDC_BUTTON_EXACT, m_btn_exact);
	DDX_Control(pDX, IDC_LIST_EVENT_RANDOM_LIST, m_list_event_random);
	DDX_Control(pDX, IDC_STATIC_EVENT_TEXT, m_stt_event_text);
	DDX_Control(pDX, IDC_EDIT_EVENT_TEXT, m_edit_event_text);
	DDX_Control(pDX, IDC_BUTTON_EVENTSET_SAVE, m_btn_save);
}


BEGIN_MESSAGE_MAP(EventSetting, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON_EXACT, &EventSetting::OnBnClickedButtonExact)
	ON_BN_CLICKED(IDC_BUTTON_EVENTSET_SAVE, &EventSetting::OnBnClickedButtonEventsetSave)
	ON_LBN_DBLCLK(IDC_LIST_EVENT_RANDOM_LIST, &EventSetting::OnLbnDblclkListEventRandomList)
END_MESSAGE_MAP()


// EventSetting 메시지 처리기


BOOL EventSetting::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	DefaultEnableCtrlItem();

	if (inputMission)
	{
		int nEventType = inputMission->GetEventType();

		switch (nEventType)
		{
			// 아무 이벤트도 선택되지 않은 미션 / 사실 이걸 타진않음..
		case 0:

			break;

			// 랜덤뽑기 이벤트가 선택된 미션
		case 1:

			this->SetWindowTextW(_T("랜덤 뽑기"));
			this->SetWindowPos(NULL, 0, 0, 400, 350, SWP_NOMOVE);
			m_stt_group_event.SetWindowTextW(_T("랜덤 뽑기"));
			m_stt_group_event.MoveWindow(10, 10, 360, 240);
			m_list_event_random.MoveWindow(20, 30, 340, 160);
			m_btn_exact.MoveWindow(20, 200, 340, 30);
			m_btn_save.MoveWindow(250, 260, 120, 30);

			m_btn_exact.Initialize(RGB(220, 220, 220), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("Tahoma"), 15, FW_BOLD);
			m_btn_save.Initialize(RGB(220, 220, 220), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("Tahoma"), 15, FW_BOLD);

			nDecreaseListCount = (int)inputMission->GetRandomTextList().size();

			EnableRandomEvent();

			break;

			// 텍스트입력 이벤트가 선택된 미션
		case 2:

			this->SetWindowTextW(_T("텍스트 입력"));
			this->SetWindowPos(NULL, 0, 0, 350, 200, SWP_NOMOVE);
			m_stt_group_event.SetWindowTextW(_T("텍스트 입력"));
			m_stt_group_event.MoveWindow(10, 10, 310, 90);
			m_stt_event_text.MoveWindow(20, 50, 70, 20);
			m_edit_event_text.MoveWindow(90, 45, 200, 25);
			m_btn_save.MoveWindow(200, 110, 120, 30);

			m_btn_save.Initialize(RGB(220, 220, 220), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("Tahoma"), 15, FW_BOLD);

			EnableInputTextEvent();

			break;

			// 실드 이벤트가 선택된 미션  / 사실 이걸 타진않음..
		case 3:

			break;

			// 직접말하기 이벤트가 선택된 미션
		case 4:

			this->SetWindowTextW(_T("직접말하기"));
			this->SetWindowPos(NULL, 0, 0, 400, 610, SWP_NOMOVE);
			m_stt_group_event.SetWindowTextW(_T("직접말하기"));
			m_stt_group_event.MoveWindow(10, 10, 360, 500);
			m_list_event_random.MoveWindow(20, 30, 340, 400);
			m_stt_event_text.MoveWindow(20, 450, 70, 20);
			m_edit_event_text.MoveWindow(90, 445, 270, 25);
			m_btn_save.MoveWindow(250, 520, 120, 30);

			m_stt_event_text.SetWindowTextW(_T("선택된 미션"));
			m_edit_event_text.EnableWindow(FALSE);

			m_btn_save.Initialize(RGB(220, 220, 220), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("Tahoma"), 15, FW_BOLD);

			for (int i = 0; i < (int)curentMissionList.size(); i++)
			{
				CString strIndex;
				strIndex.Format(_T("%d. "), i + 1);
				m_list_event_random.InsertString(i, strIndex + curentMissionList.at(i)->GetMissionName());
			}

			EnableSpeakDirectlyEvent();

			break;

		default:

			break;
		}


	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void EventSetting::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}


BOOL EventSetting::PreTranslateMessage(MSG* pMsg)
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


void EventSetting::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnClose();
}


HBRUSH EventSetting::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}

void EventSetting::DefaultEnableCtrlItem()
{
	m_btn_exact.ShowWindow(SW_HIDE);
	m_list_event_random.ShowWindow(SW_HIDE);
	m_stt_event_text.ShowWindow(SW_HIDE);
	m_edit_event_text.ShowWindow(SW_HIDE);
}

void EventSetting::EnableRandomEvent()
{
	m_btn_exact.ShowWindow(SW_SHOW);
	m_list_event_random.ShowWindow(SW_SHOW);
}

void EventSetting::EnableInputTextEvent()
{
	m_stt_event_text.ShowWindow(SW_SHOW);
	m_edit_event_text.ShowWindow(SW_SHOW);
}

void EventSetting::EnableSpeakDirectlyEvent()
{
	m_list_event_random.ShowWindow(SW_SHOW);
	m_stt_event_text.ShowWindow(SW_SHOW);
	m_edit_event_text.ShowWindow(SW_SHOW);
}

void EventSetting::OnBnClickedButtonExact()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (inputMission->GetEventType() != 1)
		return;

	if (nDecreaseListCount == 0)
	{
		AfxMessageBox(_T("모든 이벤트를 사용하셨습니다."), MB_OK | MB_ICONSTOP);
		return;
	}
	

	// 랜덤 함수 
	RandomProcess random;
	RandomTextList randomTextList;
	randomTextList = inputMission->GetRandomTextList();
	int nRandomValue = random.Random(0, randomTextList.size() - 1);

	CString strRandomText = randomTextList.at(nRandomValue);
	randomTextList.erase(randomTextList.begin() + nRandomValue);
	inputMission->SetRandomTextList(randomTextList);

	int nListCount = m_list_event_random.GetCount();
	m_list_event_random.InsertString(nListCount, strRandomText);

	nDecreaseListCount--;
}


void EventSetting::OnBnClickedButtonEventsetSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (inputMission)
	{
		int nEventType = inputMission->GetEventType();

		if (nEventType == 1)
		{
			for (int i = 0; i < m_list_event_random.GetCount(); i++)
			{
				CString strOutputText;
				m_list_event_random.GetText(i, strOutputText);
				if (i == m_list_event_random.GetCount() - 1)
					outputText->AppendFormat(_T("%s"), strOutputText);
				else
					outputText->AppendFormat(_T("%s, "), strOutputText);
			}
		}
		else if (nEventType == 2)
		{
			m_edit_event_text.GetWindowTextW(*outputText);
		}
		else if (nEventType == 4)
		{
			outputText->Format(_T("%d"), nSelectMission);
		}
	}
	PostMessage(WM_CLOSE);
}


void EventSetting::OnLbnDblclkListEventRandomList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (inputMission->GetEventType() != 4)
		return;

	int nSelectIndex = m_list_event_random.GetCurSel();
	MissionItem* selectMission = curentMissionList.at(nSelectIndex);
	nSelectMission = selectMission->GetMissionSequence() - 1;
	m_edit_event_text.SetWindowTextW(selectMission->GetMissionName());
}

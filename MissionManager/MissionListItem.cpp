#include "pch.h"
#include "MissionListItem.h"

static unsigned int s_nWrapCtrlID = 5000;
static unsigned int s_nMissionCtrlID = 10000;
static unsigned int s_nWinnerCtrlID = 15000;
static unsigned int s_nEventCtrlID = 20000;
static unsigned int s_nCloseCtrlID = 25000;

MissionListItem::MissionListItem(CWnd* pParent)
{
	this->pParent = pParent;
	nDivideWidth = 0;
	m_nEventType = 0;
	m_strMissionName = _T("");
	nIndex = 0;
	nPos = 0;
	m_bUse = false;
	m_nMissionSequence = 0;
}

MissionListItem::~MissionListItem()
{
	if (wrapButton1)
	{
		delete wrapButton1;
		wrapButton1 = nullptr;
	}

	if (wrapButton2)
	{
		delete wrapButton2;
		wrapButton2 = nullptr;
	}

	if (winnerNameStatic)
	{
		delete winnerNameStatic;
		winnerNameStatic = nullptr;
	}

	if (missionStatic)
	{
		delete missionStatic;
		missionStatic = nullptr;
	}

	if (resultStatic)
	{
		delete resultStatic;
		resultStatic = nullptr;
	}

	if (eventStatic)
	{
		delete eventStatic;
		eventStatic = nullptr;
	}

	if (eventButton)
	{
		delete eventButton;
		eventButton = nullptr;
	}

	if (closeButton)
	{
		delete closeButton;
		closeButton = nullptr;
	}
}

void MissionListItem::Create(int nListSize)
{
	CRect parantSize;
	pParent->GetWindowRect(parantSize);

	nIndex = nListSize;

	wrapButton1 = new CustomButton;
	wrapButton2 = new CustomButton;
	missionStatic = new CustomStatic;
	winnerNameStatic = new CustomStatic;
	resultStatic = new CustomStatic;
	eventStatic = new CustomStatic;
	eventButton = new CustomButton;
	closeButton = new CustomButton;

	wrapButton1->Create(_T(""), BS_PUSHBUTTON | BS_LEFT, CRect(0, 0, 0, 0), pParent, s_nWrapCtrlID++);
	wrapButton1->m_bUseMouseBkGroundColorEvent = false;
	missionStatic->Create(_T(""), SS_LEFT, CRect(0, 0, 0, 0), pParent, s_nMissionCtrlID++);
	winnerNameStatic->Create(_T(""), SS_CENTER, CRect(0, 0, 0, 0), pParent, s_nWinnerCtrlID++);
	eventButton->Create(_T(""), BS_PUSHBUTTON, CRect(0, 0, 0, 0), pParent, s_nEventCtrlID++);
	closeButton->Create(_T(""), BS_PUSHBUTTON, CRect(0, 0, 0, 0), pParent, s_nCloseCtrlID++);

	wrapButton2->Create(_T(""), BS_PUSHBUTTON | BS_LEFT, CRect(0, 0, 0, 0), pParent, s_nWrapCtrlID++);
	wrapButton2->m_bUseMouseBkGroundColorEvent = false;
	resultStatic->Create(_T(""), SS_LEFT, CRect(0, 0, 0, 0), pParent, s_nMissionCtrlID++);
	eventStatic->Create(_T(""), SS_LEFT, CRect(0, 0, 0, 0), pParent, s_nWinnerCtrlID++);

	wrapButton1->Initialize(RGB(220, 220, 220), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("Tahoma"), 15);
	wrapButton2->Initialize(RGB(220, 220, 220), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("Tahoma"), 15);
	missionStatic->Initialize(15, _T("Tahoma"));
	winnerNameStatic->Initialize(20, _T("Tahoma"));
	resultStatic->Initialize(15, _T("Tahoma"));
	eventStatic->Initialize(15, _T("Tahoma"));
	eventButton->Initialize(RGB(200, 200, 200), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("Tahoma"), 15);
	closeButton->Initialize(RGB(200, 200, 200), CMFCButton::FlatStyle::BUTTONSTYLE_NOBORDERS, _T("Tahoma"), 15);

	eventButton->SetWindowTextW(_T("event"));
	closeButton->SetWindowTextW(_T("x"));
	resultStatic->SetWindowTextW(_T("실행 결과 : "));

	int nWrapWidth = parantSize.Width() - 10;
	wrapButton1->MoveWindow(0, 0, nWrapWidth, 30);
	wrapButton2->MoveWindow(0, 30, nWrapWidth, 30);
	nDivideWidth = (nWrapWidth / 10);
	missionStatic->MoveWindow(5, 0, nDivideWidth * 5, 30);
	winnerNameStatic->MoveWindow(nDivideWidth * 5 + 15, 0, nDivideWidth * 3, 30);
	resultStatic->MoveWindow(5, 30, nDivideWidth * 2, 30);
	eventStatic->MoveWindow(5 + (nDivideWidth * 2), 30, nDivideWidth * 7.5, 30);
	eventButton->MoveWindow((nDivideWidth * 5) + 15 + (nDivideWidth * 3) + 10, 0, nDivideWidth * 1.5, 30);
	closeButton->MoveWindow((nDivideWidth * 5) + 15 + (nDivideWidth * 3) + 10 + (nDivideWidth * 1.5) + 5, 0, nDivideWidth * 0.5, 30);

	wrapButton1->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	wrapButton2->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	missionStatic->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	winnerNameStatic->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	resultStatic->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	eventStatic->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	eventButton->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	closeButton->ModifyStyle(0, WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0);
	missionStatic->BringWindowToTop();
	winnerNameStatic->BringWindowToTop();
	resultStatic->BringWindowToTop();
	eventStatic->BringWindowToTop();
	eventButton->BringWindowToTop();
	closeButton->BringWindowToTop();

	wrapButton1->ShowWindow(SW_SHOW);
	wrapButton2->ShowWindow(SW_SHOW);
	missionStatic->ShowWindow(SW_SHOW);
	winnerNameStatic->ShowWindow(SW_SHOW);
	resultStatic->ShowWindow(SW_SHOW);
	eventStatic->ShowWindow(SW_SHOW);
	eventButton->ShowWindow(SW_SHOW);
	closeButton->ShowWindow(SW_SHOW);

	eventButton->SetIndex(nIndex);
	closeButton->SetIndex(nIndex);

	//missionStatic->SetWindowTextW(_T("미션미션미션미션미션미션미션미션미션미션"));
	//winnerNameStatic->SetWindowTextW(_T("테스트"));
}

void MissionListItem::MoveWindow(int y)
{
	nPos = y;
	wrapButton1->SetWindowPos(NULL, 0, y, 0, 0, SWP_NOSIZE);
	wrapButton2->SetWindowPos(NULL, 0, y + 30, 0, 0, SWP_NOSIZE);
	missionStatic->SetWindowPos(NULL, 5, y, 0, 0, SWP_NOSIZE);
	winnerNameStatic->SetWindowPos(NULL, nDivideWidth * 5 + 15, y, 0, 0, SWP_NOSIZE);
	resultStatic->SetWindowPos(NULL, 5, y + 30, 0, 0, SWP_NOSIZE);
	eventStatic->SetWindowPos(NULL, 5 + (nDivideWidth * 2), y + 30, 0, 0, SWP_NOSIZE);
	eventButton->SetWindowPos(NULL, (nDivideWidth * 4) + 15 + (nDivideWidth * 3) + 10, y, 0, 0, SWP_NOSIZE);
	closeButton->SetWindowPos(NULL, (nDivideWidth * 4) + 15 + (nDivideWidth * 3) + 10 + (nDivideWidth * 1.5) + 5, y, 0, 0, SWP_NOSIZE);
}

void MissionListItem::SetMissionName(CString strMissionName)
{
	m_strMissionName = strMissionName;
	missionStatic->SetWindowTextW(strMissionName);
}

void MissionListItem::SetMissionUserName(CString strMissionUserName)
{
	m_strMissionUserName = strMissionUserName;
	winnerNameStatic->SetWindowTextW(strMissionUserName);
}

void MissionListItem::SetEventType(int nEventType)
{
	m_nEventType = nEventType;
}

void MissionListItem::SetItemIndex(int nIndex)
{
	this->nIndex = nIndex;
	eventButton->SetIndex(nIndex);
	closeButton->SetIndex(nIndex);
}

void MissionListItem::SetPos(int y)
{
	this->nPos = nPos;
}

void MissionListItem::SetRandomTextList(RandomTextList vRandomTextList)
{
	m_vRandomTextList.clear();
	for (int i = 0; i < (int)vRandomTextList.size(); i++)
	{
		m_vRandomTextList.push_back(vRandomTextList.at(i));
	}
}

void MissionListItem::SetEventStatic(CString strStatic)
{
	eventStatic->SetWindowTextW(strStatic);
}

void MissionListItem::SetNoEvent(BOOL bChange)
{
	eventButton->EnableWindow(bChange);
}

void MissionListItem::SetUseEvent(bool bUse)
{
	this->m_bUse = bUse;
}

void MissionListItem::SetMissionSequence(int nSeq)
{
	this->m_nMissionSequence = nSeq;
}

bool MissionListItem::IsUsing() const
{
	return m_bUse;
}

int MissionListItem::GetItemIndex() const
{
	return nIndex;
}

int MissionListItem::GetPos() const
{
	return nPos;
}

int MissionListItem::GetEventType() const
{
	return m_nEventType;
}

int MissionListItem::GetMissionSequence() const
{
	return m_nMissionSequence;
}

bool MissionListItem::IsSameEventButton(CustomButton* compareButton)
{
	if (compareButton == eventButton) return true;
	else return false;

	return false;
}

MissionListItem::RandomTextList MissionListItem::GetRandomTextList() const
{
	return m_vRandomTextList;
}

void MissionListItem::ChangeMission(CString strMissionName, int nEventType, RandomTextList vRandomTextList)
{
	m_strMissionName = strMissionName;
	m_nEventType = nEventType;
	m_vRandomTextList = vRandomTextList;
	missionStatic->SetWindowTextW(strMissionName);
	eventStatic->SetWindowTextW(_T(""));
	SetNoEvent(TRUE);
	if (nEventType == 0)
		SetNoEvent(FALSE);
}
// MissionListCtrl.cpp: 구현 파일
//

#include "pch.h"
#include "MissionManager.h"
#include "MissionListCtrl.h"
#include "EventSetting.h"
#include "MissionStart.h"
#include "afxdialogex.h"


// MissionListCtrl 대화 상자

IMPLEMENT_DYNAMIC(MissionListCtrl, CDialogEx)

MissionListCtrl::MissionListCtrl(MissionList curentMissionList, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MISSIONLIST_DIALOG, pParent)
{
	this->pParent = pParent;
	this->curentMissionList = curentMissionList;

	m_nBasic = ITEM_CTRL_HEIGHT;	// 스크롤 위아래 버튼 클릭 시 스크롤 간격
	nViewHeight = 2;	// 스크롤 전체 출력 화면
	nScrollPos = 0;	// 현재 스크롤의 위치
	nPageSize = 0;	// 한페이지의 사이즈

	nItemHeight = 2;
	nCurrentPage = 0;
	nLineCount = 0;
}

MissionListCtrl::~MissionListCtrl()
{
	for (int i = 0; i < (int)activeMissionList.size(); i++)
	{
		MissionListItem* deleteMission = activeMissionList.at(i);
		delete deleteMission;
		deleteMission = nullptr;
	}
	activeMissionList.clear();

	static unsigned int s_nWrapCtrlID = 5000;
	static unsigned int s_nMissionCtrlID = 10000;
	static unsigned int s_nWinnerCtrlID = 15000;
	static unsigned int s_nEventCtrlID = 20000;
	static unsigned int s_nCloseCtrlID = 25000;
}

void MissionListCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MissionListCtrl, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// MissionListCtrl 메시지 처리기


BOOL MissionListCtrl::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_hBrush.CreateSolidBrush(RGB(220, 220, 220));
	this->SetBackgroundColor(RGB(255, 255, 255));

	missionStart = (MissionStart*)pParent;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void MissionListCtrl::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//CDialogEx::OnOK();
}


BOOL MissionListCtrl::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CDialogEx::PreTranslateMessage(pMsg);
}


void MissionListCtrl::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//CDialogEx::OnClose();
}


HBRUSH MissionListCtrl::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.
	if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetBkColor(RGB(220, 220, 220));
		hbr = m_hBrush;
	}

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void MissionListCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	//scroll.OperateScroll(nSBCode, nPos);

	if (nLineCount <= 5) return;

	int delta = 0;
	switch (nSBCode)
	{
	case SB_LINEUP:
		delta = -m_nBasic;
		nCurrentPage--;
		break;
	case SB_PAGEUP:
		delta = -nPageSize;
		nCurrentPage--;
		break;
	case SB_THUMBTRACK:
		delta = static_cast<int>(nPos) - nScrollPos;
		break;
	case SB_PAGEDOWN:
		delta = nPageSize;
		nCurrentPage++;
		break;
	case SB_LINEDOWN:
		delta = m_nBasic;
		nCurrentPage++;
		break;
	default:
		return;
	}

	if (nCurrentPage < 0)
	{
		nCurrentPage = 0;
		return;
	}


	int scrollpos = nScrollPos + delta;
	int nMaxPos = nViewHeight - nPageSize;

	if (scrollpos < 0)
	{
		delta = -nScrollPos;
	}
	else
	{
		if (scrollpos > nMaxPos)
		{
			delta = nMaxPos - nScrollPos;
		}
	}

	if (delta != 0)
	{
		nScrollPos += delta;
		SetScrollPos(SB_VERT, nScrollPos, TRUE);
		ScrollWindow(0, -delta);
		nItemHeight -= delta;
	}
	else
	{
		nCurrentPage--;
		return;
	}


	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}


BOOL MissionListCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	/*if (scroll.GetLineCount() > 1)
	{
		UINT nFlag = scroll.OperateWheel(zDelta);
		if (nFlag == SB_PAGEUP && scroll.GetCurrentLinePos() == 1) {}
		else if (nFlag == SB_PAGEDOWN && scroll.GetCurrentLinePos() == scroll.GetLineCount()) {}
		else { OnVScroll(nFlag, 0, GetScrollBarCtrl(SB_VERT)); }
	}*/

	UINT nFlag;
	if (zDelta > 0)	// 위스크롤
	{
		nFlag = SB_LINEUP;
	}
	else // 아래스크롤
	{
		nFlag = SB_LINEDOWN;
	}

	OnVScroll(nFlag, 0, GetScrollBarCtrl(SB_VERT));

	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}


void MissionListCtrl::SetScrollSize(int nThisHeight)
{
	int nScrollMax = 0;
	if (nThisHeight < nViewHeight)
	{
		nScrollMax = nViewHeight - 1;
		nPageSize = nThisHeight;
		nScrollPos = min(nScrollPos, nViewHeight - nPageSize - 1);
	}

	SCROLLINFO si;
	si.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
	si.nMin = 0;
	si.nMax = nScrollMax;
	si.nPos = nScrollPos;
	si.nPage = nPageSize;
	SetScrollInfo(SB_VERT, &si, TRUE);
}


void MissionListCtrl::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	this->cy = cy;
	SetScrollSize(cy);
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void MissionListCtrl::InsertItem(MissionItem* inputMission, CString strMissionUserName)
{
	//int nHeight = 2;
	//if (scroll.GetLineCount() != 0) nHeight = 0;

	MissionListItem* newItem = new MissionListItem(this);
	newItem->Create((int)activeMissionList.size());
	newItem->MoveWindow(nItemHeight);
	//newItem->MoveWindow(scroll.GetLineCount() * 32 + nHeight);
	newItem->SetMissionUserName(strMissionUserName);
	newItem->SetMissionName(inputMission->GetMissionName());
	newItem->SetEventType(inputMission->GetEvent()->GetEventType());
	newItem->SetRandomTextList(inputMission->GetEvent()->GetRandomTextList());

	if (newItem->GetEventType() == 0)
		newItem->SetNoEvent(FALSE);

	//scroll.LineEnd();

	//scroll.ExecuteScrollPos();

	if (nViewHeight == 0) nViewHeight = 0;
	nViewHeight += ITEM_CTRL_HEIGHT;
	nItemHeight += ITEM_CTRL_HEIGHT;
	nLineCount++;


	SetScrollSize(cy);
	if (cy < nViewHeight) 
		OnVScroll(SB_LINEDOWN, 0, GetScrollBarCtrl(SB_VERT));


	activeMissionList.push_back(newItem);
}

void MissionListCtrl::DeleteItem(int nItemIndex)
{
	nLineCount--;

	for (int i = nItemIndex; i < (int)activeMissionList.size(); i++)
	{
		MissionListItem* updateItem = activeMissionList.at(i);
		updateItem->SetItemIndex(updateItem->GetItemIndex() - 1);
	}


	MissionListItem* selectItem = activeMissionList.at(nItemIndex);
	for (int i = 0; i < (int)activeMissionList.size(); i++)
	{
		if (i == nItemIndex)
		{
			activeMissionList.erase(activeMissionList.begin() + i);
			break;
		}
	}
	delete selectItem;
	selectItem = nullptr;

	int nFixScrollPage = nCurrentPage;
	nViewHeight = 2;
	nItemHeight = 2;
	nScrollPos = 0;
	nPageSize = 0;
	nCurrentPage = 0;

	SetScrollSize(cy);

	for (int i = 0; i < (int)activeMissionList.size(); i++)
	{
		MissionListItem* moveItem = activeMissionList.at(i);

		moveItem->MoveWindow(nItemHeight);

		nItemHeight += ITEM_CTRL_HEIGHT;
		nViewHeight += ITEM_CTRL_HEIGHT;
	}

	SetScrollSize(cy);

	for (int i = 0; i < nFixScrollPage; i++)
	{
		OnVScroll(SB_LINEDOWN, 0, GetScrollBarCtrl(SB_VERT));
	}
}

BOOL MissionListCtrl::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	// event버튼
	if (LOWORD(wParam) >= 20000 && LOWORD(wParam) < 25000)
	{
		CustomButton* eventButton = (CustomButton*)GetDlgItem((int)wParam);
		for (int i = 0; i < (int)activeMissionList.size(); i++)
		{
			MissionListItem* compare = activeMissionList.at(i);
			if (compare->IsSameEventButton(eventButton))
			{
				if (compare->GetEventType() == 0)
				{
					AfxMessageBox(_T("등록된 이벤트가 없습니다."), MB_OK | MB_ICONSTOP);
					break;
				}
				else if (compare->GetEventType() == 3)
				{
					break;
				}

				CString strOutput;
				EventSetting eventDlg(curentMissionList, compare, &strOutput, this);
				eventDlg.DoModal();

				if (strOutput.IsEmpty())
					break;

				if (compare->GetEventType() == 4)
				{
					int nMissionSeq = _ttoi(strOutput);
					MissionItem* selectMission = curentMissionList.at(nMissionSeq);
					compare->ChangeMission(selectMission->GetMissionName(), selectMission->GetEvent()->GetEventType(), selectMission->GetEvent()->GetRandomTextList());
					break;
				}

				compare->SetEventStatic(strOutput);

				break;
			}
		}
	}
	// x버튼
	else if (LOWORD(wParam) >= 25000)
	{
		CustomButton* closeButton = (CustomButton*)GetDlgItem((int)wParam);
		DeleteItem(closeButton->GetIndex());
		missionStart->nMissionCount--;
		CString strMissionCount;
		strMissionCount.Format(_T("보유중인 미션 : %d"), missionStart->nMissionCount);
		missionStart->m_stt_having_mission.SetWindowTextW(strMissionCount);

		return FALSE;
	}

	return CDialogEx::OnCommand(wParam, lParam);
}

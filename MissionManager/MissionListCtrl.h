#pragma once
#include "MissionListItem.h"
#include "MissionItem.h"


// MissionListCtrl 대화 상자
class MissionStart;

class MissionListCtrl : public CDialogEx
{
	DECLARE_DYNAMIC(MissionListCtrl)

	typedef std::vector<MissionListItem*> MissionOutputList;
	typedef std::vector<MissionItem*> MissionList;

public:
	MissionListCtrl(MissionList curentMissionList, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MissionListCtrl();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MISSIONLIST_DIALOG };
#endif

public:

	void InsertItem(MissionItem* inputMission, CString strMissionUserName);

private:

	MissionList curentMissionList;
	MissionOutputList activeMissionList;
	CWnd* pParent;
	MissionStart* missionStart;

	CBrush m_hBrush;

	int nViewHeight;
	int nScrollPos;
	int nPageSize;
	int m_nBasic;
	int cy;

	int nItemHeight;
	int nLineCount;
	int nCurrentPage;
	const int ITEM_CTRL_HEIGHT = 62;

	void SetScrollSize(int nThisHeight);
	void DeleteItem(int nItemIndex);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};

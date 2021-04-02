#pragma once
#include "MissionManagerDlg.h"
#include "MissionListCtrl.h"

// MissionStart 대화 상자

class MissionStart : public CDialogEx
{
	DECLARE_DYNAMIC(MissionStart)

	friend class MissionListCtrl;

	typedef std::vector<MissionItem*> MissionList;

public:
	MissionStart(MissionVersionItem* currentMissionVersionItem, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MissionStart();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MISSION_START_DIALOG };
#endif

public:


private:

	MissionVersionItem* currentMissionVersionItem;
	MissionList curentMissionList;
	MissionList sheildList;
	CWnd* pParent;
	CMissionManagerDlg* missionManager;
	MissionListCtrl* missionListCtrl;

	CustomButton m_btn_mission_extract;
	CustomButton m_btn_sheild_extract;
	CustomButton m_btn_timer;
	CustomStatic m_stt_mission_performer;
	CustomStatic m_stt_having_mission;
	CustomStatic m_stt_having_sheild;
	CustomEdit m_edit_mission_performer;

	int nMissionCount;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonStartExtract();
	afx_msg void OnBnClickedButtonSheildExtract();
};

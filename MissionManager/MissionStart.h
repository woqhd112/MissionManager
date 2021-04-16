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

	struct HavingMission
	{
		MissionItem* havingMission;
		CString strMissionPerformer;
		CString strEventText;
		bool bUsingEvent;
	};

	typedef std::vector<HavingMission*> HavingMissionList;

	struct ProgressingMissionStartingData
	{
		HavingMissionList havingMissionList;
		HavingMissionList havingSheildList;
		CString strMissionPerformer;
		CString strMissionText;
		int nMissionOutPrefixCount;
		int nMissionOutSuffixCount;
		int nSheildPrefixCount;
		int nSheildSuffixCount;
		int nHavingMissionCount;
		int nHavingSheildCount;
	};

	MissionStart(MissionVersionItem* currentMissionVersionItem, ProgressingMissionStartingData* pmsd = nullptr, CWnd* pParent = nullptr);   // 표준 생성자입니다.
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
	CustomStatic m_stt_mission_view_static;
	CustomEdit m_edit_mission_performer;
	CStatic m_stt_mission_view_picture;

	CStatic m_stt_group_count;
	CustomStatic m_stt_out_count;
	CustomStatic m_stt_sheild_count;
	CustomStatic m_stt_out_count_view;
	CustomStatic m_stt_sheild_count_view;
	CustomButton m_btn_count_setting;
	CustomButton m_btn_out_count_up;
	CustomButton m_btn_out_count_down;
	CustomButton m_btn_sheild_count_up;
	CustomButton m_btn_sheild_count_down;
	CustomButton m_btn_sheild_up;

	CBrush m_backBrush;
	CRect viewRect;

	COLORREF currentColor;

	ProgressingMissionStartingData* pmsd;

	int nMissionCount;


	void LoadProgressingMissionData();

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
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButtonStartCountSet();
	afx_msg void OnBnClickedButtonStartOutCountUp();
	afx_msg void OnBnClickedButtonStartOutCountDown();
	afx_msg void OnBnClickedButtonStartSheildCountUp();
	afx_msg void OnBnClickedButtonStartSheildCountDown();
	afx_msg void OnBnClickedButtonStartSheildUp();
	afx_msg void OnBnClickedButtonTimer();
};

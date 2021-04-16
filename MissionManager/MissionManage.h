#pragma once
#include "MissionVersionItem.h"
#include "MissionManagerDlg.h"

// MissionManage 대화 상자

class MissionManage : public CDialogEx
{
	DECLARE_DYNAMIC(MissionManage)

	friend class MissionAdd;
	typedef std::vector<MissionVersionItem*> VersionList;
	typedef std::vector<MissionItem*> MissionList;
	typedef std::vector<CString> RandomTextList;

public:
	MissionManage(VersionList cVersionList, MissionVersionItem* cMissionVersionItem, CRect parentRect, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MissionManage();

private:

	CustomButton m_btn_mission_add;
	CustomButton m_btn_mission_save;
	CustomButton m_btn_close;
	CStatic m_stt_input_group;
	CustomStatic m_stt_mission_name;
	CustomStatic m_stt_event_type;
	CustomStatic m_stt_random_output;
	CustomStatic m_stt_random_value_input;
	CustomStatic m_stt_version_name;
	CustomEdit m_edit_mission_name;
	CustomEdit m_edit_random_output;
	CustomEdit m_edit_version_name;
	CListCtrl m_list_mission_manage;
	CListCtrl m_list_random_output;
	CComboBox m_combo_event_type;

	CStatic m_stt_group_mission_grade;
	CButton m_radio_level_easy;
	CButton m_radio_level_middle;
	CButton m_radio_level_hard;

	VersionList cVersionList;
	MissionVersionItem* cMissionVersionItem;
	MissionList m_cMissionList;
	MissionList m_cNewMissionList;

	MissionItem* currentMission;

	bool bRandomListClickChange;
	int nRandomListClickRow;

	CWnd* pParent;
	CMissionManagerDlg* missionManager;

	CRect parentRect;

	void InitList();
	void LoadMissionList();
	void ExecuteMission();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MISSIONMANAGE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnNMClickListMissionManage(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeComboEventType();
	afx_msg void OnEnChangeEditMissionName();
	afx_msg void OnBnClickedButtonManageSave();
	afx_msg void OnBnClickedButtonManageClose();
	afx_msg void OnBnClickedButtonManageMissionAdd();
	afx_msg void OnNMClickListRandomOutputList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedRadioManageLevelEasy();
	afx_msg void OnBnClickedRadioManageLevelNormal();
	afx_msg void OnBnClickedRadioManageLevelHard();
};

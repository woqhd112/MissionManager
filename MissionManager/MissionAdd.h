#pragma once
#include "MissionItem.h"
#include "CustomButton.h"
#include "CustomStatic.h"
#include "CustomEdit.h"
#include "MissionManage.h"


// MissionAdd 대화 상자

class MissionAdd : public CDialogEx
{
	DECLARE_DYNAMIC(MissionAdd)

	typedef std::vector<CString> RandomTextList;

public:
	MissionAdd(int nMissionListSize, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MissionAdd();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MISSION_ADD_DIALOG };
#endif

public:


private:

	CustomStatic m_stt_mission_name;
	CustomStatic m_stt_event_type;
	CustomStatic m_stt_random_input_list;
	CustomStatic m_stt_random_value_input;
	CustomButton m_btn_save;
	CustomButton m_btn_close;
	CustomEdit m_edit_mission_name;
	CustomEdit m_edit_random_value_input;
	CComboBox m_combo_event_type;
	CListCtrl m_list_random_input_list;

	RandomTextList inputRandomTextList;
	CWnd* pParent;
	MissionManage* manage;

	bool bRandomListClickChange;
	int nRandomListClickRow;
	int nMissionListSize;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	afx_msg void OnBnClickedButtonAddClose();
	afx_msg void OnBnClickedButtonAddSave();
	afx_msg void OnCbnSelchangeComboAddEventType();
	afx_msg void OnNMClickListAddRandomInputList(NMHDR *pNMHDR, LRESULT *pResult);
};

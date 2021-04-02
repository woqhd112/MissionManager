#pragma once
#include "MissionListItem.h"
#include "MissionItem.h"

// EventSetting 대화 상자

class EventSetting : public CDialogEx
{
	DECLARE_DYNAMIC(EventSetting)

	typedef std::vector<MissionItem*> MissionList;
	typedef std::vector<CString> RandomTextList;

public:
	EventSetting(MissionList curentMissionList, MissionListItem* inputMission, CString* outputText, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~EventSetting();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETTING_EVENT_DIALOG };
#endif

public:


private:


	MissionList curentMissionList;
	CWnd* pParent;
	MissionListItem* inputMission;
	CString* outputText;

	CStatic m_stt_group_event;
	CustomStatic m_stt_event_text;
	CustomEdit m_edit_event_text;
	CustomButton m_btn_exact;
	CustomButton m_btn_save;
	CListBox m_list_event_random;

	int nDecreaseListCount;
	int nSelectMission;

	void DefaultEnableCtrlItem();
	void EnableRandomEvent();
	void EnableInputTextEvent();
	void EnableSpeakDirectlyEvent();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonExact();
	afx_msg void OnBnClickedButtonEventsetSave();
	afx_msg void OnLbnDblclkListEventRandomList();
};

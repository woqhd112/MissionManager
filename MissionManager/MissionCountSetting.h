#pragma once
#include "CustomStatic.h"
#include "CustomEdit.h"
#include "CustomButton.h"


// MissionCountSetting 대화 상자

class MissionCountSetting : public CDialogEx
{
	DECLARE_DYNAMIC(MissionCountSetting)

public:
	MissionCountSetting(int* nOut, int* nSheild, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MissionCountSetting();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MISSION_COUNT_SETTING_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:



private:

	CWnd* pParent;
	int* nOut;
	int* nSheild;

	CustomStatic m_stt_group_count;
	CustomStatic m_stt_out;
	CustomStatic m_stt_sheild;
	CustomEdit m_edit_out;
	CustomEdit m_edit_sheild;
	CustomButton m_btn_save_close;

public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonCountSave();
};

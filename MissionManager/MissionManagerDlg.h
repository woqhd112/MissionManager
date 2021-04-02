
// MissionManagerDlg.h: 헤더 파일
//

#pragma once
#include "CustomButton.h"
#include "CustomStatic.h"
#include "CustomEdit.h"
#include "MissionVersionItem.h"


// CMissionManagerDlg 대화 상자
class CMissionManagerDlg : public CDialogEx
{
// 생성입니다.
	typedef std::vector<MissionVersionItem*> VersionList;
	typedef std::vector<MissionItem*> MissionList;
	typedef std::vector<CString> RandomTextList;

public:
	CMissionManagerDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	~CMissionManagerDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MISSIONMANAGER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.

public:

	void ViewVersion(MissionVersionItem* cVersion);

private:

	CustomButton m_btn_mission_start;
	CustomButton m_btn_mission_manage;
	CustomButton m_btn_version_select;
	CustomStatic m_stt_version_name;
	CListCtrl m_list_mission_list;

	VersionList cVersionList;
	MissionVersionItem* cCurrentMissionVersionItem;

	void InitList();
	void LoadVersionList();

protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonMainVersionSelect();
	afx_msg void OnBnClickedButtonMainMissionManage();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonMainMissionStart();
};

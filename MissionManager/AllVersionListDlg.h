#pragma once
#include "MissionVersionItem.h"
#include "MissionManagerDlg.h"

// AllVersionListDlg 대화 상자

class AllVersionListDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AllVersionListDlg)

	typedef std::vector<MissionVersionItem*> VersionList;

public:
	AllVersionListDlg(VersionList cVersionList, CRect parentRect, CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~AllVersionListDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VERSIONLIST_DIALOG };
#endif

public:


private:

	CListCtrl m_list_all_version_list;

	VersionList m_cVersionList;

	CWnd* pParent;
	CMissionManagerDlg* missionManager;

	CRect parentRect;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnNMDblclkListAllVersionList(NMHDR *pNMHDR, LRESULT *pResult);
};

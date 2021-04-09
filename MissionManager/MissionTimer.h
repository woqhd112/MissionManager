#pragma once
#include "CustomStatic.h"
#include "CustomEdit.h"
#include "CustomButton.h"

#pragma comment(lib, "winmm")
#include <mmsystem.h>

// MissionTimer 대화 상자

class MissionTimer : public CDialogEx
{
	DECLARE_DYNAMIC(MissionTimer)

public:
	MissionTimer(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~MissionTimer();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MISSION_TIMER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()


public:



private:

	CStatic m_stt_picture;
	CustomEdit m_edit_minute;
	CustomEdit m_edit_second;
	CustomStatic m_stt_equal;
	CustomButton m_btn_start;
	CustomButton m_btn_reset;

	CWnd* pParent;

	CBrush m_backBrush;

	CRect drawBorderRect;

	CWinThread* m_thread;
	CWinThread* m_soundThread;

	bool bThread;
	bool bSoundThread;
	bool bStart;

	static UINT thrBaseTimer(LPVOID method);
	static UINT thrLoadSound(LPVOID method);
	void StartBaseTimer();
	void StartSound(int nSoundResourceID);
	bool DeleteMainThread();
	void ResetDefaultValue();

public:
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnClose();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedButtonTimerStart();
	afx_msg void OnBnClickedButtonTimerReset();
	afx_msg void OnPaint();
};

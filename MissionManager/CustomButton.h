#pragma once
#include "GeneralUtil.h"

// CustomButton

class CustomButton : public CMFCButton
{
	DECLARE_DYNAMIC(CustomButton)

public:
	CustomButton();
	virtual ~CustomButton();

	void Initialize(COLORREF color, FlatStyle style, CString strFontName = _T("Tahoma"), int nFontSize = 10, int nFontFlags = FW_NORMAL);
	void InsertImage(int nImageID);
	void SetAlignment(CMFCButton::AlignStyle style);
	void ColorUpdate(COLORREF updateColor);

	void SetIndex(int nIndex);
	int GetIndex() const;

	COLORREF m_defaultColor;
	COLORREF m_hoverColor;
	COLORREF m_downColor;
	bool m_bUseMouseBkGroundColorEvent;
	bool m_bClick;
	bool m_bUseMouseTextItalicEvent;
	bool m_bUseMouseTextBoldEvent;


private:
	bool m_bTrackMouse = false;
	bool m_bDown;
	int nImageID;
	int nID;
	int nIndex;

	CFont defaultFont;
	CFont hoverFont;
	CFont clickFont;
	CFont clickHoverFont;


protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};



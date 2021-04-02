#pragma once


// CustomEdit

class CustomEdit : public CEdit
{
	DECLARE_DYNAMIC(CustomEdit)

public:
	CustomEdit();
	virtual ~CustomEdit();

	void Initialize(int nFontSize, CString strFontName);

	bool m_bExampleText;
	bool m_bFocusOn;

private:

	CFont thisFont;

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};



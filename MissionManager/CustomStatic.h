#pragma once


// CustomStatic

class CustomStatic : public CStatic
{
	DECLARE_DYNAMIC(CustomStatic)

public:
	CustomStatic();
	virtual ~CustomStatic();

	void Initialize(int nFontSize, CString strFontName);
	void InvalidFont(CString strFontName);

	CString strFontName;
	int nFontSize;
private:

	CFont thisFont;

protected:
	DECLARE_MESSAGE_MAP()
};



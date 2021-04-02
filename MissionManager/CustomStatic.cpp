// CustomStatic.cpp: 구현 파일
//

#include "pch.h"
#include "MissionManager.h"
#include "CustomStatic.h"


// CustomStatic

IMPLEMENT_DYNAMIC(CustomStatic, CStatic)

CustomStatic::CustomStatic()
{
	nFontSize = 0;
	strFontName = _T("");
}

CustomStatic::~CustomStatic()
{
}


BEGIN_MESSAGE_MAP(CustomStatic, CStatic)
END_MESSAGE_MAP()



// CustomStatic 메시지 처리기

void CustomStatic::Initialize(int nFontSize, CString strFontName)
{
	this->strFontName = strFontName;
	this->nFontSize = nFontSize;
	thisFont.CreateFontW(nFontSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
		strFontName);
	this->SetFont(&thisFont);

}

void CustomStatic::InvalidFont(CString strFontName)
{
	this->strFontName = strFontName;
	thisFont.DeleteObject();
	thisFont.CreateFontW(nFontSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
		strFontName);
	this->SetFont(&thisFont);
}



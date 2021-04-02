// CustomButton.cpp: 구현 파일
//

#include "pch.h"
#include "MissionManager.h"
#include "CustomButton.h"


// CustomButton

IMPLEMENT_DYNAMIC(CustomButton, CMFCButton)

CustomButton::CustomButton()
{
	m_defaultColor = RGB(220, 220, 220);
	m_hoverColor = RGB(200, 200, 200);
	m_downColor = RGB(150, 150, 150);
	m_bUseMouseBkGroundColorEvent = true;
	m_bClick = false;
	m_bUseMouseTextItalicEvent = false;
	m_bUseMouseTextBoldEvent = false;
	m_bDown = false;
	nIndex = 0;
}

CustomButton::~CustomButton()
{
}


BEGIN_MESSAGE_MAP(CustomButton, CMFCButton)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CustomButton 메시지 처리기


void CustomButton::Initialize(COLORREF color, FlatStyle style, CString strFontName /*= _T("Tahoma")*/, int nFontSize /*= 10*/, int nFontFlags /*= FW_NORMAL*/)
{
	this->EnableWindowsTheming(FALSE);
	this->SetFaceColor(color);
	this->m_bDrawFocus = FALSE;

	nID = this->GetDlgCtrlID();
	ColorUpdate(color);

	defaultFont.CreateFontW(nFontSize, 0, 0, 0, nFontFlags, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
		strFontName);
	hoverFont.CreateFontW(nFontSize, 0, 0, 0, FW_NORMAL, FALSE, TRUE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
		strFontName);
	clickFont.CreateFontW(nFontSize, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
		strFontName);
	clickHoverFont.CreateFontW(nFontSize, 0, 0, 0, FW_BOLD, FALSE, TRUE, 0, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS,
		strFontName);

	this->CMFCButton::SetFont(&defaultFont);
	this->m_nFlatStyle = style;
	//this->SetTextColor(RGB(255, 255, 255));
}

void CustomButton::ColorUpdate(COLORREF updateColor)
{
	int nRv = GetRValue(updateColor);
	int nGv = GetGValue(updateColor);
	int nBv = GetBValue(updateColor);

	m_defaultColor = updateColor;
	m_hoverColor = RGB(MinRGBColor(nRv, 20), MinRGBColor(nGv, 20), MinRGBColor(nBv, 20));
	m_downColor = RGB(MinRGBColor(nRv, 50), MinRGBColor(nGv, 50), MinRGBColor(nBv, 50));
}

void CustomButton::SetAlignment(CMFCButton::AlignStyle style)
{
	this->m_nAlignStyle = style;
}

void CustomButton::InsertImage(int nImageID)
{
	CPngImage pngImage;
	pngImage.Load(nImageID);
	HBITMAP bitmap = (HBITMAP)pngImage.Detach();
	this->m_bTransparent = TRUE;
	this->m_bDrawFocus = FALSE;
	this->SetImage(bitmap, TRUE);
	this->SizeToContent();
	this->nImageID = nImageID;
}


void CustomButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (!m_bTrackMouse)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_HOVER | TME_LEAVE;
		tme.dwHoverTime = 1;
		if (TrackMouseEvent(&tme))
		{
			m_bTrackMouse = true;
		}
	}


	CMFCButton::OnMouseMove(nFlags, point);
}


void CustomButton::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_bUseMouseBkGroundColorEvent)
	{
		this->SetFaceColor(m_hoverColor);
	}

	if (m_bUseMouseTextItalicEvent)
	{
		if (m_bClick)
		{
			this->CMFCButton::SetFont(&clickHoverFont);
		}
		else
		{
			this->CMFCButton::SetFont(&hoverFont);
		}
	}

	CMFCButton::OnMouseHover(nFlags, point);
}


void CustomButton::OnMouseLeave()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_bUseMouseBkGroundColorEvent)
	{
		this->SetFaceColor(m_defaultColor);
	}

	if (m_bUseMouseTextItalicEvent)
	{
		if (m_bClick)
		{
			this->CMFCButton::SetFont(&clickFont);
		}
		else
		{
			this->CMFCButton::SetFont(&defaultFont);
		}
	}

	m_bTrackMouse = false;
	CMFCButton::OnMouseLeave();
}



void CustomButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_bUseMouseBkGroundColorEvent)
	{
		this->SetFaceColor(m_downColor);
	}

	if (m_bUseMouseTextBoldEvent)
	{
		m_bDown = true;
		this->CMFCButton::SetFont(&clickFont);
	}


	CMFCButton::OnLButtonDown(nFlags, point);
}


void CustomButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_bUseMouseBkGroundColorEvent)
	{
		this->SetFaceColor(m_hoverColor);
	}

	if (m_bUseMouseTextBoldEvent)
	{
		if (m_bDown)
		{
			m_bDown = false;
			this->CMFCButton::SetFont(&hoverFont);
		}
	}


	CMFCButton::OnLButtonUp(nFlags, point);
}

void CustomButton::SetIndex(int nIndex)
{
	this->nIndex = nIndex;
}

int CustomButton::GetIndex() const
{
	return nIndex;
}

#include "pch.h"
#include "CustomScroll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CustomScroll::CustomScroll()
{
	csi = { CUSTOM_SCROLL_TYPE_DEFAULT, CUSTOM_SCROLL_FLAGS_VERTICAL, CUSTOM_SCROLL_EVENT_DEFAULT, 0, 0, 0 };
	nLineCount = 0;
	nCurrentLinePos = 0;
	nButtonID = 30000;
	bOneButtonLight = false;
	nSceMaxCounts = 0;
}

CustomScroll::~CustomScroll()
{
	Destroy();
}

void CustomScroll::Destroy()
{
	csi = { CUSTOM_SCROLL_TYPE_DEFAULT, CUSTOM_SCROLL_FLAGS_VERTICAL, CUSTOM_SCROLL_EVENT_DEFAULT, 0, 0, 0 };

	nLineCount = 0;
	nCurrentLinePos = 0;
	bOneButtonLight = false;
	nSceMaxCounts = 0;
}

void CustomScroll::Create(CWnd* pDialogCtl)
{
	thisCtlDialog = pDialogCtl;
	csi = { CUSTOM_SCROLL_TYPE_DEFAULT, CUSTOM_SCROLL_FLAGS_VERTICAL, CUSTOM_SCROLL_EVENT_DEFAULT, 0, 0, 0 };
	nLineCount = 0;
	nCurrentLinePos = 0;
	nButtonID = 30000;
	bOneButtonLight = false;
	nSceMaxCounts = 0;
}

void CustomScroll::Initialize(CustomScrollInfo csi)
{
	this->csi = csi;
}

void CustomScroll::LineEnd()
{
	LineAnyEnd();
	nLineCount++;
}

void CustomScroll::LineAnyEnd()
{
	csi.nAllPageSize += csi.nOnePageSize;
}

void CustomScroll::LineDelete()
{
	csi.nAllPageSize -= csi.nOnePageSize;
	nLineCount--;
}

void CustomScroll::IncreaseScroll()
{
	LineEnd();
}

// CustomScrollType이 버튼인경우만 사용할것.
void CustomScroll::ExecuteScrollPos()
{
	LoadScroll(csi.nOnePageSize);
}

void CustomScroll::LoadScroll(int nThisHeight)
{
	int nScrollMax = 0;
	if (nThisHeight < csi.nAllPageSize)
	{
		nScrollMax = csi.nAllPageSize - 1;
		csi.nOnePageSize = nThisHeight;
		csi.nScrollPos = min(csi.nScrollPos, csi.nAllPageSize - csi.nOnePageSize - 1);
	}

	SCROLLINFO si;
	si.fMask = SIF_RANGE | SIF_PAGE | SIF_POS;
	si.nMin = 0;
	si.nMax = nScrollMax;
	si.nPos = csi.nScrollPos;
	si.nPage = csi.nOnePageSize;
	thisCtlDialog->SetScrollInfo(csi.csf, &si, TRUE);
}

int CustomScroll::GetCalculateLinePos(CustomScrollEvent cse, int nSBCode)
{
	int nReturnLinePos = 0;
	if (cse == CUSTOM_SCROLL_EVENT_DEFAULT)
	{
		if (nSBCode == SB_LINEUP || nSBCode == SB_PAGEUP)
		{
			nCurrentLinePos--;
		}
		else if (nSBCode == SB_LINEDOWN || nSBCode == SB_PAGEDOWN)
		{
			nCurrentLinePos++;
		}
		nReturnLinePos = nCurrentLinePos;
	}
	else if (cse == CUSTOM_SCROLL_EVENT_INCREASE_COUNT_LINE)
	{
		if (nSBCode == SB_LINEUP || nSBCode == SB_PAGEUP)
		{
			nSceMaxCounts--;
		}
		else if (nSBCode == SB_LINEDOWN || nSBCode == SB_PAGEDOWN)
		{
			nSceMaxCounts++;
		}

		if (nSceMaxCounts < 0)
			nSceMaxCounts = 0;
		if (nSceMaxCounts > nLineCount - 1)
			nSceMaxCounts = nLineCount - 1;

		nCurrentLinePos = nSceMaxCounts / csi.nCseMaxCount;

		nReturnLinePos = nCurrentLinePos;

	}

	return nReturnLinePos;
}

// 이 함수는 OnVScroll 이나 OnHScroll 함수안에서 호출할것.
bool CustomScroll::OperateScroll(int nSBCode, int nPos)
{
	int delta = 0;
	switch (nSBCode)
	{
	case SB_LINEUP:
		delta = -csi.nWheelValue;
		GetCalculateLinePos(csi.cse, SB_LINEUP);
		//nCurrentLinePos--;
		break;
	case SB_PAGEUP:
		delta = -csi.nOnePageSize;
		GetCalculateLinePos(csi.cse, SB_PAGEUP);
		//nCurrentLinePos--;
		break;
	case SB_THUMBTRACK:
		delta = static_cast<int>(nPos) - csi.nScrollPos;
		break;
	case SB_PAGEDOWN:
		delta = csi.nOnePageSize;
		GetCalculateLinePos(csi.cse, SB_PAGEDOWN);
		//nCurrentLinePos++;
		break;
	case SB_LINEDOWN:
		delta = csi.nWheelValue;
		GetCalculateLinePos(csi.cse, SB_LINEDOWN);
		//nCurrentLinePos++;
		break;
	default:
		return false;
	}

	if (nCurrentLinePos < 0)
	{
		nCurrentLinePos = 0;
		return false;
	}
	if (csi.bLikeButtonEvent)
	{
		if (nCurrentLinePos >= nLineCount)
		{
			nCurrentLinePos = nLineCount - 1;
			return false;
		}
	}

	int scrollpos = csi.nScrollPos + delta;
	int nMaxPos = csi.nAllPageSize - csi.nOnePageSize;

	if (scrollpos < 0)
	{
		delta = -csi.nScrollPos;
	}
	else
	{
		if (scrollpos > nMaxPos)
		{
			delta = nMaxPos - csi.nScrollPos;
		}
	}

	if (delta != 0)
	{
		csi.nScrollPos += delta;
		thisCtlDialog->SetScrollPos(csi.csf, csi.nScrollPos, TRUE);
		if (csi.csf == CUSTOM_SCROLL_FLAGS_VERTICAL)
			thisCtlDialog->ScrollWindow(0, -delta);
		else
			thisCtlDialog->ScrollWindow(-delta, 0);

		return true;
	}


	return false;
}

void CustomScroll::SetDefaultLinePos()
{
	nCurrentLinePos = 0;
}

// 이 함수는 OnMouseWheel 함수안에서 호출할것.
// 호출 후 OnVScroll 이나 OnHScroll 호출할것.
UINT CustomScroll::OperateWheel(short zDelta)
{

	UINT nFlag;
	if (zDelta > 0)	// 위스크롤
	{
		if (csi.cst == CUSTOM_SCROLL_TYPE_DEFAULT) nFlag = SB_LINEUP;
		else nFlag = SB_PAGEUP;
	}
	else // 아래스크롤
	{
		if (csi.cst == CUSTOM_SCROLL_TYPE_DEFAULT) nFlag = SB_LINEDOWN;
		else nFlag = SB_PAGEDOWN;
	}

	return nFlag;
}

int CustomScroll::GetLineCount()
{
	return nLineCount;
}

int CustomScroll::GetCurrentLinePos()
{
	return nCurrentLinePos + 1;
}
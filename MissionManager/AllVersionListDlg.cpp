// AllVersionListDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MissionManager.h"
#include "AllVersionListDlg.h"
#include "afxdialogex.h"


// AllVersionListDlg 대화 상자

IMPLEMENT_DYNAMIC(AllVersionListDlg, CDialogEx)

AllVersionListDlg::AllVersionListDlg(VersionList cVersionList, CRect parentRect, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_VERSIONLIST_DIALOG, pParent)
{
	this->parentRect = parentRect;
	this->pParent = pParent;
	this->m_cVersionList = cVersionList;
}

AllVersionListDlg::~AllVersionListDlg()
{
}

void AllVersionListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ALL_VERSION_LIST, m_list_all_version_list);
}


BEGIN_MESSAGE_MAP(AllVersionListDlg, CDialogEx)
	ON_WM_CLOSE()
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ALL_VERSION_LIST, &AllVersionListDlg::OnNMDblclkListAllVersionList)
END_MESSAGE_MAP()


// AllVersionListDlg 메시지 처리기


BOOL AllVersionListDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	this->MoveWindow(parentRect.right, parentRect.top, 300, 400);
	m_list_all_version_list.MoveWindow(10, 10, 265, 330);

	CImageList imgGap;
	imgGap.Create(1, 20, ILC_COLORDDB, 1, 0);
	m_list_all_version_list.SetImageList(&imgGap, LVSIL_SMALL);

	m_list_all_version_list.InsertColumn(0, _T("버전명"), LVCFMT_CENTER, 260);

	m_list_all_version_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER | LVS_EX_GRIDLINES);


	for (int i = 0; i < (int)m_cVersionList.size(); i++)
	{
		m_list_all_version_list.InsertItem(i, m_cVersionList.at(i)->GetVersionName());
	}

	missionManager = (CMissionManagerDlg*)pParent;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void AllVersionListDlg::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CDialogEx::OnOK();
}


BOOL AllVersionListDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN) // ENTER키 눌릴 시
			return TRUE;
		else if (pMsg->wParam == VK_ESCAPE) // ESC키 눌릴 시
			return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void AllVersionListDlg::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CDialogEx::OnClose();
}


HBRUSH AllVersionListDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


void AllVersionListDlg::OnNMDblclkListAllVersionList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int row = pNMItemActivate->iItem;	// 세로 행
	int col = pNMItemActivate->iSubItem;	// 가로 칼럼

	// 행 선택 되었을 때
	if (row > -1)
	{
		MissionVersionItem* selectVersion = m_cVersionList.at(row);
		missionManager->ViewVersion(selectVersion);
		PostMessage(WM_CLOSE);
	}

	*pResult = 0;
}

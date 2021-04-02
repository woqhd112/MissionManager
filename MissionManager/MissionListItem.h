#pragma once
#include "CustomButton.h"
#include "CustomEdit.h"
#include "CustomStatic.h"
#include <vector>


class MissionListItem
{

	typedef std::vector<CString> RandomTextList;

public:
	MissionListItem(CWnd* pParent);
	~MissionListItem();

	void Create(int nListSize);
	void MoveWindow(int y);
	void SetMissionName(CString strMissionName);
	void SetEventType(int nEventType);
	void SetMissionUserName(CString strMissionUserName);
	void SetItemIndex(int nIndex);
	void SetPos(int y);
	void SetRandomTextList(RandomTextList vRandomTextList);
	void SetEventStatic(CString strStatic);
	void ChangeMission(CString strMissionName, int nEventType, RandomTextList vRandomTextList);
	void SetNoEvent(BOOL bChange);


	int GetEventType() const;
	RandomTextList GetRandomTextList() const;
	int GetItemIndex() const;
	int GetPos() const;


	bool IsSameEventButton(CustomButton* compareButton);

private:

	CWnd* pParent;

	CustomButton* wrapButton1;
	CustomButton* wrapButton2;
	CustomStatic* winnerNameStatic;
	CustomStatic* missionStatic;
	CustomStatic* resultStatic;
	CustomStatic* eventStatic;
	CustomButton* eventButton;
	CustomButton* closeButton;

	RandomTextList m_vRandomTextList;
	CString m_strMissionUserName;
	CString m_strMissionName;
	int m_nEventType;
	int nIndex;

	int nPos;

	int nDivideWidth;

};


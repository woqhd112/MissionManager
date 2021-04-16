#pragma once
#include "EventItem.h"



class MissionItem
{

public:

	MissionItem();
	~MissionItem();

	void SetMissionSequence(int nMissionSequence);
	void SetMissionName(CString strMissionName);
	void SetEvent(EventItem* hEvent);
	void SetMissionGrade(int nGrade);
	void SetMissionPerformer(CString strMissionPerformer);

	int GetMissionGrade() const;
	int GetMissionSequence() const;
	CString GetMissionName() const;
	EventItem* GetEvent() const;
	CString GetMissionPerformer() const;

private:

	int m_nMissionGrade;
	int m_nMissionSequence;
	CString m_strMissionName;
	CString m_strMissionPerformer;
	EventItem* m_hEventItem;

};


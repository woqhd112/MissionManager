#pragma once
#include "MissionItem.h"



class MissionVersionItem
{

	typedef std::vector<MissionItem*> MissionList;

public:

	MissionVersionItem();
	~MissionVersionItem();

	void SetVersionName(CString strVersionName);
	void SetMission(MissionList hMissionList);

	CString GetVersionName() const;
	MissionList GetMission() const;

private:

	CString m_strVersionName;
	MissionList m_cMissionList;

};


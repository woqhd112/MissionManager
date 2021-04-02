#include "pch.h"
#include "MissionVersionItem.h"

MissionVersionItem::MissionVersionItem()
{
	m_strVersionName = _T("");
}

MissionVersionItem::~MissionVersionItem()
{
	for (int i = 0; i < (int)m_cMissionList.size(); i++)
	{
		MissionItem* deleteMission = m_cMissionList.at(i);
		delete deleteMission;
		deleteMission = nullptr;
	}
	m_cMissionList.clear();
}

void MissionVersionItem::SetVersionName(CString strVersionName)
{
	m_strVersionName = strVersionName;
}

void MissionVersionItem::SetMission(MissionList hMissionList)
{
	m_cMissionList = hMissionList;
}

CString MissionVersionItem::GetVersionName() const
{
	return m_strVersionName;
}

MissionVersionItem::MissionList MissionVersionItem::GetMission() const
{
	return m_cMissionList;
}
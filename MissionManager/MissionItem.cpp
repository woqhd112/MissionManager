#include "pch.h"
#include "MissionItem.h"

MissionItem::MissionItem()
{
	m_nMissionGrade = 0;
	m_nMissionSequence = 0;
	m_strMissionName = _T("");
}

MissionItem::~MissionItem()
{
	delete m_hEventItem;
	m_hEventItem = nullptr;
}

void MissionItem::SetMissionSequence(int nMissionSequence)
{
	m_nMissionSequence = nMissionSequence;
}

void MissionItem::SetMissionName(CString strMissionName)
{
	m_strMissionName = strMissionName;
}

void MissionItem::SetEvent(EventItem* hEvent)
{
	m_hEventItem = hEvent;
}

void MissionItem::SetMissionGrade(int nGrade)
{
	this->m_nMissionGrade = nGrade;
}

void MissionItem::SetMissionPerformer(CString strMissionPerformer)
{
	this->m_strMissionPerformer = strMissionPerformer;
}

int MissionItem::GetMissionGrade() const
{
	return m_nMissionGrade;
}

int MissionItem::GetMissionSequence() const
{
	return m_nMissionSequence;
}

CString MissionItem::GetMissionName() const
{
	return m_strMissionName;
}

EventItem* MissionItem::GetEvent() const
{
	return m_hEventItem;
}

CString MissionItem::GetMissionPerformer() const
{
	return m_strMissionPerformer;
}
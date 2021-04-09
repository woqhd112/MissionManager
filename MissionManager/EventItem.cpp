#include "pch.h"
#include "EventItem.h"

EventItem::EventItem()
{
	bUsing = false;
}

EventItem::~EventItem()
{
	m_cRandomTextList.clear();
}

void EventItem::SetEventType(EventType eType)
{
	m_eType = eType;
}

void EventItem::SetEventType(int nType)
{
	if (nType == 0) m_eType = EVENT_NONE;
	else if (nType == 1) m_eType = EVENT_RANDOM_PRESET;
	else if (nType == 2) m_eType = EVENT_RANDOM_POSTSET;
	else if (nType == 3) m_eType = EVENT_INPUTTEXT;
	else if (nType == 4) m_eType = EVENT_SHIELD;
	else if (nType == 5) m_eType = EVENT_SPEAKDIRECTLY;
}

void EventItem::SetRandomTextList(RandomTextList cRandomTextList)
{
	m_cRandomTextList = cRandomTextList;
}

void EventItem::SetUsingEvent(bool bUse)
{
	this->bUsing = bUse;
}

bool EventItem::IsUsing() const
{
	return bUsing;
}

EventItem::EventType EventItem::GetEventType() const
{
	return m_eType;
}

EventItem::RandomTextList EventItem::GetRandomTextList() const
{
	return m_cRandomTextList;
}
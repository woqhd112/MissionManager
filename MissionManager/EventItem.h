#pragma once
#include <vector>
#include "atlstr.h"

class EventItem
{
	typedef std::vector<CString> RandomTextList;

public:

	EventItem();
	~EventItem();

	enum EventType
	{
		EVENT_NONE				= 0,
		EVENT_RANDOM_PRESET		= 1,
		EVENT_RANDOM_POSTSET	= 2,
		EVENT_INPUTTEXT			= 3,
		EVENT_SHIELD			= 4,
		EVENT_SPEAKDIRECTLY		= 5,
	};

	void SetEventType(EventType eType);
	void SetEventType(int nType);
	void SetRandomTextList(RandomTextList cRandomEditList);
	void SetUsingEvent(bool bUse);

	bool IsUsing() const;
	EventType GetEventType() const;
	RandomTextList GetRandomTextList() const;

private:
	
	bool bUsing;
	EventType m_eType;
	RandomTextList m_cRandomTextList;

};


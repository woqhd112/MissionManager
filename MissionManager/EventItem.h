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
		EVENT_NONE			= 0,
		EVENT_RANDOM		= 1,
		EVENT_INPUTTEXT		= 2,
		EVENT_SHIELD		= 3,
		EVENT_SPEAKDIRECTLY	= 4,
	};

	void SetEventType(EventType eType);
	void SetEventType(int nType);
	void SetRandomTextList(RandomTextList cRandomEditList);

	EventType GetEventType() const;
	RandomTextList GetRandomTextList() const;

private:

	EventType m_eType;
	RandomTextList m_cRandomTextList;

};


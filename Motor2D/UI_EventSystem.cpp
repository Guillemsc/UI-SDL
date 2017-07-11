#include "UI_EventSystem.h"
#include "UI_Element.h"

UI_EventSystem::UI_EventSystem()
{
}

UI_EventSystem::~UI_EventSystem()
{
}

void UI_EventSystem::CleanUp()
{
}

UI_Event::UI_Event(ui_event_type _type, weak_ptr<UI_Element> _sender)
{
	event_type = _type;
	sender = _sender;
}

UI_Event::~UI_Event()
{
}

ui_event_type UI_Event::GetEventType()
{
	return event_type;
}

weak_ptr<UI_Element> UI_Event::GetSender()
{
	return sender;
}

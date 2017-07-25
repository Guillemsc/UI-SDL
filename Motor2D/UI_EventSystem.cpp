#include "UI_EventSystem.h"
#include "UI_Element.h"
#include "p2Log.h"

#define MAX_EVENTS_STORED 250

UI_EventSystem::UI_EventSystem(UI_Main* _ui_main)
{
	ui_main = _ui_main;
}

UI_EventSystem::~UI_EventSystem()
{
}

void UI_EventSystem::Start()
{
}

void UI_EventSystem::Update()
{
	if (events.size() > MAX_EVENTS_STORED)
	{
		delete *events.begin();
		events.erase(events.begin());
	}
}

void UI_EventSystem::CleanUp()
{
	ui_main = nullptr;

	for (list<UI_Event*>::iterator it = events.begin(); it != events.end();)
	{
		delete (*it);
		it = events.erase(it);
	}
}

void UI_EventSystem::SendEvent(UI_Event * ev)
{
	if(ui_main != nullptr)
		ui_main->ExpandEvent(ev);

	events.push_back(ev);
}

UI_Event::UI_Event(ui_event_type _type, UI_Element* _sender)
{
	event_type = _type;
	sender = _sender;
}

UI_Event::~UI_Event()
{
}

void UI_Event::CleanUp()
{

}

ui_event_type UI_Event::GetEventType()
{
	return event_type;
}

UI_Element* UI_Event::GetSender()
{
	return sender;
}

UI_EventMouse::UI_EventMouse(ui_event_type type, UI_Element * sender, bool _button_left, bool _button_right) : UI_Event(type, sender)
{
	button_left = _button_left;
	button_right = _button_right;
}

UI_EventMouse::~UI_EventMouse()
{
}

bool UI_EventMouse::ButtonLeft()
{
	return button_left;
}

bool UI_EventMouse::ButtonRight()
{
	return right;
}

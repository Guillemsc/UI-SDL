#ifndef __UI_EventSystem_H__
#define __UI_EventSystem_H__

#include "UI_Main.h"

class UI_EventSystem;
enum ui_event_type;

// --------------------------------------------------

class UI_EventSystem
{
public:
	UI_EventSystem(UI_Main* ui_main);
	virtual ~UI_EventSystem();

	void CleanUp();

	void SendEvent(UI_Event* ev);

private:
	UI_Main* ui_main = nullptr;
};

// --------------------------------------------------

class UI_Event
{
public:
	UI_Event(ui_event_type type, weak_ptr<UI_Element> sender);
	virtual ~UI_Event();

	void CleanUp();

	ui_event_type GetEventType();
	weak_ptr<UI_Element> GetSender();

private:
	ui_event_type event_type = (ui_event_type)0;
	weak_ptr<UI_Element> sender;
};

enum ui_event_type
{
	event_null,
	event_click,
	event_double_click,
	event_mouse_over,
	event_mouse_enter,
	event_mouse_out,
	event_destroy,
};

#endif // __UI_EventSystem_H__
#ifndef __UI_EventSystem_H__
#define __UI_EventSystem_H__

#include "UI_Main.h"

class UI_EventSystem
{
public:
	UI_EventSystem();
	virtual ~UI_EventSystem();

	void CleanUp();
};

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
	null,
	click,
	double_click,
	mouse_over,
	mouse_enter,
	mouse_out,
	destroy,
};

#endif // __UI_EventSystem_H__
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

	void Start();
	void Update();
	void PostUpdate();
	void CleanUp();

	void SendEvent(UI_Event* ev);

private:
	UI_Main* ui_main = nullptr;

	list<UI_Event*> events;
};

// --------------------------------------------------

class UI_Event
{
public:
	UI_Event(ui_event_type type, UI_Element* sender = nullptr);
	virtual ~UI_Event();

	void CleanUp();

	ui_event_type GetEventType();
	UI_Element* GetSender();

private:
	ui_event_type event_type = (ui_event_type)0;
	UI_Element*   sender = nullptr;
};

// --------------------------------------------------

class UI_EventMouse : public UI_Event
{
public:
	UI_EventMouse(ui_event_type type, UI_Element* sender, bool _button_left, bool _button_right);

	virtual ~UI_EventMouse();

	bool ButtonLeft();
	bool ButtonRight();

private:
	bool button_left = false;
	bool button_right = false;
};

// --------------------------------------------------

class UI_EventTarget : public UI_Event
{
public:
	UI_EventTarget(ui_event_type type, UI_Element* sender, UI_Element* target);

	virtual ~UI_EventTarget();

	UI_Element* GetTarget();

private:
	UI_Element* target = nullptr;
};

// --------------------------------------------------

enum ui_event_type
{
	event_null,

	event_mouse_over,
	event_mouse_over_enter,
	event_mouse_over_out,
	event_mouse_click,
	event_mouse_double_click,
	event_mouse_down,
	event_mouse_up,

	event_delete,

	event_interactable_on,
	event_interactable_off,
	event_visible_on,
	event_visible_off,

	event_interpolation_anim_finished,
	event_alpha_anim_finished,

	event_child_added,
	event_child_removed,

	event_window_resize,
};

#endif // __UI_EventSystem_H__
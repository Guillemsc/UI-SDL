#ifndef __UI_Panel_H__
#define __UI_Panel_H__

#include "UI_Element.h"

class UI_Main;

struct ui_panel_element
{
	UI_Element* element;
	UI_Point starting_pos;
};

class UI_Panel : public UI_Element
{
public:
	UI_Panel(UI_Main* ui_main);
	
private:
	void Update();
	void Draw();
	void OnEvent(UI_Event* ev);
	void CleanUp();

	void UpdateSize();

public:
	UI_Button* updown_scroll_button = nullptr;
	UI_Button* leftright_scroll_button = nullptr;

	float updown_scroll = 0.0f;
	float leftright_scroll = 0.0f;

	float updown_button_pos = 0.0f;

	float updown_size = 0.0f;
	float leftright_size = 0.0f;

	bool track_updown = false;

	int button_size = 0;

	UI_Point last_mouse;

	list<ui_panel_element> panel_elements;
};

#endif
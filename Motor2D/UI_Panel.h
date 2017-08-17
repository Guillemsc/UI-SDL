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

	void SetUseScrolls(bool set);
	void SetAutoScrollDown(float set);
	
private:
	void Update();
	void Draw();
	void OnEvent(UI_Event* ev);
	void CleanUp();

	void UpdateUpdownButton();
	void UpdownInput();
	void UpdateUpdownScroll();

	void UpdateLeftrightButton();
	void LeftrightInput();
	void UpdateLeftrightScroll();

	void UpdateElementsPos();

	void ScrollDown();

public:
	bool auto_scroll_down = false;
	bool use_scrolls = false;

	// Button
	UI_Button* updown_scroll_button = nullptr;
	UI_Button* leftright_scroll_button = nullptr;

	// Scroll positoin
	float updown_scroll = 0.0f;
	float leftright_scroll = 0.0f;

	// Button position
	float updown_button_pos = 0.0f;
	float leftright_button_pos = 0.0f;

	// Size of the elements
	float updown_size = 0.0f;
	float leftright_size = 0.0f;

	// Track mouse pos
	bool track_updown = false;
	bool track_leftright = false;

	// Button size
	int button_size = 0;

	// Last mouse pos
	UI_Point last_mouse;

	// List of elements
	list<ui_panel_element> panel_elements;
};

#endif
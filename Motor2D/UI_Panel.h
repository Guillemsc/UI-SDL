#ifndef __UI_Panel_H__
#define __UI_Panel_H__

#include "UI_Element.h"

class UI_Main;

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

	float updrown_scroll = 0.0f;
	float leftright_scroll = 0.0f;

	float updown_size = 0.0f;
	float leftright_size = 0.0f;

	int button_size = 0;
};

#endif
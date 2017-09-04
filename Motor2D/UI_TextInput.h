#ifndef __UI_TextInput_H__
#define __UI_TextInput_H__

#include "UI_Element.h"

class UI_Main;

enum ui_textinputevent
{
	ui_null,
	ui_bar_left,
	ui_bar_right,
	ui_text_input,
	ui_backspace,
	ui_delete,
};

class UI_TextInput : public UI_Element
{
public:
	UI_TextInput(UI_Main* ui_main);
	void SetText(char* text);
	UI_Text* GetText();

private:
	void Update(float dt);
	void CleanUp();
	void Draw();
	void OnEvent(UI_Event* ev);

	void UpdateBarPos(float dt);
	void UpdateDynamicPos();

private:
	UI_Text* text = nullptr;
	string   internal_text = "";

	int bar_pos = 0;
	int bar_x = 0;
	int bar_w = 2;
	float bar_flicker_time = 0;
	float bar_flicker_total_time = 1.0f;

	ui_textinputevent curr_event = ui_null;

	bool update_text = false;
};

#endif
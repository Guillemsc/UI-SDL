#ifndef __UI_Button_H__
#define __UI_Button_H__

#include "UI_Element.h"

class UI_Main;

class UI_Button : public UI_Element
{
public:
	UI_Button(UI_Main* ui_main);

	void SetPressedColor(UI_Color background, UI_Color outline);
	void SetOverColor(UI_Color background, UI_Color outline);
	void SetIdleColor(UI_Color background, UI_Color outline);

private:
	void Update();
	void Draw();
	void OnEvent(UI_Event* ev);

	void SetIdle();
	void SetOver();
	void SetPressed();

private:
	UI_Color background_idle;
	UI_Color outline_idle;

	UI_Color background_over;
	UI_Color background_pressed;

	UI_Color outline_over;
	UI_Color outline_pressed;
};

#endif
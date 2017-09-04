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

	void SetPressedImage(UI_Quad rect);
	void SetOverImage(UI_Quad rect);
	void SetIdleImage(UI_Quad rect);

	UI_Text* GetText();

private:
	void Update(float dt);
	void Draw();
	void OnEvent(UI_Event* ev);
	void CleanUp();

	void SetIdle();
	void SetOver();
	void SetPressed();

private:
	UI_Color background_idle;
	UI_Color outline_idle;
	UI_Quad image_idle;

	UI_Color outline_over;
	UI_Color background_over;
	UI_Quad image_over;

	UI_Color outline_pressed;
	UI_Color background_pressed;
	UI_Quad image_pressed;

	UI_Quad current_image;
	UI_Text* text = nullptr;
};

#endif
#ifndef __UI_Text_H__
#define __UI_Text_H__

#include "UI_Element.h"

class UI_Main;

class UI_Text : public UI_Element
{
public:
	UI_Text(UI_Main* ui_main);

	void Update();
	void Draw();

	void SetText(const char* text);
	char* GetText;
	void SetFont(const char* name);

private:
	string text;
	UI_Color color;
	Font* font = nullptr;
};

#endif
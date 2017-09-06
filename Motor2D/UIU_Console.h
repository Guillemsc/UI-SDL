#ifndef __UIU_Console_H__
#define __UIU_Console_H__

#include "UI_Element.h"

class UI_Main;
class UI_Image;
class UI_Panel;
class UI_TextInput;

enum uia_console_errortype
{
	uia_console_succes,
	uia_console_info,
	uia_console_warning,
	uia_console_danger,
};

class UIU_Console : public UI_Element
{
public:
	UIU_Console(UI_Main* ui_main);
	void AddText(const char* text, uia_console_errortype type = uia_console_succes);
	void SetMaxElements(int set);
	UI_TextInput* GetTextInput();
	void Hide();
	void Show();

private:
	void Update(float dt);
	void Draw();
	void OnEvent(UI_Event* ev);
	void CleanUp();

private:
	UI_Image* back = nullptr;
	UI_Text* console_name = nullptr;
	UI_Panel* panel = nullptr;
	UI_TextInput* input = nullptr;

	int margin_size = 0;

	int elements_count = 0;
	int elements_max = 20;

	bool hide = false;
};

#endif
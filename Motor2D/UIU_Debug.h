#ifndef __UIU_Debug_H__
#define __UIU_Debug_H__

#include "UI_Element.h"

class UI_Main;
class UI_Image;
class UI_Panel;
class UI_TextInput;

struct ui_debug_item
{
	UI_Text* element = nullptr;
	const char* name;
};

class UIU_Debug : public UI_Element
{
public:
	UIU_Debug(UI_Main* ui_main);
	void AddDebug(const char* name);
	void SetDebug(const char* name, const char* value);

private:
	void Update(float dt);
	void Draw();
	void OnEvent(UI_Event* ev);
	void CleanUp();

private:
	list<ui_debug_item> debug_items;
	int max_width = 0;
};

#endif
#ifndef __UIU_Message_H__
#define __UIU_Message_H__

#include "UI_Element.h"
#include "UI_Image.h"
#include "UI_Text.h"

class UI_Main;

enum uia_message_errortype
{
	uia_message_succes,
	uia_message_info,
	uia_message_warning,
	uia_message_danger,
};

class UIU_Message : public UI_Element
{
public:
	UIU_Message(UI_Main* ui_main, uia_message_errortype = uia_message_succes);

	void SetText(char* text);
	void SetType(uia_message_errortype set);

private:
	void Update(float dt);
	void Draw();
	void OnEvent(UI_Event* ev);
	void CleanUp();

private:
	UI_Image* panel = nullptr;
	UI_Text* text = nullptr;

	uia_message_errortype type = uia_message_succes;
};

#endif
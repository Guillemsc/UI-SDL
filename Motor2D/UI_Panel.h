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

public:
};

#endif
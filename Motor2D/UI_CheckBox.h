#ifndef __UI_Button_H__
#define __UI_Button_H__

#include "UI_Element.h"

class UI_Main;
class UI_Image;

class UI_CheckBox : public UI_Element
{
public:
	UI_CheckBox(UI_Main* ui_main);

	void AddBox(UI_Point pos);

	//void SetImages();

private:
	list<UI_Image> boxes;
};

#endif
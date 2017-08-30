#ifndef __UI_Button_H__
#define __UI_Button_H__

#include "UI_Element.h"
#include "UI_Image.h"

class UI_Main;

struct ui_box
{
	UI_Image* image = nullptr;
	bool	  checked = false;
	int		  index = 0;
};

class UI_CheckBox : public UI_Element
{
public:
	UI_CheckBox(UI_Main* ui_main);

	void AddBox(UI_Point pos, int index);
	void SetBoxSize(UI_Point size);
	void SetBoxImages(int idle_x, int idle_y, int idle_w, int idle_h, int pressed_x, int pressed_y, int pressed_w, int pressed_h);

	//void SetImages();

private:
	list<ui_box> boxes;
};

#endif
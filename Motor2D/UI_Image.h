#ifndef __UI_Image_H__
#define __UI_Image_H__

#include "UI_Element.h"

class UI_Main;

class UI_Image : public UI_Element
{
public:
	UI_Image(UI_Main* ui_main);

	void SetImage(int rect_x, int rect_y, int rect_w, int rect_h);

private:
	void Update();
	void Draw();

private:
	int rect_x = 0;
	int rect_y = 0;
	int rect_w = 0;
	int rect_h = 0;

};

#endif
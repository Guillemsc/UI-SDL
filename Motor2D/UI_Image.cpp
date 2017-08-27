#include "UI_Image.h"

UI_Image::UI_Image(UI_Main * ui_main) : UI_Element(ui_main, ui_element_type::ui_element_image)
{
	SetSize(UI_Point(100, 100));
	SetBackgroundColor(UI_Color(255, 0, 0, 255));
}

void UI_Image::SetImage(int _rect_x, int _rect_y, int _rect_w, int _rect_h)
{
	rect_x = _rect_x;
	rect_y = _rect_y;
	rect_w = _rect_w;
	rect_h = _rect_h;

	SetSize(UI_Point(_rect_w, _rect_h));

	SetBackgroundColor(UI_Color(0, 0, 0, 0));
	SetBackgroundColor(UI_Color(0, 0, 0, 0));
}

void UI_Image::Update(float dt)
{
}

void UI_Image::Draw()
{
	this->GetUiMain()->UIRenderImage(ZeroPos().x, ZeroPos().y, rect_x, rect_y, rect_w, rect_h, GetAlpha());
}

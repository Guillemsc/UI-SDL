#include "UI_Image.h"

UI_Image::UI_Image(UI_Main * ui_main) : UI_Element(ui_main, ui_element_type::ui_element_image)
{

}

void UI_Image::SetImage(int _rect_x, int _rect_y, int _rect_w, int _rect_h)
{
	rect_x = _rect_x;
	rect_y = _rect_y;
	rect_w = _rect_w;
	rect_h = _rect_h;

	if (GetSize().x < _rect_w)
		SetSize(UI_Point(_rect_w, GetSize().y));

	if (GetSize().y < _rect_h)
		SetSize(UI_Point(GetSize().x, _rect_h));
}

void UI_Image::Update()
{
}

void UI_Image::Draw()
{
	this->GetUiMain()->UIRenderImage(ZeroPos().x, ZeroPos().y, rect_x, rect_y, rect_w, rect_h, GetAlpha());
}

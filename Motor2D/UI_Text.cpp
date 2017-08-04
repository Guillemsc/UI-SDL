#include "UI_Text.h"

UI_Text::UI_Text(UI_Main * ui_main) : UI_Element(ui_main, ui_element_type::ui_element_text)
{
	SetFont("default");
}

void UI_Text::Update()
{

}

void UI_Text::Draw()
{
	this->GetUiMain()->UIRenderText(ZeroPos().x, ZeroPos().y, text.c_str(), font, color.r, color.g, color.b, this->GetAlpha());
}

void UI_Text::SetText(const char* _text)
{
	text = _text;
}

void UI_Text::SetFont(const char * name)
{
	font = this->GetUiMain()->UILoadFont(name);
}

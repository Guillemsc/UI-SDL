#include "UI_Text.h"

UI_Text::UI_Text(UI_Main * ui_main) : UI_Element(ui_main, ui_element_type::ui_element_text)
{
	SetFont("default");
	SetText("Text");
	SetTextColor(UI_Color(255, 255, 255));
	SetMultiLine(true);
}

void UI_Text::Update(float dt)
{

}

void UI_Text::Draw()
{
	int height = 0;
	int biggest_width = 0;

	for (list<ui_text_line>::iterator it = text_lines.begin(); it != text_lines.end(); it++)
	{
		switch (align)
		{
		case ui_text_align::ui_text_align_left:
		{
			(*it).align_pos.x = 0;
		}
		break;
		case ui_text_align::ui_text_align_middle:
		{
			(*it).align_pos.x = (GetSize().x / 2.0f) - ((*it).text_size.x / 2.0f);
		}
		break;
		case ui_text_align::ui_text_align_right:
		{
			(*it).align_pos.x = GetSize().x - (*it).text_size.x;
		}
		break;
		}

		(*it).text_size = ui_main->UIRenderText(ZeroPos().x + (*it).align_pos.x, ZeroPos().y + (*it).align_pos.y + height, (*it).text.c_str(), font, color.r, color.g, color.b, this->GetAlpha());

		height += (*it).text_size.y;

		if ((*it).text_size.x > biggest_width)
			biggest_width = (*it).text_size.x;
	}

	if (height == 0 && font != nullptr)
		height = ui_main->UIGetFontSize(font);

	SetSize(UI_Point(biggest_width, height));
}

void UI_Text::SetText(const char* _text)
{
	text = _text;

	text_lines.clear();

	string acumulate;
	for (int i = 0; i < text.length(); i++)
	{
		if (text[i] == '\n' && multi_line)
		{
			ui_text_line new_line;
			new_line.text = acumulate;

			text_lines.push_back(new_line);
			
			acumulate.clear();
			continue;
		}

		acumulate += text[i];
	}

	if (acumulate.length() > 0)
	{
		ui_text_line new_line;
		new_line.text = acumulate;

		text_lines.push_back(new_line);
	}
}

void UI_Text::SetTextColor(UI_Color _color)
{
	color = _color;
}

const char * UI_Text::GetText()
{
	return text.c_str();
}

void UI_Text::SetFont(const char * name)
{
	font = ui_main->UILoadFont(name);
}

void UI_Text::SetTextAlign(ui_text_align _align)
{
	align = _align;
}

void UI_Text::SetLineHeight(int _height)
{
	line_height = _height;
}

void UI_Text::SetMultiLine(bool set)
{
	multi_line = set;
}

Font * UI_Text::GetFont()
{
	return font;
}

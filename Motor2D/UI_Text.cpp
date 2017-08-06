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
	int height = 0;

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

		(*it).text_size = this->GetUiMain()->UIRenderText(ZeroPos().x + (*it).align_pos.x, ZeroPos().y + (*it).align_pos.y + height, (*it).text.c_str(), font, color.r, color.g, color.b, this->GetAlpha());

		height += (*it).text_size.y;
	}
}

void UI_Text::SetText(const char* _text)
{
	text = _text;

	text_lines.clear();

	string acumulate;
	for (int i = 0; i < text.length(); i++)
	{
		if (text[i] == '\n')
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

const char * UI_Text::GetText()
{
	return text.c_str();
}

void UI_Text::SetFont(const char * name)
{
	font = this->GetUiMain()->UILoadFont(name);
}

void UI_Text::SetTextAlign(ui_text_align _align)
{
	align = _align;
}

void UI_Text::SetLineHeight(int _height)
{
	line_height = _height;
}

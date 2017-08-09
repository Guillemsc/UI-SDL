#ifndef __UI_Text_H__
#define __UI_Text_H__

#include "UI_Element.h"

class UI_Main;

enum ui_text_align
{
	ui_text_align_left,
	ui_text_align_right,
	ui_text_align_middle,
};

struct ui_text_line
{
	string text;
	UI_Point text_size;
	UI_Point align_pos;
};

class UI_Text : public UI_Element
{
public:
	UI_Text(UI_Main* ui_main);

	void SetText(const char* text);
	void SetTextColor(UI_Color color);
	const char* GetText();
	void SetFont(const char* name);
	void SetTextAlign(ui_text_align align);
	void SetLineHeight(int height);

private:
	void Update();
	void Draw();

private:
	string        text;
	UI_Color      color;
	Font*		  font = nullptr;
	int			  line_height = 0;
	int			  line_biggest_width = 0;

	ui_text_align align = ui_text_align_left;

	list<ui_text_line> text_lines;
};

#endif
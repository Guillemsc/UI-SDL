#include "UI_Panel.h"

UI_Panel::UI_Panel(UI_Main * ui_main) : UI_Element(ui_main, ui_element_type::ui_element_panel)
{
	SetSize(UI_Point(100, 200));
}

void UI_Panel::Update()
{
}

void UI_Panel::Draw()
{
}

void UI_Panel::OnEvent(UI_Event * ev)
{
}

void UI_Panel::CleanUp()
{
}

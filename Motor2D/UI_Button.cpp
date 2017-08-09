#include "UI_Button.h"
#include "UI_EventSystem.h"

UI_Button::UI_Button(UI_Main * ui_main) : UI_Element(ui_main, ui_element_type::ui_element_button)
{
	SetSize(UI_Point(150, 40));

	SetIdleColor(UI_Color(230, 230, 230), UI_Color(102, 178, 250));
	SetOverColor(UI_Color(128, 128, 128), UI_Color(51, 153, 250));
	SetPressedColor(UI_Color(102, 178, 250), UI_Color(0, 102, 204));

	SetBackgroundColor(background_idle);
}

void UI_Button::Update()
{
}

void UI_Button::Draw()
{
}

void UI_Button::OnEvent(UI_Event * ev)
{
	if (ev->GetSender() != this)
		return;

	if (ev->GetEventType() == ui_event_type::event_mouse_down)
		SetPressed();

	else if (ev->GetEventType() == ui_event_type::event_mouse_over_enter || ev->GetEventType() == ui_event_type::event_mouse_up)
		SetOver();

	else if (ev->GetEventType() == ui_event_type::event_mouse_over_out)
		SetIdle();
}

void UI_Button::SetIdle()
{
	SetBackgroundColor(background_idle);
	SetOutlineColor(outline_idle);
}

void UI_Button::SetOver()
{
	SetBackgroundColor(background_over);
	SetOutlineColor(outline_over);
}

void UI_Button::SetPressed()
{
	SetBackgroundColor(background_pressed);
	SetOutlineColor(outline_pressed);
}

void UI_Button::SetPressedColor(UI_Color _background, UI_Color _outline)
{
	background_pressed = _background;
	outline_pressed = _outline;
}

void UI_Button::SetOverColor(UI_Color _background, UI_Color _outline)
{
	background_over = _background;
	outline_over = _outline;
}

void UI_Button::SetIdleColor(UI_Color _background, UI_Color _outline)
{
	background_idle = _background;
	outline_idle = _outline;
}

#include "UI_Button.h"
#include "UI_Text.h"
#include "UI_EventSystem.h"

UI_Button::UI_Button(UI_Main * ui_main) : UI_Element(ui_main, ui_element_type::ui_element_button)
{
	SetSize(UI_Point(150, 40));

	SetIdleColor(UI_Color(230, 230, 230), UI_Color(102, 178, 250));
	SetOverColor(UI_Color(128, 128, 128), UI_Color(102, 178, 250));
	SetPressedColor(UI_Color(102, 178, 250), UI_Color(102, 178, 250));

	SetBackgroundColor(background_idle);

	text = new UI_Text(ui_main);
	text->SetPos(UI_Point(0, 0));
	text->SetText("Button text");
	text->SetInteractable(false);
	text->SetTextColor(UI_Color(0, 0, 0));
	AddChild(text);
}

void UI_Button::Update(float dt)
{
}

void UI_Button::Draw()
{
}

void UI_Button::OnEvent(UI_Event * ev)
{
	if (ev->GetSender() == text)
	{
		if (ev->GetEventType() == ui_event_type::event_delete)
		{
			text = nullptr;
		}
		return;
	}

	if (ev->GetSender() != this)
		return;

	if (ev->GetEventType() == ui_event_type::event_mouse_down)
	{
		SetPressed();
	}
	else if (ev->GetEventType() == ui_event_type::event_mouse_up)
	{
		if(ev->GetSender()->GetMouseOver())
			SetOver();
		else
			SetIdle();
	}
	else if (ev->GetEventType() == ui_event_type::event_mouse_over_enter)
	{
		if(!ev->GetSender()->GetMouseDown())
		SetOver();
	}
	else if (ev->GetEventType() == ui_event_type::event_mouse_over_out)
	{
		if(ev->GetSender()->GetMouseDown())
			SetPressed();
		else
			SetIdle();
	}
}

void UI_Button::CleanUp()
{
	if(text != nullptr)
		text->Delete();
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

UI_Text * UI_Button::GetText()
{
	return text;
}

#include "UI_Panel.h"
#include "UI_Button.h"
#include "UI_Text.h"
#include "UI_EventSystem.h"
#include "p2Log.h"

UI_Panel::UI_Panel(UI_Main * ui_main) : UI_Element(ui_main, ui_element_type::ui_element_panel)
{
	SetSize(UI_Point(200, 300));
	SetBackgroundColor(UI_Color(255, 0, 0));

	button_size = 10;

	updown_scroll_button = new UI_Button(ui_main);
	leftright_scroll_button = new UI_Button(ui_main);

	updown_scroll_button->GetText()->SetText("");

	leftright_scroll_button->GetText()->SetText("");

	AddChild(updown_scroll_button);
	AddChild(leftright_scroll_button);
}

void UI_Panel::Update()
{
	//UpdateSize();

	// Updown
	updown_scroll_button->SetPos(UI_Point(GetSize().x - button_size, updown_button_pos));

	float new_size = (((GetSize().y - button_size) * (GetSize().y)) / updown_size);

	updown_scroll_button->SetSize(UI_Point(button_size, new_size));

	if (track_updown)
	{
		if (updown_button_pos - (last_mouse.y - GetUiMain()->GetMousePos().y) > GetSize().y - updown_scroll_button->GetSize().y - button_size)
		{
			updown_button_pos = GetSize().y - updown_scroll_button->GetSize().y - button_size;
		}
		else if (updown_button_pos - (last_mouse.y - GetUiMain()->GetMousePos().y) < 0)
		{
			updown_button_pos = 0;
		}
		else
			updown_button_pos -= last_mouse.y - GetUiMain()->GetMousePos().y;

		last_mouse.y = GetUiMain()->GetMousePos().y;
	}

	// updownscroll
	float button_total_distance = GetSize().y - updown_scroll_button->GetSize().y - button_size;

	float total_distance = updown_size - GetSize().y;

	updown_scroll = (updown_button_pos*total_distance) / button_total_distance;
	// ------------

	// Leftright
	leftright_scroll_button->SetPos(UI_Point(0, GetSize().y - button_size));

	new_size = (GetSize().x * (GetSize().x - button_size) / leftright_size);
	leftright_scroll_button->SetSize(UI_Point(new_size, button_size));


	updown_size = 0;

	for (list<ui_panel_element>::iterator it = panel_elements.begin(); it != panel_elements.end(); it++)
	{
		if ((*it).element == updown_scroll_button || (*it).element == leftright_scroll_button)
			continue;

		(*it).element->SetPos(UI_Point((*it).starting_pos.x, (*it).starting_pos.y - updown_scroll));

		if (updown_size < (*it).starting_pos.y + (*it).element->GetSize().y)
			updown_size = (*it).starting_pos.y + (*it).element->GetSize().y;
	}
}

void UI_Panel::Draw()
{
}

void UI_Panel::OnEvent(UI_Event * ev)
{
	if (ev->GetSender() == updown_scroll_button)
	{
		if (ev->GetEventType() == ui_event_type::event_mouse_down)
		{
			track_updown = true;
			last_mouse.y = GetUiMain()->GetMousePos().y;
		}
		else if (ev->GetEventType() == ui_event_type::event_mouse_up)
		{
			track_updown = false;
		}
	}

	if (ev->GetSender() == this)
	{
		if (ev->GetEventType() == ui_event_type::event_child_added)
		{
			UI_EventTarget* ta = (UI_EventTarget*)ev;

			ui_panel_element el;
			el.element = ta->GetTarget();
			el.starting_pos = ta->GetTarget()->GetPos();

			panel_elements.push_back(el);
		}
	}
}

void UI_Panel::CleanUp()
{
}

void UI_Panel::UpdateSize()
{
	leftright_size = 0.0f;
	updown_size = 0.0f;

	for (list<UI_Element*>::iterator it = childs.begin(); it != childs.end(); it++)
	{
		if ((*it) == updown_scroll_button || (*it) == leftright_scroll_button)
			continue;

		if ((*it)->GetPos().x + (*it)->GetSize().x > leftright_size)
			leftright_size = (*it)->GetPos().x + (*it)->GetSize().x;

		if ((*it)->GetPos().y + (*it)->GetSize().y > updown_size)
			updown_size = (*it)->GetPos().y + (*it)->GetSize().y;
	}

	if (leftright_size < GetSize().x)
		leftright_size = GetSize().x;

	if (updown_size < GetSize().y)
		updown_size = GetSize().y;
}

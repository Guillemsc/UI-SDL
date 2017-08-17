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

	SetUseScrolls(false);
}

void UI_Panel::SetUseScrolls(bool set)
{
	use_scrolls = set;

	updown_scroll_button->SetVisibleAndChilds(set);
	leftright_scroll_button->SetVisibleAndChilds(set);
}

void UI_Panel::SetAutoScrollDown(float set)
{
	auto_scroll_down = set;
}

void UI_Panel::Update()
{
	// Updown ----
	UpdateUpdownButton();

	if (track_updown && use_scrolls)
		UpdownInput();
	
	UpdateUpdownScroll();
	// ------------

	// Leftright --
	UpdateLeftrightButton();

	if(track_leftright && use_scrolls)
	LeftrightInput();

	UpdateLeftrightScroll();
	// ------------

	UpdateElementsPos();
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
	else if (ev->GetSender() == leftright_scroll_button)
	{
		if (ev->GetEventType() == ui_event_type::event_mouse_down)
		{
			track_leftright = true;
			last_mouse.x = GetUiMain()->GetMousePos().x;
		}
		else if (ev->GetEventType() == ui_event_type::event_mouse_up)
		{
			track_leftright = false;
		}
	}

	else if (ev->GetSender() == this)
	{
		if (ev->GetEventType() == ui_event_type::event_child_added)
		{
			UI_EventTarget* ta = (UI_EventTarget*)ev;

			ui_panel_element el;
			el.element = ta->GetTarget();
			el.starting_pos = ta->GetTarget()->GetPos();

			panel_elements.push_back(el);

			updown_scroll_button->BringToFront();
			leftright_scroll_button->BringToFront();

			if (auto_scroll_down)
				ScrollDown();
		}
		else if (ev->GetEventType() == ui_event_type::event_child_removed)
		{
			UI_EventTarget* ta = (UI_EventTarget*)ev;

			for (list<ui_panel_element>::iterator it = panel_elements.begin(); it != panel_elements.end();)
			{
				if (ta->GetTarget() == (*it).element)
				{
					panel_elements.erase(it);
					break;
				}
				else
					++it;
			}
		}
	}
	else if (ev->GetSender() == updown_scroll_button)
	{
		if (ev->GetEventType() == ui_event_type::event_delete)
		{
			updown_scroll_button = nullptr;
		}
	}
	else if (ev->GetSender() == leftright_scroll_button)
	{
		if (ev->GetEventType() == ui_event_type::event_delete)
		{
			leftright_scroll_button = nullptr;
		}
	}
}

void UI_Panel::CleanUp()
{
	if (updown_scroll_button != nullptr)
		updown_scroll_button->Delete();
	
	if (leftright_scroll_button != nullptr)
		leftright_scroll_button->Delete();

}

void UI_Panel::UpdateUpdownButton()
{
	updown_scroll_button->SetPos(UI_Point(GetSize().x - button_size, updown_button_pos));

	float new_size = (((GetSize().y - button_size) * (GetSize().y)) / updown_size);

	updown_scroll_button->SetSize(UI_Point(button_size, new_size));
}

void UI_Panel::UpdownInput()
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

void UI_Panel::UpdateUpdownScroll()
{
	float button_total_distance = GetSize().y - updown_scroll_button->GetSize().y - button_size;

	float total_distance = updown_size - GetSize().y;

	if (button_total_distance > 0 && total_distance > 0)
		updown_scroll = (updown_button_pos*total_distance) / button_total_distance;
}

void UI_Panel::UpdateLeftrightButton()
{
	leftright_scroll_button->SetPos(UI_Point(leftright_button_pos, GetSize().y - button_size));

	float new_size = (((GetSize().x - button_size) * (GetSize().x)) / leftright_size);

	leftright_scroll_button->SetSize(UI_Point(new_size, button_size));
}

void UI_Panel::LeftrightInput()
{
	if (leftright_button_pos - (last_mouse.x - GetUiMain()->GetMousePos().x) > GetSize().x - leftright_scroll_button->GetSize().x - button_size)
	{
		leftright_button_pos = GetSize().x - leftright_scroll_button->GetSize().x - button_size;
	}
	else if (leftright_button_pos - (last_mouse.x - GetUiMain()->GetMousePos().x) < 0)
	{
		leftright_button_pos = 0;
	}
	else
		leftright_button_pos -= last_mouse.x - GetUiMain()->GetMousePos().x;

	last_mouse.x = GetUiMain()->GetMousePos().x;
}

void UI_Panel::UpdateLeftrightScroll()
{
	float button_total_distance = GetSize().x - leftright_scroll_button->GetSize().x - button_size;

	float total_distance = leftright_size - GetSize().x;

	if(button_total_distance > 0 && total_distance > 0)
		leftright_scroll = (leftright_button_pos * total_distance) / button_total_distance;
}

void UI_Panel::UpdateElementsPos()
{
	updown_size = GetSize().y;
	leftright_size = GetSize().x;

	for (list<ui_panel_element>::iterator it = panel_elements.begin(); it != panel_elements.end(); it++)
	{
		if ((*it).element == updown_scroll_button || (*it).element == leftright_scroll_button)
			continue;

		(*it).element->SetPos(UI_Point((*it).starting_pos.x - leftright_scroll, (*it).starting_pos.y - updown_scroll));

		if (updown_size < (*it).starting_pos.y + (*it).element->GetSize().y)
			updown_size = (*it).starting_pos.y + (*it).element->GetSize().y;

		if (leftright_size < (*it).starting_pos.x + (*it).element->GetSize().x)
			leftright_size = (*it).starting_pos.x + (*it).element->GetSize().x;
	}
}

void UI_Panel::ScrollDown()
{
	UpdateElementsPos();
	UpdateUpdownButton();

	updown_button_pos = GetSize().y - updown_scroll_button->GetSize().y - button_size;

	UpdateUpdownButton();
}


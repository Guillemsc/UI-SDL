#include "UI_TextInput.h"
#include "UI_Text.h"
#include "UI_EventSystem.h"
#include "j1Input.h"

UI_TextInput::UI_TextInput(UI_Main * ui_main) : UI_Element(ui_main, ui_element_type::ui_element_textinput)
{
	text = new UI_Text(ui_main);
	text->SetMultiLine(false);
	text->SetText("");
	text->SetInteractable(false);

	bar_x = text->GetPos().x;

	SetSize(UI_Point(200, text->GetSize().y));
	SetOutlineColor(UI_Color(255, 255, 255, 255));

	AddChild(text);
}

void UI_TextInput::SetText(char* text)
{
	internal_text = text;
	bar_pos = strlen(text);
	curr_event = ui_text_input;
	update_text = true;
}

UI_Text * UI_TextInput::GetText()
{
	return text;
}

void UI_TextInput::Update(float dt)
{
	// Dinamic pos
	UpdateDynamicPos();

	bar_flicker_time += dt;

	// Text input
	if (ui_main->GetFocusedElement() == this)
	{
		const char* input;
		if (ui_main->UIGetKeyboardInput(input))
		{
			internal_text.insert(bar_pos, input);
			bar_pos += strlen(input);
			curr_event = ui_text_input;
			update_text = true;
		}

		// Key input
		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
		{
			bar_pos--;
			curr_event = ui_bar_left;
			update_text = true;
		}
		else if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
		{
			bar_pos++;
			curr_event = ui_bar_right;
			update_text = true;
		}
		if (App->input->GetKey(SDL_SCANCODE_BACKSPACE) == KEY_DOWN)
		{
			if (internal_text.size() > 0 && bar_pos > 0)
			{
				internal_text.erase(bar_pos - 1, 1);
				bar_pos--;
				curr_event = ui_backspace;
				update_text = true;
			}
		}
		if (App->input->GetKey(SDL_SCANCODE_DELETE) == KEY_DOWN)
		{
			if (internal_text.size() > 0 && bar_pos < internal_text.size())
			{
				internal_text.erase(bar_pos, 1);
				curr_event = ui_delete;
				update_text = true;
			}
		}
	}

	if (update_text)
	{
		update_text = false;
		bar_flicker_time = -0.4f;

		if (bar_pos < 0)
			bar_pos = 0;

		if (bar_pos > internal_text.size())
			bar_pos = internal_text.size();

		// Update text
		text->SetText(internal_text.c_str());
	}

	// Update bar pos
	UpdateBarPos(dt);

	SetSize(UI_Point(GetSize().x, text->GetSize().y));
}

void UI_TextInput::CleanUp()
{
	if (text != nullptr)
		text->Delete();
}

void UI_TextInput::Draw()
{
	if (bar_flicker_time < bar_flicker_total_time / 2)
	{
		if(ui_main->GetFocusedElement() == this)
			ui_main->UIRenderQuad(bar_x, 0, bar_w, text->GetSize().y, 255, 255, 255, 255, true);
	}

	if (bar_flicker_time > bar_flicker_total_time)
		bar_flicker_time = 0;
}

void UI_TextInput::OnEvent(UI_Event * ev)
{
	if (ev->GetSender() == text)
	{
		if (ev->GetEventType() == ui_event_type::event_delete)
		{
			text = nullptr;
		}
	}
}

void UI_TextInput::UpdateBarPos(float dt)
{
	string part = internal_text.substr(0, bar_pos);

	bar_x = text->GetPos().x + ui_main->UIGetTextSize(part.c_str(), text->GetFont()).x;
}

void UI_TextInput::UpdateDynamicPos()
{
	switch (curr_event)
	{
	case ui_null:
		break;
	case ui_bar_left:
		if (bar_x < 0)
		{
			int difference = 0 - bar_x;
			text->SetPos(UI_Point(text->GetPos().x + difference, text->GetPos().y));
			curr_event = ui_null;
		}
		break;
	case ui_bar_right:
		break;
	case ui_text_input:
		if (bar_x + bar_w > GetSize().x)
		{
			int difference = (bar_x + bar_w) - GetSize().x;
			text->SetPos(UI_Point(text->GetPos().x - difference - 1, text->GetPos().y));
			curr_event = ui_null;
		}
		break;
	case ui_backspace:
		if (text->GetSize().x + bar_w > GetSize().x)
		{
			if (text->GetPos().x + text->GetSize().x + bar_w < GetSize().x)
			{
				int difference = (text->GetPos().x + text->GetSize().x + bar_w) - GetSize().x;
				text->SetPos(UI_Point(text->GetPos().x - difference, text->GetPos().y));
				curr_event = ui_null;
			}
		}
		else
		{
			text->SetPos(UI_Point(0, text->GetPos().y));
		}
		break;
	case ui_delete:
		if (text->GetSize().x + bar_w > GetSize().x)
		{
			if (text->GetPos().x + text->GetSize().x + bar_w < GetSize().x)
			{
				int difference = (text->GetPos().x + text->GetSize().x + bar_w) - GetSize().x;
				text->SetPos(UI_Point(text->GetPos().x - difference - 1, text->GetPos().y));
				curr_event = ui_null;
			}
		}
		else
		{
			text->SetPos(UI_Point(0, text->GetPos().y));
		}
		break;
	default:
		break;
	}
}

#include "UI_TextInput.h"
#include "UI_Text.h"
#include "UI_EventSystem.h"
#include "j1Input.h"

UI_TextInput::UI_TextInput(UI_Main * ui_main) : UI_Element(ui_main, ui_element_type::ui_element_textinput)
{
	text = new UI_Text(ui_main);
	text->SetMultiLine(false);
	text->SetText("");
	text->SetPos(UI_Point(5, text->GetPos().y));
	text->SetInteractable(false);

	bar_x = text->GetPos().x;

	SetSize(UI_Point(200, text->GetSize().y));
	//SetOutlineColor(UI_Color(255, 255, 255, 255));

	AddChild(text);
}

UI_Text * UI_TextInput::GetText()
{
	return text;
}

void UI_TextInput::Update(float dt)
{
	bar_flicker_time += dt;

	bool update_text = false;

	// Text input
	if (ui_main->GetFocusedElement() == this)
	{
		const char* input;
		if (ui_main->UIGetKeyboardInput(input))
		{
			internal_text.insert(bar_pos, input);
			bar_pos += strlen(input);
			update_text = true;
		}

		// Key input
		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
		{
			bar_pos--;
			update_text = true;
		}
		else if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
		{
			bar_pos++;
			update_text = true;
		}
		if (App->input->GetKey(SDL_SCANCODE_BACKSPACE) == KEY_DOWN)
		{
			if (internal_text.size() > 0 && bar_pos > 0)
			{
				internal_text.erase(bar_pos - 1, 1);
				bar_pos--;
				update_text = true;
			}
		}
		if (App->input->GetKey(SDL_SCANCODE_DELETE) == KEY_DOWN)
		{
			if (internal_text.size() > 0 && bar_pos < internal_text.size())
			{
				internal_text.erase(bar_pos, 1);
				update_text = true;
			}
		}
	}

	if (update_text)
	{
		bar_flicker_time = -0.4f;

		if (bar_pos < 0)
			bar_pos = 0;

		if (bar_pos > internal_text.size())
			bar_pos = internal_text.size();

		// Update bar pos
		UpdateBarPos(dt);

		// Update text
		text->SetText(internal_text.c_str());

		// Dinamic pos
		UpdateDynamicPos();
	}

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
	if (bar_x > GetSize().x)
	{
		int difference = bar_x + bar_w - GetSize().x;
		text->SetPos(UI_Point(text->GetPos().x - difference, text->GetPos().y));
	}

	if (bar_x < 0)
	{
		int difference = 0 - bar_x;
		text->SetPos(UI_Point(text->GetPos().x + difference, text->GetPos().y));
	}
}

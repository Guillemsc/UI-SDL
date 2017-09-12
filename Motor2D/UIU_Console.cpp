#include "UIU_Console.h"
#include "UI_Image.h"
#include "UI_Text.h"
#include "UI_Panel.h"
#include "UI_TextInput.h"
#include "UI_Button.h"
#include "UIA_Interpolation.h"
#include "UI_EventSystem.h"
#include "p2Log.h"

UIU_Console::UIU_Console(UI_Main * ui_main) : UI_Element(ui_main, ui_element_type::uiu_console)
{
	margin_size = 10;

	back = new UI_Image(ui_main);
	back->SetPos(UI_Point(0, -10));
	back->SetBackgroundColor(UI_Color(30, 30, 30, 200));
	AddChild(back);

	console_name = new UI_Text(ui_main);
	console_name->SetPos(UI_Point(margin_size, margin_size));
	console_name->SetText("Console");
	console_name->SetFont("default_small");
	AddChild(console_name);

	panel = new UI_Panel(ui_main);
	panel->SetUseScrolls(true);
	panel->SetAutoScrollDown(true);
	panel->SetBackgroundColor(UI_Color(10, 10, 10, 255));
	panel->GetUpDownButton()->SetIdleColor(UI_Color(50, 50, 50), UI_Color(90, 90, 90));
	panel->GetUpDownButton()->SetOverColor(UI_Color(70, 70, 70), UI_Color(102, 178, 250));
	panel->GetUpDownButton()->SetPressedColor(UI_Color(102, 178, 250), UI_Color(102, 178, 250));
	
	panel->GetLeftRightButton()->SetIdleColor(UI_Color(50, 50, 50), UI_Color(90, 90, 90));
	panel->GetLeftRightButton()->SetOverColor(UI_Color(70, 70, 70), UI_Color(102, 178, 250));
	panel->GetLeftRightButton()->SetPressedColor(UI_Color(102, 178, 250), UI_Color(102, 178, 250));
	AddChild(panel);

	input = new UI_TextInput(ui_main);
	input->SetBackgroundColor(UI_Color(10, 10, 10, 255));
	input->SetOutlineColor(UI_Color(5, 5, 5, 0));
	input->GetText()->SetFont("default_small");
	AddChild(input);

	Update(0);
	SetPos(UI_Point(0, -back->GetSize().y));
	SetVisible(false);
}

void UIU_Console::AddText(const char * text, uia_console_errortype type)
{
	UI_Text* t = new UI_Text(ui_main);
	t->SetText(text);
	t->SetFont("default_verysmall");
	t->SetPos(UI_Point(0, elements_count* (ui_main->UIGetFontSize(t->GetFont()))));

	switch (type)
	{
	case uia_console_default:
		t->SetTextColor(UI_Color(245, 245, 245));
		break;
	case uia_console_succes:
		t->SetTextColor(UI_Color(120, 200, 120));
		break;
	case uia_console_info:
		t->SetTextColor(UI_Color(100, 182, 255));
		break;
	case uia_console_warning:
		t->SetTextColor(UI_Color(255, 149, 89));
		break;
	case uia_console_danger:
		t->SetTextColor(UI_Color(250, 88, 96));
		break;
	default:
		break;
	}

	panel->AddChild(t);

	elements_count++;

	if (elements_max < elements_count)
	{
		elements_count = elements_max;
		panel->RemoveFirst();
		panel->MoveChilds(UI_Point(0, -ui_main->UIGetFontSize(t->GetFont())));
	}
}

void UIU_Console::SetMaxElements(int set)
{
	elements_max = set;
}

UI_TextInput * UIU_Console::GetTextInput()
{
	return input;
}

void UIU_Console::Hide()
{
	input->ClearFocus();
	GetAnimator()->StartAnimationInterpolation(uia_interpolation_type::uia_interpolation_cubicEaseInOut, UI_Point(0, -back->GetSize().y), 0.6f);
	hide = true;
}

void UIU_Console::Show()
{
	SetVisible(true);
	GetAnimator()->StartAnimationInterpolation(uia_interpolation_type::uia_interpolation_cubicEaseInOut, UI_Point(0, 0), 0.5f);
	hide = false;
}

void UIU_Console::Update(float dt)
{
	back->SetSize(UI_Point(ui_main->GetWindowSize().x, ui_main->GetWindowSize().y * 0.6));

	panel->SetPos(UI_Point(margin_size, console_name->GetPos().y + console_name->GetSize().y + margin_size));
	panel->SetSize(UI_Point(ui_main->GetWindowSize().x - (margin_size * 2), back->GetSize().y - 100));

	input->SetPos(UI_Point(margin_size, panel->GetPos().y + panel->GetSize().y + margin_size));
	input->SetSize(UI_Point(ui_main->GetWindowSize().x - (margin_size * 2), input->GetSize().y));

	SetSize(back->GetSize());
}

void UIU_Console::Draw()
{
}

void UIU_Console::OnEvent(UI_Event * ev)
{
	if (ev->GetSender() == this)
	{
		if (ev->GetEventType() == ui_event_type::event_interpolation_anim_finished)
		{
			if (hide)
				SetVisible(false);
		}
	}

	if (ev->GetSender() == back)
	{
		if (ev->GetEventType() == ui_event_type::event_delete)
		{
			back = nullptr;
		}
	}

	if (ev->GetSender() == console_name)
	{
		if (ev->GetEventType() == ui_event_type::event_delete)
		{
			console_name = nullptr;
		}
	}

	if (ev->GetSender() == panel)
	{
		if (ev->GetEventType() == ui_event_type::event_delete)
		{
			panel = nullptr;
		}
	}

	if (ev->GetSender() == input)
	{
		if (ev->GetEventType() == ui_event_type::event_delete)
		{
			input = nullptr;
		}
	}
}

void UIU_Console::CleanUp()
{
	if(back != nullptr)
		back->Delete();

	if(console_name != nullptr)
		console_name->Delete();

	if(panel != nullptr)
		panel->Delete();

	if(input != nullptr)
		input->Delete();
}

#include "UIU_Console.h"
#include "UI_Image.h"
#include "UI_Text.h"
#include "UI_Panel.h"
#include "UI_TextInput.h"
#include "UI_Button.h"

UIU_Console::UIU_Console(UI_Main * ui_main) : UI_Element(ui_main, ui_element_type::uiu_console)
{
	margin_size = 10;

	back = new UI_Image(ui_main);
	back->SetPos(UI_Point(0, 0));
	back->SetBackgroundColor(UI_Color(30, 30, 30, 200));

	console_name = new UI_Text(ui_main);
	console_name->SetPos(UI_Point(margin_size, margin_size));
	console_name->SetText("Console");
	console_name->SetFont("default_small");
	back->AddChild(console_name);

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

	input = new UI_TextInput(ui_main);
	input->SetBackgroundColor(UI_Color(10, 10, 10, 255));
	input->SetOutlineColor(UI_Color(5, 5, 5, 0));
	input->GetText()->SetFont("default_small");
}

void UIU_Console::AddText(const char * text, uia_console_errortype type)
{
	UI_Text* t = new UI_Text(ui_main);
	t->SetText(text);
	t->SetFont("default_verysmall");
	t->SetPos(UI_Point(0, elements_count* (ui_main->UIGetFontSize(t->GetFont()))));
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

void UIU_Console::Update(float dt)
{
	back->SetPos(UI_Point(0, 0));
	back->SetSize(UI_Point(ui_main->GetWindowSize().x, ui_main->GetWindowSize().y * 0.6));

	panel->SetPos(UI_Point(margin_size, console_name->GetPos().y + console_name->GetSize().y + margin_size));
	panel->SetSize(UI_Point(ui_main->GetWindowSize().x - (margin_size * 2), back->GetSize().y - 90));

	input->SetPos(UI_Point(margin_size, panel->GetPos().y + panel->GetSize().y + margin_size));
	input->SetSize(UI_Point(ui_main->GetWindowSize().x - (margin_size * 2), input->GetSize().y));
}

void UIU_Console::Draw()
{
}

void UIU_Console::OnEvent(UI_Event * ev)
{
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

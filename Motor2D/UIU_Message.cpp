#include "UIU_Message.h"
#include "UI_EventSystem.h"

UIU_Message::UIU_Message(UI_Main * ui_main, uia_message_errortype _type) : UI_Element(ui_main, ui_element_type::uiu_message)
{
	panel = new UI_Image(ui_main);
	panel->SetAnchor(UI_Point(0, 1));

	text = new UI_Text(ui_main);
	text->SetFont("default_small");
	panel->AddChild(text);

	SetType(_type);

	SetText("You have created a message!");
}

void UIU_Message::SetText(char * _text)
{
	string t;

	switch (type)
	{
	case uia_message_succes:
		t = "Succes!  ";
		break;
	case uia_message_info:
		t = "Info!  ";
		break;
	case uia_message_warning:
		t = "Warning!  ";
		break;
	case uia_message_danger:
		t = "Danger!  ";
		break;
	default:
		break;
	}

	t += _text;
	text->SetText(t.c_str());
}

void UIU_Message::SetType(uia_message_errortype set)
{
	type = set;
	switch (type)
	{
	case uia_message_succes:
		panel->SetBackgroundColor(UI_Color(223, 240, 216));
		panel->SetOutlineColor(UI_Color(60, 118, 60));
		text->SetTextColor(UI_Color(60, 118, 60));
		break;
	case uia_message_info:
		panel->SetBackgroundColor(UI_Color(217, 237, 247));
		panel->SetOutlineColor(UI_Color(49, 112, 143));
		text->SetTextColor(UI_Color(49, 112, 143));
		break;
	case uia_message_warning:
		panel->SetBackgroundColor(UI_Color(252, 248, 227));
		panel->SetOutlineColor(UI_Color(138, 109, 59));
		text->SetTextColor(UI_Color(138, 109, 59));
		break;
	case uia_message_danger:
		panel->SetBackgroundColor(UI_Color(242, 222, 222));
		panel->SetOutlineColor(UI_Color(169, 68, 66));
		text->SetTextColor(UI_Color(169, 68, 66));
		break;
	default:
		break;
	}
}

void UIU_Message::Update(float dt)
{
	panel->SetPos(UI_Point(30, - text->GetSize().y - 30));
	panel->SetSize(UI_Point(ui_main->GetWindowSize().x - 60, text->GetSize().y + 10));
	text->SetPos(UI_Point(13, 5));
}

void UIU_Message::Draw()
{
}

void UIU_Message::OnEvent(UI_Event * ev)
{
	if (ev->GetSender() == text)
	{
		if (ev->GetEventType() == ui_event_type::event_delete)
		{
			text = nullptr;
		}
		return;
	}

	if (ev->GetSender() == panel)
	{
		if (ev->GetEventType() == ui_event_type::event_delete)
		{
			panel = nullptr;
		}
		return;
	}
}

void UIU_Message::CleanUp()
{
	if (panel != nullptr)
		panel->Delete();

	if (text != nullptr)
		text->Delete();
}

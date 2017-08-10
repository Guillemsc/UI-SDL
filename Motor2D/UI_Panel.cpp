#include "UI_Panel.h"
#include "UI_Button.h"
#include "UI_Text.h"

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
	UpdateSize();

	updown_scroll_button->SetPos(UI_Point(GetSize().x - button_size, 0));
	leftright_scroll_button->SetPos(UI_Point(0, GetSize().y - button_size));

	float new_size = (GetSize().y * (GetSize().y - button_size) / updown_size);
	updown_scroll_button->SetSize(UI_Point(button_size, new_size));

	new_size = (GetSize().x * (GetSize().x - button_size) / leftright_size);
	leftright_scroll_button->SetSize(UI_Point(new_size, button_size));


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

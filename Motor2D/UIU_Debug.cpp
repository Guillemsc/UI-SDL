#include "UIU_Debug.h"
#include "UI_Image.h"
#include "UI_Text.h"
#include "UI_EventSystem.h"

UIU_Debug::UIU_Debug(UI_Main * ui_main) : UI_Element(ui_main, ui_element_type::uiu_debug)
{
	SetBackgroundColor(UI_Color(40, 30, 30, 200));
	SetOutlineColor(UI_Color(100, 182, 255));
}

void UIU_Debug::AddDebug(const char * name)
{
	ui_debug_item i;

	i.element = new UI_Text(ui_main);
	i.element->SetFont("default_verysmall");
	i.element->SetMultiLine(false);
	i.name = name;
	i.element->SetPos(UI_Point(3, debug_items.size() * ui_main->UIGetFontSize(i.element->GetFont())));
	AddChild(i.element);

	debug_items.push_back(i);

	SetSize(UI_Point(GetSize().x, debug_items.size() * ui_main->UIGetFontSize(i.element->GetFont())));
}

void UIU_Debug::SetDebug(const char * name, const char * value)
{
	for (list<ui_debug_item>::iterator it = debug_items.begin(); it != debug_items.end(); it++)
	{
		if ((*it).name == name)
		{
			string text = name;
			text += ": ";
			text += value;
			(*it).element->SetText(text.c_str());

			int size = ui_main->UIGetTextSize(text.c_str(), (*it).element->GetFont()).x + (*it).element->GetPos().x + 3;

			if (size > max_width)
				max_width = size;

			break;
		}
	}
}

void UIU_Debug::Update(float dt)
{
	SetSize(UI_Point(max_width, GetSize().y));
	max_width = 0;
}

void UIU_Debug::Draw()
{
}

void UIU_Debug::OnEvent(UI_Event * ev)
{
	if (ev->GetEventType() == ui_event_type::event_delete)
	{
		for (list<ui_debug_item>::iterator it = debug_items.begin(); it != debug_items.end(); it++)
		{
			if ((*it).element == ev->GetSender())
			{
				debug_items.erase(it);
				break;
			}
		}
	}
}

void UIU_Debug::CleanUp()
{
	for (list<ui_debug_item>::iterator it = debug_items.begin(); it != debug_items.end(); it++)
	{
		(*it).element->Delete();
	}

	debug_items.clear();
}

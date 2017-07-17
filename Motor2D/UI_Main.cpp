#include "UI_Main.h"
#include "UI_EventSystem.h"
#include "UI_Element.h"

#include "p2Log.h"

UI_Main::UI_Main() : j1Module()
{
	name = "UI";
}

UI_Main::~UI_Main()
{
	
}

bool UI_Main::Awake(pugi::xml_node &)
{
	bool ret = true;

	ui_event_system = new UI_EventSystem(this);

	return ret;
}

bool UI_Main::Start()
{
	bool ret = true;

	LOG("Start module ui");

	return ret;
}

bool UI_Main::PreUpdate()
{
	bool ret = true;



	return ret;
}

bool UI_Main::Update(float dt)
{
	bool ret = true;

	CheckEvents();

	return ret;
}

bool UI_Main::PostUpdate()
{
	bool ret = true;

	DeleteElements();

	return ret;
}

bool UI_Main::CleanUp()
{
	bool ret = true;

	ui_event_system->CleanUp();
	delete ui_event_system;

	return ret;
}

void UI_Main::ExpandEvent(UI_Event * ev)
{
	for (list<UI_Element*>::iterator it = elements.begin(); it != elements.end(); it++)
	{
		(*it)->OnEvent(ev);
	}
}

UI_EventSystem * UI_Main::GetEventSystem()
{
	return ui_event_system;
}

UI_Point UI_Main::GetMousePos()
{
	UI_Point ret;
	int x, y;

	App->input->GetMousePosition(x, y);

	ret.x = x;
	ret.y = y;

	return ret;
}

bool UI_Main::GetMouseLeftDown()
{
	return (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN);
}

bool UI_Main::GetMouseRightDown()
{
	return (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN);
}

bool UI_Main::GetMouseLeftUp()
{
	return (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP);
}

bool UI_Main::GetMouseRightUp()
{
	return (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_UP);
}

void UI_Main::CheckEvents()
{
	UI_Element* mouse_enter = nullptr;
	UI_Element* mouse_click = nullptr;

	for (list<UI_Element*>::iterator it = elements.begin(); it != elements.end(); it++)
	{
		// Mouse in quad -------------

		UI_Point mouse = GetMousePos();
		UI_Point pos = (*it)->GetRealtivePos();
		UI_Point size = (*it)->GetSize();

		if (mouse.x > pos.x && mouse.x < pos.x + size.x && mouse.y > pos.y && mouse.y < pos.y + size.y)
		{
			// Mouse enter -------------
			if (!(*it)->GetMouseOver())
			{
				mouse_enter = (*it);
			}

			if (GetMouseLeftDown())
			{
				mouse_click = (*it);
			}
		}
	}

	if (mouse_enter != nullptr)
	{
		mouse_enter->InvokeOnMouseOver();
	}
}

void UI_Main::DeleteElements()
{
	for (list<UI_Element*>::iterator del = to_delete.begin(); del != to_delete.end();)
	{
		for (list<UI_Element*>::iterator el = elements.begin(); el != elements.end(); el++)
		{
			if ((*del) == (*el))
				continue;

			// Clean from childs
			for (list<UI_Element*>::iterator ch = (*el)->GetChilds().begin(); ch != (*el)->GetChilds().end(); )
			{
				if ((*ch) == (*del))
				{
					(*el)->GetChilds().erase(ch);
				}
				else
					++ch;
			}

			// Clean from parents
			if ((*el)->GetParent() == (*del))
				(*el)->ResetParent();
		}

		// Clean
		(*del)->CleanUp();
		(*del)->CleanElement();

		// Delete
		delete (*del);
		to_delete.erase(del);
	}
}

list<UI_Element*> UI_Main::GetElements()
{
	return elements;
}

void UI_Main::AddToDelete(UI_Element * element)
{
	to_delete.push_back(element);
}

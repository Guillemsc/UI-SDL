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



	return ret;
}

bool UI_Main::PostUpdate()
{
	bool ret = true;

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

ui_point UI_Main::GetMousePos()
{
	ui_point ret;
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

void UI_Main::CheckOnMouseEnter()
{
}

void UI_Main::DeleteElements()
{
	for (list<UI_Element*>::iterator del = to_delete.begin(); del != to_delete.end();)
	{
		for (list<UI_Element*>::iterator el = elements.begin(); el != to_delete.end(); el++)
		{
			if ((*del) == (*el))
				continue;

			// Clean from childs
			for (list<UI_Element*>::iterator ch = (*el)->GetChilds().begin(); (*el)->GetChilds().end; )
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

#include "UI_Main.h"
#include "UI_EventSystem.h"
#include "UI_Element.h"
#include "j1Render.h"

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

	// 1 //
	UpdateElements();

	// 2 //
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

void UI_Main::UIUpdatingInfo(int _window_width, int _window_height)
{
	if ((window_width != _window_width) || (window_height != _window_height))
	{
		window_width = _window_width;
		window_height = _window_height;

		UI_Event* e = new UI_Event(ui_event_type::event_window_resize);
		GetEventSystem()->SendEvent(e);
	}

	window_width = _window_width;
	window_height = _window_height;
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

UI_Point UI_Main::GetWindowSize()
{
	UI_Point ret;

	ret.x = window_width;
	ret.y = window_height;

	return ret;
}

void UI_Main::UIRenderQuad(int x, int y, int w, int h)
{
	//App->render->DrawQuad();
}

void UI_Main::UpdateElements()
{
	for (list<UI_Element*>::iterator it = elements.begin(); it != elements.end(); it++)
	{
		(*it)->Update();
	}
}

void UI_Main::CheckEvents()
{
	UI_Element* mouse_over = nullptr;
	UI_Element* mouse_over_enter = nullptr;
	UI_Element* mouse_over_out = nullptr;

	UI_Element* mouse_click = nullptr;
	UI_Element* mouse_down = nullptr;
	UI_Element* mouse_up = nullptr;

	for (list<UI_Element*>::iterator it = elements.begin(); it != elements.end(); it++)
	{
		// Mouse in quad -------------

		UI_Point mouse = GetMousePos();
		UI_Point pos = (*it)->GetRealtivePos();
		UI_Point size = (*it)->GetSize();

		if (mouse.x > pos.x && mouse.x < pos.x + size.x && mouse.y > pos.y && mouse.y < pos.y + size.y)
		{
			// Mouse over --------------
			mouse_over = (*it);

			// Mouse over enter --------
			if (!(*it)->GetMouseOver())
			{
				mouse_over_enter = (*it);
			}

			// Mouse click -------------
			if (!(*it)->GetMouseDown() && (GetMouseLeftDown() || GetMouseRightDown()))
			{
				mouse_click = (*it);
			}

			// Mouse down --------------
			if (GetMouseLeftDown() || GetMouseRightDown())
			{
				mouse_down = (*it);
			}
		}
		else
		{
			// Mouse over out ----------
			if ((*it)->GetMouseOver())
			{
				mouse_over_out = (*it);
			}

			// Mouse up ----------------
			if ((*it)->GetMouseDown() && (GetMouseLeftUp() || GetMouseRightUp()))
			{
				mouse_up = (*it);
			}
		}
	}

	// Invoke
	if (mouse_over != nullptr)
		mouse_over->InvokeOnMouseOver();
	
	if (mouse_over_enter != nullptr)
		mouse_over_enter->InvokeOnMouseOverEnter();
	
	if (mouse_over_out != nullptr)
		mouse_over_out->InvokeOnMouseOverOut();
	
	if (mouse_click != nullptr)
		mouse_click->InvokeOnMouseClick();
	
	if (mouse_down != nullptr)
		mouse_down->InvokeOnMouseDown();
	
	if (mouse_up != nullptr)
		mouse_up->InvokeOnMouseUp();
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

void UI_Main::BringToFrontElement(UI_Element * element)
{
	for (list<UI_Element*>::iterator it = elements.begin(); it != elements.end(); it++)
	{
		if ((*it) == element)
		{
			elements.erase(it);
			break;
		}
	}

	elements.push_back(element);
}

void UI_Main::BringToFrontAndChilds(UI_Element * element)
{
	list<UI_Element*> childs = element->GetChilds();

	for (list<UI_Element*>::iterator it = elements.begin(); it != elements.end();)
	{
		bool deleted = false;

		for (list<UI_Element*>::iterator ch = childs.begin(); ch != childs.end(); ch++)
		{
			if ((*it) == (*ch))
			{
				elements.erase(it);
				deleted = true;
				break;
			}
		}

		if (!deleted)
			++it;
	}

	for (list<UI_Element*>::iterator ch = childs.begin(); ch != childs.end(); ch++)
	{
		elements.push_back((*ch));
	}
}

void UI_Main::DeleteElement(UI_Element * element)
{
	to_delete.push_back(element);
}

#include "UI_Main.h"
#include "UI_EventSystem.h"
#include "UI_Animator.h"
#include "UI_Element.h"

#include "j1Render.h"
#include "j1Fonts.h"
#include "j1Textures.h"
#include "j1Window.h"

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
	LoadAtlas();

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
	GetEventSystem()->Update();

	// 2 //
	CheckWindowResize();

	// 3 //
	UpdateElements();

	// 4 //
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

	for (list<UI_Element*>::iterator it = elements.begin(); it != elements.end(); it++)
	{
		(*it)->Delete();
	}

	DeleteElements();

	ui_event_system->CleanUp();
	delete ui_event_system;

	UnloadAtlas();

	return ret;
}

void UI_Main::CheckWindowResize()
{
	UI_Point actual_window = { GetWindowSize().x, GetWindowSize().y };

	if ((window_width != actual_window.x) || (window_height != actual_window.y))
	{
		window_width = actual_window.x;
		window_height = actual_window.y;

		UI_Event* e = new UI_Event(ui_event_type::event_window_resize);
		GetEventSystem()->SendEvent(e);
	}

	window_width = actual_window.x;
	window_height = actual_window.y;
}

bool UI_Main::LoadAtlas()
{
	atlas = App->tex->LoadTexture("atlas.png");

	return (atlas != nullptr) ? true : false;
}

void UI_Main::UnloadAtlas()
{
	App->tex->UnLoadTexture(atlas);
}

void UI_Main::ExpandEvent(UI_Event * ev)
{
	OnEvent(ev);

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

	ret.x = App->win->GetWindowSize().x;
	ret.y = App->win->GetWindowSize().y;

	return ret;
}

void UI_Main::UIRenderQuad(int x, int y, int w, int h, int r, int g, int b, int a, bool filled)
{
	App->render->DrawQuad({x, y, w, h}, r, g, b, a, filled);
}

void UI_Main::UIRenderLine(int x1, int y1, int x2, int y2, int r, int g, int b, int a)
{
	App->render->DrawLine(x1, y1, x2, y2, r, g, b, a);
}

void UI_Main::UIRenderPoint(int x, int y, int r, int g, int b, int a)
{
	App->render->DrawCircle(x, y, 1, r, g, b, a, true);
}

void UI_Main::UIRenderText(int x, int y, char* text, Font* font, int r, int g, int b, int a)
{
	int size_w, size_h = 0;

	SDL_Texture* texture = App->font->Print(text, { (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a }, font);
	App->font->CalcSize(text, size_w, size_h, font);

	SDL_Rect rect = { 0, 0, size_w, size_h };

	App->render->Blit(texture, x, y, &rect);

	App->tex->UnLoadTexture(texture);
}

void UI_Main::UIRenderImage(int x, int y, SDL_Rect rect)
{
	App->render->Blit(GetAtlas(), x, y, &rect);
}

void UI_Main::UISetViewport(int x, int y, int w, int h)
{
	App->render->SetViewPort({ x, y, w, h });
}

void UI_Main::UIResetViewport()
{
	App->render->ResetViewPort();
}

bool UI_Main::GetDebug()
{
	return debug;
}

void UI_Main::SetDebug(bool set)
{
	debug = set;
}

SDL_Texture * UI_Main::GetAtlas()
{
	return atlas;
}

void UI_Main::UpdateElements()
{
	for (list<UI_Element*>::iterator it = elements.begin(); it != elements.end(); it++)
	{
		if (GetDebug())
		{
			if ((*it)->GetUsesAnchor())
			{
				UIRenderLine((*it)->GetAnchorPos().x, (*it)->GetAnchorPos().y - 5, (*it)->GetAnchorPos().x, (*it)->GetAnchorPos().y + 5, 255, 255, 255, 255);
				UIRenderLine((*it)->GetAnchorPos().x - 5, (*it)->GetAnchorPos().y, (*it)->GetAnchorPos().x + 5, (*it)->GetAnchorPos().y, 255, 255, 255, 255);
			}
		}

		UISetViewport((*it)->GetViewport().X(), (*it)->GetViewport().Y(), (*it)->GetViewport().W(), (*it)->GetViewport().H());

		if ((*it)->GetVisible())
		{
			(*it)->Update();

			(*it)->Draw();

			(*it)->UpdateElement();
		}

		UIResetViewport();
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
		if (!(*it)->GetInteractable() || !(*it)->GetVisible())
			continue;

		// Mouse in quad -------------

		UI_Point mouse = GetMousePos();
		UI_Point pos = UI_Point((*it)->GetViewport().X(), (*it)->GetViewport().Y());
		UI_Point size = UI_Point((*it)->GetViewport().W(), (*it)->GetViewport().H());

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

			// Mouse up ----------------
			if ((*it)->GetMouseDown() && (GetMouseLeftUp() || GetMouseRightUp()))
			{
				mouse_up = (*it);
			}
		}
		else
		{
			// Mouse over out ----------
			if ((*it)->GetMouseOver())
			{
				mouse_over_out = (*it);
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
		for (list<UI_Element*>::iterator el = elements.begin(); el != elements.end();)
		{
			if ((*del) == (*el))
			{
				el = elements.erase(el);
				continue;
			}

			// Clean from childs
			for (list<UI_Element*>::iterator ch = (*el)->GetChilds().begin(); ch != (*el)->GetChilds().end(); )
			{
				if ((*ch) == (*del))
				{
					ch = (*el)->GetChilds().erase(ch);
				}
				else
					++ch;
			}

			// Clean from parents
			if ((*el)->GetParent() == (*del))
				(*el)->ResetParent();

			++el;
		}

		// Clean
		(*del)->CleanUp();
		(*del)->CleanElement();

		// Delete
		delete (*del);
		del = to_delete.erase(del);
	}
}

void UI_Main::OnEvent(UI_Event * ev)
{
	switch (ev->GetEventType())
	{
	default:
		break;
	}
}

list<UI_Element*> UI_Main::GetElements()
{
	return elements;
}

void UI_Main::ElementBringToFront(UI_Element * element)
{
	for (list<UI_Element*>::iterator it = elements.begin(); it != elements.end(); it++)
	{
		if ((*it) == element)
		{
			it = elements.erase(it);
			break;
		}
	}

	elements.push_back(element);
}

void UI_Main::ElementBringToFrontAndChilds(UI_Element * element)
{
	list<UI_Element*> childs = element->GetChilds();

	for (list<UI_Element*>::iterator it = elements.begin(); it != elements.end();)
	{
		bool deleted = false;

		for (list<UI_Element*>::iterator ch = childs.begin(); ch != childs.end(); ch++)
		{
			if ((*it) == (*ch))
			{
				it = elements.erase(it);
				deleted = true;
				break;
			}
		}

		if (!deleted)
			++it;
	}
	
	elements.push_back(element);

	for (list<UI_Element*>::iterator ch = childs.begin(); ch != childs.end(); ch++)
	{
		elements.push_back((*ch));
	}
}

void UI_Main::ElementSendToBack(UI_Element * element)
{
	for (list<UI_Element*>::iterator it = elements.begin(); it != elements.end(); it++)
	{
		if ((*it) == element)
		{
			it = elements.erase(it);
			break;
		}
	}

	elements.push_front(element);
}

void UI_Main::ElementSendToBackAndChilds(UI_Element * element)
{
	list<UI_Element*> childs = element->GetChilds();

	for (list<UI_Element*>::iterator it = elements.begin(); it != elements.end();)
	{
		bool deleted = false;

		for (list<UI_Element*>::iterator ch = childs.begin(); ch != childs.end(); ch++)
		{
			if ((*it) == (*ch))
			{
				it = elements.erase(it);
				deleted = true;
				break;
			}
		}

		if (!deleted)
			++it;
	}

	elements.push_front(element);

	for (list<UI_Element*>::iterator ch = childs.begin(); ch != childs.end(); ch++)
	{
		elements.push_front((*ch));
	}
}

void UI_Main::AddElement(UI_Element * element)
{
	elements.push_back(element);
}

void UI_Main::DeleteElement(UI_Element * element)
{
	to_delete.push_back(element);
}

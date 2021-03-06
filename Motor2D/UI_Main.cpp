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

	float start = UIGetTimeFromStart();

	// 1 //
	GetEventSystem()->Update();

	// 2 //
	CheckWindowResize();

	// 3 //
	UpdateElements(dt);

	// 4 //
	CheckEvents();

	debug_info.ui_main += UIGetTimeFromStart() - start;
	debug_info.avg_ui_main = debug_info.ui_main / UIGetFramesFromStart();
	
	return ret;
}

bool UI_Main::PostUpdate()
{
	bool ret = true;

	// 1 //
	GetEventSystem()->PostUpdate();

	// 2 //
	DeleteElements();

	return ret;
}

bool UI_Main::CleanUp()
{
	bool ret = true;

	for (list<UI_Element*>::iterator it = elements.begin(); it != elements.end(); it++)
		(*it)->Delete();
	
	DeleteElements();

	ui_event_system->CleanUp();
	delete ui_event_system;

	UnloadAtlas();

	return ret;
}

UI_DebugInfo UI_Main::GetUIDebugInfo()
{
	return debug_info;
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

UI_Point UI_Main::UIRenderText(int x, int y, const char* text, Font* font, int r, int g, int b, int a)
{
	int size_w, size_h = 0;

	SDL_Texture* texture = App->font->Print(text, { (Uint8)r, (Uint8)g, (Uint8)b, (Uint8)a }, font);
	App->font->CalcSize(text, size_w, size_h, font);

	SDL_Rect rect = { 0, 0, size_w, size_h };

	App->render->Blit(texture, x, y, &rect, (Uint8)a);

	App->tex->UnLoadTexture(texture);

	return UI_Point(size_w, size_h);
}

void UI_Main::UIRenderImage(int x, int y, int rect_x, int rect_y, int rect_w, int rect_h, float alpha)
{
	SDL_Rect rect = { rect_x, rect_y, rect_w, rect_h };
	App->render->Blit(GetAtlas(), x, y, &rect, alpha);
}

Font * UI_Main::UILoadFont(const char * name)
{
	Font* ret = nullptr;

	ret = App->font->GetFont(name);

	return ret;
}

float UI_Main::UIGetFontSize(Font* font)
{
	float ret = 0;

	int size_w, size_h = 0;
	App->font->CalcSize("@", size_w, size_h, font);

	ret = size_h;

	return ret;
}

UI_Point UI_Main::UIGetTextSize(const char * text, Font* font)
{
	UI_Point ret;

	int w, h;
	App->font->CalcSize(text, w, h, font);

	ret.x = w;
	ret.y = h;

	return ret;
}

bool UI_Main::UIGetKeyboardInput(const char *& input)
{
	if (App->input->input_text != "")
	{
		input = App->input->input_text.c_str();
		return true;
	}

	return false;
}

float UI_Main::UIGetTimeFromStart()
{
	return SDL_GetTicks();
}

int UI_Main::UIGetFramesFromStart()
{
	return App->GetFramesFromStart();
}

void UI_Main::UISetViewport(int x, int y, int w, int h)
{
	App->render->SetViewPort({ x, y, w, h });
}

void UI_Main::UIResetViewport()
{
	App->render->ResetViewPort();
}

void UI_Main::ClearFocusedElement()
{
	focused_element = nullptr;
}

bool UI_Main::GetDebug()
{
	return debug;
}

void UI_Main::SetDebug(bool set)
{
	debug = set;
}

int UI_Main::GetElementsCount()
{
	return elements.size();
}

SDL_Texture * UI_Main::GetAtlas()
{
	return atlas;
}

void UI_Main::UpdateElements(float dt)
{
	for (list<UI_Element*>::iterator it = elements.begin(); it != elements.end(); it++)
	{
		float start = UIGetTimeFromStart();

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
			(*it)->UpdateElement(dt);

			(*it)->Update(dt);

			(*it)->Draw();
		}

		UIResetViewport();

		AddToDebugInfo((*it)->GetType(), UIGetTimeFromStart() - start);
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
			mouse_over_enter = nullptr;
			mouse_click = nullptr;
			mouse_down = nullptr;
			mouse_up = nullptr;

			// Mouse over --------------
			if (mouse_over != nullptr && mouse_over->GetMouseOver())
			{
				mouse_over_out = mouse_over;
			}

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
		}

		// Mouse up ----------------
		if ((*it)->GetMouseDown() && (GetMouseLeftUp() || GetMouseRightUp()))
		{
			mouse_up = (*it);
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
		// Iterate thorugh all elements and clean everything
		for (list<UI_Element*>::iterator el = elements.begin(); el != elements.end();)
		{
			if ((*del) == (*el))
			{
				el = elements.erase(el);
				continue;
			}

			// Clean from childs
			(*el)->RemoveChild((*del));

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

void UI_Main::AddToDebugInfo(ui_element_type element, float time)
{
	switch (element)
	{
	case ui_element_null:
		break;
	case ui_element_text:
		debug_info.texts += time;
		debug_info.avg_texts = debug_info.texts / UIGetFramesFromStart();
		break;
	case ui_element_panel:
		debug_info.panels += time;
		debug_info.avg_panels = debug_info.panels / UIGetFramesFromStart();
		break;
	case ui_element_button:
		debug_info.buttons += time;
		debug_info.avg_buttons = debug_info.buttons / UIGetFramesFromStart();
		break;
	case ui_element_image:
		debug_info.images += time;
		debug_info.avg_images = debug_info.images / UIGetFramesFromStart();
		break;
	case ui_element_checkbox:
		debug_info.check_boxes += time;
		debug_info.avg_check_boxes = debug_info.check_boxes / UIGetFramesFromStart();
		break;
	case ui_element_textinput:
		debug_info.texts_input += time;
		debug_info.texts_input = debug_info.texts_input / UIGetFramesFromStart();
		break;
	case uiu_message:
		break;
	case uiu_console:
		break;
	case uiu_debug:
		break;
	default:
		break;
	}
}

void UI_Main::OnEvent(UI_Event * ev)
{
	switch (ev->GetEventType())
	{
		case ui_event_type::event_mouse_down:
		{
			focused_element = ev->GetSender();
		}
		break;
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

		if ((*it) == element)
		{
			it = elements.erase(it);
			deleted = true;
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

		if ((*it) == element)
		{
			it = elements.erase(it);
			deleted = true;
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
	for (list<UI_Element*>::iterator del = to_delete.begin(); del != to_delete.end(); del++)
	{
		if ((*del) == element)
			return;
	}

	to_delete.push_back(element);
}

UI_Element * UI_Main::GetFocusedElement()
{
	return focused_element;
}

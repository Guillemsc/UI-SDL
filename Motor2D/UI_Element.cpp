#include "UI_Element.h"
#include "UI_EventSystem.h"

UI_Element::UI_Element(UI_Main* _ui_main, UI_EventSystem* _event_system, ui_element_type _type)
{
	ui_main = _ui_main;
	event_system = _event_system;
	type = _type;
}

UI_Element::~UI_Element()
{
}

void UI_Element::InvokeOnMouseOver()
{
	UI_Event* e = new UI_Event(ui_event_type::event_mouse_over, this);
	OnMouseOver(e);
	GetEventSystem()->SendEvent(e);
	mouse_over = true;
}

void UI_Element::InvokeOnMouseOverEnter()
{
	UI_Event* e = new UI_Event(ui_event_type::event_mouse_over_enter, this);
	OnMouseOverEnter(e);
	GetEventSystem()->SendEvent(e);
	mouse_over = true;
}

void UI_Element::InvokeOnMouseOverOut()
{
	UI_Event* e = new UI_Event(ui_event_type::event_mouse_over_out, this);
	OnMouseOverOut(e);
	GetEventSystem()->SendEvent(e);
	mouse_over = false;
}

void UI_Element::InvokeOnMouseClick()
{
	UI_EventMouse* e = new UI_EventMouse(ui_event_type::event_mouse_click, this, ui_main->GetMouseLeftDown(), ui_main->GetMouseRightDown());
	OnMouseClick(e);
	GetEventSystem()->SendEvent(e);
	mouse_down = true;
}

void UI_Element::InvokeOnMouseDown()
{
	UI_EventMouse* e = new UI_EventMouse(ui_event_type::event_mouse_down, this, ui_main->GetMouseLeftDown(), ui_main->GetMouseRightDown());
	OnMouseDown(e);
	GetEventSystem()->SendEvent(e);
	mouse_down = true;
}

void UI_Element::InvokeOnMouseUp()
{
	UI_EventMouse* e = new UI_EventMouse(ui_event_type::event_mouse_up, this, ui_main->GetMouseLeftDown(), ui_main->GetMouseRightDown());
	OnMouseUp(e);
	GetEventSystem()->SendEvent(e);
	mouse_down = false;
}

// Position from 0 to 1 relative to the screen
void UI_Element::SetPos(UI_Point pos)
{
	if(uses_anchor_pos)
	{
		UI_Point window = ui_main->GetWindowSize();

		int anchor_x = int(anchor_pos.x * window.x);
		int anchor_y = int(anchor_pos.y * window.y);

		transform.SetPos(anchor_x + pos.x, anchor_y + pos.y);
	}
	else
	{
		transform.SetPos(pos.x, pos.y);
	}
}

void UI_Element::SetAnchor(UI_Point anchor)
{
	anchor_pos = anchor;
	uses_anchor_pos = true;
}

void UI_Element::DeleteAnchor()
{
	uses_anchor_pos = false;
}

void UI_Element::SetRenderingViewport(int x, int y, int width, int height)
{
	rendering_viewport.SetPos(x, y);
	rendering_viewport.SetSize(width, height);
}

UI_Point UI_Element::GetLocalPos()
{
	UI_Point ret;

	ret.x = transform.X();
	ret.y = transform.Y();

	return ret;
}

UI_Point UI_Element::GetRealtivePos()
{
	UI_Point ret;

	ret.x = transform.X();
	ret.y = transform.Y();

	UI_Element* curr_parent = parent;

	while (curr_parent != nullptr)
	{
		ret.x += curr_parent->transform.X();
		ret.y += curr_parent->transform.Y();

		curr_parent = parent;
	}

	return ret;
}

UI_Point UI_Element::GetSize()
{
	UI_Point ret;

	ret.x = transform.W();
	ret.y = transform.H();

	return ret;
}

bool UI_Element::GetMouseOver()
{
	return mouse_over;
}

bool UI_Element::GetMouseDown()
{
	return mouse_down;
}

void UI_Element::BringToFront()
{
	ui_main->BringToFrontElement(this);
}

void UI_Element::BringToFrontAndChilds()
{
	ui_main->BringToFrontAndChilds(this);
}

void UI_Element::Delete()
{
	UI_Event* e = new UI_Event(ui_event_type::event_delete, this);
	event_system->SendEvent(e);

	ui_main->DeleteElement(this);
}

void UI_Element::DeleteAndChilds()
{
	for (list<UI_Element*>::iterator it = childs.begin(); it != childs.end();)
	{
		(*it)->DeleteAndChilds();

		childs.erase(it);
	}

	Delete();
}

ui_element_type UI_Element::GetType()
{
	return type;
}

void UI_Element::AddChild(UI_Element* child)
{
	if (child == nullptr)
		return;
	
	child->parent = this;
	child->DeleteAnchor();
	childs.push_back(child);
}

void UI_Element::RemoveChild(UI_Element* child)
{
	if (child == nullptr)
		return;

	for (list<UI_Element*>::iterator it = childs.begin(); it != childs.end(); it++)
	{
		if ((*it) == child)
		{
			childs.erase(it);
			break;
		}
	}
}

void UI_Element::StartElement()
{
}

void UI_Element::UpdateElement()
{
}

void UI_Element::CleanElement()
{
}

list<UI_Element*> UI_Element::GetChilds()
{
	return childs;
}

UI_Element* UI_Element::GetParent()
{
	return parent;
}

void UI_Element::ResetParent()
{
	parent = nullptr;
}

UI_Main* UI_Element::GetUiMain()
{
	return ui_main;
}

UI_EventSystem * UI_Element::GetEventSystem()
{
	return event_system;
}

void UI_Transform::operator=(UI_Transform& trans)
{
	trans.x = x;
	trans.y = y;
	trans.w = w;
	trans.h = h;
}

bool UI_Transform::operator == (UI_Transform trans)
{
	return ((trans.x == x) && (trans.y == y) && (trans.w = w) && (trans.h == h)) ? true : false;
}

void UI_Transform::SetPos(int _x, int _y)
{
	x = _x;
	y = _y;
}

void UI_Transform::SetPos(UI_Point pos)
{
	x = pos.x;
	y = pos.y;
}

void UI_Transform::AddToPos(int add_x, int add_y)
{
	x += add_x;
	y += add_y;
}

void UI_Transform::SubstractToPos(int sub_x, int sub_y)
{
	x -= sub_x;
	y -= sub_y;
}

void UI_Transform::SetSize(int _width, int _height)
{
	w = _width;
	h = _height;
}

int UI_Transform::X()
{
	return x;
}

int UI_Transform::Y()
{
	return y;
}

int UI_Transform::W()
{
	return w;
}

int UI_Transform::H()
{
	return h;
}

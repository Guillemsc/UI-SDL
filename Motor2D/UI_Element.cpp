#include "UI_Element.h"
#include "UI_EventSystem.h"
#include "p2Log.h"

UI_Element::UI_Element(UI_Main* _ui_main, ui_element_type _type)
{
	ui_main = _ui_main;
	event_system = _ui_main->GetEventSystem();
	type = _type;
}

UI_Element::~UI_Element()
{
}

void UI_Element::InvokeOnMouseOver()
{
	UI_Event* e = new UI_Event(ui_event_type::event_mouse_over, this);

	if(OnMouseOver)
		OnMouseOver(e);

	GetEventSystem()->SendEvent(e);
	mouse_over = true;
}

void UI_Element::InvokeOnMouseOverEnter()
{
	UI_Event* e = new UI_Event(ui_event_type::event_mouse_over_enter, this);

	if(OnMouseOverEnter)
		OnMouseOverEnter(e);

	GetEventSystem()->SendEvent(e);
	mouse_over = true;
}

void UI_Element::InvokeOnMouseOverOut()
{
	UI_Event* e = new UI_Event(ui_event_type::event_mouse_over_out, this);

	if(OnMouseOverOut)
		OnMouseOverOut(e);

	GetEventSystem()->SendEvent(e);
	mouse_over = false;
}

void UI_Element::InvokeOnMouseClick()
{
	UI_EventMouse* e = new UI_EventMouse(ui_event_type::event_mouse_click, this, ui_main->GetMouseLeftDown(), ui_main->GetMouseRightDown());

	if(OnMouseClick)
		OnMouseClick(e);

	GetEventSystem()->SendEvent(e);
	mouse_down = true;
}

void UI_Element::InvokeOnMouseDown()
{
	UI_EventMouse* e = new UI_EventMouse(ui_event_type::event_mouse_down, this, ui_main->GetMouseLeftDown(), ui_main->GetMouseRightDown());

	if(OnMouseDown)
		OnMouseDown(e);

	GetEventSystem()->SendEvent(e);
	mouse_down = true;
}

void UI_Element::InvokeOnMouseUp()
{
	UI_EventMouse* e = new UI_EventMouse(ui_event_type::event_mouse_up, this, ui_main->GetMouseLeftDown(), ui_main->GetMouseRightDown());

	if(OnMouseUp)
		OnMouseUp(e);

	GetEventSystem()->SendEvent(e);
	mouse_down = false;
}

void UI_Element::InvokeOnInteractableTrue()
{
	UI_Event* ev = new UI_Event(ui_event_type::event_interactable_on);

	if (OnInteractableTrue)
		OnInteractableTrue(ev);

	GetEventSystem()->SendEvent(ev);
}

void UI_Element::InvokeOnInteractableFalse()
{
	UI_Event* ev = new UI_Event(ui_event_type::event_interactable_off);

	if (OnInteractableFalse)
		OnInteractableFalse(ev);

	GetEventSystem()->SendEvent(ev);
}

void UI_Element::InvokeOnVisibleTrue()
{
	UI_Event* ev = new UI_Event(ui_event_type::event_visible_on);

	if (OnVisibleTrue)
		OnVisibleTrue(ev);

	GetEventSystem()->SendEvent(ev);
}

void UI_Element::InvokeOnVisibleFalse()
{
	UI_Event* ev = new UI_Event(ui_event_type::event_visible_off);

	if (OnVisibleFalse)
		OnVisibleFalse(ev);

	GetEventSystem()->SendEvent(ev);
}

void UI_Element::SetPos(UI_Point _pos)
{
	pos = _pos;

	UpdatePos();
}

void UI_Element::UpdatePos()
{
	UI_Point new_pos = pos;

	new_pos = GetRelativePosToParents();

	transform.SetPos(new_pos);
}

void UI_Element::UpdateViewport()
{
	int view_x = GetTransformPos().x;
	int view_y = GetTransformPos().y;
	int view_w = GetSize().x;
	int view_h = GetSize().y;

	// Scissor
	if(parent != nullptr)
	{
		if (parent->GetViewport().X() > view_x)
			view_x = parent->GetViewport().X();

		if (parent->GetViewport().Y() > view_y)
			view_y = parent->GetViewport().Y();

		if (parent->GetViewport().X() + parent->GetViewport().W() < view_x + view_w)
		{
			view_w = parent->GetViewport().X() + parent->GetViewport().W() - view_x;

			if (view_w < 0)
				view_w = 0;
		}

		if (parent->GetViewport().Y() + parent->GetViewport().H() < view_y + view_h)
		{
			view_h = parent->GetViewport().Y() + parent->GetViewport().H() - view_y;
		}
	}

	viewport.SetPos(view_x, view_y); 
	viewport.SetSize(view_w, view_h);
}

void UI_Element::SetSize(UI_Point pos)
{
	transform.SetSize(pos.x, pos.y);
}

void UI_Element::SetAnchor(UI_Point _anchor)
{
	if (parent != nullptr)
		return;

	anchor = _anchor;

	if (anchor.x > 1)
		anchor.x = 1;
	if (anchor.y > 1)
		anchor.y = 1;

	uses_anchor = true;
}

void UI_Element::SetInteractable(bool set)
{
	if (interactable != set)
	{
		interactable = set;

		interactable ? InvokeOnInteractableTrue() : InvokeOnInteractableFalse();
	}
}

void UI_Element::SetVisible(bool set)
{
	if (visible != set)
	{
		visible = set;

		visible ? InvokeOnVisibleTrue() : InvokeOnVisibleFalse();
	}
}

void UI_Element::SetDebugColor(UI_Color color)
{
	debug_color = color;
}

bool UI_Element::GetUsesAnchor()
{
	return uses_anchor;
}

void UI_Element::DeleteAnchor()
{
	uses_anchor = false;
}

UI_Point UI_Element::GetPos()
{
	return pos;
}

UI_Point UI_Element::GetRelativePosToParents()
{
	UI_Point ret = { GetRelativePosToAnchor().x , GetRelativePosToAnchor().y};

	UI_Element* curr_parent = parent;

	while (curr_parent != nullptr)
	{
		ret.x += curr_parent->GetRelativePosToAnchor().x;
		ret.y += curr_parent->GetRelativePosToAnchor().y;

		curr_parent = curr_parent->parent;
	}

	return ret;
}

UI_Point UI_Element::GetRelativePosToAnchor()
{
	UI_Point ret;

	ret.x = GetPos().x + GetAnchorPos().x;
	ret.y = GetPos().y + GetAnchorPos().y;

	return ret;
}

UI_Point UI_Element::GetSize()
{
	return UI_Point(transform.W(), transform.H());
}

UI_Point UI_Element::GetTransformPos()
{
	return UI_Point(transform.X(), transform.Y());
}

UI_Point UI_Element::GetAnchorPos()
{
	UI_Point ret;

	ret.x = anchor.x * GetUiMain()->GetWindowSize().x;
	ret.y = anchor.y * GetUiMain()->GetWindowSize().y;

	return ret;
}

UI_Transform UI_Element::GetViewport()
{
	return viewport;
}

bool UI_Element::GetInteractable()
{
	return interactable;
}

bool UI_Element::GetVisible()
{
	return visible;
}

bool UI_Element::GetMouseOver()
{
	return mouse_over;
}

bool UI_Element::GetMouseDown()
{
	return mouse_down;
}

UI_Color UI_Element::GetDebugColor()
{
	return debug_color;
}

void UI_Element::BringToFront()
{
	ui_main->ElementBringToFront(this);
}

void UI_Element::BringToFrontAndChilds()
{
	ui_main->ElementBringToFrontAndChilds(this);
}

void UI_Element::SendToBack()
{
	ui_main->ElementSendToBack(this);
}

void UI_Element::SendToBackAndChilds()
{
	ui_main->ElementSendToBackAndChilds(this);
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

		it = childs.erase(it);
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
			it = childs.erase(it);
			break;
		}
	}
}

void UI_Element::StartElement()
{
}

void UI_Element::UpdateElement()
{
	if (GetUiMain()->GetDebug())
	{
	}

	UpdatePos();

	UpdateViewport();
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

UI_Point UI_Element::ZeroPos()
{
	UI_Point ret;

	ret.x = GetTransformPos().x - GetViewport().X();
	ret.y = GetTransformPos().y - GetViewport().Y();

	return ret;
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

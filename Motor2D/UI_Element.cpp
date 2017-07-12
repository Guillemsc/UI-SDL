#include "UI_Element.h"

UI_Element::UI_Element(ui_element_type _type)
{
	type = _type;
}

UI_Element::~UI_Element()
{
}

void UI_Element::Delete()
{
	to_delete = true;
}

void UI_Element::CleanElement()
{
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

list<UI_Element*> UI_Element::GetChilds()
{
	return childs;
}

UI_Element* UI_Element::GetParent()
{
	return parent;
}

bool UI_Element::ToDelete()
{
	return to_delete;
}

void Transform::operator=(Transform& trans)
{
	trans.x = x;
	trans.y = y;
	trans.w = w;
	trans.h = h;
}

bool Transform::operator == (Transform trans)
{
	if ((trans.x == x) && (trans.y == y) && (trans.w = w) && (trans.h == h))
		return true;
	return false;
}


void Transform::SetPos(int _x, int _y)
{
	x = _x;
	y = _y;
}

void Transform::AddToPos(int add_x, int add_y)
{
	x += add_x;
	y += add_y;
}

void Transform::SubstractToPos(int sub_x, int sub_y)
{
	x -= sub_x;
	y -= sub_y;
}

void Transform::SetSize(int _width, int _height)
{
	w = _width;
	h = _height;
}

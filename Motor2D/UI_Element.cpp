#include "UI_Element.h"

UI_Element::UI_Element(ui_element_type _type)
{
	type = _type;
}

UI_Element::~UI_Element()
{
}

void UI_Element::CleanElement()
{
}

ui_element_type UI_Element::GetType()
{
	return type;
}

void UI_Element::AddChild(weak_ptr<UI_Element> child)
{
	if (child.expired())
		return;
	
	child.lock()->transform.AddToPos(transform.x, transform.y);
	childs.push_back(child);
}

void UI_Element::RemoveChild(weak_ptr<UI_Element> child)
{
	if (child.expired())
		return;

	for (list<weak_ptr<UI_Element>>::iterator it = childs.begin(); it != childs.end();)
	{
		if ((*it).expired())
		{
			childs.erase(it);
			continue;
		}

		if ((*it).lock() == child.lock())
		{
			childs.erase(it);
			break;
		}

		++it;
	}
}

list<weak_ptr<UI_Element>> UI_Element::GetChilds()
{
	return childs;
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

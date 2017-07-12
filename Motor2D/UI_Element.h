#ifndef __UI_Element_H__
#define __UI_Element_H__

#include "UI_Main.h"

class UI_Element;
class Transform;
class UI_Event;

enum ui_element_type;

// --------------------------------------------------

class Transform
{
public:
	void operator = (Transform& trans);
	bool operator == (Transform trans);

	void SetPos(int x, int y);
	void AddToPos(int add_x, int add_y);
	void SubstractToPos(int sub_x, int sub_y);
	void SetSize(int width, int height);

public:
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;
};


// --------------------------------------------------

enum ui_element_type
{
	element_null,
	element_panel,
	element_button,
};


// --------------------------------------------------

class UI_Element
{
public:
	UI_Element(ui_element_type type);
	virtual ~UI_Element();

	virtual void Start() {};
	virtual void Update() {};
	virtual void CleanUp() {};
	virtual void OnEvent(UI_Event* ev) {};

	void CleanElement();

	ui_element_type GetType();
	void AddChild(weak_ptr<UI_Element> child);
	void RemoveChild(weak_ptr<UI_Element> child); 
	list<weak_ptr<UI_Element>> GetChilds();

public:
	Transform transform;
	std::function<void(UI_Event*)> OnClick;

private: 
	ui_element_type type = (ui_element_type)0;
	list<weak_ptr<UI_Element>> childs;
};

#endif // __UI_EventSystem_H__
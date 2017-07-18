#ifndef __UI_Element_H__
#define __UI_Element_H__

#include "UI_Main.h"

class UI_Element;
class UI_Transform;
class UI_Event;
class UI_EventMouse;
class UI_Point;

enum ui_element_type;

// --------------------------------------------------

class UI_Transform
{
public:
	void operator = (UI_Transform& trans);
	bool operator == (UI_Transform trans);

	void SetPos(int x, int y);
	void SetPos(UI_Point pos);
	void AddToPos(int add_x, int add_y);
	void SubstractToPos(int sub_x, int sub_y);
	void SetSize(int width, int height);

	int X();
	int Y();
	int W();
	int H();

private:
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
	UI_Element(UI_Main* ui_main, UI_EventSystem* event_system, ui_element_type type);
	virtual ~UI_Element();

	virtual void Start() {};
	virtual void Update() {};
	virtual void CleanUp() {};
	virtual void OnEvent(UI_Event* ev) {};

	void InvokeOnMouseOver();
	void InvokeOnMouseOverEnter();
	void InvokeOnMouseOverOut();

	void InvokeOnMouseClick();
	void InvokeOnMouseDown();
	void InvokeOnMouseUp();

	void SetPos(UI_Point pos);

	void SetRenderingViewport(int x, int y, int width, int height);

	// Gets the local position of the object
	UI_Point GetLocalPos();

	// Gets the position of the object relative to the window
	UI_Point GetRealtivePos();
	UI_Point GetSize();

	bool GetMouseOver();
	bool GetMouseDown();

	void BringToFront();
	void BringToFrontAndChilds();

	void Delete();
	void DeleteAndChilds();

	UI_Main* GetUiMain();
	UI_EventSystem* GetEventSystem();
	list<UI_Element*> GetChilds();
	UI_Element* GetParent();
	void ResetParent();
	void CleanElement();

protected:
	ui_element_type GetType();

	void AddChild(UI_Element* child);
	void RemoveChild(UI_Element* child);

public:
	// Called every frame that the mouse is over an element.
	std::function<void(UI_Event*)> OnMouseOver;

	// Called the frame that the mouse goes into an element.
	std::function<void(UI_Event*)> OnMouseOverEnter;

	// Called the frame that the mouse goes out an element.
	std::function<void(UI_Event*)> OnMouseOverOut;

	// Called the frame that the mouse clicks over an element.
	std::function<void(UI_EventMouse*)> OnMouseClick;

	// Called every frame that the mouse is clicked over an element.
	std::function<void(UI_EventMouse*)> OnMouseDown;

	// Called the frame that the mouse click is released of an element.
	std::function<void(UI_EventMouse*)> OnMouseUp;

private: 
	UI_Transform      rendering_viewport;

	bool              mouse_over = false;
	bool              mouse_down = false;

	UI_Transform      transform;
	ui_element_type   type = (ui_element_type)0;

	list<UI_Element*> childs;
	UI_Element*       parent = nullptr;

	UI_Main*          ui_main = nullptr;
	UI_EventSystem*   event_system = nullptr;
};

#endif // __UI_EventSystem_H__
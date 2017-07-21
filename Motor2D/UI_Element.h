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
	ui_element_null,
	ui_element_panel,
	ui_element_button,
};

// --------------------------------------------------

class UI_Element
{
public:
	UI_Element(UI_Main* ui_main, ui_element_type type);
	virtual ~UI_Element();

	virtual void Start() {};
	virtual void Update() {};
	virtual void CleanUp() {};
	virtual void OnEvent(UI_Event* ev) {};

	void StartElement();
	void UpdateElement();
	void CleanElement();

	void InvokeOnMouseOver();
	void InvokeOnMouseOverEnter();
	void InvokeOnMouseOverOut();

	void InvokeOnMouseClick();
	void InvokeOnMouseDown();
	void InvokeOnMouseUp();

	ui_element_type GetType();

	void AddChild(UI_Element* child);
	void RemoveChild(UI_Element* child);

	void SetPos(UI_Point pos);
	void SetSize(UI_Point pos);
	void SetAnchor(UI_Point anchor);
	bool GetUsesAnchor();

	void DeleteAnchor();

	void SetRenderingViewport(int x, int y, int width, int height);

	// Gets the local position of the object
	UI_Point GetLocalPos();

	// Gets the position of the object relative to the it's parents
	UI_Point GetRelativePosToParents();

	// Gets the position, with (0, 0) on the anchor point
	UI_Point GetRelativePosToAnchor();

	// Gets size of the element
	UI_Point GetSize();

	UI_Point GetAnchorPos();

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
	UI_Point		  pos_from_anchor;
	UI_Point		  anchor;
	bool			  uses_anchor = false;

	ui_element_type   type = ui_element_type::ui_element_null;

	list<UI_Element*> childs;
	UI_Element*       parent = nullptr;

	UI_Main*          ui_main = nullptr;
	UI_EventSystem*   event_system = nullptr;
};

#endif // __UI_EventSystem_H__
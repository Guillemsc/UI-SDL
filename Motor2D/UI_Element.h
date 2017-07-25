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
	virtual void Draw() {};
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

	void InvokeOnInteractableTrue();
	void InvokeOnInteractableFalse();
	void InvokeOnVisibleTrue();
	void InvokeOnVisibleFalse();

	// Get the UI_Element type
	ui_element_type GetType();

	// Adds a child to the current element
	void AddChild(UI_Element* child);

	// Removes a child from the current element
	void RemoveChild(UI_Element* child);

	// Sets the position of the element
	void SetPos(UI_Point pos);

	// Sets size of the element
	void SetSize(UI_Point pos);

	// Sets the anchor of the element
	void SetAnchor(UI_Point anchor);

	// Changes element detection of events
	void SetInteractable(bool set);

	// Changes the element visibility
	void SetVisible(bool set);

	// Return if ui_element uses an anchor
	bool GetUsesAnchor();

	// Deletes the ui_element anchor
	void DeleteAnchor();

	// Gets size of the element
	UI_Point GetSize();

	// Gets the position of the transform element
	UI_Point GetTransformPos();

	// Gets the position of the anchor in the world
	UI_Point GetAnchorPos();

	// Gets the size of the element viewport
	UI_Transform GetViewport();

	// Returns true if the element is interactable
	bool GetInteractable();

	// Returns true if the element is visible
	bool GetVisible();

	// Returns true if the mouse is over the element
	bool GetMouseOver();

	// Returns true if the mouse is over the element and down
	bool GetMouseDown();

	void BringToFront();
	void BringToFrontAndChilds();

	void SendToBack();
	void SendToBackAndChilds();

	// Deletes the element
	void Delete();

	// Deletes the elements and it's childs
	void DeleteAndChilds();

	UI_Main* GetUiMain();
	UI_EventSystem* GetEventSystem();
	list<UI_Element*> GetChilds();
	UI_Element* GetParent();
	void ResetParent();

protected:
	// Gets the 0, 0 position inside the element
	UI_Point ZeroPos();

private:
	// Gets the position of the object set by the user
	UI_Point GetPos();

	// Gets the position of the object relative to the it's parents
	UI_Point GetRelativePosToParents();

	// Gets the position, with (0, 0) on the anchor point
	UI_Point GetRelativePosToAnchor();

	// Updates the position of the element in the world
	void UpdatePos();

	// Updated the viewport of the element depending on parents
	void UpdateViewport();

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

	// Called the frame that an element interactability is set to true.
	std::function<void(UI_Event*)> OnInteractableTrue;

	// Called the frame that an element interactability is set to false.
	std::function<void(UI_Event*)> OnInteractableFalse;

	// Called the frame that the element becomes visible.
	std::function<void(UI_Event*)> OnVisibleTrue;

	// Called the frame that the element becomes invisible.
	std::function<void(UI_Event*)> OnVisibleFalse;

private: 
	bool              mouse_over = false;
	bool              mouse_down = false;

	UI_Transform      transform;
	UI_Point	      pos;
	UI_Point		  anchor;
	bool			  uses_anchor = false;
	UI_Transform	  viewport;

	ui_element_type   type = ui_element_type::ui_element_null;

	bool			  interactable = true;
	bool			  visible = true;

	list<UI_Element*> childs;
	UI_Element*       parent = nullptr;

	UI_Main*          ui_main = nullptr;
	UI_EventSystem*   event_system = nullptr;
};

#endif // __UI_EventSystem_H__
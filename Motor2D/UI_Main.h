#ifndef __UI_Main_H__
#define __UI_Main_H__

#include <iostream>
#include <memory>
#include <functional>

#include "SDL/include/SDL.h"
#include "j1Module.h"
#include "j1App.h"
#include "j1Input.h"

using namespace std;

class UI_EventSystem;
class UI_Event;
class UI_Element;
class Transform;

struct ui_point;

enum ui_event_type;
enum ui_element_type;

class UI_Main : public j1Module
{
public:
	UI_Main();

	virtual ~UI_Main();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called each loop iteration
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	void ExpandEvent(UI_Event* ev);

	UI_EventSystem* GetEventSystem();
	list<UI_Element*> GetElements();

	void AddToDelete(UI_Element* element);

	ui_point GetMousePos();
	bool GetMouseLeftDown();
	bool GetMouseRightDown();
	bool GetMouseLeftUp();
	bool GetMouseRightUp();

private:
	void CheckOnMouseEnter();
	void DeleteElements();

private:
	UI_EventSystem* ui_event_system = nullptr;
	list<UI_Element*> elements;
	list<UI_Element*> to_delete;
};

// --------------------------------------------------

struct ui_point
{
	int x = 0;
	int y = 0;
};

#endif // __UI_Main_H__
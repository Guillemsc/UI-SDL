#ifndef __UI_Main_H__
#define __UI_Main_H__

#include <iostream>
#include <memory>
#include <functional>

#include "SDL/include/SDL.h"
#include "j1Module.h"

using namespace std;

class UI_EventSystem;
class UI_Event;
class UI_Element;
class Transform;

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

	void OnEvent(UI_Event* ev);

	UI_EventSystem* GetEventSystem();
	list<shared_ptr<UI_Element>> GetElements();

private:
	UI_EventSystem* ui_event_system = nullptr;
	list<shared_ptr<UI_Element>> elements;
};

#endif // __UI_Main_H__
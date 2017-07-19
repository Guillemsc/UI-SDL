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
class UI_Transform;
class UI_Point;

enum ui_event_type;
enum ui_element_type;

struct Font;

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

	void UIUpdatingInfo(int window_width, int window_height);

	bool LoadAtlas();
	void UnloadAtlas();

	void ExpandEvent(UI_Event* ev);

	UI_EventSystem* GetEventSystem();
	list<UI_Element*> GetElements();
	SDL_Texture* GetAtlas();

	void BringToFrontElement(UI_Element* element);
	void BringToFrontAndChilds(UI_Element* element);

	void DeleteElement(UI_Element* element);

	UI_Point GetMousePos();
	bool GetMouseLeftDown();
	bool GetMouseRightDown();
	bool GetMouseLeftUp();
	bool GetMouseRightUp();
	UI_Point GetWindowSize();

	void UIRenderQuad(int x, int y, int w, int h, int r, int g, int b, int a, bool filled);
	void UIRenderLine(int x1, int y1, int x2, int y2, int r, int g, int b, int a);
	void UIRenderText(int x, int y, char* text, Font* font, int r, int g, int b, int a);
	void UIRenderImage(int x, int y, SDL_Rect rect);

private:
	void UpdateElements();
	void CheckEvents();
	void DeleteElements();

private:
	UI_EventSystem*   ui_event_system = nullptr;
	list<UI_Element*> elements;
	list<UI_Element*> to_delete;

	int window_width = 0;
	int window_height = 0;

	SDL_Texture* atlas = nullptr;
};


// --------------------------------------------------

class UI_Point
{
public:
	float x = 0;
	float y = 0;
};

#endif // __UI_Main_H__
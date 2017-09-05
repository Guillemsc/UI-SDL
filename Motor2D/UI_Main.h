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

#define DEGTORAD 0.0174532925199432957f
#define RADTODEG 57.295779513082320876f
#define PI       3.1415926535897932384f

class UI_EventSystem;
class UI_Animator;
class UI_Bezier;
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

	void CheckWindowResize();

	bool LoadAtlas();
	void UnloadAtlas();

	void ExpandEvent(UI_Event* ev);

	UI_EventSystem* GetEventSystem();
	list<UI_Element*> GetElements();
	SDL_Texture* GetAtlas();

	void ElementBringToFront(UI_Element* element);
	void ElementBringToFrontAndChilds(UI_Element* element);
	void ElementSendToBack(UI_Element* element);
	void ElementSendToBackAndChilds(UI_Element* element);

	void AddElement(UI_Element* element);
	void DeleteElement(UI_Element* element);
	UI_Element* GetFocusedElement();

	UI_Point GetMousePos();
	bool GetMouseLeftDown();
	bool GetMouseRightDown();
	bool GetMouseLeftUp();
	bool GetMouseRightUp();
	UI_Point GetWindowSize();

	void UIRenderQuad(int x, int y, int w, int h, int r, int g, int b, int a, bool filled);
	void UIRenderLine(int x1, int y1, int x2, int y2, int r, int g, int b, int a);
	void UIRenderPoint(int x, int y, int r, int g, int b, int a);
	UI_Point UIRenderText(int x, int y, const char* text, Font* font, int r, int g, int b, int a);
	void UIRenderImage(int x, int y, int rect_x, int rect_y, int rect_w, int rect_h, float alpha);
	Font* UILoadFont(const char* name);
	float UIGetFontSize(Font* font);
	UI_Point UIGetTextSize(const char* text, Font* font);
	bool UIGetKeyboardInput(const char*& input);

	void UISetViewport(int x, int y, int w, int h);
	void UIResetViewport();
	void ClearFocusedElement();

	bool GetDebug();
	void SetDebug(bool set);

private:
	void UpdateElements(float dt);
	void CheckEvents();
	void DeleteElements();

	void OnEvent(UI_Event* ev);

private:
	UI_EventSystem*   ui_event_system = nullptr;
	list<UI_Element*> elements;
	list<UI_Element*> to_delete;

	SDL_Texture*      atlas = nullptr;

	int				  window_width = 0;
	int				  window_height = 0;

	bool              debug = false;

	UI_Element*		  focused_element = nullptr;
};


// --------------------------------------------------

class UI_Point
{
public:
	UI_Point() {};

	UI_Point(float _x, float _y)
	{
		x = _x; y = _y;
	}

	void operator = (UI_Point point)
	{
		x = point.x;
		y = point.y;
	}

	bool operator != (UI_Point point)
	{
		if (x == point.x && y == point.y)
			return false;
		return true;
	}

	float x = 0;
	float y = 0;
};

// --------------------------------------------------

class UI_Quad
{
public:
	UI_Quad() {};

	UI_Quad(float _x, float _y, float _w, float _h)
	{
		x = _x; y = _y; w = _w; h = _h;
	}

	void operator = (UI_Quad quad)
	{
		x = quad.x;
		y = quad.y;
		w = quad.w;
		h = quad.h;
	}

	float x = 0;
	float y = 0;
	float w = 0;
	float h = 0;
};

// --------------------------------------------------
class UI_Color
{
public:
	UI_Color() 
	{
		r = 255;
		g = 255;
		b = 255;
		a = 255;
	};

	UI_Color(int _r, int _g, int _b, int _a = 255)
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}

	void operator = (UI_Color color)
	{
		r = color.r;
		g = color.g;
		b = color.b;
		a = color.a;
	}
	
	int r = 0;
	int g = 0;
	int b = 0;
	int a = 0;
};

#endif // __UI_Main_H__
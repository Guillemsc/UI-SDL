#ifndef __UI_Main_H__
#define __UI_Main_H__

#include "SDL/include/SDL.h"
#include "j1Module.h"

class UI_Main : public j1Module
{
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
};

#endif // __UI_Main_H__
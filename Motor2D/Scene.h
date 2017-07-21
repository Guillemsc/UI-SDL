#ifndef _SCENE_
#define _SCENE_

#include "j1App.h"
#include "j1Render.h"
#include "UI_Main.h"
#include "PugiXml\src\pugixml.hpp"

#include <string>
#include <list>

class Scene
{
public:
	Scene() {};

	virtual ~Scene() {};

	virtual bool Start() { return true; };
	virtual bool PreUpdate() { return true; };
	virtual bool Update(float dt) { return true; };
	virtual bool PostUpdate() { return true; };
	virtual bool CleanUp() { return true; };
};

#endif
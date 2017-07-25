#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "Scene.h"
#include "UI_Main.h"

struct SDL_Texture;
class TestScene;
																					 
																						 
class j1Scene : public j1Module															  
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Change scene
	void ChangeScene(Scene* new_scene);
	Scene* GetCurrentScene();

public:
	// Scenes
	TestScene*	 test_scene = nullptr;
				 
private:		 
	// Scenes li st
	list<Scene*> scenes;
				 
	// Current s cen
	Scene*		 current_scene = nullptr;

		
};

#endif // __j1SCENE_H__
#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Scene.h"
#include "TestScene.h"

j1Scene::j1Scene() : j1Module()
{
	name = "scene";
}

// Destructor
j1Scene::~j1Scene()
{

}

// Called before render is available
bool j1Scene::Awake()
{
	bool ret = true;

	LOG("Loading SceneManager");

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	bool ret = false;

	LOG("Start module scene");


	// Create scenes
	test_scene = new TestScene();
	// -------------

	// Starting scene
	current_scene = test_scene;

	if(current_scene != nullptr)
		ret = current_scene->Start();

	return ret;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	bool ret = false;

	if (current_scene != nullptr)
		ret = current_scene->PreUpdate();

	return ret;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	bool ret = false;

	if (current_scene != nullptr)
		ret = current_scene->Update(dt);
	
	return ret;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = false;

	if (current_scene != nullptr)
		ret = current_scene->PostUpdate();

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	bool ret = false;

	if (current_scene != nullptr)
		ret = current_scene->CleanUp();

	return ret;
}

void j1Scene::ChangeScene(Scene * new_scene)
{
	LOG("Changing current scene");

	current_scene->CleanUp();
	current_scene = new_scene;
	current_scene->Start();
}

Scene * j1Scene::GetCurrentScene()
{
	return current_scene;
}




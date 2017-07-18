#include <iostream> 
#include <sstream> 

#include "p2Defs.h"
#include "p2Log.h"
#include "Functions.h"

#include "j1Window.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Scene.h"
#include "j1FileSystem.h"
#include "j1Fonts.h"
#include "j1Gui.h"
#include "j1App.h"
#include "j1Viewports.h"
#include "j1XMLLoader.h"
#include "UI_Main.h"

// Constructor
j1App::j1App(int argc, char* args[]) : argc(argc), args(args)
{
	input = new j1Input();
	win = new j1Window();
	render = new j1Render();
	tex = new j1Textures();
	scene = new j1Scene();
	fs = new j1FileSystem();
	font = new j1Fonts();
	gui = new j1Gui();
	view = new j1Viewports();
	xml = new j1XMLLoader();
	ui = new UI_Main();

	// Ordered for awake / Start / Update
	// Reverse order of CleanUp
	AddModule(fs);
	AddModule(xml);
	AddModule(input);
	AddModule(win);
	AddModule(tex);
	AddModule(font);
	AddModule(view);

	// Scene
	AddModule(scene);

	// Gui
	AddModule(ui);

	// Render (last to swap buffer)
	AddModule(render);
}

// Destructor
j1App::~j1App()
{
	// release modules
	for (list<j1Module*>::iterator it = modules.begin(); it != modules.end(); it++)
		RELEASE(*it);
	
	modules.clear();
}

void j1App::AddModule(j1Module* module)
{
	module->Init();
	modules.push_back(module);
}

// Called before render is available
bool j1App::Awake()
{
	pugi::xml_document	config_file;
	pugi::xml_node		config;
	pugi::xml_node		app_config;

	bool ret = false;
		
	config = LoadConfig(config_file);

	if(config.empty() == false)
	{
		// Self-config
		ret = true;
		app_config = config.child("app");
		title = app_config.child("title").attribute("name").as_string();
		organization = app_config.child("organization").child_value();

		CapFps(app_config.attribute("framerate_cap").as_int(-1));
	}

	if(ret == true)
	{
		for (list<j1Module*>::iterator it = modules.begin(); it != modules.end(); it++)
			ret = (*it)->Awake(config.child((*it)->name.c_str()));
	}

	return ret;
}

// Called before the first frame
bool j1App::Start()
{
	bool ret = true;

	for (list<j1Module*>::iterator it = modules.begin(); it != modules.end(); it++)
		ret = (*it)->Start();
	
	startup_time.Start();;

	return ret;
}

// Called each loop iteration
bool j1App::Update()
{
	bool ret = true;
	PrepareUpdate();

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug_mode = !debug_mode;

	if(input->GetWindowEvent(WE_QUIT) == true || end_program)
		ret = false;

	App->ui->UIUpdatingInfo(App->win->GetWindowSize().x, App->win->GetWindowSize().y);

	if(ret == true)
		ret = PreUpdate();

	if(ret == true)
		ret = DoUpdate();

	if(ret == true)
		ret = PostUpdate();

	FinishUpdate();
	return ret;
}

// ---------------------------------------------
pugi::xml_node j1App::LoadConfig(pugi::xml_document& config_file) const
{
	pugi::xml_node ret;

	App->xml->LoadXML("config.xml", config_file);

	ret = config_file.child("config");

	return ret;
}

// ---------------------------------------------
void j1App::PrepareUpdate()
{
	frame_count++;
	last_sec_frame_count++;

	dt = frame_time.ReadSec();
	frame_time.Start();
}

// ---------------------------------------------
void j1App::FinishUpdate()
{

}

// Call modules before each loop iteration
bool j1App::PreUpdate()
{
	bool ret = true;

	for (list<j1Module*>::iterator it = modules.begin(); it != modules.end(); it++)
	{
		if((*it)->active)
			ret = (*it)->PreUpdate();
	}

	return ret;
}

// Call modules on each loop iteration
bool j1App::DoUpdate()
{
	bool ret = true;

	for (list<j1Module*>::iterator it = modules.begin(); it != modules.end(); it++)
	{
		if ((*it)->active)
			ret = (*it)->Update(dt);
	}

	return ret;
}

// Call modules after each loop iteration
bool j1App::PostUpdate()
{
	bool ret = true;

	for (list<j1Module*>::iterator it = modules.begin(); it != modules.end(); it++)
	{
		if ((*it)->active)
			ret = (*it)->PostUpdate();
	}

	return ret;
}

// Called before quitting
bool j1App::CleanUp()
{
	bool ret = true;

	deleting_engine = true;

	// Cleaning up in reverse order
	for (list<j1Module*>::reverse_iterator it = modules.rbegin(); it != modules.rend(); it++)
		ret = (*it)->CleanUp();

	return ret;
}

// ---------------------------------------
int j1App::GetArgc() const
{
	return argc;
}

// ---------------------------------------
const char* j1App::GetArgv(int index) const
{
	if(index < argc)
		return args[index];
	else
		return NULL;
}

// ---------------------------------------
const char* j1App::GetTitle() const
{
	return title.c_str();
}

// ---------------------------------------
float j1App::GetDT() const
{
	return dt;
}

// ---------------------------------------
const char* j1App::GetOrganization() const
{
	return organization.c_str();
}

list<j1Module*> j1App::GetModules()
{
	return modules;
}

void j1App::CapFps(float fps)
{
	if(fps > 0)
		capped_ms = (1000 / fps);
}

void j1App::EndSDL()
{
	end_program = true;
}

void j1App::OpenWebPage(char * url)
{
	ShellExecute(NULL, "open", url, NULL, NULL, SW_SHOWMAXIMIZED);
}

void j1App::SetGamePause(bool set)
{
	if (set != game_paused)
	{
		switch (set)
		{
		case true:
			for (int i = 0; i < gameplay_timers.size(); i++)
				gameplay_timers.at(i)->PauseOn();
			break;
		case false:
			for (int i = 0; i < gameplay_timers.size(); i++)
				gameplay_timers.at(i)->PauseOff();
			break;
		}

		game_paused = set;
	}
}

bool j1App::GetGamePause()
{
	return game_paused;
}

j1Timer * j1App::AddGameplayTimer()
{
	j1Timer* ret = nullptr;

	ret = new j1Timer();
	ret->Start();
	gameplay_timers.push_back(ret);

	return ret;
}

void j1App::DeleteGameplayTimer(j1Timer * t)
{
	for (vector<j1Timer*>::iterator it = gameplay_timers.begin(); it != gameplay_timers.end();)
	{
		if ((*it) == t)
		{
			RELEASE((*it));
			gameplay_timers.erase(it);
			break;
		}
		else
			++it;
	}
}

void j1App::ClearGameplayTimers()
{
	if (!gameplay_timers.empty())
	{
		for (vector<j1Timer*>::iterator it = gameplay_timers.begin(); it != gameplay_timers.end();)
		{
			RELEASE((*it));
			it = gameplay_timers.erase(it);
		}
	}
}

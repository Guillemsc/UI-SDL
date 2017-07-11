#include "UI_Main.h"
#include "UI_EventSystem.h"
#include "UI_Element.h"

UI_Main::UI_Main() : j1Module()
{
	name = "UI";
}

UI_Main::~UI_Main()
{

}

bool UI_Main::Awake(pugi::xml_node &)
{
	bool ret = true;

	ui_event_system = new UI_EventSystem();

	return ret;
}

bool UI_Main::Start()
{
	bool ret = true;



	return ret;
}

bool UI_Main::PreUpdate()
{
	bool ret = true;



	return ret;
}

bool UI_Main::Update(float dt)
{
	bool ret = true;



	return ret;
}

bool UI_Main::PostUpdate()
{
	bool ret = true;



	return ret;
}

bool UI_Main::CleanUp()
{
	bool ret = true;

	ui_event_system->CleanUp();
	delete ui_event_system;

	return ret;
}

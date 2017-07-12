#include "j1App.h"
#include "UI_Main.h"
#include "UI_EventSystem.h"
#include "UI_Element.h"

#include "p2Log.h"

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

	ui_event_system = new UI_EventSystem(this);

	return ret;
}

bool UI_Main::Start()
{
	bool ret = true;

	LOG("Start module ui");

	UI_Element* e = new UI_Element(ui_element_type::element_null);
	e->OnClick = UI_Main::OnEvent;


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

void UI_Main::OnEvent(UI_Event * ev)
{
	for (list<shared_ptr<UI_Element>>::iterator it = elements.begin(); it != elements.end(); it++)
	{
		(*it).get()->OnEvent(ev);
	}
}

UI_EventSystem * UI_Main::GetEventSystem()
{
	return ui_event_system;
}

list<shared_ptr<UI_Element>> UI_Main::GetElements()
{
	return elements;
}

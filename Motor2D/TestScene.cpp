#include "TestScene.h"
#include "j1App.h"
#include "UI_Element.h"
#include "p2Log.h"

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}

bool TestScene::Start()
{
	App->ui->SetDebug(true);

	test_element = new UI_Element(App->ui, ui_element_button);
	test_element->SetPos(UI_Point(-355, 35));
	test_element->SetSize(UI_Point(300, 300));
	test_element->SetAnchor(UI_Point(1.0f, 0.0f));
	App->ui->AddElement(test_element);

	test_element2 = new UI_Element(App->ui, ui_element_button);
	test_element2->SetPos(UI_Point(130, 100));
	test_element2->SetSize(UI_Point(100, 100));
	test_element->AddChild(test_element2);
	App->ui->AddElement(test_element2);

	test_element3 = new UI_Element(App->ui, ui_element_button);
	test_element3->SetPos(UI_Point(-10, 10));
	test_element3->SetSize(UI_Point(30, 30));
	test_element2->AddChild(test_element3);
	App->ui->AddElement(test_element3);
	test_element3->OnMouseClick = Test1MouseClick;

	return true;
}

bool TestScene::PreUpdate()
{
	return true;
}

bool TestScene::Update(float dt)
{
	return true;
}

bool TestScene::PostUpdate()
{
	return true;
}

bool TestScene::CleanUp()
{
	return true;
}

void Test1MouseClick(UI_EventMouse * ev)
{
	LOG("HI");
}

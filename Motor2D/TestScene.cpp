#include "TestScene.h"
#include "j1App.h"
#include "UI_Element.h"

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
	test_element->SetPos(UI_Point(-305, 5));
	test_element->SetSize(UI_Point(300, 300));
	test_element->SetAnchor(UI_Point(1.0f, 0.0f));
	App->ui->AddElement(test_element);

	test_element2 = new UI_Element(App->ui, ui_element_button);
	test_element2->SetPos(UI_Point(-100, 0));
	test_element2->SetSize(UI_Point(50, 50));
	test_element->AddChild(test_element2);
	App->ui->AddElement(test_element2);

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

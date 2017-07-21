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
	test_element = new UI_Element(App->ui, ui_element_button);
	test_element->SetPos(UI_Point(-50, -15));
	test_element->SetSize(UI_Point(100, 30));
	test_element->SetAnchor(UI_Point(0.5f, 0.5f));
	App->ui->AddElement(test_element);

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

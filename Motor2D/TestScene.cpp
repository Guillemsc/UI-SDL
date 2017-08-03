#include "j1Scene.h"
#include "TestScene.h"
#include "UI_Element.h"
#include "UI_Animator.h"
#include "UIA_Interpolation.h"
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
	test_element->SetDebugColor(UI_Color(255, 0, 0, 255));
	App->ui->AddElement(test_element);

	test_element2 = new UI_Element(App->ui, ui_element_button);
	test_element2->SetPos(UI_Point(130, 100));
	test_element2->SetSize(UI_Point(100, 100));
	test_element2->SetDebugColor(UI_Color(0, 255, 0, 255));
	test_element->AddChild(test_element2);
	App->ui->AddElement(test_element2);

	test_element3 = new UI_Element(App->ui, ui_element_button);
	test_element3->SetPos(UI_Point(-10, 10));
	test_element3->SetSize(UI_Point(30, 30));
	test_element3->SetDebugColor(UI_Color(0, 0, 255, 255));
	test_element2->AddChild(test_element3);
	App->ui->AddElement(test_element3);
	test_element->OnMouseClick = Test1MouseClick;

	test_element->GetAnimator()->StartAnimationInterpolation(uia_interpolation_type::uia_interpolation_quarticEaseInOut, UI_Point(100, 100), 10);

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
	LOG("hi");
}

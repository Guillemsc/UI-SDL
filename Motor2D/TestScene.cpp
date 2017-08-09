#include "j1Scene.h"
#include "TestScene.h"
#include "UI_Element.h"
#include "UI_Animator.h"
#include "UIA_Interpolation.h"
#include "UIA_Alpha.h"
#include "UI_Text.h"
#include "p2Log.h"
#include "UI_Image.h"

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}

bool TestScene::Start()
{
	//App->ui->SetDebug(true);

	//test_element = new UI_Element(App->ui, ui_element_button);
	//test_element->SetPos(UI_Point(-355, 35));
	//test_element->SetAnchor(UI_Point(1.0f, 0.0f));
	//test_element->SetAlpha(0);
	//App->ui->AddElement(test_element);

	//test_element2 = new UI_Element(App->ui, ui_element_button);
	//test_element2->SetPos(UI_Point(130, 100));
	//test_element2->SetSize(UI_Point(100, 100));
	//test_element2->SetBackgroundColor(UI_Color(0, 255, 0));
	//test_element->AddChild(test_element2);
	//App->ui->AddElement(test_element2);

	//test_element3 = new UI_Element(App->ui, ui_element_button);
	//test_element3->SetPos(UI_Point(-10, 10));
	//test_element3->SetSize(UI_Point(30, 30));
	//test_element3->SetBackgroundColor(UI_Color(0, 0, 255));
	//test_element2->AddChild(test_element3);
	//App->ui->AddElement(test_element3);
	//test_element->OnMouseClick = Test1MouseClick;

	//test_element->GetAnimator()->StartAnimationAlpha(uia_alpha_type::uia_alpha_quadraticEaseInOut, 255, 2);

	text_test = new UI_Text(App->ui);
	text_test->SetAnchor(UI_Point(0, 1));
	text_test->SetPos(UI_Point(50, -100));
	text_test->SetTextAlign(ui_text_align::ui_text_align_left);
	text_test->OnMouseClick = TextClick;
	text_test->SetBackgroundColor(UI_Color(0, 0, 255));
	App->ui->AddElement(text_test);

	image_test = new UI_Image(App->ui);
	image_test->SetPos(UI_Point(500, 400));
	//image_test->SetImage(0, 0, 190, 49);

	App->ui->AddElement(image_test);

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

void TextClick(UI_EventMouse * ev)
{
	App->ui->CleanUp();
}

#include "j1Scene.h"
#include "TestScene.h"
#include "UI_Element.h"
#include "UI_Animator.h"
#include "UIA_Interpolation.h"
#include "UIA_Alpha.h"
#include "UI_Text.h"
#include "UI_Button.h"
#include "p2Log.h"
#include "UI_Image.h"
#include "UI_Panel.h"
#include "UI_TextInput.h"
#include "UIU_Message.h"
#include "UIU_Console.h"
#include "UIU_Debug.h"

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}

bool TestScene::Start()
{
	//base_panel = new UI_Panel(App->ui);
	//base_panel->SetPos(UI_Point(10, 10));
	//base_panel->SetAnchor(UI_Point(0, 0));
	//base_panel->SetSize(UI_Point(500, 500));
	//base_panel->SetBackgroundColor(UI_Color(30, 30, 30, 100));

	button = new UI_Button(App->ui);
	button->SetPos(UI_Point(10, -60));
	button->SetAnchor(UI_Point(0, 1));
	button->SetSize(UI_Point(190, 49));
	button->SetIdleImage(UI_Quad(0, 192, 190, 45));
	button->SetOverImage(UI_Quad(190, 49, 190, 45));
	button->SetPressedImage(UI_Quad(0, 49, 190, 45));
	button->GetText()->SetText("Press");
	button->GetText()->SetPos(UI_Point(70, 3));
	button->GetText()->SetTextColor(UI_Color(255, 255, 255, 200));
	button->OnMouseClick = Test1MouseClick;

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

	//test_element3 = new UI_Element(App->ui, ui_element_button);
	//test_element3->SetPos(UI_Point(-10, 10));
	//test_element3->SetSize(UI_Point(30, 30));
	//test_element3->SetBackgroundColor(UI_Color(0, 0, 255));
	//test_element2->AddChild(test_element3);
	//test_element->OnMouseClick = Test1MouseClick;

	//test_element->GetAnimator()->StartAnimationAlpha(uia_alpha_type::uia_alpha_quadraticEaseInOut, 255, 2);

	//text_test = new UI_Text(App->ui);
	//text_test->SetAnchor(UI_Point(0, 1));
	//text_test->SetPos(UI_Point(50, -100));
	//text_test->SetTextAlign(ui_text_align::ui_text_align_left);
	//text_test->OnMouseClick = TextClick;
	//text_test->SetBackgroundColor(UI_Color(0, 0, 255));

	//image_test = new UI_Image(App->ui);
	//image_test->SetPos(UI_Point(0, -90));
	////image_test->SetImage(0, 0, 190, 49);

	//button_test = new UI_Button(App->ui);
	//button_test->SetPos(UI_Point(10, 10));

	//panel_test = new UI_Panel(App->ui);
	//panel_test->SetPos(UI_Point(10, 10));
	//panel_test->AddChild(button_test);

	//textinput_test = new UI_TextInput(App->ui);

	message = new UIU_Message(App->ui, uia_message_errortype::uia_message_danger);
	console = new UIU_Console(App->ui);
	console->AddText("helllooo");

	debug = new UIU_Debug(App->ui);
	debug->AddDebug("fps");
	debug->AddDebug("ui elements");
	debug->AddDebug("ui time");
	debug->AddDebug("buttons time");
	debug->AddDebug("check boxes time");
	debug->AddDebug("images time");
	debug->AddDebug("panels time");
	debug->AddDebug("texts time");
	debug->AddDebug("texts input time");

	return true;
}

bool TestScene::PreUpdate()
{
	return true;
}

bool TestScene::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_GRAVE) == KEY_DOWN)
	{
		if (App->scene->test_scene->console->GetVisible())
			App->scene->test_scene->console->Hide();
		else
			App->scene->test_scene->console->Show();
	}

	debug->SetDebug("fps", to_string(App->GetFps()).c_str());
	debug->SetDebug("ui elements", to_string(App->ui->GetElementsCount()).c_str());
	debug->SetDebug("ui time", to_string(App->ui->GetUIDebugInfo().avg_ui_main).c_str());
	debug->SetDebug("buttons time", to_string(App->ui->GetUIDebugInfo().avg_buttons).c_str());
	debug->SetDebug("check boxes time", to_string(App->ui->GetUIDebugInfo().avg_check_boxes).c_str());
	debug->SetDebug("images time", to_string(App->ui->GetUIDebugInfo().avg_images).c_str());
	debug->SetDebug("panels time", to_string(App->ui->GetUIDebugInfo().avg_panels).c_str());
	debug->SetDebug("texts time", to_string(App->ui->GetUIDebugInfo().avg_texts).c_str());
	debug->SetDebug("texts input time", to_string(App->ui->GetUIDebugInfo().texts_input).c_str());

	 
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
	//string a = to_string(App->scene->test_scene->counter) + "dfdsdadasdasdfsadfasdfsadfasdfasdfasdfasdfasdfasdfasdfasdfasdfasddfdsdadasdasdfsadfasdfsadfasdfasdfasdfasdfasdfasdfasdfasdfasdfasddfdsdadasdasdfsadfasdfsadfasdfasdfasdfasdfasdfasdfasdfasdfasdfasd";
	//App->scene->test_scene->console->AddText(a.c_str(), uia_console_errortype::uia_console_succes);
	//App->scene->test_scene->counter++;

	if (App->scene->test_scene->message != nullptr)
	{
		App->scene->test_scene->message->Delete();
		App->scene->test_scene->message = nullptr;
	}
	else
	{
		App->scene->test_scene->console->Delete();
	}
}

void TextClick(UI_EventMouse * ev)
{
	App->ui->CleanUp();
}

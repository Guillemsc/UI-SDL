#ifndef _TEST_SCENE_
#define _TEST_SCENE_

#include "j1Scene.h"
#include "j1App.h"
#include "j1Render.h"

class UI_EventMouse;

class UI_Image;
class UI_Button;
class UI_Panel;
class UI_TextInput;
class UIU_Message;
class UIU_Console;
class UIU_Debug;

class TestScene : public Scene
{
public:
	TestScene();

	virtual ~TestScene();

	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();

	UI_Element* test_element = nullptr;
	UI_Element* test_element2 = nullptr;
	UI_Element* test_element3 = nullptr;

	UI_Text*    text_test = nullptr;

	UI_Image*   image_test = nullptr;

	UI_Button*  button_test = nullptr;

	UI_Panel*   panel_test = nullptr;

	UI_TextInput* textinput_test = nullptr;

	//
	UI_Panel* base_panel = nullptr;
	UI_Button* button = nullptr;
	//

	UIU_Message* message = nullptr;

	UIU_Console* console = nullptr;
	int counter = 0;

	UIU_Debug* debug = nullptr;
};

void Test1MouseClick(UI_EventMouse* ev);
void TextClick(UI_EventMouse * ev);

#endif
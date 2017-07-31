#ifndef __UI_Animator_H__
#define __UI_Animator_H__

#include "UI_Main.h"

class UI_Point;

enum ui_animation_type
{
	ui_animation_null,

};

class UI_Animation
{
public:
	UI_Animation(UI_Main* ui_main);

	virtual void Update(float dt) {};

	bool GetFinished();

private:
	bool finished = false;

};

class UI_Animator
{
public:
	UI_Animator(UI_Main* ui_main);
	void Start();
	void Update(float dt);
	void CleanUp();

private:
	list<UI_Animation*> animations;

private:
};

#endif
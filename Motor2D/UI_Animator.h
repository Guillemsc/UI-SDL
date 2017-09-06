#ifndef __UI_Animator_H__
#define __UI_Animator_H__

#include "UI_Main.h"

class UI_Point;
enum uia_interpolation_type;
enum uia_alpha_type;

enum ui_animation_type
{
	ui_animation_null,
	ui_animation_interpolation,
	ui_animation_alpha,
};

class UI_Animation
{
public:
	UI_Animation(UI_Element* target, ui_animation_type type);

	UI_Main* GetUIMain();

	virtual void Update(float dt) {};

	UI_Element* GetTarget();
	ui_animation_type GetType();
	bool GetFinished();
	void Finished();
	

private:
	UI_Main* ui_main = nullptr;

	bool finished = false;
	UI_Element* target = nullptr;

	ui_animation_type type = ui_animation_null;
};

class UI_Animator
{
public:
	UI_Animator(UI_Element* owner);
	void Start();
	void Update(float dt);
	void PostUpdate();
	void CleanUp();

	void StartAnimationInterpolation(uia_interpolation_type type, UI_Point target_pos, float time_sec);
	void StartAnimationAlpha(uia_alpha_type type, float target_alpha, float time_sec);

	void AddToDelete(UI_Animation* ani);
	float AngleFromTwoPoint(UI_Point p1, UI_Point p2);
	float DistanceFromtTwoPoints(UI_Point p1, UI_Point p2);

private:
	void DeleteAnimations();
	void AddAnimation(UI_Animation* ani);

private:
	UI_Main* ui_main = nullptr;
	UI_Element* owner = nullptr;
	list<UI_Animation*> animations;
	list<UI_Animation*> to_delete;

private:
};

#endif
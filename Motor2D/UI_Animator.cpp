#include "UI_Animator.h"
#include "UI_Main.h"
#include "UI_Element.h"
#include "UIA_Interpolation.h"
#include "UIA_Alpha.h"
#include "p2Log.h"

UI_Animator::UI_Animator(UI_Element* _owner)
{
	ui_main = _owner->GetUiMain();
	owner = _owner;
}

void UI_Animator::Start()
{
}

void UI_Animator::Update(float dt)
{
	for (list<UI_Animation*>::iterator it = animations.begin(); it != animations.end(); it++)
	{
		if (!(*it)->GetFinished())
			(*it)->Update(dt);
	}
}

void UI_Animator::PostUpdate()
{
	DeleteAnimations();
}

void UI_Animator::CleanUp()
{
	for (list<UI_Animation*>::iterator it = animations.begin(); it != animations.end(); it++)
		(*it)->Finished();
	
	DeleteAnimations();
}

void UI_Animator::StartAnimationInterpolation(uia_interpolation_type type, UI_Point target_pos, float time_sec)
{
	UIA_Interpolation* anim = new UIA_Interpolation(type, owner, target_pos, time_sec);

	animations.push_back(anim);
}

void UI_Animator::StartAnimationAlpha(uia_alpha_type type, float target_alpha, float time_sec)
{
	UIA_Alpha* anim = new UIA_Alpha(type, owner, target_alpha, time_sec);

	animations.push_back(anim);
}

void UI_Animator::AddToDelete(UI_Animation * ani)
{
	to_delete.push_back(ani);
}

float UI_Animator::AngleFromTwoPoint(UI_Point p1, UI_Point p2)
{
	float deltaY = p2.y - p1.y;
	float deltaX = p2.x - p1.x;

	return (atan2(deltaY, deltaX) * RADTODEG);
}

float UI_Animator::DistanceFromtTwoPoints(UI_Point p1, UI_Point p2)
{
	int distance_x = p2.x - p1.x;
	int distance_y = p2.y - p1.y;

	float dist = abs((distance_x * distance_x) + (distance_y * distance_y));

	return sqrt(dist);
}

void UI_Animator::DeleteAnimations()
{
	for (list<UI_Animation*>::iterator it = to_delete.begin(); it != to_delete.end(); it++)
	{
		for (list<UI_Animation*>::iterator an = animations.begin(); an != animations.end(); an++)
		{
			if ((*it) == (*an))
			{
				delete (*an);
				animations.erase(an);
				break;
			}
		}

		it = to_delete.erase(it);
	}
}

UI_Animation::UI_Animation(UI_Element* _target)
{
	ui_main = _target->GetUiMain();
	target = _target;
}

UI_Main * UI_Animation::GetUIMain()
{
	return ui_main;
}

UI_Element * UI_Animation::GetTarget()
{
	return target;
}

bool UI_Animation::GetFinished()
{
	return finished;
}

void UI_Animation::Finished()
{
	GetTarget()->GetAnimator()->AddToDelete(this);
	finished = true;
}


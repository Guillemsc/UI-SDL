#ifndef __UIA_Interpolation_H__
#define __UIA_Interpolation_H__

#include "UI_Animator.h"

enum uia_interpolation_type
{
	uia_interpolation_null,
	uia_interpolation_linear,
	uia_interpolation_quadraticEaseIn,
	uia_interpolation_quadraticEaseOut,
	uia_interpolation_quadraticEaseInOut,
};

class UIA_Interpolation : public UI_Animation
{
public:
	UIA_Interpolation(UI_Main* ui_main, uia_interpolation_type type, UI_Element* target, UI_Point target_pos, float time_sec);
	void Update(float dt);

private:
	float GetNormalizedPos(float normalized_time);

private:
	uia_interpolation_type type = uia_interpolation_type::uia_interpolation_linear;

	float    time_seconds = 0.0f;
	UI_Point target_pos;
	UI_Point starting_pos;

	float    curr_time = 0.0f;
	float	 angle = 0.0f;
	float    starting_distance = 0.0f;

	UI_Point pos_track;
};

#endif
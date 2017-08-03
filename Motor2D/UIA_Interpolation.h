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

	uia_interpolation_cubicEaseIn,
	uia_interpolation_cubicEaseOut,
	uia_interpolation_cubicEaseInOut,

	uia_interpolation_quarticEaseIn,
	uia_interpolation_quarticEaseOut,
	uia_interpolation_quarticEaseInOut,

	uia_interpolation_quinticEaseIn,
	uia_interpolation_quinticEaseOut,
	uia_interpolation_quinticEaseInOut,

	uia_interpolation_sineEaseIn,
	uia_interpolation_sineEaseOut,
	uia_interpolation_sineEaseInOut,

	uia_interpolation_circularEaseIn,
	uia_interpolation_circularEaseOut,
	uia_interpolation_circularEaseInOut,

	uia_interpolation_exponentialEaseIn,
	uia_interpolation_exponentialEaseOut,
	uia_interpolation_exponentialEaseInOut,
};

class UIA_Interpolation : public UI_Animation
{
public:
	UIA_Interpolation(uia_interpolation_type type, UI_Element* target, UI_Point target_pos, float time_sec);
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
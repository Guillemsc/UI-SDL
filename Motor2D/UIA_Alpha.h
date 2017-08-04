#ifndef __UIA_Alpha_H__
#define __UIA_Alpha_H__

#include "UI_Animator.h"

enum uia_alpha_type
{
	uia_alpha_null,
	uia_alpha_linear,
	uia_alpha_quadraticEaseIn,
	uia_alpha_quadraticEaseOut,
	uia_alpha_quadraticEaseInOut,
};

class UIA_Alpha : public UI_Animation
{
public:
	UIA_Alpha(uia_alpha_type type, UI_Element* target, float target_alpha, float time_sec);
	void Update(float dt);

private:
	float GetNormalizedAlpha(float normalized_time);

private:
	uia_alpha_type type = uia_alpha_type::uia_alpha_linear;

	float    time_seconds = 0.0f;
	float	 target_alpha = 0.0f;
	float	 starting_alpha = 0.0f;
	float	 alpha_difference = 0.0f;

	float    curr_time = 0.0f;
};

#endif
#include "UIA_Interpolation.h"
#include "UI_Element.h"
#include "p2Log.h"

UIA_Interpolation::UIA_Interpolation(UI_Main* ui_main, uia_interpolation_type _type, UI_Element* target, UI_Point _target_pos, float _time_sec) : UI_Animation(ui_main, target)
{
	type = _type;
	target_pos = _target_pos;
	time_seconds = _time_sec;
	starting_pos = target->GetTransformPos();

	angle = GetTarget()->GetAnimator()->AngleFromTwoPoint(starting_pos, target_pos);
	starting_distance = GetTarget()->GetAnimator()->DistanceFromtTwoPoints(starting_pos, target_pos);

	pos_track = target->GetTransformPos();
}

void UIA_Interpolation::Update(float dt)
{
	curr_time += dt;

	float normalized_time = curr_time / time_seconds;

	float normalized_pos = GetNormalizedPos(normalized_time);

	float distance = starting_distance * normalized_pos;

	UI_Point pos = { starting_pos.x + (distance * cos(angle*DEGTORAD)), starting_pos.y + (distance * sin(angle*DEGTORAD)) };

	float to_move = GetTarget()->GetAnimator()->DistanceFromtTwoPoints(GetTarget()->GetTransformPos(), pos);

	GetTarget()->MoveToAngle(to_move, angle);

	// End
	if (curr_time >= time_seconds)
	{
		float angle = GetTarget()->GetAnimator()->AngleFromTwoPoint(GetTarget()->GetTransformPos(), target_pos);
		float distance = GetTarget()->GetAnimator()->DistanceFromtTwoPoints(GetTarget()->GetTransformPos(), target_pos);
		GetTarget()->MoveToAngle(distance, angle);
		Finished();
	}
}

// The easeing functions code was extracted from the github page: https://github.com/warrenm/AHEasing/blob/master/AHEasing/easing.c
// Copyright (c) 2011, Auerhaus Development, LLC
//  This program is free software. It comes without any warranty, to
//  the extent permitted by applicable law. You can redistribute it
//  and/or modify it under the terms of the Do What The Fuck You Want
//  To Public License, Version 2, as published by Sam Hocevar. See
//  http://sam.zoy.org/wtfpl/COPYING for more details.

/*
The following types of easing functions are supported:
- Linear
- Quadratic
- Cubic
- Quartic
- Quintic
- Sine
- Circular
- Elastic
- Bounce
- Back
*/

float UIA_Interpolation::GetNormalizedPos(float normalized_time)
{
	switch (type)
	{
		case uia_interpolation_type::uia_interpolation_linear:
		{
			return normalized_time;
		}
		break;
		case uia_interpolation_type::uia_interpolation_quadraticEaseIn:
		{
			return normalized_time*normalized_time;
		}
		break;
		case uia_interpolation_type::uia_interpolation_quadraticEaseOut:
		{
			return -(normalized_time * (normalized_time - 2));
		}
		break;
		case uia_interpolation_type::uia_interpolation_quadraticEaseInOut:
		{
			if (normalized_time < 0.5)
			{
				return 2 * normalized_time * normalized_time;
			}
			else
			{
				return (-2 * normalized_time * normalized_time) + (4 * normalized_time) - 1;
			}
		}
		break;
		case uia_interpolation_type::uia_interpolation_cubicEaseIn:
		{
			return normalized_time * normalized_time * normalized_time;
		}
		break;
		case uia_interpolation_type::uia_interpolation_cubicEaseOut:
		{
			float f = (normalized_time - 1);
			return f * f * f + 1;
		}
		break;
		case uia_interpolation_type::uia_interpolation_cubicEaseInOut:
		{
			if (normalized_time < 0.5)
			{
				return 4 * normalized_time * normalized_time * normalized_time;
			}
			else
			{
				float f = ((2 * normalized_time) - 2);
				return 0.5 * f * f * f + 1;
			}
		}
		break;
		case uia_interpolation_type::uia_interpolation_quarticEaseIn:
		{
			return normalized_time * normalized_time * normalized_time * normalized_time;
		}
		break;
		case uia_interpolation_type::uia_interpolation_quarticEaseOut:
		{
			float f = (normalized_time - 1);
			return f * f * f * (1 - normalized_time) + 1;
		}
		break;
		case uia_interpolation_type::uia_interpolation_quarticEaseInOut:
		{
			if (normalized_time < 0.5)
			{
				return 8 * normalized_time * normalized_time * normalized_time * normalized_time;
			}
			else
			{
				float f = (normalized_time - 1);
				return -8 * f * f * f * f + 1;
			}
		}
		break;
		case uia_interpolation_type::uia_interpolation_quinticEaseIn:
		{
			return normalized_time * normalized_time * normalized_time * normalized_time * normalized_time;
		}
		break;
		case uia_interpolation_type::uia_interpolation_quinticEaseOut:
		{
			float f = (normalized_time - 1);
			return f * f * f * f * f + 1;
		}
		break;
		case uia_interpolation_type::uia_interpolation_quinticEaseInOut:
		{
			if (normalized_time < 0.5)
			{
				return 16 * normalized_time * normalized_time * normalized_time * normalized_time * normalized_time;
			}
			else
			{
				float f = ((2 * normalized_time) - 2);
				return 0.5 * f * f * f * f * f + 1;
			}
		}
		break;
		case uia_interpolation_type::uia_interpolation_sineEaseIn:
		{
			return sin((normalized_time - 1) * (PI/2)) + 1;
		}
		break;
		case uia_interpolation_type::uia_interpolation_sineEaseOut:
		{
			return sin(normalized_time * (PI/2));
		}
		break;
		case uia_interpolation_type::uia_interpolation_sineEaseInOut:
		{
			return 0.5 * (1 - cos(normalized_time * PI));
		}
		break;
		case uia_interpolation_type::uia_interpolation_circularEaseIn:
		{
			return 1 - sqrt(1 - (normalized_time * normalized_time));
		}
		break;
		case uia_interpolation_type::uia_interpolation_circularEaseOut:
		{
			return sqrt((2 - normalized_time) * normalized_time);
		}
		break;
		case uia_interpolation_type::uia_interpolation_circularEaseInOut:
		{
			if (normalized_time < 0.5)
			{
				return 0.5 * (1 - sqrt(1 - 4 * (normalized_time * normalized_time)));
			}
			else
			{
				return 0.5 * (sqrt(-((2 * normalized_time) - 3) * ((2 * normalized_time) - 1)) + 1);
			}
		}
		break;
		case uia_interpolation_type::uia_interpolation_exponentialEaseIn:
		{
			return (normalized_time == 0.0) ? normalized_time : pow(2, 10 * (normalized_time - 1));
		}
		break;
		case uia_interpolation_type::uia_interpolation_exponentialEaseOut:
		{
			return (normalized_time == 1.0) ? normalized_time : 1 - pow(2, -10 * normalized_time);
		}
		break;
		case uia_interpolation_type::uia_interpolation_exponentialEaseInOut:
		{
			if (normalized_time == 0.0 || normalized_time == 1.0) return normalized_time;

			if (normalized_time < 0.5)
			{
				return 0.5 * pow(2, (20 * normalized_time) - 10);
			}
			else
			{
				return -0.5 * pow(2, (-20 * normalized_time) + 10) + 1;
			}
		}
		break;
	}
}

float UIA_Interpolation::BounceEaseIn(float p)
{
	return 1 - BounceEaseOut(1 - p);
}

float UIA_Interpolation::BounceEaseOut(float p)
{
	if (p < (4 / 11.0))
	{
		return (121 * p * p) / 16.0;
	}
	else if (p < (8 / 11.0))
	{
		return (363 / (40.0 * p * p)) - (99 / (10.0 * p)) + (17 / 5.0);
	}
	else if (p < 9 / 10.0)
	{
		return (4356 / (361.0 * p * p)) - (35442 / (1805.0 * p)) + (16061 / 1805.0);
	}
	else
	{
		return (54 / (5.0 * p * p)) - (513 / (25.0 * p)) + (268 / 25.0);
	}
}

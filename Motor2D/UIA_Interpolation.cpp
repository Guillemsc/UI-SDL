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
	}
}

#include "UIA_Alpha.h"
#include "UI_Element.h"
#include "UI_EventSystem.h"

UIA_Alpha::UIA_Alpha(uia_alpha_type _type, UI_Element * target, float _target_alpha, float _time_sec) : UI_Animation(target)
{
	type = _type;
	target_alpha = _target_alpha;

	if (target_alpha > 255)
		target_alpha = 255;

	if (target_alpha < 0)
		target_alpha = 0;

	time_seconds = _time_sec;

	starting_alpha = target->GetAlpha();
	alpha_difference = target_alpha - starting_alpha;
}

void UIA_Alpha::Update(float dt)
{
	curr_time += dt;

	float normalized_time = curr_time / time_seconds;

	float normalized_alpha = GetNormalizedAlpha(normalized_time);

	float alpha = starting_alpha + (normalized_alpha * alpha_difference);

	GetTarget()->SetAlpha(alpha);

	if (curr_time >= time_seconds)
	{
		GetTarget()->SetAlpha(target_alpha);
		Finished();

		UI_Event* ev = new UI_Event(ui_event_type::event_alpha_anim_finished, GetTarget());
		GetUIMain()->ExpandEvent(ev);
	}
}

float UIA_Alpha::GetNormalizedAlpha(float normalized_time)
{
	switch (type)
	{
		case uia_alpha_type::uia_alpha_linear:
		{
			return normalized_time;
		}
		break;
		case uia_alpha_type::uia_alpha_quadraticEaseIn:
		{
			return normalized_time*normalized_time;
		}
		break;
		case uia_alpha_type::uia_alpha_quadraticEaseOut:
		{
			return -(normalized_time * (normalized_time - 2));
		}
		break;
		case uia_alpha_type::uia_alpha_quadraticEaseInOut:
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


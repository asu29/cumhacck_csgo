#include "../features.hpp"
#include "../../../security/cl_junkcode.hpp"

#include "sound.h"

int hitmarker_time = 0;

void misc::hitmarker::run() 
{
	junkcode::call();

	if (!interfaces::engine->is_connected() && !interfaces::engine->is_in_game())
		return;

	if (variables.misc.hitmarker) 
	{
		misc::hitmarker::draw();
	}
}

void  misc::hitmarker::event(i_game_event* event) 
{
	junkcode::call();

	if (!event)
		return;

	auto local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));
	if (!local_player)
		return;

	auto attacker = interfaces::entity_list->get_client_entity(interfaces::engine->get_player_for_user_id(event->get_int("attacker")));
	if (!attacker)
		return;

	if (attacker == local_player)
	{
		hitmarker_time = 255;

		if (variables.misc.hitsound == true) 
		{
			if (variables.misc.hitsound_int == 0)
				interfaces::surface->play_sound("buttons\\arena_switch_press_02.wav");
			if (variables.misc.hitsound_int == 1)
				PlaySoundA(hitsound1, NULL, SND_ASYNC | SND_MEMORY);
			if (variables.misc.hitsound_int == 2)
				PlaySoundA(hitsound2, NULL, SND_ASYNC | SND_MEMORY);
		}
	}
}

void  misc::hitmarker::draw() 
{
	junkcode::call();

	if (!variables.misc.hitmarker)
		return;

	int width, height;
	interfaces::engine->get_screen_size(width, height);
	int width_mid = width / 2;
	int height_mid = height / 2;

	if (hitmarker_time > 0) 
	{
		float alpha = hitmarker_time;

		render::draw_line(width_mid + 6, height_mid + 6, width_mid + 3, height_mid + 3, color(255, 0, 255, alpha));
		render::draw_line(width_mid - 6, height_mid + 6, width_mid - 3, height_mid + 3, color(255, 0, 255, alpha));
		render::draw_line(width_mid + 6, height_mid - 6, width_mid + 3, height_mid - 3, color(255, 0, 255, alpha));
		render::draw_line(width_mid - 6, height_mid - 6, width_mid - 3, height_mid - 3, color(255, 0, 255, alpha));

		hitmarker_time -= 2;
	}
}














































































































































































































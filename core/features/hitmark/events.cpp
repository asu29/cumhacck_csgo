#include "events.hpp"
#include "../features.hpp"
#include "../../../security/cl_junkcode.hpp"

#pragma comment(lib, "Winmm.lib")

c_hooked_events events;

void c_hooked_events::fire_game_event(i_game_event* event) 
{
	junkcode::call();
	auto event_name = event->get_name();

	if (!strcmp(event_name, "player_hurt")) 
	{
		misc::hitmarker::event(event);
	}

	else if (strstr(event->get_name(), "item_purchase")) 
	{
		//event_logs.event_item_purchase(event);
	}

	else if (strstr(event->get_name(), "player_footstep")) 
	{
	
	}

	else if (!strcmp(event_name, "player_death")) 
	{

	}

	else if (!strcmp(event_name, "round_end")) 
	{

	}

}

int c_hooked_events::get_event_debug_id(void) 
{
	junkcode::call();
	return EVENT_DEBUG_ID_INIT;
}

void c_hooked_events::initialize() 
{
	junkcode::call();
	m_i_debug_id = EVENT_DEBUG_ID_INIT;
	interfaces::event_manager->add_listener(this, "player_hurt", false);
	interfaces::event_manager->add_listener(this, "item_purchase", false);
	interfaces::event_manager->add_listener(this, "player_footstep", false);
	interfaces::event_manager->add_listener(this, "player_death", false);
	interfaces::event_manager->add_listener(this, "round_end", false);

	printf("[setup] events initialized!\n");
}

void c_hooked_events::release() 
{
	junkcode::call();
	interfaces::event_manager->remove_listener(this);
}

















































































































































































































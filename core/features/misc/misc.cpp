#include "../features.hpp"
#include "../../../security/xor.h"
#include "d3d/d3dx9math.h"
#include "../../../security/cl_junkcode.hpp"
#include "../../../dependencies/math/math.hpp"
#include "directxmath.h"
#include "../../hooks/hooks.hpp"

void misc::bunny_hop(c_usercmd* cmd) 
{
	junkcode::call();

	if (!variables.misc.bunny_hop)
		return;

	if (variables.misc.jumpbug == true && GetAsyncKeyState(variables.misc.jumpbugkey))
		return;

/*	if (variables.misc.edgebug == true && GetAsyncKeyState(variables.misc.edgebugkey))
		return; */

	if (!(cmd->buttons & in_jump)										
	|| (csgo::local_player->move_type() & movetype_ladder))					
		return;

	if (!(csgo::local_player->flags() & fl_onground))
	{
		cmd->buttons &= ~in_jump;
	}
};


/*if (!(cmd->buttons & in_jump)
	|| (csgo::local_player->move_type() & movetype_ladder))
		return;*/

int sct;
void SetMyClanTag(const char* tag, const char* name)
{
	static auto pSetClanTag = reinterpret_cast<void(__fastcall*)(const char*, const char*)>(((DWORD)utilities::pattern_scan(GetModuleHandleW(L"engine.dll"), "53 56 57 8B DA 8B F9 FF 15")));
	pSetClanTag(tag, name);
}

void misc::ClanTagApply(const char* tag)
{
	SetMyClanTag(tag, " ");
}

void misc::clantag()
{
	static int counter = 0;

	if (!csgo::local_player || !csgo::local_player->is_alive())
		return;

	if (!variables.misc.clantag)
		return;

	if (variables.misc.clantag_type == 0)
	{
		static int motion = 0;
		if (counter % 48 == 0)
			motion++;

		int ServerTime = (float)csgo::local_player->get_tick_base() * interfaces::globals->interval_per_tick;

		int value = ServerTime % 22;
		switch (value)
		{
		case 0: SetMyClanTag("             ", "cumhacck"); break;
		case 1: SetMyClanTag("            c", "cumhacck"); break;
		case 2: SetMyClanTag("           cu", "cumhacck"); break;
		case 3: SetMyClanTag("          cum", "cumhacck"); break;
		case 4: SetMyClanTag("         cumh", "cumhacck"); break;
		case 5: SetMyClanTag("        cumha", "cumhacck"); break;
		case 6: SetMyClanTag("       cumhac", "cumhacck"); break;
		case 7: SetMyClanTag("      cumhacc", "cumhacck"); break;
		case 8: SetMyClanTag("     cumhacck", "cumhacck"); break;
		case 9: SetMyClanTag("    cumhacck ", "cumhacck"); break;
		case 10:SetMyClanTag("   cumhacck  ", "cumhacck"); break;
		case 11:SetMyClanTag("  cumhacck   ", "cumhacck"); break;
		case 12:SetMyClanTag(" cumhacck    ", "cumhacck"); break;
		case 13:SetMyClanTag("cumhacck     ", "cumhacck"); break;
		case 14:SetMyClanTag("umhacck      ", "cumhacck"); break;
		case 15:SetMyClanTag("mhacck       ", "cumhacck"); break;
		case 16:SetMyClanTag("hacck        ", "cumhacck"); break;
		case 17:SetMyClanTag("acck         ", "cumhacck"); break;
		case 18:SetMyClanTag("cck          ", "cumhacck"); break;
		case 19:SetMyClanTag("ck           ", "cumhacck"); break;
		case 20:SetMyClanTag("k            ", "cumhacck"); break;
		case 21:SetMyClanTag("             ", "cumhacck"); break;
		}
		counter++;
	}
	else if (variables.misc.clantag_type == 1) 
	{
		static int motion = 0;
		if (counter % 48 == 0)
			motion++;

		int ServerTime = (float)csgo::local_player->get_tick_base() * interfaces::globals->interval_per_tick;

		int value = ServerTime % 22;
		switch (value)
		{
		case 0: SetMyClanTag("cum", "cum"); break;
		}
		counter++;
	}
		
}

void misc::chatspam() 
{
	junkcode::call();

	static float old_curtime = interfaces::globals->cur_time;

	if (variables.misc.chatspam) 
	{
		while (interfaces::globals->cur_time > old_curtime + 2.f)
		{
			interfaces::engine->execute_cmd("say discord.gg/Jz6V3Fn");
			old_curtime = interfaces::globals->cur_time;
		}
	}
}

void misc::disable_post_processing() 
{
	junkcode::call();

	static auto mat_postprocess_enable = interfaces::console->get_convar("mat_postprocess_enable");
	mat_postprocess_enable->set_value(variables.misc.disable_post_processing ? 0 : 1);
}

void misc::disable_blur()
{
	junkcode::call();

	static auto blur = interfaces::console->get_convar("@panorama_disable_blur");

	if (variables.misc.disable_blur)
		blur->set_value(1);

	if (!variables.misc.disable_blur)
		blur->set_value(0);
}

void misc::nade_predict() 
{
	junkcode::call();

	if (!csgo::local_player)
		return;

	static auto nadeVar = interfaces::console->get_convar("cl_grenadepreview");

	nadeVar->callbacks.size = 0;

	if (variables.misc.nade_predict)
		nadeVar->set_value(1);

	if (!variables.misc.nade_predict)
		nadeVar->set_value(0);
}

void misc::disable_shadow() 
{
	junkcode::call();

	static auto mat_postprocess_enable = interfaces::console->get_convar("cl_csm_enabled");
	mat_postprocess_enable->set_value(variables.misc.disable_shadow ? 0 : 1);
}

void misc::remove_3dsky() 
{
	junkcode::call();

	static auto mat_postprocess_enable = interfaces::console->get_convar("r_3dsky");
	mat_postprocess_enable->set_value(variables.misc.remove_3dsky ? 0 : 1);
}

void misc::remove_bloom() 
{
	junkcode::call();

	static auto mat_postprocess_enable = interfaces::console->get_convar("mat_disable_bloom");
	mat_postprocess_enable->set_value(variables.misc.remove_bloom ? 0 : 1);
}

vec3_t view_angles;
void misc::auto_strafe(c_usercmd* user_cmd) noexcept
{
	junkcode::call();

	if (!variables.misc.auto_strafe)
		return;

	auto local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));

	
	bool bKeysPressed = true;
	if (GetAsyncKeyState(0x41) || GetAsyncKeyState(0x57) || GetAsyncKeyState(0x53) || GetAsyncKeyState(0x44))
	bKeysPressed = false;

	if (!(local_player->flags() & fl_onground) && bKeysPressed)
	{
		user_cmd->forwardmove = (1550.f * 5) / local_player->velocity().Length2D();
		user_cmd->sidemove = (user_cmd->command_number % 2) == 0 ? -450.f : 450.f;
		if (user_cmd->forwardmove > 450.f)
			user_cmd->forwardmove = 450.f;
		interfaces::engine->get_view_angles_alternative(view_angles);

	}
}

bool unduck = false;

void misc::jumpbug(c_usercmd* cmd)
{
	junkcode::call();

	if (!variables.misc.jumpbug || !GetAsyncKeyState(variables.misc.jumpbugkey))
		return;

	if (!csgo::local_player || !csgo::local_player->is_alive())
		return;

	float max_radias = D3DX_PI * 2;
	float step = max_radias / 128; // normal is 128
	float xThick = 25;


	if (variables.misc.jumpbug && GetAsyncKeyState(variables.misc.jumpbugkey) && (csgo::local_player->flags() & (1 << 0)))
	{
		int screenWidth, screenHeight;
		interfaces::engine->get_screen_size(screenWidth, screenHeight);
		if (unduck)
		{
			cmd->buttons &= ~in_duck; // duck
			cmd->buttons |= in_jump; // jump
			unduck = false;
		}
		vec3_t pos = csgo::local_player->origin();
		for (float a = 0.f; a < max_radias; a += step)
		{
			vec3_t pt;
			pt.x = (xThick * cos(a)) + pos.x;
			pt.y = (xThick * sin(a)) + pos.y;
			pt.z = pos.z;


			vec3_t pt2 = pt;
			pt2.z -= 6;

			trace_t fag;

			ray_t ray;
			ray.initialize(pt, pt2);

			trace_filter flt;
			flt.skip = csgo::local_player; 
			interfaces::trace_ray->trace_ray(ray, MASK_SOLID_BRUSHONLY, &flt, &fag);

			if (fag.flFraction != 1.f && fag.flFraction != 0.f)
			{
				cmd->buttons |= in_duck; // duck
				cmd->buttons &= ~in_jump; // jump
				unduck = true;
			}
		}
		for (float a = 0.f; a < max_radias; a += step)
		{
			vec3_t pt;
			pt.x = ((xThick - 2.f) * cos(a)) + pos.x;
			pt.y = ((xThick - 2.f) * sin(a)) + pos.y;
			pt.z = pos.z;

			vec3_t pt2 = pt;
			pt2.z -= 6;

			trace_t fag;

			ray_t ray;
			ray.initialize(pt, pt2);

			trace_filter flt;
			flt.skip = csgo::local_player;
			interfaces::trace_ray->trace_ray(ray, MASK_SOLID_BRUSHONLY, &flt, &fag);

			if (fag.flFraction != 1.f && fag.flFraction != 0.f)
			{
				cmd->buttons |= in_duck; // duck
				cmd->buttons &= ~in_jump; // jump
				unduck = true;
			}
		}
		for (float a = 0.f; a < max_radias; a += step)
		{
			vec3_t pt;
			pt.x = ((xThick - 20.f) * cos(a)) + pos.x;
			pt.y = ((xThick - 20.f) * sin(a)) + pos.y;
			pt.z = pos.z;

			vec3_t pt2 = pt;
			pt2.z -= 6;

			trace_t fag;

			ray_t ray;
			ray.initialize(pt, pt2);

			trace_filter flt;
			flt.skip = csgo::local_player;
			interfaces::trace_ray->trace_ray(ray, MASK_SOLID_BRUSHONLY, &flt, &fag);

			if (fag.flFraction != 1.f && fag.flFraction != 0.f)
			{
				cmd->buttons |= in_duck; // duck
				cmd->buttons &= ~in_jump; // jump
				unduck = true;
			}
		}
	}
	else
	{			
		variables.misc.didJumpBug = false;
	}
}

void misc::edgejump(c_usercmd* cmd)
{
	junkcode::call();

	if (!variables.misc.bEdgeJump || !GetAsyncKeyState(variables.misc.edgejumpkey))
		return;

	if (!csgo::local_player || !csgo::local_player->is_alive())
		return;

	if ((prediction::getFlags() & fl_onground) && !(csgo::local_player->flags() & fl_onground))
		cmd->buttons |= in_jump;
}


void misc::edgebug(c_usercmd* cmd)
{
	junkcode::call();

	if (!variables.misc.edgebug || !GetAsyncKeyState(variables.misc.edgebugkey))
		return;

	if (variables.misc.jumpbug == true && GetAsyncKeyState(variables.misc.jumpbugkey))
		return;

	if (!csgo::local_player || !csgo::local_player->is_alive())
		return;

	if (!(prediction::getFlags() & fl_onground) && csgo::local_player->flags() & fl_onground)
		cmd->buttons |= in_duck;
}


void misc::showimpacts()
{
	junkcode::call();

	if (!csgo::local_player)
		return;

	convar* sv_showimpacts = interfaces::console->get_convar("sv_showimpacts");
	*(int*)((DWORD)&sv_showimpacts->callbacks + 0xC) = 0;

	if (variables.visuals.showimpacts)
		sv_showimpacts->set_value(1);

	if (!variables.visuals.showimpacts)
		sv_showimpacts->set_value(0);
}

void misc::autopistol(c_usercmd* cmd)
{
	//int ServerTime = (float)csgo::local_player->get_tick_base() * interfaces::globals->interval_per_tick;

	if (variables.misc.autopistol && csgo::local_player->is_alive())
	{
		const auto activeWeapon = csgo::local_player->active_weapon();
		if (activeWeapon && activeWeapon->is_pistol() && activeWeapon->next_primary_attack() > interfaces::globals->cur_time)
		{
			if (activeWeapon->item_definition_index() == WEAPON_REVOLVER)
				cmd->buttons &= ~in_attack2;
			else
				cmd->buttons &= ~in_attack;
		}
	}
}

void misc::nopunch()
{
	if (!variables.misc.nopunch || !interfaces::engine->is_in_game())
		return;

	csgo::local_player->punch_angle(); NULL;
	csgo::local_player->aim_punch_angle(); NULL;
}


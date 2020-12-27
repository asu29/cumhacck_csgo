#include "../features.hpp"
#include "../../../dependencies/utilities/renderer/renderer.hpp"
#include "../../../security/cl_junkcode.hpp"


void visuals::nightmode() 
{
	junkcode::call();

	static convar* draw_specific_static_prop = interfaces::console->get_convar("r_drawspecificstaticprop");
	if (draw_specific_static_prop->get_int() != 0)
		draw_specific_static_prop->set_value(0);

	for (MaterialHandle_t i = interfaces::material_system->first_material(); i != interfaces::material_system->invalid_material_handle(); i = interfaces::material_system->next_material(i))
	{
		i_material* material = interfaces::material_system->get_material(i);
		if (!material)
			continue;

		if (strstr(material->get_texture_group_name(), "World") || strstr(material->get_texture_group_name(), "StaticProp"))
		{
			float nightmode_value = (100.f - float(variables.visuals.nightmode)) / 100.f;
			float props_value = std::clamp(nightmode_value + 0.3f, 0.00f, 1.00f);

			if (variables.visuals.nightmode > 0) {
				if (strstr(material->get_texture_group_name(), "StaticProp"))
					material->color_modulate(props_value, props_value, props_value);
				else
					material->color_modulate(nightmode_value, nightmode_value, nightmode_value);
			}
			else
				material->color_modulate(1.0f, 1.0f, 1.0f);
		}
	}
}

int tick_prev = 0;
float last_vel = 0.f;
void visuals::speed()
{
	junkcode::call();

	if (variables.visuals.bSpeedIndicator && interfaces::engine->is_in_game() && interfaces::engine->is_connected()) 
	{
		int screenWidth, screenHeight;
		interfaces::engine->get_screen_size(screenWidth, screenHeight);

		auto local = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));

		if (!local)
		{
			last_vel = 0;
			return;
		}
		int vel = local->velocity().Length2D() + 0.5;

		int logVel = 0;

		color c = vel == last_vel ? color(255, 199, 89) : vel < last_vel ? color(255, 119, 119) : color(30, 255, 109);
		//render::text(point(screen_size.x / 2, screen_size.y - 100), c, skeet, font_centered | font_dropshadow, L"%.0f\n", vel);

		if (local->flags() & fl_onground) {
			logVel = local->velocity().Length2D() + 0.5;
		}
		//FIX
		std::string finalVelo = std::to_string(vel);
		std::string tick = std::to_string(interfaces::globals->tick_count);
		auto red = variables.visuals.clr_velocity[0] * 255;
		auto green = variables.visuals.clr_velocity[1] * 255;
		auto blue = variables.visuals.clr_velocity[2] * 255;
		auto alpha = variables.visuals.clr_velocity[3] * 255;
		//g_Render.String(8, 8, FONT_DROPSHADOW, Color(250, 150, 200, 180), g_Fonts.vecFonts[FONT_TAHOMA_8], szWatermark.c_str());
		//g_Render.String(screenWidth / 2, screenHeight - 50, FONT_DROPSHADOW | FONT_CENTERED_X, c, g_Fonts.vecFonts[FONT_INDICATOR], tick.c_str());
		//g_Render.String(screenWidth / 2, screenHeight - 100, FONT_DROPSHADOW | FONT_CENTERED_X, c, g_Fonts.vecFonts[FONT_INDICATOR], finalVelo.c_str());// + "(" + std::to_string(vel) + ")");
		render::draw_text_string(screenWidth / 2, screenHeight - 100, render::fonts::main_font1, finalVelo.c_str(), true, color(red, green, blue, alpha));

		if (tick_prev + 5 < interfaces::globals->tick_count) 
		{
			last_vel = vel;
			tick_prev = interfaces::globals->tick_count;
		}
		if (interfaces::globals->tick_count <= 2000)
		{
			vel = 0;
			logVel = 0;
			finalVelo = "";
			tick_prev = 0;

		}
	}

}

void visuals::sniper_crosshair() 
{
	junkcode::call();

	if (interfaces::engine->is_in_game() && interfaces::engine->is_connected() && csgo::local_player) 
	{
		static convar* weapon_debug_spread_show = interfaces::console->get_convar("weapon_debug_spread_show");
		if (variables.visuals.sniper_crosshair && csgo::local_player->is_alive() && !csgo::local_player->is_scoped()) 
		{
			if (weapon_debug_spread_show->get_int() != 69)
				weapon_debug_spread_show->set_value(69);
		}
		else {
			if (weapon_debug_spread_show->get_int() != 0)
				weapon_debug_spread_show->set_value(0);
		}
	}
}


void visuals::keyStrokes()
{
	junkcode::call();

	auto red = variables.visuals.clr_lolkeystrokescolor[0] * 255;
	auto green = variables.visuals.clr_lolkeystrokescolor[1] * 255;
	auto blue = variables.visuals.clr_lolkeystrokescolor[2] * 255;
	auto alpha = variables.visuals.clr_lolkeystrokescolor[3] * 255;

	if (variables.visuals.bKeyStrokes)
	{
		auto local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));
		if (!local_player || !local_player->is_alive())
			return;

		int w22, h22;
		interfaces::engine->get_screen_size(w22, h22);

		if (GetAsyncKeyState(0x57))//w
		{
			render::draw_text_string((w22 + 50) - (w22 - 30), h22 - 110, render::fonts::main_font1, "w", false, color(red, green, blue, alpha)); //x = 80 //y = 1835
		}
		if (GetAsyncKeyState(0x41))//a
		{
			render::draw_text_string((w22 + 50) - (w22 - 10), h22 - 90, render::fonts::main_font1, "a", false, color(red, green, blue, alpha)); //x = 60 //y = 1855
		}
		if (GetAsyncKeyState(0x44))//d
		{
			render::draw_text_string((w22 + 50) - (w22 - 59), h22 - 90, render::fonts::main_font1, "d", false, color(red, green, blue, alpha)); //x = 100 //y = 1855
		}
		if (GetAsyncKeyState(0x53))//s
		{
			render::draw_text_string((w22 + 50) - (w22 - 35), h22 - 90, render::fonts::main_font1, "s", false, color(red, green, blue, alpha));  //x = 80 //y = 1855
		}
		if (GetAsyncKeyState(0x20))//space        
		{
			render::draw_text_string((w22 + 50) - (w22 - 30), h22 - 70, render::fonts::main_font1, "_", false, color(red, green, blue, alpha)); //x = 80 //y = 1875
		}
	}
}

std::vector<const char*> smoke_materials = 
{
	"particle/vistasmokev1/vistasmokev1_smokegrenade",
	"particle/vistasmokev1/vistasmokev1_emods",
	"particle/vistasmokev1/vistasmokev1_emods_impactdust",
	"particle/vistasmokev1/vistasmokev1_fire",
};

void visuals::onDrawModelExecute()
{
	junkcode::call();

	static bool NoSmoke = false;
	static bool NoFlashReset = false;
	i_material* flash = interfaces::material_system->find_material("effects\\flashbang", TEXTURE_GROUP_CLIENT_EFFECTS);
	i_material* flashWhite = interfaces::material_system->find_material("effects\\flashbang_white", TEXTURE_GROUP_CLIENT_EFFECTS);

	if (flash && flashWhite)
	{
		if (variables.visuals.noflash && !NoFlashReset)
		{
			flash->set_material_var_flag(material_var_no_draw, true);
			flashWhite->set_material_var_flag(material_var_no_draw, true);

			NoFlashReset = true;
		}
		else if (!variables.visuals.noflash && NoFlashReset)
		{
			flash->set_material_var_flag(material_var_no_draw, false);
			flashWhite->set_material_var_flag(material_var_no_draw, false);

			NoFlashReset = false;
		}
	}

	if (variables.visuals.nosmoke && !NoSmoke)
	{
		for (auto mat : smoke_materials)
			interfaces::material_system->find_material(mat, TEXTURE_GROUP_CLIENT_EFFECTS)->set_material_var_flag(material_var_no_draw, true);

		NoSmoke = true;
	}
	else if (!variables.visuals.nosmoke && NoSmoke)
	{
		for (auto mat : smoke_materials)
			interfaces::material_system->find_material(mat, TEXTURE_GROUP_CLIENT_EFFECTS)->set_material_var_flag(material_var_no_draw, false);

		NoSmoke = false;
	}
}

void visuals::jumpbugindicator()
{
	junkcode::call();

	if (variables.visuals.jumpbugindicator)
	{
		auto local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));

		auto red = variables.visuals.clr_jumpbugindicator[0] * 255;
		auto green = variables.visuals.clr_jumpbugindicator[1] * 255;
		auto blue = variables.visuals.clr_jumpbugindicator[2] * 255;
		auto alpha = variables.visuals.clr_jumpbugindicator[3] * 255;

		if (interfaces::engine->is_in_game() && interfaces::engine->is_connected() && variables.misc.jumpbug && GetAsyncKeyState(variables.misc.jumpbugkey) && variables.misc.didJumpBug == true && local_player->is_alive()) 
		{
			int screenWidth, screenHeight;
			interfaces::engine->get_screen_size(screenWidth, screenHeight);
			render::draw_text_string(screenWidth / 50 + 520, screenHeight - 125, render::fonts::main_font1, "[jb]", false, color(red, green, blue, alpha));
		}
	}
}

void visuals::edgejumpindicator()
{
	junkcode::call();

	if (variables.visuals.edgejumpindicator)
	{
		auto local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));

		auto red = variables.visuals.clr_edgejumpindicator[0] * 255;
		auto green = variables.visuals.clr_edgejumpindicator[1] * 255;
		auto blue = variables.visuals.clr_edgejumpindicator[2] * 255;
		auto alpha = variables.visuals.clr_edgejumpindicator[3] * 255;

		if (interfaces::engine->is_in_game() && interfaces::engine->is_connected() && variables.misc.bEdgeJump && GetAsyncKeyState(variables.misc.edgejumpkey) && variables.misc.didEdgeJump == true && local_player->is_alive())
		{
			int screenWidth, screenHeight;
			interfaces::engine->get_screen_size(screenWidth, screenHeight);
			render::draw_text_string(screenWidth / 50 + 620, screenHeight - 125, render::fonts::main_font1, "[ej]", false, color(red, green, blue, alpha));
		}
	}
}

void visuals::edgebugindicator()
{
	junkcode::call();

	if (variables.visuals.edgebugindicator)
	{
		auto local_player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player()));

		auto red = variables.visuals.clr_edgebugindicator[0] * 255;
		auto green = variables.visuals.clr_edgebugindicator[1] * 255;
		auto blue = variables.visuals.clr_edgebugindicator[2] * 255;
		auto alpha = variables.visuals.clr_edgebugindicator[3] * 255;

		if (interfaces::engine->is_in_game() && interfaces::engine->is_connected() && variables.misc.edgebug && GetAsyncKeyState(variables.misc.edgebugkey) && variables.misc.didEdgeBug == true && local_player->is_alive())
		{
			int screenWidth, screenHeight;
			interfaces::engine->get_screen_size(screenWidth, screenHeight);
			render::draw_text_string(screenWidth / 50 + 720, screenHeight - 125, render::fonts::main_font1, "[eb]", false, color(red, green, blue, alpha));
		}
	}
}

void visuals::thirdperson() 
{
	static float progress;
	static bool in_transition;

	if (variables.misc.thirdperson && GetAsyncKeyState(variables.misc.thirdperson_key))
	{
		in_transition = false;
		if (!interfaces::input->m_fCameraInThirdPerson)
		{
			interfaces::input->m_fCameraInThirdPerson = true;
		}
	}

	else
	{
		progress -= interfaces::globals->frame_time * 8.f + (progress / 100);

		progress = std::clamp(progress, 0.f, 1.f);
		interfaces::input->m_vecCameraOffset.z = 150 * progress;

		if (!progress)
			interfaces::input->m_fCameraInThirdPerson = false;
		else
		{
			in_transition = true;
			interfaces::input->m_fCameraInThirdPerson = true;
		}
	}

	if (interfaces::input->m_fCameraInThirdPerson && !in_transition)
	{
		progress += interfaces::globals->frame_time * 8.f + (progress / 100);

		progress = std::clamp(progress, 0.f, 1.f);
		interfaces::input->m_vecCameraOffset.z = 150 * progress;
	}
}
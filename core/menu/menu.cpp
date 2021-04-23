#include "menu.hpp"
#include "../features/skinchanger/skin_list.hpp"
#include "../../security/cl_junkcode.hpp"

std::vector<const char*> search_results = { "Skins" };
void skin_input(std::string& search_str, int& skinid, const char* control_name) 
{
	junkcode::call();
	zgui::text_input(control_name, search_str, 5);
	if (search_str.size() > 0) {
		std::string::size_type sz;
		int i_dec = std::stoi(search_str, &sz);
		if (i_dec >= 0 && i_dec <= 920)
			skinid = i_dec;
	}
}
void fullupdate() 
{
	junkcode::call();
	//typedef void (*ForceUpdate)(void);
	//static ForceUpdate FullUpdate = (ForceUpdate)utilities::pattern_scan(GetModuleHandleA("engine.dll"), "A1 ? ? ? ? B9 ? ? ? ? 56 FF 50 14 8B 34 85");
	//FullUpdate();
	interfaces::clientstate->full_update();
}
void menu::draw()
{
	junkcode::call();
	zgui::poll_input("Counter-Strike: Global Offensive");

	csgo::menu_open = false;
	if (zgui::begin_window("cum hacck", { 507, 510 }, render::fonts::main_font, zgui::zgui_window_flags_no_ontoggle_animation)) //x = 507 //y = 434
	{
		csgo::menu_open = true;

		zgui::next_column(-9, -9);
		if (zgui::tab_button("aimbot", { 100,30 }, csgo::menu_tab == 0)) csgo::menu_tab = 0;
		zgui::next_column(-9 + 99, -9);
		if (zgui::tab_button("visuals", { 100,30 }, csgo::menu_tab == 1)) csgo::menu_tab = 1;
		zgui::next_column(-9 + 99 * 2, -9);
		if (zgui::tab_button("misc", { 100,30 }, csgo::menu_tab == 2)) csgo::menu_tab = 2;
		zgui::next_column(-9 + 99 * 3, -9);
		if (zgui::tab_button("skins", { 100,30 }, csgo::menu_tab == 3)) csgo::menu_tab = 3;
		zgui::next_column(-9 + 99 * 4, -9);
		if (zgui::tab_button("info", { 100, 30 }, csgo::menu_tab == 4)) csgo::menu_tab = 4;
		zgui::next_column(0, 29);

		if (csgo::menu_tab == 0) 
		{
			zgui::combobox("aimbot mode", { "on", "off" }, variables.aimbot_mode);
			zgui::begin_groupbox("aimbot settings", { 236,203 - 53 - 39 + 18 - 2 });
			{
				zgui::checkbox("ignore flash", variables.aimbot.ignore_flash);
				zgui::checkbox("ignore smoke", variables.aimbot.ignore_smoke);
				zgui::end_groupbox();
			}
			zgui::begin_groupbox("rifles", { 236,203 - 53 - 39 + 18 - 2 }); 
			{
				zgui::checkbox("enabled#rifles", variables.aimbot.rifles.enabled);
				zgui::combobox("mode#rifles", { "aimlock", "smoothed", "silent" }, variables.aimbot.rifles.mode);
				zgui::combobox("hitpoint#rifles", { "head", "neck", "chest", "nearest" }, variables.aimbot.rifles.hitpoint);
				zgui::slider_float("fov#rifles", 0.f, 180.f, variables.aimbot.rifles.fov, 1);
				if (variables.aimbot.rifles.mode == 1)
					zgui::slider_float("smooth#rifles", 0.f, 50.f, variables.aimbot.rifles.smooth, 1);
				zgui::end_groupbox();
			}
			zgui::next_column(244, 29);
			zgui::begin_groupbox("backtrack", { 235,140 - 75 + 20 }); 
			{
				zgui::checkbox("backtrack#enabled", variables.backtracking.enabled);
				zgui::slider_int("backtrack range", 0, 200, variables.backtracking.range);
				zgui::checkbox("aim at backtrack", variables.backtracking.aimatbt);
				zgui::end_groupbox();
			}
			zgui::begin_groupbox("pistols", { 235,203 - 53 - 39 + 19 }); 
			{
				zgui::checkbox("enabled#pistols", variables.aimbot.pistols.enabled);
				zgui::combobox("mode#pistols", { "aimlock", "smoothed", "silent" }, variables.aimbot.pistols.mode);
				zgui::combobox("hitpoint#pistols", { "head", "neck", "chest", "nearest" }, variables.aimbot.pistols.hitpoint);
				zgui::slider_float("fov#pistols", 0.f, 180.f, variables.aimbot.pistols.fov, 1);
				if (variables.aimbot.pistols.mode == 1)
					zgui::slider_float("smooth#pistols", 0.f, 50.f, variables.aimbot.pistols.smooth, 1);
				zgui::end_groupbox();
			}
			zgui::begin_groupbox("snipers", { 236,203 - 53 - 39 + 18 + 14 }); 
			{
				zgui::checkbox("enabled#snipers", variables.aimbot.snipers.enabled);
				zgui::combobox("mode#snipers", { "aimlock", "smoothed", "silent" }, variables.aimbot.snipers.mode);
				zgui::combobox("hitpoint#snipers", { "head", "neck", "chest", "nearest" }, variables.aimbot.snipers.hitpoint);
				zgui::slider_float("fov#snipers", 0.f, 180.f, variables.aimbot.snipers.fov, 1);
				if (variables.aimbot.snipers.mode == 1)
					zgui::slider_float("smooth#snipers", 0.f, 50.f, variables.aimbot.snipers.smooth, 1);
				zgui::end_groupbox();
			}
		}
		else if (csgo::menu_tab == 1) 
		{
			zgui::begin_groupbox("esp", { 236, 245 });  
			{
				zgui::key_bind("esp on key", variables.pl_esp.key_bind);
				zgui::checkbox("esp only when dead", variables.pl_esp.dead_only);
				zgui::checkbox("box", variables.pl_esp.box);
				zgui::colorpicker("clr#boxclr", variables.pl_esp.box_clr, 202);
				zgui::checkbox("name", variables.pl_esp.name);
				zgui::colorpicker("clr#nameclr", variables.pl_esp.name_clr, 202);
				zgui::checkbox("weapon", variables.pl_esp.weapon);
				zgui::colorpicker("clr#wepclr", variables.pl_esp.weapon_clr, 202);
				zgui::checkbox("health", variables.pl_esp.health);
				zgui::checkbox("thirdperson", variables.misc.thirdperson);
				zgui::key_bind("thirdperson Key", variables.misc.thirdperson_key);
				zgui::end_groupbox();
			}
			zgui::begin_groupbox("misc", { 236,185 - 22 + 56 - 40 }); 
			{
				zgui::slider_int("fov", 0, 30, variables.visuals.fov);
				zgui::slider_int("viewmodel fov", 0, 30, variables.visuals.viewmodel_fov);
				zgui::slider_int("nightmode", 0, 100, variables.visuals.nightmode);
				zgui::checkbox("force crosshair", variables.visuals.sniper_crosshair);
				zgui::checkbox("bomb timer", variables.visuals.bomb_timer);
				zgui::checkbox("no flash", variables.visuals.noflash);
				zgui::checkbox("no smoke", variables.visuals.nosmoke);
				zgui::checkbox("show impacts", variables.visuals.showimpacts);
				zgui::end_groupbox();
			}
			zgui::next_column(244, 29);
			zgui::begin_groupbox("fps", { 235,140 - 18 }); 
			{
				zgui::checkbox("disable shadow", variables.misc.disable_shadow);
				zgui::checkbox("remove 3d sky", variables.misc.remove_3dsky);
				zgui::checkbox("remove bloom", variables.misc.remove_bloom);
				zgui::checkbox("disable post processing", variables.misc.disable_post_processing);
				zgui::end_groupbox();
			}
			zgui::begin_groupbox("chams", { 235,125 + 63 + 18 + 34 }); 
			{
				zgui::checkbox("enabled#chams", variables.pl_mdl.chams.enabled);
				zgui::colorpicker("clr#chams", variables.pl_mdl.chams.clr, 202);
				zgui::checkbox("flat#chams", variables.pl_mdl.chams.flat);
				zgui::checkbox("ignore z#chams", variables.pl_mdl.chams.ignore_z);
				zgui::colorpicker("clr#chamsz", variables.pl_mdl.chams.clr_z, 202);
				zgui::slider_int("transparency#alpha", 0, 100, variables.pl_mdl.chams.transparency);
				zgui::checkbox("glow overlay", variables.pl_mdl.chams.glow_overlay);
				zgui::colorpicker("clr#glowoverlay", variables.pl_mdl.chams.glow_clr, 202);
				zgui::slider_int("transparency#glowoverlay", 0, 100, variables.pl_mdl.chams.transparency_glow);
				zgui::checkbox("backtrack#chams", variables.pl_mdl.chams.backtrack);
				zgui::colorpicker("clr#chamsback", variables.pl_mdl.chams.clr_backtrack, 202);
				zgui::slider_int("transparency#backalpha", 0, 100, variables.pl_mdl.chams.transparency_backtrack);
				zgui::end_groupbox();
			}
		}
		else if (csgo::menu_tab == 2) 
		{
			zgui::begin_groupbox("misc", { 236, 355 }); //y = 243
			{
				zgui::checkbox("nade predict", variables.misc.nade_predict);
				zgui::checkbox("radar", variables.misc.radar);
				zgui::checkbox("hit marker", variables.misc.hitmarker);
				zgui::checkbox("hit sound", variables.misc.hitsound);
				if (variables.misc.hitsound == true)
					zgui::combobox("hitsound type", { "metallic", "cod", "moan" }, variables.misc.hitsound_int);
				zgui::checkbox("reveal ranks", variables.misc.reveal_ranks);

				zgui::slider_int("viewmodel x", -10, 10, variables.misc.viewmodel[0]);
				zgui::slider_int("viewmodel y", -10, 10, variables.misc.viewmodel[1]);
				zgui::slider_int("viewmodel z", -10, 10, variables.misc.viewmodel[2]);
				zgui::checkbox("clantag", variables.misc.clantag);
				zgui::checkbox("chatspam", variables.misc.chatspam);
				zgui::checkbox("auto pistol", variables.misc.autopistol);
				zgui::checkbox("no punch", variables.misc.nopunch);
				zgui::checkbox("auto accept", variables.misc.autoaccept);
				zgui::checkbox("spectator list", variables.misc.speclist);
				zgui::colorpicker("clr#speclist", variables.misc.clr_speclist, 202);
				zgui::checkbox("watermark", variables.visuals.watermark);
				zgui::colorpicker("clr#watermark", variables.visuals.clr_watermark, 202);
				zgui::end_groupbox();
			}
			zgui::next_column(244, 29);
			zgui::begin_groupbox("movement", { 236, 445 }); //y=365
			{
				zgui::checkbox("show velocity", variables.visuals.bSpeedIndicator);
				zgui::colorpicker("clr#velocity", variables.visuals.clr_velocity, 202);
				zgui::checkbox("show keypress", variables.visuals.bKeyStrokes);
				zgui::colorpicker("clr#keysshow", variables.visuals.clr_lolkeystrokescolor, 202);
				zgui::checkbox("jumpbug indicator", variables.visuals.jumpbugindicator);
				zgui::colorpicker("clr#jbclr", variables.visuals.clr_jumpbugindicator, 202);
				zgui::checkbox("edgejump indicator", variables.visuals.edgejumpindicator);
				zgui::colorpicker("clr#ejclr", variables.visuals.clr_edgejumpindicator, 202);
				zgui::checkbox("edgebug indicator", variables.visuals.edgebugindicator);
				zgui::colorpicker("clr#ebclr", variables.visuals.clr_edgebugindicator, 202);

				zgui::text("");
				zgui::checkbox("bunny hop", variables.misc.bunny_hop);
				zgui::checkbox("auto strafe", variables.misc.auto_strafe);
				zgui::checkbox("infinite duck", variables.misc.infduck);
				zgui::checkbox("edge jump", variables.misc.bEdgeJump);
				if (variables.misc.bEdgeJump)
					zgui::key_bind("edge jump key", variables.misc.edgejumpkey);
				zgui::checkbox("jump bug", variables.misc.jumpbug);
				if (variables.misc.jumpbug)
					zgui::key_bind("jump bug key", variables.misc.jumpbugkey);
				zgui::checkbox("edge bug", variables.misc.edgebug);
				if (variables.misc.edgebug)
					zgui::key_bind("edge bug key", variables.misc.edgebugkey);
				zgui::checkbox("fake backwords", variables.misc.fakebackword);
				
				zgui::end_groupbox();
			}
		}
		else if (csgo::menu_tab == 3)
		{
			zgui::begin_groupbox("skin list", { 236,203 + 129 + 34 }); 
			{
				static std::string search_str = "";
				zgui::text_input("search", search_str, 30);
				const static int arraysize = ARRAYSIZE(skin_list_array);
				search_results.clear();
				zgui::begin_groupbox("search results", { 226,278 + 34 }); 
				{
					for (int i = 0; i < arraysize; i++) 
					{
						std::size_t found = std::string(skin_list_array[i]).find(":");
						if (strstr(skin_list_array[i] + found, search_str.c_str()))
							search_results.insert(search_results.begin(), skin_list_array[i]);
					}
					static int page = 0;
					int length = std::clamp(int(search_results.size()), 0, 17);
					for (int i = 0 + page * 17; i < length + page * 17; i++) 
					{
						if (search_results.size() > 0 && i < search_results.size())
							zgui::text(search_results.at(i));
					}
					if (search_results.size() > 17) 
					{
						if (page * 17 < search_results.size() - page * 17) 
						{
							if (zgui::button("next", { 106,23 })) page += 1;
							if (page > 0)
								zgui::next_column(50 + 70, 230 + 98 + 30);
						}
						if (page > 0)
							if (zgui::button("back", { 106,23 })) page -= 1;
					}
					zgui::end_groupbox();
				}
				zgui::end_groupbox();
			}
			zgui::next_column(244, 29);
			zgui::begin_groupbox("skin changer", { 235,140 - 18 + 210 + 34 }); 
			{
				if (interfaces::engine->is_in_game() && interfaces::engine->is_connected() && csgo::local_player && csgo::local_player->is_alive()) 
				{
					auto weapon = csgo::local_player->active_weapon();
					if (weapon && weapon->item_definition_index() && !weapon->is_c4() && !weapon->is_nade() && !weapon->is_taser()) 
					{
						if (zgui::button("update", { 100,23 })) 
						{
							interfaces::clientstate->full_update();
						}
						zgui::checkbox("enabled#skinchanger", variables.skins.enabled);
						static std::string usp_str = std::to_string(variables.skins.paint_kit_index_usp);
						static std::string p2000_str = std::to_string(variables.skins.paint_kit_index_p2000);
						static std::string glock_str = std::to_string(variables.skins.paint_kit_index_glock);
						static std::string p250_str = std::to_string(variables.skins.paint_kit_index_p250);
						static std::string fiveseven_str = std::to_string(variables.skins.paint_kit_index_fiveseven);
						static std::string tec_str = std::to_string(variables.skins.paint_kit_index_tec);
						static std::string cz_str = std::to_string(variables.skins.paint_kit_index_cz);
						static std::string elite_str = std::to_string(variables.skins.paint_kit_index_duals);
						static std::string deagle_str = std::to_string(variables.skins.paint_kit_index_deagle);
						static std::string revolver_str = std::to_string(variables.skins.paint_kit_index_revolver);
						static std::string famas_str = std::to_string(variables.skins.paint_kit_index_famas);
						static std::string galil_str = std::to_string(variables.skins.paint_kit_index_galil);
						static std::string m4a4_str = std::to_string(variables.skins.paint_kit_index_m4a4);
						static std::string m4a1_str = std::to_string(variables.skins.paint_kit_index_m4a1);
						static std::string ak_str = std::to_string(variables.skins.paint_kit_index_ak47);
						static std::string sg_str = std::to_string(variables.skins.paint_kit_index_sg553);
						static std::string aug_str = std::to_string(variables.skins.paint_kit_index_aug);
						static std::string ssg_str = std::to_string(variables.skins.paint_kit_index_ssg08);
						static std::string awp_str = std::to_string(variables.skins.paint_kit_index_awp);
						static std::string scar_str = std::to_string(variables.skins.paint_kit_index_scar);
						static std::string g3sg1_str = std::to_string(variables.skins.paint_kit_index_g3sg1);
						static std::string sawedoff_str = std::to_string(variables.skins.paint_kit_index_sawoff);
						static std::string m249_str = std::to_string(variables.skins.paint_kit_index_m249);
						static std::string negev_str = std::to_string(variables.skins.paint_kit_index_negev);
						static std::string mag7_str = std::to_string(variables.skins.paint_kit_index_mag7);
						static std::string xm_str = std::to_string(variables.skins.paint_kit_index_xm1014);
						static std::string nova_str = std::to_string(variables.skins.paint_kit_index_nova);
						static std::string bizon_str = std::to_string(variables.skins.paint_kit_index_bizon);
						static std::string mp5_str = std::to_string(variables.skins.paint_kit_index_mp5sd);
						static std::string mp7_str = std::to_string(variables.skins.paint_kit_index_mp7);
						static std::string mp9_str = std::to_string(variables.skins.paint_kit_index_mp9);
						static std::string mac10_str = std::to_string(variables.skins.paint_kit_index_mac10);
						static std::string p90_str = std::to_string(variables.skins.paint_kit_index_p90);
						static std::string ump_str = std::to_string(variables.skins.paint_kit_index_ump45);
						if (interfaces::clientstate->delta_tick == -1) 
						{
							usp_str = std::to_string(variables.skins.paint_kit_index_usp);
							p2000_str = std::to_string(variables.skins.paint_kit_index_p2000);
							glock_str = std::to_string(variables.skins.paint_kit_index_glock);
							p250_str = std::to_string(variables.skins.paint_kit_index_p250);
							fiveseven_str = std::to_string(variables.skins.paint_kit_index_fiveseven);
							tec_str = std::to_string(variables.skins.paint_kit_index_tec);
							cz_str = std::to_string(variables.skins.paint_kit_index_cz);
							elite_str = std::to_string(variables.skins.paint_kit_index_duals);
							deagle_str = std::to_string(variables.skins.paint_kit_index_deagle);
							revolver_str = std::to_string(variables.skins.paint_kit_index_revolver);
							famas_str = std::to_string(variables.skins.paint_kit_index_famas);
							galil_str = std::to_string(variables.skins.paint_kit_index_galil);
							m4a4_str = std::to_string(variables.skins.paint_kit_index_m4a4);
							m4a1_str = std::to_string(variables.skins.paint_kit_index_m4a1);
							ak_str = std::to_string(variables.skins.paint_kit_index_ak47);
							sg_str = std::to_string(variables.skins.paint_kit_index_sg553);
							aug_str = std::to_string(variables.skins.paint_kit_index_aug);
							ssg_str = std::to_string(variables.skins.paint_kit_index_ssg08);
							awp_str = std::to_string(variables.skins.paint_kit_index_awp);
							scar_str = std::to_string(variables.skins.paint_kit_index_scar);
							g3sg1_str = std::to_string(variables.skins.paint_kit_index_g3sg1);
							sawedoff_str = std::to_string(variables.skins.paint_kit_index_sawoff);
							m249_str = std::to_string(variables.skins.paint_kit_index_m249);
							negev_str = std::to_string(variables.skins.paint_kit_index_negev);
							mag7_str = std::to_string(variables.skins.paint_kit_index_mag7);
							xm_str = std::to_string(variables.skins.paint_kit_index_xm1014);
							nova_str = std::to_string(variables.skins.paint_kit_index_nova);
							bizon_str = std::to_string(variables.skins.paint_kit_index_bizon);
							mp5_str = std::to_string(variables.skins.paint_kit_index_mp5sd);
							mp7_str = std::to_string(variables.skins.paint_kit_index_mp7);
							mp9_str = std::to_string(variables.skins.paint_kit_index_mp9);
							mac10_str = std::to_string(variables.skins.paint_kit_index_mac10);
							p90_str = std::to_string(variables.skins.paint_kit_index_p90);
							ump_str = std::to_string(variables.skins.paint_kit_index_ump45);
						}
						switch (weapon->item_definition_index()) 
						{
						case WEAPON_USP_SILENCER:
							skin_input(usp_str, variables.skins.paint_kit_index_usp, "USP-S Skin");
							break;
						case WEAPON_HKP2000:
							skin_input(p2000_str, variables.skins.paint_kit_index_p2000, "P2000 Skin");
							break;
						case WEAPON_GLOCK:
							skin_input(glock_str, variables.skins.paint_kit_index_glock, "Glock Skin");
							break;
						case WEAPON_P250:
							skin_input(p250_str, variables.skins.paint_kit_index_p250, "P250 Skin");
							break;
						case WEAPON_FIVESEVEN:
							skin_input(fiveseven_str, variables.skins.paint_kit_index_fiveseven, "Five-Seven Skin");
							break;
						case WEAPON_TEC9:
							skin_input(tec_str, variables.skins.paint_kit_index_tec, "Tec-9 Skin");
							break;
						case WEAPON_CZ75A:
							skin_input(cz_str, variables.skins.paint_kit_index_cz, "CZ75 Skin");
							break;
						case WEAPON_ELITE:
							skin_input(elite_str, variables.skins.paint_kit_index_duals, "Beretas Skin");
							break;
						case WEAPON_DEAGLE:
							skin_input(deagle_str, variables.skins.paint_kit_index_deagle, "Deagle Skin");
							break;
						case WEAPON_REVOLVER:
							skin_input(revolver_str, variables.skins.paint_kit_index_revolver, "Revolver Skin");
							break;
						case WEAPON_FAMAS:
							skin_input(famas_str, variables.skins.paint_kit_index_famas, "Famas Skin");
							break;
						case WEAPON_GALILAR:
							skin_input(galil_str, variables.skins.paint_kit_index_galil, "Galil Skin");
							break;
						case WEAPON_M4A1:
							skin_input(m4a4_str, variables.skins.paint_kit_index_m4a4, "M4A4 Skin");
							break;
						case WEAPON_M4A1_SILENCER:
							skin_input(m4a1_str, variables.skins.paint_kit_index_m4a1, "M4A1-S Skin");
							break;
						case WEAPON_AK47:
							skin_input(ak_str, variables.skins.paint_kit_index_ak47, "AK47 Skin");
							break;
						case WEAPON_SG556:
							skin_input(sg_str, variables.skins.paint_kit_index_sg553, "SG553 Skin");
							break;
						case WEAPON_AUG:
							skin_input(aug_str, variables.skins.paint_kit_index_aug, "Aug Skin");
							break;
						case WEAPON_SSG08:
							skin_input(ssg_str, variables.skins.paint_kit_index_ssg08, "SSG08 Skin");
							break;
						case WEAPON_AWP:
							skin_input(awp_str, variables.skins.paint_kit_index_awp, "AWP Skin");
							break;
						case WEAPON_SCAR20:
							skin_input(scar_str, variables.skins.paint_kit_index_scar, "SCAR20 Skin");
							break;
						case WEAPON_G3SG1:
							skin_input(g3sg1_str, variables.skins.paint_kit_index_g3sg1, "G3SG1 Skin");
							break;
						case WEAPON_SAWEDOFF:
							skin_input(sawedoff_str, variables.skins.paint_kit_index_sawoff, "Sawedoff Skin");
							break;
						case WEAPON_M249:
							skin_input(m249_str, variables.skins.paint_kit_index_m249, "M249 Skin");
							break;
						case WEAPON_NEGEV:
							skin_input(negev_str, variables.skins.paint_kit_index_negev, "Negev Skin");
							break;
						case WEAPON_MAG7:
							skin_input(mag7_str, variables.skins.paint_kit_index_mag7, "MAG-7 Skin");
							break;
						case WEAPON_XM1014:
							skin_input(xm_str, variables.skins.paint_kit_index_xm1014, "XM1014 Skin");
							break;
						case WEAPON_NOVA:
							skin_input(nova_str, variables.skins.paint_kit_index_nova, "Nova Skin");
							break;
						case WEAPON_BIZON:
							skin_input(bizon_str, variables.skins.paint_kit_index_bizon, "Bizon Skin");
							break;
						case WEAPON_MP5_SD:
							skin_input(mp5_str, variables.skins.paint_kit_index_mp5sd, "MP5 Skin");
							break;
						case WEAPON_MP7:
							skin_input(mp7_str, variables.skins.paint_kit_index_mp7, "MP7 Skin");
							break;
						case WEAPON_MP9:
							skin_input(mp9_str, variables.skins.paint_kit_index_mp9, "MP9 Skin");
							break;
						case WEAPON_MAC10:
							skin_input(mac10_str, variables.skins.paint_kit_index_mac10, "MAC10 Skin");
							break;
						case WEAPON_P90:
							skin_input(p90_str, variables.skins.paint_kit_index_p90, "P90 Skin");
							break;
						case WEAPON_UMP45:
							skin_input(ump_str, variables.skins.paint_kit_index_ump45, "UMP-45 Skin");
							break;
						}
						zgui::combobox("Knife Model", { "Default", "Bayonet", "Flip", "Gut Knife", "Karambit", "M9 Bayonet", "Huntsman Knife", "Falchion Knife", "Bowie Knife", "Butterfly Knife", "Shadow Daggers", "Ursus Knife", "Navaja Knife", "Stiletto Knife", "Talon Knife", "Nomad Knife", "Skeleton Knife", "Survival Knife", "Paracord Knife", "Classic Knife" }, variables.skins.knife_model);
						switch (variables.skins.knife_model)
						{
						case 1:
							zgui::combobox("Bayonet Skin", { "Vanilla", "Lore", "Gamma Doppler", "Autotronic", "Black Laminate", "Freehand", "Bright Water", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, variables.skins.knife_skin);
							break;
						case 2:
							zgui::combobox("Flip Knife Skin", { "Vanilla", "Lore", "Gamma Doppler", "Autotronic", "Black Laminate", "Freehand", "Bright Water", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, variables.skins.knife_skin);
							break;
						case 3:
							zgui::combobox("Gut Knife Skin", { "Vanilla", "Lore", "Gamma Doppler", "Autotronic", "Black Laminate", "Freehand", "Bright Water", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, variables.skins.knife_skin);
							break;
						case 4:
							zgui::combobox("Karambit Skin", { "Vanilla", "Lore", "Gamma Doppler", "Autotronic", "Black Laminate", "Freehand", "Bright Water", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, variables.skins.knife_skin);
							break;
						case 5:
							zgui::combobox("M9 Bayonet Skin", { "Vanilla", "Lore", "Gamma Doppler", "Autotronic", "Black Laminate", "Freehand", "Bright Water", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, variables.skins.knife_skin);
							break;
						case 6:
							zgui::combobox("Huntsman Knife Skin", { "Vanilla", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, variables.skins.knife_skin);
							break;
						case 7:
							zgui::combobox("Falchion Knife Skin", { "Vanilla", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, variables.skins.knife_skin);
							break;
						case 8:
							zgui::combobox("Bowie Knife Skin", { "Vanilla", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, variables.skins.knife_skin);
							break;
						case 9:
							zgui::combobox("Butterfly Knife Skin", { "Vanilla", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, variables.skins.knife_skin);
							break;
						case 10:
							zgui::combobox("Shadow Daggers Skin", { "Vanilla", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, variables.skins.knife_skin);
							break;
						case 11:
							zgui::combobox("Ursus Knife Skin", { "Vanilla", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, variables.skins.knife_skin);
							break;
						case 12:
							zgui::combobox("Navaja Knife Skin", { "Vanilla", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, variables.skins.knife_skin);
							break;
						case 13:
							zgui::combobox("Stiletto Knife Skin", { "Vanilla", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, variables.skins.knife_skin);
							break;
						case 14:
							zgui::combobox("Talon Knife Skin", { "Vanilla", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, variables.skins.knife_skin);
							break;
						case 15:
							zgui::combobox("Nomad Knife Skin", { "Vanilla", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, variables.skins.knife_skin);
							break;
						case 16:
							zgui::combobox("Skeleton Knife Skin", { "Vanilla", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, variables.skins.knife_skin);
							break;
						case 17:
							zgui::combobox("Survival Knife Skin", { "Vanilla", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, variables.skins.knife_skin);
							break;
						case 18:
							zgui::combobox("Paracord Knife Skin", { "Vanilla", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, variables.skins.knife_skin);
							break;
						case 19:
							zgui::combobox("Classic Knife Skin", { "Vanilla", "Marble Fade", "Tiger Tooth", "Doppler", "Ultraviolet", "Damascus Steel", "Rust Coat", "Fade", "Slaughter", "Case Hardened", "Crimson Web", "Blue Steel", "Night", "Safari Mesh", "Forest DDPAT", "Stained", "Scorched", "Boreal Forest", "Urban Masked" }, variables.skins.knife_skin);
							break;
						}
						zgui::combobox("Glove Model", { "Default", "Bloodhound", "Sport", "Driver", "Hand Wraps", "Moto", "Specialist", "Hydra" }, variables.skins.glove_model);
						switch (variables.skins.glove_model) {
						case 1:
							zgui::combobox("Bloodhound Skin", { "Snakebite", "Guerrilla", "Charred", "Bronzed" }, variables.skins.bloodhound_skin);
							break;
						case 2:
							zgui::combobox("Sport Skin", { "Vice", "Amphibious", "Omega", "Bronze Morph", "Pandora's Box", "Superconductor", "Hedge Maze", "Arid" }, variables.skins.sport_skin);
							break;
						case 3:
							zgui::combobox("Driver Skin", { "King Snake", "Imperial Plaid", "Overtake", "Racing Green", "Crimson Weave", "Diamondback", "Lunar Weave", "Convoy" }, variables.skins.driver_skin);
							break;
						case 4:
							zgui::combobox("Hand Wrap Skin", { "Cobalt Skulls", "Overprint", "Arboreal", "Duct Tape", "Slaughter", "Badlands", "Leather", "Spruce DDPAT" }, variables.skins.handwrap_skin);
							break;
						case 5:
							zgui::combobox("Moto Skin", { "POW!", "Turtle", "Polygon", "Transport", "Spearmint", "Boom!", "Cool Mint", "Eclipse" }, variables.skins.moto_skin);
							break;
						case 6:
							zgui::combobox("Specialist Skin", { "Fade", "Crimson Web", "Mogul", "Buckshot", "Crimson Kimono", "Emerald Web", "Foundation", "Forest DDPAT" }, variables.skins.specialist_skin);
							break;
						case 7:
							zgui::combobox("Hydra Skin", { "Emerald", "Mangrove", "Case Hardened", "Rattler" }, variables.skins.hydra_skin);
							break;
						}
					}
				}
				zgui::end_groupbox();
			}
		}
		else if (csgo::menu_tab == 4) 
		{
			zgui::begin_groupbox("credits", { 236,203 + 129 + 34 });
			{
				zgui::text("zxvnme for zgui");
				zgui::text("designer1337 for base");
				zgui::text("tsuda kageyu for minhook");
				zgui::text("namazso for nskinz");
				zgui::text("brofield for simpleini");
				zgui::text("clifton for help with jb");
				zgui::text("random snippets from unknowncheats");
				zgui::text("a few leaked sources");
				zgui::text("everyone who submitted bug reports ");
				zgui::text("or feature reqests on discord");

				zgui::end_groupbox();
			}
			zgui::next_column(244, 29);
			zgui::begin_groupbox("lexi#0001", { 235,140 - 18 });
			{
				zgui::text("this was made for fun and my own education ");
				zgui::text("into game hacking");
				zgui::text("this will always be a free piece of software ");
				zgui::text("for anyone to use");
				zgui::text(" ");
				zgui::clickable_text("lexi.best");

				zgui::end_groupbox();
			}
			zgui::begin_groupbox("config", { 236, 119 });
			{
				zgui::combobox("config file", { "1" ,"2" ,"3" ,"4" ,"5" }, variables.misc.config_file);
				if (zgui::button("save", { 100,23 }))
				{
					config::save(); fullupdate();
				}
				if (zgui::button("load", { 100,23 }))
				{
					config::load(); fullupdate();
				}

				zgui::end_groupbox();
			}
		}
		zgui::end_window();
	}
}

void zgui_line(int x, int y, int x2, int y2, zgui::color c) noexcept
{
	junkcode::call();
	render::draw_line(x, y, x2, y2, color(c.r, c.g, c.b, c.a));
}

void zgui_outline(int x, int y, int w, int h, zgui::color c) noexcept
{
	junkcode::call();
	render::draw_outline(x, y, w, h, color(c.r, c.g, c.b, c.a));
}

void zgui_filled_rect(int x, int y, int w, int h, zgui::color c) noexcept
{
	junkcode::call();
	render::draw_filled_rect(x, y, w, h, color(c.r, c.g, c.b, c.a));
}

void zgui_text(int x, int y, zgui::color c, int font, bool center, const char* text) noexcept
{
	junkcode::call();
	render::draw_text_string(x, y, font, text, center, color(c.r, c.g, c.b, c.a));
}

void zgui_get_text_size(unsigned long font, const char* text, int& width, int& height) noexcept
{
	junkcode::call();
	render::get_text_size(font, text, width, height);
}

float zgui_get_frametime() noexcept
{
	junkcode::call();
	return interfaces::globals->frame_time;
}

void menu::initialize()
{
	junkcode::call();
	csgo::menu_open = false;
	csgo::menu_tab = 0;
	zgui::functions.draw_line = zgui_line;
	zgui::functions.draw_rect = zgui_outline;
	zgui::functions.draw_filled_rect = zgui_filled_rect;
	zgui::functions.draw_text = zgui_text;
	zgui::functions.get_text_size = zgui_get_text_size;
	zgui::functions.get_frametime = zgui_get_frametime;

	console::log("[setup] menu initialized!\n");
}
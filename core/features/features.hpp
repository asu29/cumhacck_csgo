#pragma once
#include "../menu/config.hpp"
#include "../../dependencies/common_includes.hpp"
#include "../../security/cl_junkcode.hpp"
#include "../../dependencies/math/math.hpp"
#include "../../source-sdk/classes/c_usercmd.hpp"

namespace misc 
{
	void bunny_hop(c_usercmd* cmd);
	void clantag();
	void ClanTagApply(const char* TagName);
	void disable_post_processing();
	void disable_shadow();
	void remove_3dsky();
	void auto_strafe(c_usercmd* user_cmd) noexcept;
	void remove_bloom();
	void jumpbug(c_usercmd* cmd);
	void edgejump(c_usercmd* cmd);
	void edgebug(c_usercmd* cmd);
	void fakebackword(c_usercmd* cmd);
	void nade_predict();
	void chatspam();
	void showimpacts();
	void disable_blur();
	void autopistol(c_usercmd* cmd);
	void nopunch();
	void autoaccept(const char* pSoundEntry);

	namespace hitmarker 
	{
		void run();
		void event(i_game_event* event);
		void draw();
	}
}

namespace prediction 
{
	void start(c_usercmd* cmd);
	void end();
	int getFlags() noexcept;
};

struct bbox_t
{
	long x, y, w, h;
};

struct esp_ctx_t
{
	int screen_w, screen_h;
	player_t* pl;
	bbox_t bbox;
	int weapon_offset;
	float f_temp_alpha[65];
	int i_temp_alpha[65];
	int main_alpha[65];
	int outline_alpha[65];
};

namespace esp 
{
	extern esp_ctx_t ctx;
	void box();
	void name();
	void weapon();
	void health();
	void bomb_timer();
	void spectator_list();
	void render();
};


namespace chams 
{
	void init();
	void shutdown();
	void run(hooks::draw_model_execute::fn ofunc, IMatRenderContext* ctx, const draw_model_state_t& state, const model_render_info_t& info, matrix_t* matrix);
}

struct tick_info
{
	tick_info()
	{
		head_pos = vec3_t{};
		simulation_time = -1.f;
		bone_matrix_built = false;
	}
	tick_info(player_t* player)
	{
		head_pos = player->get_hitbox_position(hitbox_head);
		simulation_time = player->simulation_time();
		bone_matrix_built = false;
		if (player->setup_bones(bone_matrix, 128, BONE_USED_BY_ANYTHING, interfaces::globals->cur_time))
			bone_matrix_built = true;
	}
	vec3_t head_pos;
	float simulation_time;
	bool bone_matrix_built;
	matrix_t bone_matrix[128];
};

namespace backtracking 
{
	extern std::vector<tick_info> records[65];
	extern int closest_player;
	extern int closest_tick;
	bool is_tick_valid(float simulation_time, float backtrack_time);
	void store(c_usercmd* cmd);
	void run(c_usercmd* cmd);
}

struct aimbot_ctx_t
{
	bool enabled;
	int mode;
	int hitpoint;
	float fov;
	float smooth;
	bool rcs;
	vec3_t hitbox_pos;
	player_t* pl;
};
namespace aimbot 
{
	extern aimbot_ctx_t ctx;
	void weapon_cfg(weapon_t* weapon);
	int get_hitbox(int hitpoint);
	int get_hitbox(player_t* player, matrix_t* matrix, vec3_t eye_pos);
	void run(c_usercmd* cmd);
}

struct fake_state_t 
{
	bool m_should_update_fake = false;
	std::array< animation_layer, 13 > m_fake_layers;
	std::array< float, 24 > m_fake_poses;
	anim_state* m_fake_state = nullptr;
	float m_fake_rotation = 0.f;
	bool init_fake_anim = false;
	float m_fake_spawntime = 0.f;
	float m_fake_delta = 0.f;
	matrix_t m_fake_matrix[128];
	matrix_t m_fake_position_matrix[128];
	bool m_got_fake_matrix = false;
	float m_real_yaw_ang = 0.f;
};
extern fake_state_t fake_state;


namespace skinchanger 
{
	void run();
	void animfix_hook();
	void animfix_unhook();
}

namespace glovechanger 
{
	bool apply_glove_model(attributable_item_t* glove, const char* model);
	bool apply_glove_skin(attributable_item_t* glove, int item_definition_index, int paint_kit, int model_index, int entity_quality, float fallback_wear);
	void run();
}

namespace visuals 
{
	void nightmode();
	void speed();
	void sniper_crosshair();
	void keyStrokes();
	void jumpbugindicator();
	void edgejumpindicator();
	void edgebugindicator();
	void thirdperson();
}
#include "../features.hpp"
#include "../../../security/cl_junkcode.hpp"

void chams::init() 
{
	junkcode::call();

	std::ofstream("csgo/materials/glow_overlay.vmt") << R"#("VertexLitGeneric" {
 
	"$additive" "1"
	"$envmap" "models/effects/cube_white"
	"$envmaptint" "[1 1 1]"
	"$envmapfresnel" "1"
	"$envmapfresnelminmaxexp" "[0 1 2]"
	"$alpha" "0.8"
})#";
}
void chams::shutdown() 
{
	junkcode::call();

	std::remove("csgo\\materials\\glow_overlay.vmt");
}
void modulate_shit_clr(i_material* mat, float* clr) 
{
	junkcode::call();

	bool b_found = false;
	auto p_var = mat->find_var("$envmaptint", &b_found);
	if (b_found)
		(*(void(__thiscall**)(int, float, float, float))(*(DWORD*)p_var + 44))((uintptr_t)p_var, clr[0], clr[1], clr[2]);
}
void modulate_shit_alpha(i_material* mat, float alpha) 
{
	junkcode::call();

	bool b_found = false;
	auto p_var = mat->find_var("$alpha", &b_found);
	if (b_found)
		(*(void(__thiscall**)(int, float))(*(DWORD*)p_var + 44))((uintptr_t)p_var, alpha);
}
void set_tint(i_material* mat) 
{
	junkcode::call();

	bool b_found; 
	auto p_var = mat->find_var("$envmapfresnelminmaxexp", &b_found);
	if (b_found && p_var) {
		p_var->set_vector(0.f, 1.f, 5.f);
	}
}
void chams::run(hooks::draw_model_execute::fn ofunc, IMatRenderContext* ctx, const draw_model_state_t& state, const model_render_info_t& info, matrix_t* matrix) 
{
	junkcode::call();

	static i_material* mat_textured = interfaces::material_system->find_material("debug/debugambientcube", TEXTURE_GROUP_MODEL);
	static i_material* mat_flat = interfaces::material_system->find_material("debug/debugdrawflat", TEXTURE_GROUP_MODEL);
	static i_material* mat_eso_glow = interfaces::material_system->find_material("dev/glow_armsrace", TEXTURE_GROUP_MODEL);
	static i_material* mat_glow = interfaces::material_system->find_material("dev/glow_armsrace", TEXTURE_GROUP_MODEL);

	i_material* material = variables.pl_mdl.chams.flat ? mat_flat : mat_textured;

	if (interfaces::engine->is_in_game() && interfaces::engine->is_connected() && csgo::local_player) {
		if (info.model)
		{
			std::string model_name = interfaces::model_info->get_model_name(info.model);

			if (model_name.find("models/player/") != std::string::npos && variables.pl_mdl.chams.enabled) {
				auto player = reinterpret_cast<player_t*>(interfaces::entity_list->get_client_entity(info.entity_index));
				if (csgo::local_player && player && player->is_player() && !player->dormant() && player->is_alive()) {
					if (player->team() != csgo::local_player->team()) {
						if (variables.backtracking.enabled &&
							variables.backtracking.range &&
							variables.pl_mdl.chams.backtrack &&
							backtracking::records[info.entity_index].size() > 0 &&
							backtracking::records[info.entity_index].back().bone_matrix_built &&
							backtracking::records[info.entity_index].back().bone_matrix &&
							csgo::local_player->is_alive())
						{
							interfaces::render_view->modulate_color(variables.pl_mdl.chams.clr_backtrack);
							interfaces::render_view->set_blend(float(100 - variables.pl_mdl.chams.transparency_backtrack) / 100.f);
							material->set_material_var_flag(material_var_flags_t::material_var_ignorez, variables.pl_mdl.chams.ignore_z);
							interfaces::model_render->override_material(material);
							ofunc(interfaces::model_render, ctx, state, info, backtracking::records[info.entity_index].back().bone_matrix);
						}
						if (variables.pl_mdl.chams.ignore_z) {
							interfaces::render_view->modulate_color(variables.pl_mdl.chams.clr_z);
							interfaces::render_view->set_blend(float(100 - variables.pl_mdl.chams.transparency) / 100.f);
							material->set_material_var_flag(material_var_flags_t::material_var_ignorez, true);
							interfaces::model_render->override_material(material);
							ofunc(interfaces::model_render, ctx, state, info, matrix);
						}
						interfaces::render_view->modulate_color(variables.pl_mdl.chams.clr);
						interfaces::render_view->set_blend(float(100 - variables.pl_mdl.chams.transparency) / 100.f);
						material->set_material_var_flag(material_var_flags_t::material_var_ignorez, false);
						interfaces::model_render->override_material(material);
						if (variables.pl_mdl.chams.glow_overlay) 
						{
							ofunc(interfaces::model_render, ctx, state, info, matrix);
							interfaces::render_view->modulate_color(variables.pl_mdl.chams.glow_clr);
							modulate_shit_clr(mat_eso_glow, variables.pl_mdl.chams.glow_clr);
							interfaces::render_view->set_blend(float(100 - variables.pl_mdl.chams.transparency_glow) / 100.f);
							modulate_shit_alpha(mat_eso_glow, float(100 - variables.pl_mdl.chams.transparency_glow) / 100.f);
							mat_eso_glow->set_material_var_flag(material_var_flags_t::material_var_ignorez, variables.pl_mdl.chams.ignore_z);
							interfaces::model_render->override_material(mat_eso_glow);
						}
					}
				}
			}
		}
	}
	ofunc(interfaces::model_render, ctx, state, info, matrix);
	interfaces::model_render->override_material(nullptr);
}
#include "grid_resampler.h"

#include <cassert>

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/variant.hpp>

namespace grid
{

    using ClassDB = godot::ClassDB;
    using PropertyInfo = godot::PropertyInfo;
    using Variant = godot::Variant;
    using Vector2i = godot::Vector2i;

    static const Vector2i MAPPING[16] = {
        Vector2i{0, 3}, Vector2i{3, 3}, Vector2i{0, 2}, Vector2i{1, 2},
        Vector2i{0, 0}, Vector2i{3, 2}, Vector2i{2, 3}, Vector2i{3, 1},
        Vector2i{1, 3}, Vector2i{0, 1}, Vector2i{1, 0}, Vector2i{2, 2},
        Vector2i{3, 0}, Vector2i{2, 0}, Vector2i{1, 1}, Vector2i{2, 1}};

    void GridResampler::_bind_methods()
    {
        ClassDB::bind_method(godot::D_METHOD("resample"), &GridResampler::resample);

        ClassDB::bind_method(godot::D_METHOD("set_primary_id", "id"), &GridResampler::set_primary_id);
        ClassDB::bind_method(godot::D_METHOD("get_primary_id"), &GridResampler::get_primary_id);
        ADD_PROPERTY(godot::PropertyInfo(Variant::INT, "primary_id"), "set_primary_id", "get_primary_id");

        ClassDB::bind_method(godot::D_METHOD("set_transition_id", "id"), &GridResampler::set_transition_id);
        ClassDB::bind_method(godot::D_METHOD("get_transition_id"), &GridResampler::get_transition_id);
        ADD_PROPERTY(godot::PropertyInfo(Variant::INT, "transition_id"), "set_transition_id", "get_transition_id");
    }

    void GridResampler::_ready()
    {
        game_layer = get_node<TileMapLayer>("GameLayer");
        render_layer = get_node<TileMapLayer>("RenderLayer");
    }

    void GridResampler::resample()
    {
        assert(game_layer && render_layer);

        render_layer->clear();
        godot::Rect2i game_grid = game_layer->get_used_rect();
        godot::Vector2 end = game_grid.get_end();

        for (int y = game_grid.position.y; y <= end.y; ++y)
        {
            for (int x = game_grid.position.x; x <= end.x; ++x)
            {
                const bool tl = game_layer->get_cell_source_id(Vector2i(x - 1, y - 1)) == primary_id;
                const bool tr = game_layer->get_cell_source_id(Vector2i(x, y - 1)) == primary_id;
                const bool bl = game_layer->get_cell_source_id(Vector2i(x - 1, y)) == primary_id;
                const bool br = game_layer->get_cell_source_id(Vector2i(x, y)) == primary_id;

                const int mask = tl | (tr << 1) | (bl << 2) | (br << 3);
                render_layer->set_cell(Vector2i(x, y), transition_id, MAPPING[mask]);
            }
        }
    }

    void GridResampler::set_primary_id(int p_id) noexcept { primary_id = p_id; };
    void GridResampler::set_transition_id(int p_id) noexcept { transition_id = p_id; };
    int GridResampler::get_primary_id() const noexcept { return primary_id; };
    int GridResampler::get_transition_id() const noexcept { return transition_id; };
}
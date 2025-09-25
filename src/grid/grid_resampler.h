#pragma once

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/tile_map_layer.hpp>
#include <godot_cpp/core/class_db.hpp>

namespace grid
{
    using TileMapLayer = godot::TileMapLayer;
    class GridResampler : public godot::Node2D
    {
        GDCLASS(GridResampler, godot::Node2D)

    private:
        TileMapLayer *game_layer = nullptr;
        TileMapLayer *render_layer = nullptr;

        int primary_id = 1;
        int transition_id = 0;

    protected:
        static void _bind_methods();

    public:
        void _ready() override;
        void resample();

        void set_primary_id(int p_id) noexcept;
        int get_primary_id() const noexcept;
        void set_transition_id(int p_id) noexcept;
        int get_transition_id() const noexcept;
    };
}
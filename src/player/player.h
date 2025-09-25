#pragma once

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/input.hpp>

namespace renderer
{
    class DirectionalAnimatedSpriteRenderer;
}

namespace player
{
    class Player : public godot::CharacterBody2D
    {
        GDCLASS(Player, godot::CharacterBody2D)

    private:
        godot::Input *input = nullptr;
        renderer::DirectionalAnimatedSpriteRenderer *renderer = nullptr;

    protected:
        static void _bind_methods() {}

    public:
        void _physics_process(double) override;
        void _ready() override;
    };
}

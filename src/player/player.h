#pragma once

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/input.hpp>

namespace godot
{
    class Player : public CharacterBody2D
    {
        GDCLASS(Player, CharacterBody2D)

    private:
        Input *input = nullptr;

    protected:
        static void _bind_methods() {};

    public:
        void _physics_process(double delta) override;
        void _ready() override;
    };
}
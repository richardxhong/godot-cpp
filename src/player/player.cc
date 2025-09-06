#include "player.h"
#include "common/sname_compat.h"

#include <cassert>

#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/variant/string_name.hpp>

namespace godot
{
    void Player::_ready()
    {
        input = Input::get_singleton();
    }

    void Player::_physics_process(double delta)
    {
        assert(input != nullptr);

        Vector2 mv = input->get_vector(SNAME("move_left"), SNAME("move_right"), SNAME("move_up"), SNAME("move_down"));
        set_velocity(mv * 100.0);
        move_and_slide();
    }
}
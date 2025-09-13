#include "player.h"

#include <cassert>

#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/variant/string_name.hpp>

#include "common/sname_compat.h"
#include "common/direction.h"
#include "renderer/directional_renderer.h"

namespace godot
{
    void Player::_ready()
    {
        if (Node *n = get_node_or_null(NodePath("DirectionalAnimatedSpriteRenderer")))
        {
            renderer = Object::cast_to<DirectionalAnimatedSpriteRenderer>(n);
        }
        input = Input::get_singleton();
    }

    void Player::_physics_process(double)
    {
        if (!input)
            return;

        Vector2 mv = input->get_vector(SNAME("move_left"), SNAME("move_right"), SNAME("move_up"), SNAME("move_down"));
        int mult = 50;
        if (input->is_action_pressed(SNAME("sprint_hold")))
        {
            mult = 80;
        }
        set_velocity(mv * mult);
        move_and_slide();

        if (!renderer)
            return;

        const bool moving = !mv.is_zero_approx();
        if (moving)
        {
            renderer->set_state(mult == 50 ? SNAME("walk") : SNAME("run"));
            renderer->set_direction(from_vector(mv));
        }
        else
        {
            renderer->set_state(SNAME("idle"));
        }
    }
}
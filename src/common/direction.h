#pragma once
#include <cstdint>
#include <cstddef>
#include <cmath>

#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include "common/sname_compat.h"

namespace common
{
    // Local aliases to reduce repeated godot:: qualifiers in this header
    using StringName = godot::StringName;
    using Vector2 = godot::Vector2;
    using real_t = godot::real_t;
    enum class Direction : uint8_t
    {
        NORTH = 0,
        NORTH_EAST = 1,
        EAST = 2,
        SOUTH_EAST = 3,
        SOUTH = 4,
        SOUTH_WEST = 5,
        WEST = 6,
        NORTH_WEST = 7,
        COUNT
    };

    inline constexpr std::size_t direction_count = static_cast<std::size_t>(Direction::COUNT);

    inline const StringName &direction_name(Direction d) noexcept
    {
        static const StringName kNames[] = {
            SNAME("north"),
            SNAME("north_east"),
            SNAME("east"),
            SNAME("south_east"),
            SNAME("south"),
            SNAME("south_west"),
            SNAME("west"),
            SNAME("north_west")};
        const std::size_t idx = static_cast<std::size_t>(d);
        if (idx < direction_count)
            return kNames[idx];
        static const StringName empty;
        return empty;
    }

    [[nodiscard]] inline Direction from_vector(const Vector2 &v) noexcept
    {
        if (v.is_zero_approx())
        {
            return Direction::SOUTH;
        }
        const real_t x = v.x;
        const real_t y = v.y;
        const real_t ax = std::fabs(x);
        const real_t ay = std::fabs(y);

        constexpr real_t TAN_22_5 = static_cast<real_t>(0.41421356237309504880);

        if (ay <= ax * TAN_22_5)
            return x > 0 ? Direction::EAST : Direction::WEST;
        if (ax <= ay * TAN_22_5)
            return y > 0 ? Direction::SOUTH : Direction::NORTH;
        if (x > 0)
            return y > 0 ? Direction::SOUTH_EAST : Direction::NORTH_EAST;
        return y > 0 ? Direction::SOUTH_WEST : Direction::NORTH_WEST;
    }
}

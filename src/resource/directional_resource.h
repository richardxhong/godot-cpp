#pragma once

#include <array>

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/ref.hpp>

#include "common/direction.h"

namespace godot
{
    class DirectionalResource : public Resource
    {
        GDCLASS(DirectionalResource, Resource)
    private:
        std::array<Ref<Resource>, direction_count> assets;
        void validate_index(int index) const;

    protected:
        static void _bind_methods();

    public:
        void set_asset(int index, const Ref<Resource> &asset);
        [[nodiscard]] Ref<Resource> get_asset(int index) const;
        [[nodiscard]] Ref<Resource> get_best_asset_for(Direction dir, bool &flip_h) const;
    };
}

#pragma once

#include <array>

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/ref.hpp>

#include "common/direction.h"

namespace resource
{
    // Local aliases for commonly repeated Godot types in this header
    template <class T>
    using Ref = godot::Ref<T>;
    using Resource = godot::Resource;
    class DirectionalResource : public godot::Resource
    {
        GDCLASS(DirectionalResource, godot::Resource)
    private:
        std::array<Ref<Resource>, common::direction_count> assets;
        void validate_index(int index) const;

    protected:
        static void _bind_methods();

    public:
        void set_asset(int index, const Ref<Resource> &asset);
        [[nodiscard]] Ref<Resource> get_asset(int index) const;
        [[nodiscard]] Ref<Resource> get_best_asset_for(common::Direction dir, bool &flip_h) const;
    };
}

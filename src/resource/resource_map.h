#pragma once

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/variant/typed_dictionary.hpp>

namespace godot
{
    class DirectionalResource;

    class ResourceMap : public Resource
    {
        GDCLASS(ResourceMap, Resource)

    private:
        TypedDictionary<StringName, Ref<DirectionalResource>> states;

    protected:
        static void _bind_methods();

    public:
        void set_states(const TypedDictionary<StringName, Ref<DirectionalResource>> &states) noexcept;
        [[nodiscard]] TypedDictionary<StringName, Ref<DirectionalResource>> get_states() const noexcept;
        [[nodiscard]] Ref<DirectionalResource> get_resource_for_state(const StringName &state) const noexcept;
    };
}
#pragma once

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/variant/typed_dictionary.hpp>

namespace resource
{
    class DirectionalResource;

    // Local aliases used multiple times in this header
    using StringName = godot::StringName;
    template <class T>
    using Ref = godot::Ref<T>;
    using StatesDict = godot::TypedDictionary<StringName, Ref<DirectionalResource>>;

    class ResourceMap : public godot::Resource
    {
        GDCLASS(ResourceMap, godot::Resource)

    private:
        StatesDict states;

    protected:
        static void _bind_methods();

    public:
        void set_states(const StatesDict &states) noexcept;
        [[nodiscard]] StatesDict get_states() const noexcept;
        [[nodiscard]] Ref<DirectionalResource> get_resource_for_state(const StringName &state) const noexcept;
    };
}

#include "resource_map.h"
#include "directional_resource.h"

namespace resource
{
    void ResourceMap::set_states(const StatesDict &states) noexcept
    {
        if (&states == &this->states)
            return;
        this->states = states;
    }

    StatesDict ResourceMap::get_states() const noexcept
    {
        return states;
    }

    Ref<DirectionalResource> ResourceMap::get_resource_for_state(const StringName &state) const noexcept
    {
        static const Ref<DirectionalResource> empty;
        return states.get(state, empty);
    }

    void ResourceMap::_bind_methods()
    {
        godot::ClassDB::bind_method(godot::D_METHOD("set_states", "states"), &ResourceMap::set_states);
        godot::ClassDB::bind_method(godot::D_METHOD("get_states"), &ResourceMap::get_states);

        ADD_PROPERTY(
            godot::PropertyInfo(
                godot::Variant::DICTIONARY,
                "states",
                godot::PROPERTY_HINT_DICTIONARY_TYPE,
                vformat("%s:;%s/%s:%s", godot::Variant::STRING_NAME, godot::Variant::OBJECT, godot::PROPERTY_HINT_RESOURCE_TYPE, "DirectionalResource")),
            "set_states",
            "get_states");
    }
}

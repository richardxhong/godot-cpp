#include "resource_map.h"
#include "directional_resource.h"

namespace godot
{
    void ResourceMap::set_states(const TypedDictionary<StringName, Ref<DirectionalResource>> &states) noexcept
    {
        if (&states == &this->states)
            return;
        this->states = states;
    }

    TypedDictionary<StringName, Ref<DirectionalResource>> ResourceMap::get_states() const noexcept
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
        ClassDB::bind_method(D_METHOD("set_states", "states"), &ResourceMap::set_states);
        ClassDB::bind_method(D_METHOD("get_states"), &ResourceMap::get_states);

        ADD_PROPERTY(
            PropertyInfo(
                Variant::DICTIONARY,
                "states",
                PROPERTY_HINT_DICTIONARY_TYPE,
                vformat("%s:;%s/%s:%s", Variant::STRING_NAME, Variant::OBJECT, PROPERTY_HINT_RESOURCE_TYPE, "DirectionalResource")),
            "set_states",
            "get_states");
    }
}
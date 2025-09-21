#include "directional_resource.h"

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/core/error_macros.hpp>

namespace resource
{
    template <class T>
    using Ref = godot::Ref<T>;
    using Resource = godot::Resource;
    void DirectionalResource::validate_index(int index) const
    {
        ERR_FAIL_INDEX_EDMSG(index, static_cast<int>(assets.size()), "DirectionalResource: index out of range.");
    }

    void DirectionalResource::set_asset(int index, const Ref<Resource> &asset)
    {
        validate_index(index);
        if (assets[index] == asset)
            return;
        assets[index] = asset;
        emit_changed();
    }

    Ref<Resource> DirectionalResource::get_asset(int index) const
    {
        validate_index(index);
        return assets[index];
    }

    Ref<Resource> DirectionalResource::get_best_asset_for(common::Direction dir, bool &flip_h) const
    {
        static const Ref<Resource> empty;
        flip_h = false;
        const int idx = static_cast<int>(dir);
        if (dir == common::Direction::COUNT || idx < 0 || idx >= static_cast<int>(assets.size()))
            return empty;

        Ref<Resource> a = assets[idx];
        if (a.is_valid())
            return a;

        if (idx % 4 == 0)
            return empty;

        a = assets[8 - idx];
        if (a.is_valid())
        {
            flip_h = true;
            return a;
        }
        constexpr int SE = static_cast<int>(common::Direction::SOUTH_EAST);
        constexpr int SW = static_cast<int>(common::Direction::SOUTH_WEST);

        if (dir == common::Direction::EAST)
        {
            a = assets[SE];
            if (a.is_valid())
                return a;
            a = assets[SW];
            if (a.is_valid())
            {
                flip_h = true;
                return a;
            }
        }

        if (dir == common::Direction::WEST)
        {
            a = assets[SW];
            if (a.is_valid())
                return a;
            a = assets[SE];
            if (a.is_valid())
            {
                flip_h = true;
                return a;
            }
        }
        return empty;
    }

    void DirectionalResource::_bind_methods()
    {
        godot::ClassDB::bind_method(godot::D_METHOD("set_asset", "index", "resource"), &DirectionalResource::set_asset);
        godot::ClassDB::bind_method(godot::D_METHOD("get_asset", "index"), &DirectionalResource::get_asset);

        ADD_GROUP("Directional Assets", "");

        for (std::size_t i = 0; i < common::direction_count; ++i)
        {
            const godot::StringName name = common::direction_name(static_cast<common::Direction>(i));
            godot::PropertyInfo pi(godot::Variant::OBJECT, name, godot::PROPERTY_HINT_RESOURCE_TYPE, "Resource");
            ADD_PROPERTYI(pi, "set_asset", "get_asset", static_cast<int>(i));
        }
    }
}

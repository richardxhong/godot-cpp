#include "directional_renderer.h"

#include <type_traits>

#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/sprite_frames.hpp>

#include "resource/directional_resource.h"

namespace renderer
{
    using AnimatedSprite2D = godot::AnimatedSprite2D;
    template <class T>
    using Ref = godot::Ref<T>;
    using Resource = godot::Resource;
    template <class ChildT>
    void NodeApplyPolicy<ChildT>::ensure(Child *&child, godot::Node *owner) noexcept
    {
        if (!child)
        {
            child = memnew(Child);
            child->set_visible(false);
            owner->add_child(child);
        }
    }

    template <class ChildT>
    bool NodeApplyPolicy<ChildT>::apply(Child *, const Ref<Resource> &)
    {
        return false;
    }

    template <>
    bool NodeApplyPolicy<AnimatedSprite2D>::apply(AnimatedSprite2D *child, const Ref<Resource> &res)
    {
        Ref<godot::SpriteFrames> frames = res;
        if (!frames.is_valid())
            return false;

        if (child->get_sprite_frames() != frames)
        {
            child->set_sprite_frames(frames);
            child->play();
        }

        child->set_visible(true);
        return true;
    }

    template <class Policy>
    void DirectionalRenderer<Policy>::_ready()
    {
        Policy::ensure(child, this);
        render();
    }

    template <class Policy>
    void DirectionalRenderer<Policy>::set_resources(const godot::Ref<resource::ResourceMap> &resources) noexcept
    {
        this->resources = resources;
    }

    template <class Policy>
    godot::Ref<resource::ResourceMap> DirectionalRenderer<Policy>::get_resources() const noexcept
    {
        return resources;
    }

    template <class Policy>
    void DirectionalRenderer<Policy>::set_state(const godot::StringName &state) noexcept
    {
        if (state == this->state)
            return;

        this->state = state;
        render();
    }

    template <class Policy>
    void DirectionalRenderer<Policy>::set_direction(const common::Direction &direction) noexcept
    {
        if (direction == this->direction)
            return;

        this->direction = direction;
        render();
    }

    template <class Policy>
    void DirectionalRenderer<Policy>::_bind_methods() {}

    template <class Policy>
    void DirectionalRenderer<Policy>::render()
    {
        if (!resources.is_valid())
            return;

        godot::Ref<resource::DirectionalResource> dr = resources->get_resource_for_state(state);
        if (!dr.is_valid())
            return;

        bool flip_h = false;
        Ref<Resource> asset = dr->get_best_asset_for(direction, flip_h);
        if (!asset.is_valid())
            return;

        if (!Policy::apply(child, asset))
            return;

        if constexpr (std::is_same_v<typename Policy::Child, AnimatedSprite2D>)
        {
            if (child->is_flipped_h() != flip_h)
                child->set_flip_h(flip_h);
        }
    }

    void DirectionalAnimatedSpriteRenderer::_bind_methods()
    {
        godot::ClassDB::bind_method(godot::D_METHOD("get_resources"), &DirectionalAnimatedSpriteRenderer::get_resources);
        godot::ClassDB::bind_method(godot::D_METHOD("set_resources", "resources"), &DirectionalAnimatedSpriteRenderer::set_resources);

        ADD_PROPERTY(godot::PropertyInfo(godot::Variant::OBJECT, "resources", godot::PROPERTY_HINT_RESOURCE_TYPE, "ResourceMap"), "set_resources", "get_resources");
    }

    void DirectionalAnimatedSpriteRenderer::_ready()
    {
        DirectionalRenderer<AnimatedSprite2DPolicy>::_ready();
    }

    void DirectionalAnimatedSpriteRenderer::set_resources(const godot::Ref<resource::ResourceMap> &res) noexcept
    {
        DirectionalRenderer<AnimatedSprite2DPolicy>::set_resources(res);
    }

    godot::Ref<resource::ResourceMap> DirectionalAnimatedSpriteRenderer::get_resources() const noexcept
    {
        return DirectionalRenderer<AnimatedSprite2DPolicy>::get_resources();
    }

    template class DirectionalRenderer<AnimatedSprite2DPolicy>;
}

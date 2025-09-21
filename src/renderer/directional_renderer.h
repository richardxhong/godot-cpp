#pragma once

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/resource.hpp>

#include "resource/resource_map.h"
#include "common/direction.h"

namespace renderer
{
    // Local aliases for frequently used Godot types in this module
    using Node2D = godot::Node2D;
    using AnimatedSprite2D = godot::AnimatedSprite2D;
    template <class T>
    using Ref = godot::Ref<T>;
    using Resource = godot::Resource;
    using StringName = godot::StringName;
    template <class ChildT>
    struct NodeApplyPolicy
    {
        using Child = ChildT;

        static void ensure(Child *&child, godot::Node *owner) noexcept;
        static bool apply(Child *child, const Ref<Resource> &res);
    };

    using AnimatedSprite2DPolicy = NodeApplyPolicy<AnimatedSprite2D>;

    template <class Policy>
    class DirectionalRenderer : public Node2D
    {

    private:
        Ref<resource::ResourceMap> resources;
        StringName state = StringName("idle");
        common::Direction direction = common::Direction::SOUTH;
        typename Policy::Child *child = nullptr;

        void render();

    protected:
        static void _bind_methods();

    public:
        void _ready() override;
        void set_resources(const Ref<resource::ResourceMap> &res) noexcept;
        [[nodiscard]] Ref<resource::ResourceMap> get_resources() const noexcept;

        void set_state(const StringName &state) noexcept;
        void set_direction(const common::Direction &direction) noexcept;
    };

    class DirectionalAnimatedSpriteRenderer : public DirectionalRenderer<AnimatedSprite2DPolicy>
    {
        GDCLASS(DirectionalAnimatedSpriteRenderer, godot::Node2D)

    protected:
        static void _bind_methods();

    public:
        void _ready() override;
        void set_resources(const Ref<resource::ResourceMap> &res) noexcept;
        [[nodiscard]] Ref<resource::ResourceMap> get_resources() const noexcept;
    };
}

#pragma once

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/resource.hpp>

#include "resource/resource_map.h"
#include "common/direction.h"

namespace godot
{
    template <class ChildT>
    struct NodeApplyPolicy
    {
        using Child = ChildT;

        static void ensure(Child *&child, Node *owner) noexcept;
        static bool apply(Child *child, const Ref<Resource> &res);
    };

    using AnimatedSprite2DPolicy = NodeApplyPolicy<AnimatedSprite2D>;

    template <class Policy>
    class DirectionalRenderer : public Node2D
    {

    private:
        Ref<ResourceMap> resources;
        StringName state = StringName("idle");
        Direction direction = Direction::SOUTH;
        typename Policy::Child *child = nullptr;

        void render();

    protected:
        static void _bind_methods();

    public:
        void _ready() override;
        void set_resources(const Ref<ResourceMap> &res) noexcept;
        [[nodiscard]] Ref<ResourceMap> get_resources() const noexcept;

        void set_state(const StringName &state) noexcept;
        void set_direction(const Direction &direction) noexcept;
    };

    class DirectionalAnimatedSpriteRenderer : public DirectionalRenderer<AnimatedSprite2DPolicy>
    {
        GDCLASS(DirectionalAnimatedSpriteRenderer, Node2D)

    protected:
        static void _bind_methods();

    public:
        void _ready() override;
        void set_resources(const Ref<ResourceMap> &res) noexcept;
        [[nodiscard]] Ref<ResourceMap> get_resources() const noexcept;
    };
}
#include <register_types.h>
#include "example/logger_node.h"
#include "player/player.h"
#include "resource/directional_resource.h"
#include "resource/resource_map.h"
#include "renderer/directional_renderer.h"

namespace godot
{
    void init(const ModuleInitializationLevel level)
    {
        if (level != MODULE_INITIALIZATION_LEVEL_SCENE)
            return;

        GDREGISTER_CLASS(resource::DirectionalResource)
        GDREGISTER_CLASS(resource::ResourceMap);
        GDREGISTER_CLASS(renderer::DirectionalAnimatedSpriteRenderer)

        GDREGISTER_RUNTIME_CLASS(example::LoggerNode);
        GDREGISTER_RUNTIME_CLASS(player::Player);
    }

    void uninit(const ModuleInitializationLevel level)
    {
        if (level != MODULE_INITIALIZATION_LEVEL_SCENE)
            return;
    }

    extern "C"
    {
        GDExtensionBool GDE_EXPORT init(GDExtensionInterfaceGetProcAddress gde_get_proc_addr, GDExtensionClassLibraryPtr p_lib, GDExtensionInitialization *r_init)
        {
            const godot::GDExtensionBinding::InitObject init_obj(gde_get_proc_addr, p_lib, r_init);

            init_obj.register_initializer(init);
            init_obj.register_terminator(uninit);
            init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

            return init_obj.init();
        }
    }
}
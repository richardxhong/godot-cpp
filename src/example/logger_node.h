#pragma once

#include <godot_cpp/classes/node.hpp>

namespace example
{
    class LoggerNode : public godot::Node
    {
        GDCLASS(LoggerNode, godot::Node)
        double time;
        double frequency;

    protected:
        static void _bind_methods();

    public:
        LoggerNode();

        void _process(double delta) override;

        void set_frequency(double f) { frequency = f; }
        double get_frequency() const { return frequency; }
    };
}

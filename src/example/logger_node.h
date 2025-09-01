#pragma once

#include <godot_cpp/classes/node.hpp>

namespace godot
{
    class LoggerNode : public Node
    {
        GDCLASS(LoggerNode, Node)
        double time;
        double frequency;

    protected:
        static void _bind_methods();

    public:
        LoggerNode();
        ~LoggerNode();

        void _process(double delta);

        void set_frequency(double f) { frequency = f; }
        double get_frequency() const { return frequency; }
    };
}

#include "logger_node.h"

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <cmath>

namespace example
{
    LoggerNode::LoggerNode() : time(0.0), frequency(1.0) {}

    void LoggerNode::_bind_methods()
    {
        godot::ClassDB::bind_method(godot::D_METHOD("set_frequency"), &LoggerNode::set_frequency);
        godot::ClassDB::bind_method(godot::D_METHOD("get_frequency"), &LoggerNode::get_frequency);
        ADD_PROPERTY(godot::PropertyInfo(godot::Variant::FLOAT, "frequency"), "set_frequency", "get_frequency");
    }

    void LoggerNode::_process(double delta)
    {
        time += delta;
        if (time > frequency)
        {
            godot::UtilityFunctions::print(godot::String("some time has passed..."));
        }
        time = std::fmod(time, frequency);
    }
}

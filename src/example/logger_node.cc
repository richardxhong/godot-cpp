#include "logger_node.h"

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <cmath>

namespace godot
{
    LoggerNode::LoggerNode() : time(0.0), frequency(1.0) {}
    LoggerNode::~LoggerNode() = default;

    void LoggerNode::_bind_methods()
    {
        ClassDB::bind_method(D_METHOD("set_frequency"), &LoggerNode::set_frequency);
        ClassDB::bind_method(D_METHOD("get_frequency"), &LoggerNode::get_frequency);
        ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "frequency"), "set_frequency", "get_frequency");
    }

    void LoggerNode::_process(double delta)
    {
        time += delta;
        if (time > frequency)
        {
            UtilityFunctions::print(String("some time has passed..."));
        }
        time = std::fmod(time, frequency);
    }
}
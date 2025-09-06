#pragma once
#include <godot_cpp/variant/string_name.hpp>

#ifndef SNAME
#define SNAME(lit) ([]() -> const godot::StringName & { static const godot::StringName s(lit);return s; }())
#endif
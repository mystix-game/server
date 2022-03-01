#include "inputs.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include <godot_cpp/classes/character_body3d.hpp>



using namespace godot;

void Inputs::_bind_methods()
{

    //gdscript @export equivalent
    ClassDB::bind_method(D_METHOD("get_motion"), &Inputs::get_motion);
    ClassDB::bind_method(D_METHOD("set_motion", "motion"),  &Inputs::set_motion);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "motion"), "set_motion", "get_motion");

    ClassDB::bind_method(D_METHOD("get_mouse_motion"), &Inputs::get_mouse_motion);
    ClassDB::bind_method(D_METHOD("set_mouse_motion", "mouse_motion"),  &Inputs::set_mouse_motion);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, "mouse_motion"), "set_mouse_motion", "get_mouse_motion");

    ClassDB::bind_method(D_METHOD("get_jump"), &Inputs::get_jump);
    ClassDB::bind_method(D_METHOD("set_jump", "jump"),  &Inputs::set_jump);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "jump"), "set_jump", "get_jump");

    ClassDB::bind_method(D_METHOD("get_shoot"), &Inputs::get_jump);
    ClassDB::bind_method(D_METHOD("set_shoot", "shoot"),  &Inputs::set_shoot);
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "shoot"), "set_shoot", "get_shoot");

}

Inputs::Inputs() {
    //UtilityFunctions::print("inputs constructor");

    //TODO convert that godot::string to int
    //StringName player_name = get_parent()->get_name();
    //int id = String::to_int(player_name);
    //set_multiplayer_authority(id);
}

Inputs::~Inputs() {
    //UtilityFunctions::print("inputs destructor");
}

Vector2 Inputs::get_motion() { return motion; }
void Inputs::set_motion(Vector2 _motion) { motion = _motion; }

Vector2 Inputs::get_mouse_motion() { return mouse_motion; }
void Inputs::set_mouse_motion(Vector2 _mouse_motion) { mouse_motion = _mouse_motion; }

bool Inputs::get_jump() { return jump; }
void Inputs::set_jump(bool _jump) { jump = _jump; }

bool Inputs::get_shoot() { return shoot; }
void Inputs::set_shoot(bool _shoot) { shoot = _shoot; }
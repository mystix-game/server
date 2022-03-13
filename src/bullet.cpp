#include "bullet.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void Bullet::_bind_methods()
{
    //ClassDB::bind_method(D_METHOD("_ready"), &Player::_ready);
    ClassDB::bind_method(D_METHOD("_pysics_process"), &Bullet::_physics_process);

    ClassDB::bind_method(D_METHOD("on_body_entered"), &Bullet::on_body_entered);

    //gdscript @export equivalent
    ClassDB::bind_method(D_METHOD("get_position"), &Bullet::get_position);
    ClassDB::bind_method(D_METHOD("set_position", "position"),  &Bullet::set_position);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "position"), "set_position", "get_position");

}

Bullet::Bullet() {
    //UtilityFunctions::print("player constructor");
    //Vector3(randi_range(-3,3), 5, randi_range(-3,3))
    set_position(Vector3(0,10,0));
}

Bullet::~Bullet() {
    //UtilityFunctions::print("player destructor");
}

void Bullet::_ready() {
    UtilityFunctions::print("bullet_ready()");
}

void Bullet::_physics_process(float delta) {

}

void Bullet::on_body_entered() {

}

Vector3 Bullet::get_position() { return position; }
void Bullet::set_position(Vector3 _position) { position = _position; }
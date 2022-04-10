#include "bullet.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void Bullet::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("_pysics_process"), &Bullet::_physics_process);

    ClassDB::bind_method(D_METHOD("on_body_entered"), &Bullet::on_body_entered);

    //gdscript @export equivalent
    ClassDB::bind_method(D_METHOD("get_synced_position"), &Bullet::get_synced_position);
    ClassDB::bind_method(D_METHOD("set_synced_position", "synced_position"),  &Bullet::set_synced_position);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "synced_position"), "set_synced_position", "get_synced_position");

    ClassDB::bind_method(D_METHOD("get_from_player"), &Bullet::get_from_player);
    ClassDB::bind_method(D_METHOD("set_from_player", "from_player"),  &Bullet::set_from_player);
}

Bullet::Bullet() {

}

Bullet::~Bullet() {

}

void Bullet::_ready() {
    UtilityFunctions::print("bullet_ready()");

    player_path = "../../Players/" + String::num(from_player) + "/";
    //TODO
    //camera = get_node<Camera3D>(NodePath(player_path + "CameraArm/Camera3D"));
    //crosshair_position = Vector2();
    //ray_from = Vector3();
    //ray_dir = Vector3();

    //old gdscript way
    //@onready var player := get_node("../../Players/" + str(from_player))
    //@onready var camera := player.get_node("CameraArm/Camera3D")
    //@onready var ch_pos : Vector2 = player.get_node("Crosshair").position + player.get_node("Crosshair").size * 0.5
    //@onready var ray_from = player.get_node("Position3D/").global_transform.origin
    //@onready var ray_dir : Vector3 = camera.project_ray_normal(ch_pos)


    UtilityFunctions::print("camera_path: " + player_path + "CameraArm/Camera3D");

    //self.add_collision_exception_with(player)
}

void Bullet::_physics_process(float delta) {
    //Todo

    //Destroy bullet after 5 sec
    time_alive -= delta;
    if (time_alive <= 0) {
        queue_free();
    }

    //Ref<KinematicCollision3D> col = move_and_collide(delta * ray_dir * bullet_velocity);
    //if (col->get_collision_count() > 0) {
    //    UtilityFunctions::print("Collision detected");

        //TODO
        //if (col.get_collider() and col.get_collider().has_method("damage")):
		//    col.collider.damage(damage)
		//$CollisionShape3D.disabled=true

    //    queue_free();
    //}


    set_synced_position(get_position());
        //UtilityFunctions::print("synced_position: ", get_synced_position());
}

void Bullet::on_body_entered() {
    UtilityFunctions::print("Collided with a body");
}

Vector3 Bullet::get_synced_position() { return synced_position; }
void Bullet::set_synced_position(Vector3 _synced_position) { synced_position = _synced_position; }

int Bullet::get_from_player() { return from_player; }
void Bullet::set_from_player(int _from_player) { from_player = _from_player; }

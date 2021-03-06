#include "player.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/position3d.hpp>
#include <string>
#include <inputs.h>

using namespace godot;

void Player::_bind_methods()
{
    //ClassDB::bind_method(D_METHOD("_ready"), &Player::_ready);
    ClassDB::bind_method(D_METHOD("_pysics_process"), &Player::_physics_process);

    ClassDB::bind_method(D_METHOD("damage"), &Player::damage);

    //gdscript @export equivalent
    ClassDB::bind_method(D_METHOD("get_synced_position"), &Player::get_synced_position);
    ClassDB::bind_method(D_METHOD("set_synced_position", "synced_position"),  &Player::set_synced_position);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "synced_position"), "set_synced_position", "get_synced_position");

    ClassDB::bind_method(D_METHOD("get_synced_rotation_y"), &Player::get_synced_rotation_y);
    ClassDB::bind_method(D_METHOD("set_synced_rotation_y", "synced_rotation_y"),  &Player::set_synced_rotation_y);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "synced_rotation_y"), "set_synced_rotation_y", "get_synced_rotation_y");

    ClassDB::bind_method(D_METHOD("get_synced_camera_arm_rotation_x"), &Player::get_synced_camera_arm_rotation_x);
    ClassDB::bind_method(D_METHOD("set_synced_camera_arm_rotation_x", "synced_camera_arm_rotation_x"),  &Player::set_synced_camera_arm_rotation_x);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "synced_camera_arm_rotation_x"), "set_synced_camera_arm_rotation_x", "get_synced_camera_arm_rotation_x");

    ClassDB::bind_method(D_METHOD("get_synced_player_name"), &Player::get_synced_player_name);
    ClassDB::bind_method(D_METHOD("set_synced_player_name", "synced_player_name"),  &Player::set_synced_player_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "synced_player_name"), "set_synced_player_name", "get_synced_player_name");

    ClassDB::bind_method(D_METHOD("get_synced_health"), &Player::get_synced_health);
    ClassDB::bind_method(D_METHOD("set_synced_health", "synced_health"),  &Player::set_synced_health);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "synced_health"), "set_synced_health", "get_synced_health");

    ClassDB::bind_method(D_METHOD("get_synced_mana"), &Player::get_synced_mana);
    ClassDB::bind_method(D_METHOD("set_synced_mana", "synced_mana"),  &Player::set_synced_mana);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "synced_mana"), "set_synced_mana", "get_synced_mana");

}

Player::Player() {
    //UtilityFunctions::print("player constructor");
    //Vector3(randi_range(-3,3), 5, randi_range(-3,3))
    set_position(Vector3(0,10,0));
}

Player::~Player() {
    //UtilityFunctions::print("player destructor");
}

void Player::_ready() {
    UtilityFunctions::print("_ready()");
}

void Player::_physics_process(float delta) {

    SpringArm3D * camera_arm = get_node<SpringArm3D>(NodePath("CameraArm")); //why doesnt this line work in constructor or _ready()??
    Inputs * inputs = get_node<Inputs>(NodePath("Inputs"));

    Vector3 rot = Vector3(inputs->get_mouse_motion().y, inputs->get_mouse_motion().x, 0) * mouse_sensitivity * delta;
    inputs->set_mouse_motion(Vector2());

    //rotation x
    Vector3 arm_rot = camera_arm->get_rotation();
    arm_rot.x = arm_rot.x - rot.x;
    //TODO: $CameraArm.rotation.x = clamp(rotation.x, -90.0, 30.0) #TODO: limit camera rotation up/down, new Vector3.limit_lengthfunction ?
    camera_arm->set_rotation(arm_rot);
    synced_camera_arm_rotation_x = arm_rot.x;
    
    //rotation y
    Vector3 player_rot = get_rotation();
    player_rot.y = player_rot.y - rot.y;
    set_rotation(player_rot);
    synced_rotation_y = player_rot.y;

    // Add the gravity.
    if(is_on_floor() == false)
    {
        Vector3 vel = get_velocity();
        vel.y = vel.y - gravity * delta;
        set_velocity(vel);
    }

    //Handle Jump.
    if (inputs->get_jump() == true && is_on_floor() == true) {
        Vector3 vel = get_velocity();
        vel.y = jump_force;
        set_velocity(vel);
        synced_mana = synced_mana - 10;
        UtilityFunctions::print("synced_mana: ", synced_mana);
    }

    //TODO
    //Handle Shoot
    if (inputs->get_shoot() == true) {
        UtilityFunctions::print("Todo: handle_shoot");
        BulletSpawner *bullets = get_node<BulletSpawner>(NodePath("../../Bullets"));
        
        Dictionary bullet_data;
        bullet_data["synced_position"] = get_node<Position3D>(NodePath("Position3D"))->get_global_transform().origin;
        bullet_data["name"] = String(get_name()).to_int();

        bullets->spawn(bullet_data);
    }
    //if $Inputs.shoot == true:
    //    get_node("../../Bullets").spawn([$"Position3D".global_transform.origin, str(name).to_int()])

    Vector3 dir = (get_global_transform().get_basis() * Vector3(inputs->get_motion().y, 0, inputs->get_motion().x).normalized()).get_euler_xzy();
    //UtilityFunctions::print("direction:", direction);

    if (dir != Vector3()) {
        Vector3 vel = (dir * speed);
        set_velocity(Vector3(vel.x, get_velocity().y, vel.z));
    }
    else {
        Vector3 vel = Vector3(godot::Math::move_toward(get_velocity().x, 0, speed), 0, godot::Math::move_toward(get_velocity().z, 0, speed));
        set_velocity(Vector3(vel.x, get_velocity().y, vel.z));
    }

    move_and_slide();
    synced_position = get_position();
}

void Player::damage(int dmg) {
    synced_health = synced_health - dmg;
    UtilityFunctions::print("Health: ", synced_health);
}

Vector3 Player::get_synced_position() { return synced_position; }
void Player::set_synced_position(Vector3 _synced_position) { synced_position = _synced_position; }

float Player::get_synced_rotation_y() { return synced_rotation_y; }
void Player::set_synced_rotation_y(float _synced_rotation_y) { synced_rotation_y = _synced_rotation_y; }

float Player::get_synced_camera_arm_rotation_x() { return synced_camera_arm_rotation_x; }
void Player::set_synced_camera_arm_rotation_x(float _synced_camera_arm_rotation_x) { synced_camera_arm_rotation_x = _synced_camera_arm_rotation_x; }

String Player::get_synced_player_name() { return synced_player_name; }
void Player::set_synced_player_name(String _synced_player_name) { synced_player_name = _synced_player_name; }

int Player::get_synced_health() { return synced_health; }
void Player::set_synced_health(int _synced_health) { synced_health = _synced_health; }

int Player::get_synced_mana() { return synced_mana; }
void Player::set_synced_mana(int _synced_mana) { synced_mana = _synced_mana; }

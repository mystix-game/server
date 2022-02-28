#include "player.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void Player::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("test_func"), &Player::test_func);

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
    UtilityFunctions::print("player constructor");
}

Player::~Player() {
    UtilityFunctions::print("player destructor");
}

void Player::test_func()
{
    UtilityFunctions::print("player test func called");
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
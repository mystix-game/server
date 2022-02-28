#include "player.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void Player::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("test_func"), &Player::test_func);
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


#include "bullet_spawner.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void BulletSpawner::_bind_methods()
{

}

BulletSpawner::BulletSpawner() {

}

BulletSpawner::~BulletSpawner() {

}

void BulletSpawner::_ready() {
    UtilityFunctions::print("BulletSpawner_ready()");
}

//TODO:
//func _spawn_custom(data : Variant):
//	#if data.size() != 2 or typeof(data[0]) != TYPE_VECTOR3 or typeof(data[1]) != TYPE_INT:
//#		return null
//	var bullet := preload("res://bullet.tscn").instantiate()
//	bullet.position = data[0]
//	bullet.from_player = data[1]
//	return bullet
#include "bullet_spawner.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <bullet.h>

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

Object *BulletSpawner::_spawn_custom(Variant data) {
    UtilityFunctions::print("hello this is bullet spawner");

    ResourceLoader *loader = ResourceLoader::get_singleton();
    Ref<PackedScene> res = loader->load(NodePath("bullet.tscn"));
    if (res == NULL) {
        return nullptr;
    }

    Bullet *bullet = cast_to<Bullet>(res->instantiate());
    bullet->set_position(data.get("synced_position"));
    bullet->set_from_player(data.get("name"));
    bullet->set_multiplayer_authority(int(0));

    return bullet;
}

//TODO:
//func _spawn_custom(data : Variant):
//	#if data.size() != 2 or typeof(data[0]) != TYPE_VECTOR3 or typeof(data[1]) != TYPE_INT:
//#		return null
//	var bullet := preload("res://bullet.tscn").instantiate()
//	bullet.position = data[0]
//	bullet.from_player = data[1]
//	return bullet
#include "register_types.h"

#include <godot/gdnative_interface.h>

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "server.h"
#include "player.h"
#include "inputs.h"
#include "bullet.h"
#include "bullet_spawner.h"

using namespace godot;

void register_cpp_server_types()
{
	ClassDB::register_class<Server>();
	ClassDB::register_class<Player>();
	ClassDB::register_class<Inputs>();
	ClassDB::register_class<Bullet>();
	ClassDB::register_class<BulletSpawner>();
}

void unregister_cpp_server_types() {}

extern "C"
{

	// Initialization.

	GDNativeBool GDN_EXPORT server_library_init(const GDNativeInterface *p_interface, const GDNativeExtensionClassLibraryPtr p_library, GDNativeInitialization *r_initialization)
	{
		godot::GDExtensionBinding::InitObject init_obj(p_interface, p_library, r_initialization);

		init_obj.register_scene_initializer(register_cpp_server_types);
		init_obj.register_scene_terminator(unregister_cpp_server_types);

		return init_obj.init();
	}
}

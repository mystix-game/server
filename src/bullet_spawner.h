#ifndef SERVER_BULLET_SPAWNER_H
#define SERVER_BULLET_SPAWNER_H

#ifdef WIN32
#include <windows.h>
#endif

#include <godot_cpp/classes/multiplayer_spawner.hpp>
#include <godot_cpp/core/binder_common.hpp>
#include <bullet.h>

using namespace godot;

class BulletSpawner : public MultiplayerSpawner
{
    GDCLASS(BulletSpawner, MultiplayerSpawner);

protected:
    static void _bind_methods();

private:
    Vector3 position;

public:

    BulletSpawner();
    ~BulletSpawner();

    void _ready();

    Object *_spawn_custom(Variant data);
};

#endif //SERVER_BULLET_SPAWNER_H

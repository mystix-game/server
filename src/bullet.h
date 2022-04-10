#ifndef SERVER_BULLET_H
#define SERVER_BULLET_H

#ifdef WIN32
#include <windows.h>
#endif

#include <godot_cpp/classes/rigid_dynamic_body3d.hpp>
#include <godot_cpp/core/binder_common.hpp>

using namespace godot;

class Bullet : public RigidDynamicBody3D
{
    GDCLASS(Bullet, RigidDynamicBody3D);

protected:
    static void _bind_methods();

private:
    Vector3 synced_position;
    int from_player;

public:

    Bullet();
    ~Bullet();

    void _ready();
    void _physics_process(float delta);

    void on_body_entered();

    Vector3 get_synced_position();
    void set_synced_position(Vector3 _synced_position);

    int get_from_player();
    void set_from_player(int _from_player);
};

#endif //SERVER_BULLET_H

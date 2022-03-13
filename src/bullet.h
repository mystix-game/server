#ifndef SERVER_BULLET_H
#define SERVER_BULLET_H

#ifdef WIN32
#include <windows.h>
#endif

#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/core/binder_common.hpp>
#include <godot_cpp/classes/spring_arm3d.hpp>
#include <godot_cpp/classes/node.hpp>

using namespace godot;

class Bullet : public CharacterBody3D
{
    GDCLASS(Bullet, CharacterBody3D);

protected:
    static void _bind_methods();

private:
    Vector3 position;

public:

    Bullet();
    ~Bullet();

    void _ready();
    void _physics_process(float delta);

    void on_body_entered();

    Vector3 get_position();
    void set_position(Vector3 _position);

};

#endif //SERVER_PLAYER_H

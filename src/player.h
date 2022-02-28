#ifndef SERVER_PLAYER_H
#define SERVER_PLAYER_H

#ifdef WIN32
#include <windows.h>
#endif

#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/core/binder_common.hpp>

using namespace godot;

class Player : public CharacterBody3D
{
    GDCLASS(Player, CharacterBody3D);

protected:
    static void _bind_methods();

private:
    Vector3 synced_position;
    float synced_rotation_y;
    float synced_camera_arm_rotation_x;
    String synced_player_name;
    int synced_health = 100;
    int synced_mana = 100;
public:

    Player();
    ~Player();

    void _init(); // our initializer called by Godot
    void _physics_process(float delta);

    Vector3 get_synced_position();
    void set_synced_position(Vector3);

    float get_synced_rotation_y();
    void set_synced_rotation_y(float);

    float get_synced_camera_arm_rotation_x();
    void set_synced_camera_arm_rotation_x(float);

    String get_synced_player_name();
    void set_synced_player_name(String);

    int get_synced_health();
    void set_synced_health(int);

    int get_synced_mana();
    void set_synced_mana(int);

};

#endif //SERVER_PLAYER_H

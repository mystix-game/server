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
public:
    void test_func();

    Player();
    ~Player();
};


#endif //SERVER_PLAYER_H

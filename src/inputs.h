#ifndef SERVER_INPUTS_H
#define SERVER_INPUTS_H

#ifdef WIN32
#include <windows.h>
#endif
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/binder_common.hpp>

using namespace godot;

class Inputs : public Node
{
    GDCLASS(Inputs, Node);

protected:
    static void _bind_methods();

private:
    Vector2 motion;
    Vector2 mouse_motion;
    bool jump;
    bool shoot;
public:

    Inputs();
    ~Inputs();

    Vector2 get_motion();
    void set_motion(Vector2);

    Vector2 get_mouse_motion();
    void set_mouse_motion(Vector2);

    bool get_jump();
    void set_jump(bool);

    bool get_shoot();
    void set_shoot(bool);

};

#endif //SERVER_INPUTS_H

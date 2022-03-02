#ifndef SERVER_CLASS_H
#define SERVER_CLASS_H

// We don't need windows.h in this plugin but many others do and it throws up on itself all the time
// So best to include it and make sure CI warns us when we use something Microsoft took for their own goals....
#ifdef WIN32
#include <windows.h>
#endif

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/multiplayer_api.hpp>

#include <godot_cpp/core/binder_common.hpp>

using namespace godot;

class Server : public Node
{
    GDCLASS(Server, Node);

protected:
    static void _bind_methods();

private:
    int port = 4242;
    String world_path = "world.tscn";
    String player_path = "player.tscn";
public:

    Server();
    ~Server();

    void start_server();
    void player_connected(int id);
    void player_disconnected(int id);
    void spawn_player(int id);
    void load_world();

    int get_port();
    void set_port(int);

    String get_world_path();
    void set_world_path(String);

    String get_player_path();
    void set_player_path(String);
};

#endif // ! SERVER_CLASS_H

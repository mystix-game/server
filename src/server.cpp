#include "server.h"

#include <godot_cpp/core/class_db.hpp>

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/e_net_multiplayer_peer.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void Server::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("test_func"), &Server::test_func);
    ClassDB::bind_method(D_METHOD("start_server"), &Server::start_server);
    ClassDB::bind_method(D_METHOD("player_connected"), &Server::player_connected);
}

Server::Server()
{
    UtilityFunctions::print("constructor");
}

Server::~Server()
{
    UtilityFunctions::print("destructor");
}

void Server::start_server()
{
    // TODO
    int port = 4242;
    UtilityFunctions::print("starting server");

    ENetMultiplayerPeer *peer = new ENetMultiplayerPeer();
    UtilityFunctions::print("test1");

    Ref<MultiplayerAPI> multiplayer = get_multiplayer();
    CRASH_COND(multiplayer.is_null());

    multiplayer->connect("peer_connected", Callable(this, "player_connected"));


    UtilityFunctions::print("test2");
//    peer->create_server(port);
//    mulltiplayer->set_multiplayer_peer(peer);
//    UtilityFunctions::print(get_multiplayer()->is_server());
 
}

void Server::player_connected(int id)
{
    UtilityFunctions::print("player connected" + id);
}

void Server::test_func()
{
    UtilityFunctions::print("test func called");
}

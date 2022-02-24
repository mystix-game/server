#include "server.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/e_net_multiplayer_peer.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <player.h>

using namespace godot;

void Server::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("test_func"), &Server::test_func);
    ClassDB::bind_method(D_METHOD("start_server"), &Server::start_server);
    ClassDB::bind_method(D_METHOD("player_connected"), &Server::player_connected);
}

Server::Server()
{
    UtilityFunctions::print("server constructor");
}

Server::~Server()
{
    UtilityFunctions::print("server destructor");
}

void Server::start_server(int port)
{
    auto *peer = new ENetMultiplayerPeer();
    Ref<MultiplayerAPI> multiplayer = get_multiplayer();
    CRASH_COND(multiplayer.is_null());
    multiplayer->connect("peer_connected", Callable(this, "player_connected"));
    peer->create_server(port);
    multiplayer->set_multiplayer_peer(peer);
}

void Server::player_connected(int id) {
    UtilityFunctions::print("player connected: ", id);
    auto *player = new Player();
    player->test_func();
}

void Server::test_func()
{
    UtilityFunctions::print("server test func called");
}

#include "server.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/e_net_multiplayer_peer.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <player.h>
#include <string>


using namespace godot;

void Server::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("test_func"), &Server::test_func);
    ClassDB::bind_method(D_METHOD("start_server"), &Server::start_server);
    ClassDB::bind_method(D_METHOD("player_connected"), &Server::player_connected);
    ClassDB::bind_method(D_METHOD("player_disconnected"), &Server::player_disconnected);
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
    multiplayer->connect("peer_disconnected", Callable(this, "player_disconnected"));
    peer->create_server(port);
    multiplayer->set_multiplayer_peer(peer);
}

void Server::player_connected(int id) {
    UtilityFunctions::print("player connected: ", id);
    //TODO load player from scene instead of player.cpp and add player c++ script to it
    //Resource res = ResourceLoader::get_singleton->load("player.tscn");
    //Node3D *player = res->instantiate();

    CharacterBody3D *player = new Player();
    player->set_name(String::num(id));
    
    NodePath PlayersNodePath = "Players";
    Node *players = get_node_internal(PlayersNodePath);

    players->add_child(player);
}

void Server::player_disconnected(int id) {
     UtilityFunctions::print("player disconnected: ", id);
     //TODO convert that gdscript: $Players.get_node(str(id)).queue_free()
}

void Server::test_func()
{
    UtilityFunctions::print("server test func called");
}

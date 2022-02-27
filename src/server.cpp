#include "server.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/e_net_multiplayer_peer.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
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
    CharacterBody3D *player = new Player();
    player->set_name(String::num(id));
    
    NodePath PlayersNodePath = "Players";
    Node *players = get_node_internal(PlayersNodePath);
   
    //Todo create a player scene with characterbody3d and meshinstance and collisionshape etc in editor and then instance and add that instead of this player class to Server/Players
    //Also add cpp script to that characterbody3d somehow

    //outside of this func do:
    //const Player := preload("res://Player.tscn")
    //var port := 4242

    //Then convert following gdscript:
    //var p := Player.instantiate()
	//p.synced_player_name = "Player " + str(id)
	//p.position = Vector3(randi_range(-3,3), 5, randi_range(-3,3))
	//p.name = str(id)
	//$Players.add_child(p) #Could probably do it via spawn func?

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

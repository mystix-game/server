#include "server.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/e_net_multiplayer_peer.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/multiplayer_spawner.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <string>

using namespace godot;

void Server::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("start_server"), &Server::start_server);
    ClassDB::bind_method(D_METHOD("player_connected"), &Server::player_connected);
    ClassDB::bind_method(D_METHOD("player_disconnected"), &Server::player_disconnected);
    ClassDB::bind_method(D_METHOD("spawn_player"), &Server::spawn_player);
    ClassDB::bind_method(D_METHOD("load_world"), &Server::load_world);

    ClassDB::bind_method(D_METHOD("get_port"), &Server::get_port);
    ClassDB::bind_method(D_METHOD("set_port", "port"),  &Server::set_port);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "port"), "set_port", "get_port");

    ClassDB::bind_method(D_METHOD("get_world_path"), &Server::get_world_path);
    ClassDB::bind_method(D_METHOD("set_world_path", "world_path"),  &Server::set_world_path);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "world_path", PROPERTY_HINT_FILE, "*.tscn"), "set_world_path", "get_world_path");

    ClassDB::bind_method(D_METHOD("get_player_path"), &Server::get_player_path);
    ClassDB::bind_method(D_METHOD("set_player_path", "player_path"),  &Server::set_player_path);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "player_path", PROPERTY_HINT_FILE, "*.tscn"), "set_player_path", "get_player_path");

}

Server::Server()
{
    //UtilityFunctions::print("server constructor");
}

Server::~Server()
{
    //UtilityFunctions::print("server destructor");
}

void Server::start_server()
{
    UtilityFunctions::print("starting server");
    auto *peer = new ENetMultiplayerPeer();

    //TODO here comes the first error: "_instance_bindings != nullptr" is true
    // in /core/object/object.cpp   -->   https://github.com/godotengine/godot/blob/3f69ea4f3bcb4f234f6e62909a79bdee221608a9/core/object/object.cpp#L1776
   
    Ref<MultiplayerAPI> multiplayer = get_multiplayer();
    //multiplayer.instantiate();
    //multiplayer->reference();
    
    CRASH_COND(multiplayer.is_null());
    multiplayer->connect("peer_connected", Callable(this, "player_connected"));
    multiplayer->connect("peer_disconnected", Callable(this, "player_disconnected"));
    peer->create_server(port);
    multiplayer->set_multiplayer_peer(peer);

    //TODO in load world come the next 3 same errors.. but its kinda working
    load_world();
}

void Server::player_connected(int id) {
    UtilityFunctions::print("player connected: ", id);
    spawn_player(id);
}

void Server::player_disconnected(int id) {
    UtilityFunctions::print("player disconnected: ", id);
    UtilityFunctions::print("free player: ", id);
    Node * node = get_node_internal(NodePath("Players/" + String::num(id)));
    node->queue_free();
}

void Server::spawn_player(int id)
{
    UtilityFunctions::print("spawn player: ", id);
    Node * node = get_node_internal(NodePath("Players"));
    if(node != NULL) {
        MultiplayerSpawner * players = cast_to<MultiplayerSpawner>(node);
        ResourceLoader* relo = ResourceLoader::get_singleton();
        Ref<PackedScene> res = relo->load(player_path);
        if (res !=NULL) {
            Node * player = res->instantiate();
            player->set_name(String::num(id));
            //Set authority to server fo Player
            player->set_multiplayer_authority(int(0));
            //Set authority to client for Inputs
            player->get_node_internal(NodePath("Inputs"))->set_multiplayer_authority(id);
            players->add_child(player);
        }
        else{
            UtilityFunctions::print(player_path, " not found");
        }
    }
    else{
        UtilityFunctions::print("Players node not found");
    }
}

void Server::load_world()
{
    UtilityFunctions::print("loading world");
    ResourceLoader* relo = ResourceLoader::get_singleton();
    Ref<PackedScene> res = relo->load(world_path);
    if (res !=NULL) {
        Node * world = res->instantiate();
        add_child(world);
    }
    else{
        UtilityFunctions::print(world_path, " not found");
    }
}

int Server::get_port() { return port; }
void Server::set_port(int _port) { port = _port; }

String Server::get_world_path() { return world_path; }
void Server::set_world_path(String _world_path) { world_path = _world_path; }

String Server::get_player_path() { return player_path; }
void Server::set_player_path(String _player_path) { player_path = _player_path; }
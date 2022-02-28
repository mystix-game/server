#include "server.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/e_net_multiplayer_peer.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/multiplayer_spawner.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
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
    //UtilityFunctions::print("server constructor");
}

Server::~Server()
{
    //UtilityFunctions::print("server destructor");
}

void Server::start_server(int port)
{
    UtilityFunctions::print("starting server");
    auto *peer = new ENetMultiplayerPeer();
    Ref<MultiplayerAPI> multiplayer = get_multiplayer();
    CRASH_COND(multiplayer.is_null());
    multiplayer->connect("peer_connected", Callable(this, "player_connected"));
    multiplayer->connect("peer_disconnected", Callable(this, "player_disconnected"));
    peer->create_server(port);
    multiplayer->set_multiplayer_peer(peer);
    load_world();
}

void Server::player_connected(int id) {
    UtilityFunctions::print("player connected: ", id);
    spawn_player(id);
}

void Server::player_disconnected(int id) {
    UtilityFunctions::print("player disconnected: ", id);
    Node * node = get_node_internal(NodePath("Players/" + String::num(id)));
    node->queue_free();
}

void Server::spawn_player(int id)
{
    //TODO variable wia player_scene und player_path wia @export  variable im gdscript mache, dassma im editor bearbeita kann
    //TODO add player c++ script to player_scene??
    //dfrog isch eifach no wia ma position ageh kann und zwar so dasses initial dia position het und nid erst no vu 0,0,0 det heraspickt 

    UtilityFunctions::print("spawn player: ", id);
    Node * node = get_node_internal(NodePath("Players"));
    if(node != NULL) {
        MultiplayerSpawner * players = cast_to<MultiplayerSpawner>(node);
        ResourceLoader* relo = ResourceLoader::get_singleton();
        String player_path = "player.tscn";
        Ref<PackedScene> res = relo->load(player_path);
        if (res !=NULL) {
            Node * player_scene = res->instantiate();
            player_scene->set_name(String::num(id));
            players->add_child(player_scene);
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
    String world_path = "world.tscn";
        Ref<PackedScene> res = relo->load(world_path);
        if (res !=NULL) {
            Node * world_scene = res->instantiate();
            add_child(world_scene);
        }
        else{
            UtilityFunctions::print(world_path, " not found");
        }
}

void Server::test_func()
{
    UtilityFunctions::print("server test func called");
}

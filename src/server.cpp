#include "server.h"

#include <godot_cpp/core/class_db.hpp>

#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void Server::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("test_func"), &Server::test_func);
}

Server::Server()
{
    UtilityFunctions::print("constructor");
}

Server::~Server()
{
    UtilityFunctions::print("destructor");
}

void Server::test_func()
{
    UtilityFunctions::print("test func called");
}

#include "player.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
//#include <string>
#include <inputs.h>


using namespace godot;

void Player::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("_pysics_process"), &Player::_physics_process);

    //gdscript @export equivalent
    ClassDB::bind_method(D_METHOD("get_synced_position"), &Player::get_synced_position);
    ClassDB::bind_method(D_METHOD("set_synced_position", "synced_position"),  &Player::set_synced_position);
    ADD_PROPERTY(PropertyInfo(Variant::VECTOR3, "synced_position"), "set_synced_position", "get_synced_position");

    ClassDB::bind_method(D_METHOD("get_synced_rotation_y"), &Player::get_synced_rotation_y);
    ClassDB::bind_method(D_METHOD("set_synced_rotation_y", "synced_rotation_y"),  &Player::set_synced_rotation_y);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "synced_rotation_y"), "set_synced_rotation_y", "get_synced_rotation_y");

    ClassDB::bind_method(D_METHOD("get_synced_camera_arm_rotation_x"), &Player::get_synced_camera_arm_rotation_x);
    ClassDB::bind_method(D_METHOD("set_synced_camera_arm_rotation_x", "synced_camera_arm_rotation_x"),  &Player::set_synced_camera_arm_rotation_x);
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "synced_camera_arm_rotation_x"), "set_synced_camera_arm_rotation_x", "get_synced_camera_arm_rotation_x");

    ClassDB::bind_method(D_METHOD("get_synced_player_name"), &Player::get_synced_player_name);
    ClassDB::bind_method(D_METHOD("set_synced_player_name", "synced_player_name"),  &Player::set_synced_player_name);
    ADD_PROPERTY(PropertyInfo(Variant::STRING, "synced_player_name"), "set_synced_player_name", "get_synced_player_name");

    ClassDB::bind_method(D_METHOD("get_synced_health"), &Player::get_synced_health);
    ClassDB::bind_method(D_METHOD("set_synced_health", "synced_health"),  &Player::set_synced_health);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "synced_health"), "set_synced_health", "get_synced_health");

    ClassDB::bind_method(D_METHOD("get_synced_mana"), &Player::get_synced_mana);
    ClassDB::bind_method(D_METHOD("set_synced_mana", "synced_mana"),  &Player::set_synced_mana);
    ADD_PROPERTY(PropertyInfo(Variant::INT, "synced_mana"), "set_synced_mana", "get_synced_mana");

}

Player::Player() {
    //UtilityFunctions::print("player constructor");
    
	//Vector3(randi_range(-3,3), 5, randi_range(-3,3))
    set_position(Vector3(0,10,0));

    //TODO
 //   SpringArm3D camera_arm = get_node<SpringArm3D>(NodePath("CameraArm"));
//    camera = get_node<Camera3D>(NodePath("CameraArm/Camera3D"));
    
    //Camera3D * camera = cast_to<Camera3D>(nodeddd);
    //if multiplayer.multiplayer_peer == null or str(multiplayer.get_unique_id()) == str(name):
	//camera.current = true
}

Player::~Player() {
    //UtilityFunctions::print("player destructor");
}

void Player::_physics_process(float delta) {
    //UtilityFunctions::print("Delta: ", String::num(delta));

	Inputs * inputs = get_node<Inputs>(NodePath("Inputs"));
	synced_position = get_position();
	Vector3 rotation = get_rotation();
	synced_rotation_y = rotation.y;

	Vector3 rot = Vector3(inputs->get_mouse_motion().y, inputs->get_mouse_motion().x, 0) * mouse_sensitivity * delta;
    inputs->set_mouse_motion(Vector2());
	
    //Vector3 rot2 = camera_arm->get_rotation();
    //rot2.x = rot2.x - rot.x;
    //camera_arm->set_rotation(rot2);
	//$CameraArm.rotation.x-= rot.x
	//synced_camera_arm_rotation_x = $CameraArm.rotation.x
	//$CameraArm.rotation.x = clamp(rotation.x, -90.0, 30.0) #TODO: limit camera rotation up/down, new Vector3.limit_lengthfunction ?
	
	Vector3 tmprot;
	tmprot.y = rotation.y - rot.y;
	set_rotation(tmprot);
	
	//# Add the gravity.
    if(is_on_floor() == false)
    {
        Vector3 vel = get_motion_velocity();
        vel.y = vel.y - gravity * delta;
        set_motion_velocity(vel);
    }
    //#Handle Jump.
    if (inputs->get_jump() == true) {
        Vector3 vel = get_motion_velocity();
        vel.y = jump_force;
        set_motion_velocity(vel);
        synced_mana = synced_mana - 10;
        UtilityFunctions::print("synced_mana: ", synced_mana);
    }
	//#Handle Shoot
	//if $Inputs.shoot == true:
	//	get_node("../../Bullets").spawn([$"Position3D".global_transform.origin, str(name).to_int()])


	Basis direction = (get_transform().basis * Vector3(inputs->get_motion().y, 0, inputs->get_motion().x)).orthonormalized();
    //TODO
	//var direction := (transform.basis * Vector3($Inputs.motion.y, 0, $Inputs.motion.x)).normalized()
	if (direction != Basis()) {
        Vector3 tmp_vel = Vector3(direction.get_rotation_quat().x * speed, 0, direction.get_rotation_quat().z * speed);
		set_motion_velocity(tmp_vel);
	}
	//if direction:
	//	velocity.x = direction.x * speed
	//	velocity.z = direction.z * speed
	//else:
	//	velocity.x = move_toward(velocity.x, 0, speed)
	//	velocity.z = move_toward(velocity.z, 0, speed)

	move_and_slide();
}

Vector3 Player::get_synced_position() { return synced_position; }
void Player::set_synced_position(Vector3 _synced_position) { synced_position = _synced_position; }

float Player::get_synced_rotation_y() { return synced_rotation_y; }
void Player::set_synced_rotation_y(float _synced_rotation_y) { synced_rotation_y = _synced_rotation_y; }

float Player::get_synced_camera_arm_rotation_x() { return synced_camera_arm_rotation_x; }
void Player::set_synced_camera_arm_rotation_x(float _synced_camera_arm_rotation_x) { synced_camera_arm_rotation_x = _synced_camera_arm_rotation_x; }

String Player::get_synced_player_name() { return synced_player_name; }
void Player::set_synced_player_name(String _synced_player_name) { synced_player_name = _synced_player_name; }

int Player::get_synced_health() { return synced_health; }
void Player::set_synced_health(int _synced_health) { synced_health = _synced_health; }

int Player::get_synced_mana() { return synced_mana; }
void Player::set_synced_mana(int _synced_mana) { synced_mana = _synced_mana; }

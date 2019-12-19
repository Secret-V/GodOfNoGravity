#include "Laser.h"
#include <string>

using namespace godot;

void Laser::_register_methods()
{
    register_method("_process", &Laser::_process);
    
    register_property("moveSpeed", &Laser::moveSpeed, 10.0f);
}

Laser::Laser()
    : moveSpeed(10.0f)
{

}

Laser::~Laser()
{

}

void Laser::_init()
{

}

void Laser::_process(float delta)
{
    set_translation(Vector3(get_translation().x, get_translation().y, get_translation().z + delta * moveSpeed));
}

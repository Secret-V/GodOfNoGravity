#include "Asteroid.h"
#include <string>

using namespace godot;

void Asteroid::_register_methods()
{
    register_method("_process", &Asteroid::_process);
    register_method("_on_Asteroid_body_entered", &Asteroid::_on_Asteroid_body_entered);
    
    register_property("moveSpeed", &Asteroid::moveSpeed, 10.0f);
}

Asteroid::Asteroid()
    : moveSpeed(10.0f)
{

}

Asteroid::~Asteroid()
{

}

void Asteroid::_init()
{

}

void Asteroid::_process(float delta)
{
    set_translation(Vector3(get_translation().x, get_translation().y, get_translation().z + delta * moveSpeed));
}

void Asteroid::_on_Asteroid_body_entered(PhysicsBody* body)
{
    hide();
}

#include "AsteroidSpawner.h"
#include <Spatial.hpp>
#include <string>

using namespace godot;

void AsteroidSpawner::_register_methods()
{
    register_method("_process", &AsteroidSpawner::_process);
    register_method("_on_AsteroidSpawner_timeout", &AsteroidSpawner::_on_AsteroidSpawner_timeout);
    register_method("_on_Kratos_intro_done", &AsteroidSpawner::_on_Kratos_intro_done);

    register_property<AsteroidSpawner, Ref<PackedScene>>("asteroidScene", &AsteroidSpawner::asteroidScene, nullptr);
}

AsteroidSpawner::AsteroidSpawner()
{

}

AsteroidSpawner::~AsteroidSpawner()
{

}

void AsteroidSpawner::_init()
{

}

void AsteroidSpawner::_process(float delta)
{
    
}

void AsteroidSpawner::_on_AsteroidSpawner_timeout()
{
    Node* asteroid = asteroidScene->instance();
    static_cast<Spatial*>(asteroid)->set_translation(static_cast<Spatial*>(get_node("../Camera"))->get_translation() + Vector3(.0f, .0f, -50.0f));
    get_node("..")->add_child(asteroid);
}

void AsteroidSpawner::_on_Kratos_intro_done()
{
    start();
}

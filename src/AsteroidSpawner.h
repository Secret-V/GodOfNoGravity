#ifndef ASTEROID_SPAWNER_H
#define ASTEROID_SPAWNER_H

#include <Godot.hpp>
#include <Timer.hpp>
#include <PackedScene.hpp>

namespace godot
{
    class AsteroidSpawner : public Timer
    {
        GODOT_CLASS(AsteroidSpawner, Timer)
    public:
        static void _register_methods();

        AsteroidSpawner();
        ~AsteroidSpawner();

        void _init();
        void _process(float delta);

        void _on_AsteroidSpawner_timeout();
        void _on_Kratos_intro_done();

    private:
        Ref<PackedScene> asteroidScene;
    };
}

#endif //ASTEROID_SPAWNER_H
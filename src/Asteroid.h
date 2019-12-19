#ifndef ASTEROID_H
#define ASTEROID_H

#include <Godot.hpp>
#include <Spatial.hpp>
#include <PhysicsBody.hpp>

namespace godot
{
    class Asteroid : public Spatial
    {
        GODOT_CLASS(Asteroid, Spatial)
    public:
        static void _register_methods();

        Asteroid();
        ~Asteroid();

        void _init();
        void _process(float delta);

        void _on_Asteroid_body_entered(PhysicsBody* body);

    private:
        float moveSpeed;
    };
}

#endif //ASTEROID
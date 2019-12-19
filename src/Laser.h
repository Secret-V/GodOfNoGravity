#ifndef LASER_H
#define LASER_H

#include <Godot.hpp>
#include <Spatial.hpp>

namespace godot
{
    class Laser : public Spatial
    {
        GODOT_CLASS(Laser, Spatial)
    public:
        static void _register_methods();

        Laser();
        ~Laser();

        void _init();
        void _process(float delta);

    private:
        float moveSpeed;
    };
}

#endif //LASER_H
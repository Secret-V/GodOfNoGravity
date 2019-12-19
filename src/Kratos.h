#ifndef KRATOS_H
#define KRATOS_H

#include <Godot.hpp>
#include <MeshInstance.hpp>
#include <PackedScene.hpp>

namespace godot
{
    class Laser;

    class Kratos : public MeshInstance
    {
        GODOT_CLASS(Kratos, MeshInstance)
    public:
        static void _register_methods();

        Kratos();
        ~Kratos();

        void _init();
        void _process(float delta);

    private:
        enum class State : unsigned
        {
            SlideDown,
            RotateForward,
            RotateDown,
            MoveCamera,
            Active
        } state;

        float time;
        float slideDownTime;
        float rotateForwardTime;
        float rotateDownTime;
        float moveCameraTime;

        float startY;

        int currentGun;
        float gunCooldownTime;
        float gunCooldownTimer;

        float moveSpeed;

        Ref<PackedScene> laserScene;
    };
}

#endif //KRATOS_H

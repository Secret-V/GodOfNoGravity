#include "Kratos.h"
#include <string>
#include <Input.hpp>
#include <GlobalConstants.hpp>
#include <AudioStreamPlayer3D.hpp>
#include <Position3D.hpp>

using namespace godot;

template<class T>
inline T Lerp(const T& from, const T& to, const double& p)
{
    return (T)(from + (to - from) * p);
}

void Kratos::_register_methods()
{
    register_method("_process", &Kratos::_process);

    register_property("slideDownTime", &Kratos::slideDownTime, 1.0f);
    register_property("rotateForwardTime", &Kratos::rotateForwardTime, 1.0f);
    register_property("rotateDownTime", &Kratos::rotateDownTime, 1.0f);
    register_property("moveCameraTime", &Kratos::moveCameraTime, 2.0f);
    register_property("gunCooldownTime", &Kratos::gunCooldownTime, .5f);
    register_property("moveSpeed", &Kratos::moveSpeed, 1.0f);
    register_property<Kratos, Ref<PackedScene>>("laserScene", &Kratos::laserScene, nullptr);

    register_signal<Kratos>(String("intro_done"), godot::Dictionary());
}

Kratos::Kratos()
    : time(.0f), state(State::SlideDown), slideDownTime(1.0f), rotateForwardTime(1.0f), rotateDownTime(1.0f), moveCameraTime(2.0f), currentGun(0), gunCooldownTime(.5f), gunCooldownTimer(.0f), moveSpeed(1.0f)
{
    
}

Kratos::~Kratos()
{

}

void Kratos::_init()
{
    startY = 1.0f;
}

void Kratos::_process(float delta)
{
    time += delta;

    if(state == State::SlideDown)
    {
        float y = Lerp(startY, .0f, time / slideDownTime);
        Vector3 position(.0f, y, .0f);

        if(time > slideDownTime)
        {
            time = .0f;
            state = State::RotateForward;
        }

        set_translation(position);
    }
    else if(state == State::RotateForward)
    {
        float y = Lerp(.0f, 180.0f, time / rotateForwardTime);
        Vector3 rotation(.0f, y, .0f);

        if(time > rotateForwardTime)
        {
            time = .0f;
            state = State::RotateDown;
        }

        set_rotation_degrees(rotation);
    }
    else if(state == State::RotateDown)
    {
        float x = Lerp(.0f, 90.0f, time / rotateDownTime);
        Vector3 rotation(x, get_rotation_degrees().y, .0f);

        if(time > rotateDownTime)
        {
            time = .0f;
            state = State::MoveCamera;
        }

        set_rotation_degrees(rotation);
    }
    else if(state == State::MoveCamera)
    {
        Spatial* camera = static_cast<Spatial*>(get_node("../Camera"));
        float y = Lerp(.115f, .195f, time / moveCameraTime);
        float z = Lerp(.44f, .0f, time / moveCameraTime);
        float rx = Lerp(.0f, -20.0f, time / moveCameraTime);

        if(time > moveCameraTime)
        {
            time = .0f;
            state = State::Active;

            emit_signal("intro_done");
        }

        camera->set_translation(Vector3(camera->get_translation().x, y, z));
        camera->set_rotation_degrees(Vector3(rx, .0f, .0f));
    }
    else if(state == State::Active)
    {
        if(gunCooldownTimer > .0f)
        {
            gunCooldownTimer -= delta;
        }
        else
        {
            Input* input = Input::get_singleton();
            if(input->is_mouse_button_pressed(1))
            {
                Node* gunpoint = get_node(("KratosShip/GunPoint" + std::to_string(currentGun)).c_str());
                static_cast<AudioStreamPlayer3D*>(gunpoint->get_node("AudioStreamPlayer3D"))->play();

                Vector3 spawnPos = static_cast<Position3D*>(gunpoint)->get_global_transform().get_origin();
                Node* laser = laserScene->instance();
                static_cast<Spatial*>(laser)->set_translation(spawnPos);
                
                get_node("..")->add_child(laser);

                gunCooldownTimer = gunCooldownTime;
                ++currentGun %= 2;
            }

            Vector3 direction;
            if(input->is_action_pressed("ui_left"))
            {
                direction.x -= 1.0f;
            }
            if(input->is_action_pressed("ui_right"))
            {
                direction.x += 1.0f;
            }
            if(input->is_action_pressed("ui_up"))
            {
                direction.y += 1.0f;
            }
            if(input->is_action_pressed("ui_down"))
            {
                direction.y -= 1.0f;
            }

            set_translation(get_translation() + direction * moveSpeed * delta);
        }
    }
}

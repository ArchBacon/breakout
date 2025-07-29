#pragma once

#include <memory>
#include "core/engine.hpp"
#include "core/types.hpp"

struct Ball
{
    float2 location = {0.0f, 0.0f};
    float2 direction = {0.0f, 0.0f};
    float speed {325.f};
    std::vector<std::shared_ptr<engine::Image>> sprites
    {
        Engine.Renderer().CreateImage("assets/images/ball_shadow.png"),
        Engine.Renderer().CreateImage("assets/images/ball.png"),
    };

    void Update(float deltaTime);
};

inline void Ball::Update(const float deltaTime)
{
    location += direction * (speed * deltaTime);
}

#pragma once

#include <memory>

#include "breakout/collision.hpp"
#include "core/engine.hpp"
#include "core/types.hpp"

namespace breakout
{
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
        Bounds bounds {};
        bool isAttachedToPaddle {true};
        float2 relAttachlocation = {0.0f, 0.0f};
        bool pendingKill = false;
        
        Ball();
        
        void Update(float deltaTime);
    };

    inline Ball::Ball()
    {
        bounds = {
            .left = 0.0f,
            .top = 0.0f,
            .right = static_cast<float>(sprites[1]->width),
            .bottom = static_cast<float>(sprites[1]->height)
        };
    }

    inline void Ball::Update(const float deltaTime)
    {
        location += direction * (speed * deltaTime);
    }
}

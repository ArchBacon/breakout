#include "breakout.hpp"

#include "core/audio.hpp"
#include "core/engine.hpp"

breakout::Breakout::Breakout()
{
    // Configure window properties
    Engine.Window().SetIcon("assets/icon.bmp");
    Engine.Window().SetTitle("Breakout");
    Engine.Window().SetSize(448, 512);

    // Change clear color
    Engine.Renderer().SetClearColor({25, 26, 69});

    // Lower default volume
    Engine.Audio().SetVolume(0.05f);

    paddle.location = {
        224 - paddle.sprites[0]->width / 2,
        464
    };
    Ball ball {};
    ball.location = paddle.location;
    ball.location.x += (float)paddle.sprites[0]->width / 2.f - (float)ball.sprites[0]->width / 2.f;
    ball.location.y -= (float)ball.sprites[0]->height;
    ball.direction = {0, -1};
    balls.push_back(ball);

    ball.direction = {-0.3, -0.7};
    balls.push_back(ball);

    ball.direction = {0.3, -0.7};
    balls.push_back(ball);
}

void breakout::Breakout::BeginPlay()
{
    Engine.Audio().Play("assets/audio/round_start.wav");
}

void breakout::Breakout::Tick(const float deltaTime)
{
    paddle.Update(deltaTime);

    for (auto& ball : balls)
    {
        ball.Update(deltaTime);
    } 
}

void breakout::Breakout::Draw()
{
    Engine.Renderer().Draw(paddle.sprites, paddle.location);

    for (auto& ball : balls)
    {
        Engine.Renderer().Draw(ball.sprites, ball.location);
    }
}

void breakout::Breakout::KeyPressed(const uint32_t key)
{
    if (key == SDLK_A || key == SDLK_LEFT)
    {
        paddle.direction = {-1, 0};
    }

    if (key == SDLK_D || key == SDLK_RIGHT)
    {
        paddle.direction = {1, 0};
    }
}

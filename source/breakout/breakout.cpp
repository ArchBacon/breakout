#include "breakout.hpp"

#include "core/engine.hpp"

breakout::Breakout::Breakout()
{
    config =
    {
        .app_name = "Breakout",
        .app_icon = "assets/icon.bmp",
        .window_width = 448,
        .window_height = 512, 
    };
}

void breakout::Breakout::Initialize()
{
    background = ::Engine.Renderer().CreateImage("assets/images/background_01.png");    
}

void breakout::Breakout::Draw()
{
    ::Engine.Renderer().Draw(background, 0, 32);
}

void breakout::Breakout::Shutdown()
{
    delete background;
}

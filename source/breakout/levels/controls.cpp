#include "controls.hpp"

#include "breakout/arkanoid_font.hpp"
#include "core/engine.hpp"

void breakout::Controls::BeginPlay()
{
    background = Engine.Renderer().CreateImage("assets/images/mainmenu.png");
    controls = Engine.GetFont<ArkanoidFont>()->CreateText("Controls");
    menu.buttons.emplace_back(Engine.GetFont<ArkanoidFont>()->CreateText("A ....... Left"), [](){});
    menu.buttons.emplace_back(Engine.GetFont<ArkanoidFont>()->CreateText("D ...... Right"), [](){});
    menu.buttons.emplace_back(Engine.GetFont<ArkanoidFont>()->CreateText("Space ... Fire"), [](){});
}

void breakout::Controls::Draw()
{
    Engine.Renderer().Draw(background, {0, 0});
    Engine.Renderer().Draw(controls, {104, 226});
    
    menu.Draw({104, 226 + 64}, 32);
}

void breakout::Controls::KeyDown(const uint32_t key)
{
    RequestLevelChange(LevelType::MainMenu);
}

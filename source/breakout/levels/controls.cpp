#include "controls.hpp"

#include "breakout/fonts/arkanoid_font.hpp"
#include "breakout/fonts/other_font.hpp"
#include "core/audio.hpp"
#include "core/engine.hpp"

void breakout::Controls::BeginPlay()
{
    background = Engine.Renderer().CreateImage("assets/images/mainmenu.png");
    controls = Engine.GetFont<ArkanoidFont>()->CreateText("Controls");
    acceptSettings = Engine.GetFont<OtherFont>()->CreateText("Accept: SPACE/Enter");
    menu.buttons.emplace_back(Engine.GetFont<ArkanoidFont>()->CreateText("A ....... Left"), [](){});
    menu.buttons.emplace_back(Engine.GetFont<ArkanoidFont>()->CreateText("D ...... Right"), [](){});
    menu.buttons.emplace_back(Engine.GetFont<ArkanoidFont>()->CreateText("Space ... Fire"), [](){});
}

void breakout::Controls::Draw()
{
    Engine.Renderer().Draw(background, {0, 0});
    Engine.Renderer().Draw(controls, {104, 226});
    
    menu.Draw({104, 226 + 64}, 32);

    Engine.Renderer().Draw(acceptSettings, {48, Engine.Window().Height() - acceptSettings->height - 32});
}

void breakout::Controls::KeyDown([[maybe_unused]] const uint32_t key)
{
    Engine.Audio().Play("assets/audio/pickup1.wav");
    RequestLevelChange(LevelType::MainMenu);
}

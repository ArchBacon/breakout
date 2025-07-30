#include "settings.hpp"

#include "breakout/fonts/arkanoid_font.hpp"
#include "breakout/fonts/other_font.hpp"
#include "core/audio.hpp"
#include "core/engine.hpp"

void breakout::Settings::BeginPlay()
{
    background = Engine.Renderer().CreateImage("assets/images/mainmenu.png");
    settings = Engine.GetFont<ArkanoidFont>()->CreateText("Settings");
    volumeText = Engine.GetFont<ArkanoidFont>()->CreateText("Volume");
    acceptSettings = Engine.GetFont<OtherFont>()->CreateText("Accept: SPACE/Enter");
    volume = Engine.GetFont<ArkanoidFont>()->CreateText(std::format("{:.2f}", Engine.Audio().GetVolume()));
    fullVolumeSize = volume->width;
    carretRight = Engine.GetFont<ArkanoidFont>()->CreateText(">");
    carretLeft = Engine.GetFont<ArkanoidFont>()->CreateText("<");
}

void breakout::Settings::Draw()
{
    Engine.Renderer().Draw(background, {0, 0});
    Engine.Renderer().Draw(settings, {104, 226});
    Engine.Renderer().Draw(carretRight, {104 - 32, 226 + 64});
    Engine.Renderer().Draw(volumeText, {104, 226 + 64});
    Engine.Renderer().Draw(carretLeft, {104 + volumeText->width + 16, 226 + 64});
    Engine.Renderer().Draw(volume, {104 + 32 + volumeText->width + 16, 226 + 64});
    Engine.Renderer().Draw(carretRight, {104 + fullVolumeSize + 32 + 8 + volumeText->width + 16, 226 + 64});

    Engine.Renderer().Draw(acceptSettings, {48, Engine.Window().Height() - acceptSettings->height - 32});
}

void breakout::Settings::KeyDown(const uint32_t key)
{
    if (key == SDLK_SPACE || key == SDLK_RETURN || key == SDLK_ESCAPE)
    {
        Engine.Audio().Play("assets/audio/pickup1.wav");
        RequestLevelChange(LevelType::MainMenu);
        return;
    }
    
    // Since there is only one option, we don't have to check for what option is selected
    float newVolume = Engine.Audio().GetVolume();
    if (key == SDLK_D || key == SDLK_RIGHT)
    {
        newVolume += volumeStep;
        Engine.Audio().SetVolume(glm::clamp(newVolume, 0.0f, 1.0f));
        volume = Engine.GetFont<ArkanoidFont>()->CreateText(std::format("{:.2f}", Engine.Audio().GetVolume()));
        Engine.Audio().Play("assets/audio/arkanoid_hit.wav");
    }
    if (key == SDLK_A || key == SDLK_LEFT)
    {
        newVolume -= volumeStep;
        Engine.Audio().SetVolume(glm::clamp(newVolume, 0.0f, 1.0f));
        volume = Engine.GetFont<ArkanoidFont>()->CreateText(std::format("{:.2f}", Engine.Audio().GetVolume()));
        Engine.Audio().Play("assets/audio/arkanoid_hit.wav");
    }
}

#include "menu.hpp"

#include "core/engine.hpp"

void breakout::Menu::Draw(const int2 location, const int spacing) const
{
    for (size_t i = 0; i < buttons.size(); i++)
    {
        Engine.Renderer().Draw(buttons[i].first, location + int2{0, spacing} * static_cast<int>(i));
    }
    
    if (pointer)
    {
        Engine.Renderer().Draw(pointer, location + int2{-spacing, spacing * buttonIndex});
    }
}

void breakout::Menu::Next()
{
    buttonIndex = RecalculatePointerPosition(++buttonIndex);
}

void breakout::Menu::Prev()
{
    buttonIndex = RecalculatePointerPosition(--buttonIndex);
}

void breakout::Menu::Click() const
{
    buttons[buttonIndex].second();
}

int breakout::Menu::RecalculatePointerPosition(const int index) const
{
    if (cycle)
    {
        return (index + static_cast<int>(buttons.size())) % static_cast<int>(buttons.size());
    }
    
    return  glm::clamp(index, 0, static_cast<int>(buttons.size() - 1));
}

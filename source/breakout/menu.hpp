#pragma once

#include <memory>
#include <vector>

#include "core/types.hpp"
#include "rendering/image.hpp"

namespace breakout
{
    struct Menu
    {
        int buttonIndex = 0;
        std::shared_ptr<engine::Image> pointer {};
        std::vector<std::pair<std::shared_ptr<engine::Image>, std::function<void()>>> buttons {};
        bool cycle = false; // Can you cycle trough menu selection?
            
        void Draw(int2 location, int spacing) const;
        void Next();
        void Prev();

        void Click() const;

    private:
        [[nodiscard]] int RecalculatePointerPosition(int index) const;
    };
}

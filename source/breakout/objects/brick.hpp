#pragma once

#include "breakout/breakout_gamestate.hpp"
#include "breakout/collision.hpp"
#include "breakout/fonts/brick_font.hpp"
#include "core/engine.hpp"
#include "core/fileio.hpp"
#include "core/string_helper.hpp"
#include "core/types.hpp"

namespace breakout
{
    // Order matters as these are mapped to the colors in the brick spritesheet
    enum class Color : uint8_t
    {
        White = 0,
        Orange = 1,
        LightBlue = 2,
        Green = 3,
        Red = 4,
        Blue = 5,
        Magenta = 6,
        Yellow = 7,
        Silver = 8,
        Gold = 9,
    };

    inline struct
    {
        uint2 bricksize {32, 16};
    } BrickData;

    struct Brick
    {
        Color color {Color::White};
        uint32_t score {0};
        std::shared_ptr<engine::Image> sprite {nullptr};
        int8_t health {1};
        int2 location {0, 0};
        Bounds bounds {.left = 0, .top = 0, .right = 32, .bottom = 16}; // 32x16 size brick
    
        Brick(const Color inColor, const int2 inPosition)
            : color{inColor}, location{inPosition}
        {
            auto colorID = static_cast<unsigned>(inColor);
            score = 50 + (10 * colorID);
            sprite = Engine.GetFont<breakout::BrickFont>()->CreateText(std::to_string(colorID));
        }
    };

    struct SilverBrick : Brick
    {
        explicit SilverBrick(const int stage, const int2 inPosition): Brick(Color::Silver, inPosition)
        {
            score = 50 * stage;
            health = static_cast<int8_t>(trunc(stage / 8) + 2);
        }
    };

    struct GoldBrick : Brick
    {
        explicit GoldBrick(const int2 inPosition): Brick(Color::Gold, inPosition)
        {
            score = 0;
            health = -1; // Indestructible
        }
    };

    inline void GetBricksFromStage(const int stage, const breakout::Bounds& fieldBounds, std::vector<Brick*>& bricks, int& bricksToClear)
    {
        // Reset return values
        bricks.clear();
        bricksToClear = 0;

        Engine.FileIO().ReadFilePerLine("assets/stages/stage_" + ZeroFill(stage, 2) + ".txt", [&](const std::string& line, const unsigned lineNumber)
        {
            if (line.empty()) return;
        
            uint32_t brickYPos = static_cast<unsigned>(fieldBounds.top) + BrickData.bricksize.y * lineNumber;

            for (int x = 0; x < static_cast<int>(line.size()); x++)
            {
                uint32_t brickXPos = static_cast<int>(fieldBounds.left) + x * BrickData.bricksize.x;

                if (!std::isdigit(line[x])) continue;
                const auto character = std::string(1, line[x]);
                const auto color = static_cast<Color>(std::stoi(character));

                // Create Silver brick
                if (color == Color::Silver)
                {
                    const auto brick = new SilverBrick(stage, {brickXPos, brickYPos});
                    bricks.push_back(brick);
                    bricksToClear++;
                    continue;
                }
            
                // Create Gold brick -- not a brick to clear
                if (color == Color::Gold)
                {
                    const auto brick = new GoldBrick({brickXPos, brickYPos});
                    bricks.push_back(brick);
                    continue;
                }

                const auto brick = new Brick(color, {brickXPos, brickYPos});
                bricks.push_back(brick);
                bricksToClear++;
            }
        });
    }
}

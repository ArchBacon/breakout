#pragma once
#include <memory>
#include <string>
#include <unordered_map>

#include "image.hpp"

namespace engine
{
    class Font
    {
        std::string characterOrder {};
        std::shared_ptr<Image> fontSheet {nullptr};
        std::unordered_map<char, std::shared_ptr<Image>> characters {};
        int charWidth = 0;
        int charHeight = 0;

    public:
        Font(const std::string& filepath, int charsHor, int charsVer, std::string charOrder);
        ~Font() = default;

        Font(const Font& other) = delete;
        Font& operator=(const Font&) = delete;
        Font(Font&& other) = delete;
        Font& operator=(Font&& other) = delete;

        [[nodiscard]] std::shared_ptr<Image> CreateText(const std::string& text);

    private:
        [[nodiscard]] std::shared_ptr<Image> GetCharacterImage(char c) const;
        [[nodiscard]] std::shared_ptr<Image> CreateImageFromPixels(unsigned char* pixels, int width, int height) const;
        void CopyPixelSection(
            const unsigned char* src,
            unsigned char* dst,
            int srcWidth,
            int srcHeight,
            int dstWidth,
            int dstHeight,
            int srcX,
            int srcY,
            int dstX,
            int dstY,
            int copyWidth,
            int copyHeight
        );
    };
}

#include "font.hpp"

#include "core/engine.hpp"

engine::Font::Font(
    const std::string& filepath,
    const int charsHor,
    const int charsVer,
    std::string charOrder
)
    : characterOrder(std::move(charOrder))
{
    // Load font sheet
    fontSheet = ::Engine.Renderer().CreateImage(filepath);
    charWidth = fontSheet->width / charsHor;
    charHeight = fontSheet->height / charsVer;

    uint16_t index = 0;
    for (char& character : characterOrder)
    {
        const int2 location
        {
            (index % charsHor) * charWidth,
            (index / charsHor) * charHeight,
        };
    
        // Create pixel buffer for this character
        auto* charPixels = new unsigned char[charWidth * charHeight * 4];

        // Copy character pixels from font sheet
        CopyPixelSection(
            fontSheet->pixels, charPixels,
            fontSheet->width, fontSheet->height,
            charWidth, charHeight,
            location.x, location.y,
            0, 0,
            charWidth, charHeight
        );

        // Create image from pixels
        const auto charImage = CreateImageFromPixels(charPixels, charWidth, charHeight);
        characters[character] = charImage;

        index++;
    } 
}

std::shared_ptr<engine::Image> engine::Font::CreateText(const std::string& text)
{
    if (text.empty()) return nullptr;
    
    const int textWidth = charWidth * static_cast<int>(text.size());
    const int textHeight = charHeight;
    
    // Create pixel buffer for the complete text
    auto* textPixels = new unsigned char[textWidth * textHeight * 4](); // Initialize to 0
    
    int index = 0;
    for (const char& c : text)
    {
        const char upper = static_cast<char>(std::toupper(c));
        auto charImage = GetCharacterImage(upper);
        
        if (charImage && charImage->pixels)
        {
            // Copy character pixels to text buffer
            CopyPixelSection(
                charImage->pixels, textPixels,
                charWidth, charWidth,
                textWidth, textHeight,
                0, 0,
                charWidth * index, 0,
                charWidth, charWidth
            );
        }
        
        index++;
    }
    
    return CreateImageFromPixels(textPixels, textWidth, textHeight);
}

std::shared_ptr<engine::Image> engine::Font::GetCharacterImage(const char c) const
{
    const auto it = characters.find(c);
    if (it != characters.end())
    {
        return it->second;
    }

    return GetCharacterImage('?');
}

std::shared_ptr<engine::Image> engine::Font::CreateImageFromPixels(
    unsigned char* pixels,
    const int width,
    const int height
) const {
    // Create SDL surface from pixels
    const auto surface = SDL_CreateSurfaceFrom(width, height, SDL_PIXELFORMAT_RGBA32, pixels, 4 * width);
    const auto texture = SDL_CreateTextureFromSurface(::Engine.Renderer().renderer, surface);

    return std::make_shared<Image>(Image{
        .channels = 4,
        .width = width,
        .height = height,
        .pixels = pixels,
        .surface = surface,
        .texture = texture,
    });
}

/** +--------------------+ */
/** + Based on AI Answer + */
/** +--------------------+ */
void engine::Font::CopyPixelSection(
    const unsigned char* src,
    unsigned char* dst,
    const int srcWidth,
    const int srcHeight,
    const int dstWidth,
    const int dstHeight,
    const int srcX,
    const int srcY,
    const int dstX,
    const int dstY,
    const int copyWidth,
    const int copyHeight
) {
    for (int y = 0; y < copyHeight; ++y)
    {
        if (srcY + y >= srcHeight || dstY + y >= dstHeight) break;
        
        for (int x = 0; x < copyWidth; ++x)
        {
            if (srcX + x >= srcWidth || dstX + x >= dstWidth) break;
            
            const int srcIndex = ((srcY + y) * srcWidth + (srcX + x)) * 4;
            const int dstIndex = ((dstY + y) * dstWidth + (dstX + x)) * 4;
            
            // Copy RGBA pixels
            dst[dstIndex + 0] = src[srcIndex + 0]; // R
            dst[dstIndex + 1] = src[srcIndex + 1]; // G
            dst[dstIndex + 2] = src[srcIndex + 2]; // B
            dst[dstIndex + 3] = src[srcIndex + 3]; // A
        }
    }

}

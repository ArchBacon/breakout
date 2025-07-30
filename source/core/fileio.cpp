#include "fileio.hpp"

#include <fstream>

#include "core.hpp"

namespace engine
{
    FileIO::FileIO() = default;
    FileIO::~FileIO() = default;

    std::string FileIO::ReadFile(const std::string& filepath) const
    {
        std::ifstream file(filepath, std::ios::ate | std::ios::binary);
        if (!file.is_open())
        {
            LogEngine->Error("Could not open file: {}", filepath);
            return {};
        }

        const std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        std::string content(size, '\0'); // Zero-fill content
        file.read(content.data(), size);
        file.close();

        return content;
    }

    void FileIO::ReadFilePerLine(const std::string& filepath, const std::function<void(std::string, unsigned)>& callback) const
    {
        std::ifstream file(filepath, std::ios::binary);
        if (!file.is_open())
        {
            LogEngine->Error("Could not open file: {}", filepath);
            return;
        }

        std::string line {};
        uint16_t lineNumber {0};
        while (std::getline(file, line))
        {
            callback(line, lineNumber);
            lineNumber++;
        }

        file.close();
    }
}

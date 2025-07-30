#pragma once

#include <functional>
#include <string>

namespace engine
{
    class FileIO
    {
    public:
        FileIO();
        ~FileIO();

        FileIO(const FileIO& other) = delete;
        FileIO &operator=(const FileIO&) = delete;
        FileIO(FileIO&& other) = delete;
        FileIO& operator=(FileIO&& other) = delete;

        [[nodiscard]] std::string ReadFile(const std::string& filepath) const;
        void ReadFilePerLine(const std::string& filepath, const std::function<void(std::string, unsigned)>& callback) const;
    };
}

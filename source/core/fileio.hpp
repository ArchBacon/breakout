#pragma once

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

        std::string ReadFile(const std::string& filepath) const;
    };
}

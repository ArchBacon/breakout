#pragma once

#include <chrono>

namespace engine
{
    // copied from https://github.com/jbikker/tmpl8/blob/master/template/precomp.h#L148-L159
    struct Timer
    {
    private:
        std::chrono::high_resolution_clock::time_point start {};
        
    public:
        
        Timer() { Reset(); }

        [[nodiscard]] float Elapsed() const
        {
            const auto now = std::chrono::high_resolution_clock::now();
            const auto elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(now - start);
            return static_cast<float>(elapsed.count());
        }
        
        void Reset() { start = std::chrono::high_resolution_clock::now(); }
    };
}

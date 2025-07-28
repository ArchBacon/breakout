#include "core/engine.hpp"
#include "breakout/breakout.hpp"

int main(int /*argc*/, char* /*argv[]*/)
{
    Engine.Initialize();
    Engine.StartGame<breakout::Breakout>();
    Engine.Run();
    Engine.Shutdown();

    return 0;
}

#pragma once

#include "core/logger.hpp"

inline auto LogEngine = std::make_unique<engine::Logger>("LogEngine");
inline auto LogRenderer = std::make_unique<engine::Logger>("LogRenderer");
inline auto LogGame = std::make_unique<engine::Logger>("LogGame");
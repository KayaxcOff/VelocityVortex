#include <iostream>
#include <memory>
#include "MindEngine/Game/game/game.hpp"

int main() {
    const auto vortex_game_ = std::make_unique<mind::VortexGame>(1200, 1000);

    try {
        vortex_game_->Init();
        if (vortex_game_->isRunning()) vortex_game_->run();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

}
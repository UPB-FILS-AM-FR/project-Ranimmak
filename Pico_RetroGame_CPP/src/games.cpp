#include "games.hpp"

void runSelectedGame(GameId id) {
    switch (id) {
        case GAME_PONG:         runPong(); break;
        case GAME_SNAKE:        runSnake(); break;
        case GAME_INVADERS:     runInvaders(); break;
        case GAME_DINO:         runDino(); break;
        case GAME_2048:         run2048(); break;
        case GAME_TETRIS:       runTetris(); break;
        case GAME_FULL_SPEED:   runFullSpeed(); break;
        case GAME_LUNAR_MODULE: runLunarModule(); break;
        default: break;
    }
}

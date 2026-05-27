#pragma once

enum GameId {
    GAME_PONG = 0,
    GAME_SNAKE,
    GAME_INVADERS,
    GAME_DINO,
    GAME_2048,
    GAME_TETRIS,
    GAME_FULL_SPEED,
    GAME_LUNAR_MODULE,
    GAME_COUNT
};

void runPong();
void runSnake();
void runInvaders();
void runDino();
void run2048();
void runTetris();
void runFullSpeed();
void runLunarModule();
void runSelectedGame(GameId id);

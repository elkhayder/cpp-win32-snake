#ifndef __BOARD_H_
#define __BOARD_H_

#include <cstdint>
#include <vector>
#include <random>
#include <memory>

#include <windows.h>

#include "Point.h"
#include "Snake.h"

// class Snake;

class Board
{
public:
    Board();
    ~Board();

    Snake &GetSnake();

    void SpawnFood();
    void Update();

    void Draw(HDC hdc);
    void DrawFood(HDC hdc);

    // void Draw(HDC hdc);
public:
    static const uint8_t GRID_SIZE;
    static const uint8_t GRID_COUNT;

private:
    std::unique_ptr<Point> _food;
    Snake _snake;
};

#endif // __BOARD_H_
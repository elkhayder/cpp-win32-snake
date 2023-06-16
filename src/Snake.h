#ifndef __SNAKE_H__
#define __SNAKE_H__

#include <Windows.h>
#include <vector>
#include <chrono>
#include <random>

#include "Point.h"
#include "Direction.h"

class Snake
{
public:
    Snake();
    ~Snake();

    int GetLength() const
    {
        return _body.size();
    };

    Point &GetHead()
    {
        return _body[0];
    };

    void MaybeUpdate();
    void ForceUpdate();
    bool CheckCollision();
    bool CheckCollision(Point &point, size_t startIndex = 0);
    void SetDirection(int keyCode);

    void Draw(HDC hdc);

private:
    std::vector<Point> _body;
    Direction _direction;
    const std::chrono::milliseconds _updateInterval;
    std::chrono::_V2::steady_clock::time_point _lastUpdate;

public:
    static const uint8_t SPEED; // Square per second
};

#endif // __SNAKE_H__
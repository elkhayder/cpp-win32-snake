#ifndef __POINT_H_
#define __POINT_H_

#include <cstdint>

class Point
{
public:
    Point(uint8_t x, uint8_t y);
    ~Point();

    bool operator==(const Point &other) const;
    bool operator!=(const Point &other) const;
    Point &operator=(const Point &other);

    uint8_t x;
    uint8_t y;
};

#endif // __POINT_H_
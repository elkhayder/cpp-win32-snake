#include "Point.h"

Point::Point(uint8_t x, uint8_t y) : x(x), y(y) {}

Point::~Point() {}

bool Point::operator==(const Point &other) const
{
    return this->x == other.x && this->y == other.y;
}

bool Point::operator!=(const Point &other) const
{
    return !(*this == other);
}

Point &Point::operator=(const Point &other)
{
    this->x = other.x;
    this->y = other.y;

    return *this;
}
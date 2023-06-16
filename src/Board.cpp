#include "Board.h"
#include "Snake.h"

const uint8_t Board::GRID_COUNT = 30;
const uint8_t Board::GRID_SIZE = 20;

Board::Board()
{
    SpawnFood();
}

Board::~Board()
{
}

Snake &Board::GetSnake()
{
    return _snake;
}

void Board::SpawnFood()
{
    if (_food != nullptr)
        return;

    std::random_device rd;
    std::mt19937 engine(rd());

    std::uniform_int_distribution<uint8_t> positionDistribution(0, Board::GRID_COUNT - 1);

    Point point(0, 0);
    do
    {
        point.x = positionDistribution(engine);
        point.y = positionDistribution(engine);
    } while (_snake.CheckCollision(point));

    _food = std::make_unique<Point>(point);
}

void Board::Update()
{
    // Update Snake
    _snake.MaybeUpdate();

    // Check for food collision
    if (*_food.get() == _snake.GetHead())
    {
        _snake.ForceUpdate();
        _food.release();
        SpawnFood();
    }
}

void Board::DrawFood(HDC hdc)
{
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0)); // Red color brush

    auto point = _food.get();

    RECT rect = {
        point->x * Board::GRID_SIZE,
        point->y * Board::GRID_SIZE,
        (point->x + 1) * Board::GRID_SIZE,
        (point->y + 1) * Board::GRID_SIZE};

    FillRect(hdc, &rect, hBrush);

    DeleteObject(hBrush);
}

void Board::Draw(HDC hdc)
{
    _snake.Draw(hdc);
    DrawFood(hdc);
}
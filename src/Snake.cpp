#include "Snake.h"
#include "Board.h"

const uint8_t Snake::SPEED = 15;

Snake::Snake() : _updateInterval(1000 / Snake::SPEED)
{
    std::random_device rd;
    std::mt19937 engine(rd());

    std::uniform_int_distribution<uint8_t> positionDistribution(0, Board::GRID_COUNT - 1);

    // Generate a random number
    uint8_t x = positionDistribution(engine);
    uint8_t y = positionDistribution(engine);

    _body.push_back({x, y});

    std::uniform_int_distribution<int> directionDistribution(0, 4);

    _direction = static_cast<Direction>(directionDistribution(engine));

    _lastUpdate = std::chrono::steady_clock::now();
}

Snake::~Snake() {}

void Snake::SetDirection(int keyCode)
{
    // TODO : Buffer input
    if (keyCode == VK_UP)
    {
        this->_direction = Direction::UP;
    }
    else if (keyCode == VK_DOWN)
    {
        this->_direction = Direction::DOWN;
    }
    else if (keyCode == VK_LEFT)
    {
        this->_direction = Direction::LEFT;
    }
    else if (keyCode == VK_RIGHT)
    {
        this->_direction = Direction::RIGHT;
    }
}

void Snake::MaybeUpdate()
{
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - _lastUpdate);
    if (elapsed < _updateInterval)
        return;

    _lastUpdate = now;

    ForceUpdate();

    if (_body.size() > 1)
        _body.pop_back();
}

void Snake::ForceUpdate()
{
    int x = _body[0].x;
    int y = _body[0].y;

    switch (this->_direction)
    {
    case Direction::UP:
        y--;
        break;

    case Direction::DOWN:
        y++;
        break;

    case Direction::LEFT:
        x--;
        break;

    case Direction::RIGHT:
        x++;
        break;
    }

    // Comment this code if you dont want the snake to wrap around the board
    if (x < 0)
    {
        x = Board::GRID_COUNT - 1;
    }
    else if (x >= Board::GRID_COUNT)
    {
        x = 0;
    }

    if (y < 0)
    {
        y = Board::GRID_COUNT - 1;
    }
    else if (y >= Board::GRID_COUNT)
    {
        y = 0;
    }

    if (_body.size() > 1 && x == _body[1].x && y == _body[1].y)
    {
        // Invalid move, trying to move to the opposite direction
        if (_direction == Direction::DOWN)
            _direction = Direction::UP;
        else if (_direction == Direction::UP)
            _direction = Direction::DOWN;
        else if (_direction == Direction::LEFT)
            _direction = Direction::RIGHT;
        else if (_direction == Direction::RIGHT)
            _direction = Direction::LEFT;

        return ForceUpdate();
    }

    _body.insert(_body.begin(),
                 {static_cast<uint8_t>(x),
                  static_cast<uint8_t>(y)});

    if (CheckCollision())
    {
        Point head = _body[0];
        _body.clear();
        _body.push_back(head);
    }
}

bool Snake::CheckCollision()
{
    auto &head = _body[0];

    return CheckCollision(head, 1);
}

bool Snake::CheckCollision(Point &point, size_t startIndex)
{
    auto size = _body.size();

    for (size_t i = startIndex; i < size; i++)
    {
        if (point == _body[i])
        {
            return true;
        }
    }

    return false;
}

void Snake::Draw(HDC hdc)
{
    const uint8_t quarter = Board::GRID_SIZE / 4;

    HBRUSH hBrush = CreateSolidBrush(RGB(221, 179, 140)); // Red color brush

    for (size_t i = 0; i < _body.size(); i++)
    {
        auto &self = _body[i];

        RECT rect = {
            self.x * Board::GRID_SIZE + quarter,
            self.y * Board::GRID_SIZE + quarter,
            (self.x + 1) * Board::GRID_SIZE - quarter,
            (self.y + 1) * Board::GRID_SIZE - quarter};

        FillRect(hdc, &rect, hBrush);

        if (i != _body.size() - 1)
        {
            RECT rect = {
                self.x * Board::GRID_SIZE + quarter,
                self.y * Board::GRID_SIZE + quarter,
                (self.x + 1) * Board::GRID_SIZE - quarter,
                (self.y + 1) * Board::GRID_SIZE - quarter};

            // Previous
            auto &next = _body[i + 1];

            if (next.x == self.x)
            {
                // Vertical
                if (next.y > self.y)
                {
                    // Down
                    rect.bottom += quarter;
                }
                else
                {
                    // Up
                    rect.top -= quarter;
                }
            }
            else
            {
                // Horizontal
                if (next.x > self.x)
                {
                    // Right
                    rect.right += quarter;
                }
                else
                {
                    // Left
                    rect.left -= quarter;
                }
            }

            FillRect(hdc, &rect, hBrush);
        }

        if (i != 0)
        {

            RECT rect = {
                self.x * Board::GRID_SIZE + quarter,
                self.y * Board::GRID_SIZE + quarter,
                (self.x + 1) * Board::GRID_SIZE - quarter,
                (self.y + 1) * Board::GRID_SIZE - quarter};

            // Previous
            auto &prev = _body[i - 1];

            if (prev.x == self.x)
            {
                // Vertical
                if (prev.y > self.y)
                {
                    // Down
                    rect.bottom += quarter;
                }
                else
                {
                    // Up
                    rect.top -= quarter;
                }
            }
            else
            {
                // Horizontal
                if (prev.x > self.x)
                {
                    // Right
                    rect.right += quarter;
                }
                else
                {
                    // Left
                    rect.left -= quarter;
                }
            }

            FillRect(hdc, &rect, hBrush);
        }
    }

    DeleteObject(hBrush);
}

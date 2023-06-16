#include "main.h"

const int MIN_WINDOW_SIZE = Board::GRID_SIZE * Board::GRID_COUNT;

int main(int argc, char **argv)
{

    HINSTANCE hInstance = GetModuleHandle(nullptr);

    // Register the window class.
    const char CLASS_NAME[] = "Snake";

    WNDCLASS wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create a window
    HWND window = CreateWindowExA(0,
                                  CLASS_NAME,
                                  CLASS_NAME,
                                  WS_OVERLAPPEDWINDOW,
                                  CW_USEDEFAULT, CW_USEDEFAULT,
                                  MIN_WINDOW_SIZE, MIN_WINDOW_SIZE,
                                  NULL,
                                  NULL,
                                  hInstance,
                                  NULL);

    // Show the window
    ShowWindow(window, SW_SHOW);

    MSG msg = {0};
    // while (GetMessage(&msg, NULL, 0, 0) > 0)
    // {
    //     TranslateMessage(&msg);
    //     DispatchMessage(&msg);
    // }

    while (true)
    {
        // Check for pending messages
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            // Handle the message if it's not a quit message
            if (msg.message == WM_QUIT)
                break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            // Perform regular screen updating logic here
            // ...

            // Invalidate the client area to trigger a WM_PAINT message
            InvalidateRect(window, nullptr, FALSE);

            // Sleep for a short duration to yield some time to other processes
            Sleep(1);
        }
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        // case WM_SIZE:
        // {
        //     int width = LOWORD(lParam);
        //     int height = HIWORD(lParam);

        //     // Respond to the message:
        //     wprintf(L"WM_SIZE: width=%d, height=%d\n", width, height);
        //     return 0;
        // }

    case WM_GETMINMAXINFO:
    {
        MINMAXINFO *pMinMaxInfo = reinterpret_cast<MINMAXINFO *>(lParam);

        pMinMaxInfo->ptMinTrackSize.x = MIN_WINDOW_SIZE;
        pMinMaxInfo->ptMinTrackSize.y = MIN_WINDOW_SIZE;

        break;
    }

    case WM_KEYDOWN:
    {
        // Check if the key code corresponds to an arrow key
        UINT keyCode = wParam;
        // printf("Key pressed: %d\n", keyCode);
        // if (keyCode == VK_UP || keyCode == VK_DOWN || keyCode == VK_LEFT || keyCode == VK_RIGHT)
        // {
        board.GetSnake().SetDirection(keyCode);
        // }

        break;
    }

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // Update
        board.Update();

        // Clear screen
        RECT rect;
        GetClientRect(hwnd, &rect);
        HBRUSH hBrush = CreateSolidBrush(RGB(92, 20, 36));
        FillRect(hdc, &rect, hBrush);
        DeleteObject(hBrush);

        SetDCPenColor(hdc, RGB(159, 69, 75));

        for (int i = 0; i <= MIN_WINDOW_SIZE; i += Board::GRID_SIZE)
        {
            MoveToEx(hdc, i, 0, nullptr);
            LineTo(hdc, i, MIN_WINDOW_SIZE);
            MoveToEx(hdc, 0, i, nullptr);
            LineTo(hdc, MIN_WINDOW_SIZE, i);
        }

        // Draw new frame
        board.Draw(hdc);

        EndPaint(hwnd, &ps);
        return 0;
    }

    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
    }
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
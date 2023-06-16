#ifndef __MAIN_H_
#define __MAIN_H_

#include <stdio.h>
#include <cstdint>
#include <windows.h>

#include "Board.h"

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

Board board;

#endif // __MAIN_H_
#pragma once
#include <windows.h>

enum Draw { NON, BOX, CIRCLE, CUBE, BONOBONO, RYAN }; // 그릴 수 있는 도형 종류

void DrawShape(HWND hWnd, HDC hdc, POINT start, POINT end, Draw shape, int blink);

void DrawBoxCircle(HDC hdc, POINT max, POINT min, Draw shape); // 박스와 원 그리는 함수
void DrawCube(HDC hdc, const POINT start, const POINT end); // 큐브 그리는 함수
void DrawBonobono(HWND hWnd, HDC hdc, int blink); // 보노보노 그리는 함수
void DrawRyan(HWND hWnd, HDC hdc, int left, int top, int right, int bottom); // 라이언 그리는 함수

bool isDrawArea(POINT start, POINT end, RECT drawArea); // 드로잉 영역 확인
bool IsMouseInBox(POINT last, POINT start, POINT end); // 마우스가 박스 범위 안에 있는지 확인
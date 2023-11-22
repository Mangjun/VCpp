#pragma once
#include <windows.h>

enum Draw { NON, BOX, CIRCLE, CUBE, BONOBONO, RYAN }; // �׸� �� �ִ� ���� ����

void DrawShape(HWND hWnd, HDC hdc, POINT start, POINT end, Draw shape, int blink);

void DrawBoxCircle(HDC hdc, POINT max, POINT min, Draw shape); // �ڽ��� �� �׸��� �Լ�
void DrawCube(HDC hdc, const POINT start, const POINT end); // ť�� �׸��� �Լ�
void DrawBonobono(HWND hWnd, HDC hdc, int blink); // ���뺸�� �׸��� �Լ�
void DrawRyan(HWND hWnd, HDC hdc, int left, int top, int right, int bottom); // ���̾� �׸��� �Լ�

bool isDrawArea(POINT start, POINT end, RECT drawArea); // ����� ���� Ȯ��
bool IsMouseInBox(POINT last, POINT start, POINT end); // ���콺�� �ڽ� ���� �ȿ� �ִ��� Ȯ��
#include "yuhanCG.h"

void DrawBonobono(HWND hWnd, HDC hdc, int blink) {
    int minX = 280;
    int maxX = 480;
    int minY = 150;
    int maxY = 350;

    HBRUSH hBrush = CreateSolidBrush(RGB(127, 200, 255));
    SelectObject(hdc, hBrush);
    // 얼굴 그리기
    Ellipse(hdc, minX, minY, maxX, maxY);

    HBRUSH hBrush2 = CreateSolidBrush(RGB(0, 0, 0));
    HBRUSH hBrushWhite = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, hBrush2);
    // 스페이스바가 안 눌렸을 때
    if (blink == 0) {
        Ellipse(hdc, minX + abs(minX - maxX) / 6, minY + abs(minY - maxY) / 3,
            minX + abs(minX - maxX) / 6 + 10, minY + abs(minY - maxY) / 3 + 20);
        Ellipse(hdc, maxX - abs(minX - maxX) / 6, minY + abs(minY - maxY) / 3,
            maxX - abs(minX - maxX) / 6 - 10, minY + abs(minY - maxY) / 3 + 20);
        SelectObject(hdc, hBrushWhite);
        Ellipse(hdc, minX + abs(minX - maxX) / 6 + 2, minY + abs(minY - maxY) / 3 + 2,
            minX + abs(minX - maxX) / 6 + 8, minY + abs(minY - maxY) / 3 + 8);
        Ellipse(hdc, maxX - abs(minX - maxX) / 6 - 2, minY + abs(minY - maxY) / 3 + 2,
            maxX - abs(minX - maxX) / 6 - 8, minY + abs(minY - maxY) / 3 + 8);

    }

    // 스페이스바가 눌렸을 때
    else {
        MoveToEx(hdc, minX + (maxX - minX) / 6, minY + (maxY - minY) / 3, NULL);
        LineTo(hdc, minX + (maxX - minX) / 6 - 10, minY + (maxY - minY) / 3 - 10);
        MoveToEx(hdc, minX + (maxX - minX) / 6, minY + (maxY - minY) / 3, NULL);
        LineTo(hdc, minX + (maxX - minX) / 6 - 10, minY + (maxY - minY) / 3 + 10);

        MoveToEx(hdc, maxX - (maxX - minX) / 6, minY + (maxY - minY) / 3, NULL);
        LineTo(hdc, maxX - (maxX - minX) / 6 + 10, minY + (maxY - minY) / 3 - 10);
        MoveToEx(hdc, maxX - (maxX - minX) / 6, minY + (maxY - minY) / 3, NULL);
        LineTo(hdc, maxX - (maxX - minX) / 6 + 10, minY + (maxY - minY) / 3 + 10);
    }

    // 입 그리기
    HBRUSH hBrush3 = CreateSolidBrush(RGB(255, 150, 255));
    SelectObject(hdc, hBrush3);
    Ellipse(hdc, minX + abs(minX - maxX) / 2 - 15, minY + abs(minY - maxY) / 3 + 40,
        minX + abs(minX - maxX) / 2 + 15, minY + abs(minY - maxY) / 3 + 100);

    // 코 그리기
    HBRUSH hBrush4 = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, hBrush4);
    Ellipse(hdc, minX + abs(minX - maxX) / 2, minY + abs(minY - maxY) / 3 + 40,
        minX + abs(minX - maxX) / 2 - 40, minY + abs(minY - maxY) / 3 + 80);
    Ellipse(hdc, minX + abs(minX - maxX) / 2, minY + abs(minY - maxY) / 3 + 40,
        minX + abs(minX - maxX) / 2 + 40, minY + abs(minY - maxY) / 3 + 80);

    SelectObject(hdc, hBrush2);
    Ellipse(hdc, minX + abs(minX - maxX) / 2 - 15, minY + abs(minY - maxY) / 3 + 30,
        minX + abs(minX - maxX) / 2 + 15, minY + abs(minY - maxY) / 2 + 30);

    // 수염 그리기
    MoveToEx(hdc, minX + (maxX - minX) / 2 - 25, minY + (maxY - minY) / 3 * 2 - 10, NULL);
    LineTo(hdc, minX + (maxX - minX) / 2 - 60, minY + (maxY - minY) / 3 * 2 - 20);
    MoveToEx(hdc, minX + (maxX - minX) / 2 - 25, minY + (maxY - minY) / 3 * 2, NULL);
    LineTo(hdc, minX + (maxX - minX) / 2 - 60, minY + (maxY - minY) / 3 * 2 + 10);

    MoveToEx(hdc, minX + (maxX - minX) / 2 + 25, minY + (maxY - minY) / 3 * 2 - 10, NULL);
    LineTo(hdc, minX + (maxX - minX) / 2 + 60, minY + (maxY - minY) / 3 * 2 - 20);
    MoveToEx(hdc, minX + (maxX - minX) / 2 + 25, minY + (maxY - minY) / 3 * 2, NULL);
    LineTo(hdc, minX + (maxX - minX) / 2 + 60, minY + (maxY - minY) / 3 * 2 + 10);


    DeleteObject(hBrush);
    DeleteObject(hBrush2);
    DeleteObject(hBrush3);
    DeleteObject(hBrush4);
}

void DrawRyan(HWND hWnd, HDC hdc, int left, int top, int right, int bottom) {
	int maxX = left > right ? left : right;
	int minX = left > right ? right : left;
	int maxY = top > bottom ? top : bottom;
	int minY = top > bottom ? bottom : top;

	int lenX = maxX - minX;
	int lenY = maxY - minY;

	HBRUSH brown = CreateSolidBrush(RGB(255, 200, 15));
	HBRUSH black = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH white = CreateSolidBrush(RGB(255, 255, 255));

	if (bottom > top) {
        SelectObject(hdc, brown);
        // 귀 그리기
        Ellipse(hdc, minX, minY, minX + lenX / 4, minY + lenY / 4);
        Ellipse(hdc, maxX - lenX / 4, minY, maxX, minY + lenY / 4);
        // 얼굴 그리기
        Ellipse(hdc, minX, minY, maxX, maxY);

        SelectObject(hdc, black);
        // 눈썹 그리기
        MoveToEx(hdc, minX + lenX / 4 + (lenX / 4) / 2, minY + lenY / 4 + (lenY / 4) / 10, NULL);
        LineTo(hdc, minX + lenX / 4 - (lenX / 4) / 2, minY + lenY / 4 + (lenY / 4) / 10);
        MoveToEx(hdc, minX + lenX / 4 + (lenX / 4) / 2, minY + lenY / 4 + (lenY / 4) / 10 * 2, NULL);
        LineTo(hdc, minX + lenX / 4 - (lenX / 4) / 2, minY + lenY / 4 + (lenY / 4) / 10 * 2);
        MoveToEx(hdc, minX + lenX / 4 + (lenX / 4) / 2, minY + lenY / 4 + (lenY / 4) / 10 * 3, NULL);
        LineTo(hdc, minX + lenX / 4 - (lenX / 4) / 2, minY + lenY / 4 + (lenY / 4) / 10 * 3);

        MoveToEx(hdc, maxX - lenX / 4 + (lenX / 4) / 2, minY + lenY / 4 + (lenY / 4) / 10, NULL);
        LineTo(hdc, maxX - lenX / 4 - (lenX / 4) / 2, minY + lenY / 4 + (lenY / 4) / 10);
        MoveToEx(hdc, maxX - lenX / 4 + (lenX / 4) / 2, minY + lenY / 4 + (lenY / 4) / 10 * 2, NULL);
        LineTo(hdc, maxX - lenX / 4 - (lenX / 4) / 2, minY + lenY / 4 + (lenY / 4) / 10 * 2);
        MoveToEx(hdc, maxX - lenX / 4 + (lenX / 4) / 2, minY + lenY / 4 + (lenY / 4) / 10 * 3, NULL);
        LineTo(hdc, maxX - lenX / 4 - (lenX / 4) / 2, minY + lenY / 4 + (lenY / 4) / 10 * 3);

        // 눈 그리기
        Ellipse(hdc, minX + lenX / 4 - (((lenX / 4) / 10 * 2) - lenX / 4 > 13 ? 2 : ((lenX / 4) / 10)),
            minY + lenY / 4 + (lenY / 4 / 2) + (((lenY / 4) / 10 * 2) > 13 ? 5 : ((lenY / 4) / 10)),
            minX + lenX / 4 + (((lenX / 4) / 10 * 2) - lenX / 4 > 13 ? 4 : ((lenX / 4) / 10 * 2)),
            minY + lenY / 4 + (lenY / 4 / 2) + (((lenY / 4) / 10 * 2) > 13 ? 20 : ((lenY / 4) / 10 * 2) * 2));
        Ellipse(hdc, maxX - lenX / 4 - (((lenX / 4) / 10 * 2) - lenX / 4 > 13 ? 2 : ((lenX / 4) / 10)),
            minY + lenY / 4 + (lenY / 4 / 2) + (((lenY / 4) / 10 * 2) > 13 ? 5 : ((lenY / 4) / 10)),
            maxX - lenX / 4 + (((lenX / 4) / 10 * 2) - lenX / 4 > 13 ? 4 : ((lenX / 4) / 10 * 2)),
            minY + lenY / 4 + (lenY / 4 / 2) + (((lenY / 4) / 10 * 2) > 13 ? 20 : ((lenY / 4) / 10 * 2) * 2));

        SelectObject(hdc, white);

        // 코 그리기
        Ellipse(hdc, minX + lenX / 2 - (lenX / 7),
            minY + lenY / 2 + (lenY / 10),
            minX + lenX / 2,
            minY + lenY / 2 + (lenY / 10) * 2);
        Ellipse(hdc, minX + lenX / 2 + (lenX / 7),
            minY + lenY / 2 + (lenY / 10),
            minX + lenX / 2,
            minY + lenY / 2 + (lenY / 10) * 2);
	}
	else {
        SelectObject(hdc, brown);
        // 귀 그리기
        Ellipse(hdc, minX, maxY, minX + lenX / 4, maxY - lenY / 4);
        Ellipse(hdc, maxX - lenX / 4, maxY, maxX, maxY - lenY / 4);
        // 얼굴 그리기
        Ellipse(hdc, minX, minY, maxX, maxY);

        SelectObject(hdc, black);
        // 눈썹 그리기
        MoveToEx(hdc, minX + lenX / 4 + (lenX / 4) / 2, maxY - lenY / 4 - (lenY / 4) / 10, NULL);
        LineTo(hdc, minX + lenX / 4 - (lenX / 4) / 2, maxY - lenY / 4 - (lenY / 4) / 10);
        MoveToEx(hdc, minX + lenX / 4 + (lenX / 4) / 2, maxY - lenY / 4 - (lenY / 4) / 10 * 2, NULL);
        LineTo(hdc, minX + lenX / 4 - (lenX / 4) / 2, maxY - lenY / 4 - (lenY / 4) / 10 * 2);
        MoveToEx(hdc, minX + lenX / 4 + (lenX / 4) / 2, maxY - lenY / 4 - (lenY / 4) / 10 * 3, NULL);
        LineTo(hdc, minX + lenX / 4 - (lenX / 4) / 2, maxY - lenY / 4 - (lenY / 4) / 10 * 3);

        MoveToEx(hdc, maxX - lenX / 4 + (lenX / 4) / 2, maxY - lenY / 4 - (lenY / 4) / 10, NULL);
        LineTo(hdc, maxX - lenX / 4 - (lenX / 4) / 2, maxY - lenY / 4 - (lenY / 4) / 10);
        MoveToEx(hdc, maxX - lenX / 4 + (lenX / 4) / 2, maxY - lenY / 4 - (lenY / 4) / 10 * 2, NULL);
        LineTo(hdc, maxX - lenX / 4 - (lenX / 4) / 2, maxY - lenY / 4 - (lenY / 4) / 10 * 2);
        MoveToEx(hdc, maxX - lenX / 4 + (lenX / 4) / 2, maxY - lenY / 4 - (lenY / 4) / 10 * 3, NULL);
        LineTo(hdc, maxX - lenX / 4 - (lenX / 4) / 2, maxY - lenY / 4 - (lenY / 4) / 10 * 3);

        // 눈 그리기
        Ellipse(hdc, minX + lenX / 4 - (((lenX / 4) / 10 * 2) - lenX / 4 > 13 ? 2 : ((lenX / 4) / 10)),
            maxY - lenY / 4 - (lenY / 4 / 2) - (((lenY / 4) / 10 * 2) > 13 ? 5 : ((lenY / 4) / 10)),
            minX + lenX / 4 + (((lenX / 4) / 10 * 2) - lenX / 4 > 13 ? 4 : ((lenX / 4) / 10 * 2)),
            maxY - lenY / 4 - (lenY / 4 / 2) - (((lenY / 4) / 10 * 2) > 13 ? 20 : ((lenY / 4) / 10 * 2) * 2));
        Ellipse(hdc, maxX - lenX / 4 - (((lenX / 4) / 10 * 2) - lenX / 4 > 13 ? 2 : ((lenX / 4) / 10)),
            maxY - lenY / 4 - (lenY / 4 / 2) - (((lenY / 4) / 10 * 2) > 13 ? 5 : ((lenY / 4) / 10)),
            maxX - lenX / 4 + (((lenX / 4) / 10 * 2) - lenX / 4 > 13 ? 4 : ((lenX / 4) / 10 * 2)),
            maxY - lenY / 4 - (lenY / 4 / 2) - (((lenY / 4) / 10 * 2) > 13 ? 20 : ((lenY / 4) / 10 * 2) * 2));

        SelectObject(hdc, white);

        // 코 그리기
        Ellipse(hdc, minX + lenX / 2 - (lenX / 7),
            maxY - lenY / 2,
            minX + lenX / 2,
            maxY - lenY / 2 - (lenY / 10));
        Ellipse(hdc, minX + lenX / 2 + (lenX / 7),
            maxY - lenY / 2,
            minX + lenX / 2,
            maxY - lenY / 2 - (lenY / 10));
	}

    DeleteObject(brown);
    DeleteObject(black);
    DeleteObject(white);
}
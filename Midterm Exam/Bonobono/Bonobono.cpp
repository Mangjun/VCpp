#include <windows.h>

// 그릴 수 있는 도형들
enum Draw { BOX, CIRCLE, CUBE, BONOBONO, RYAN, NON };

Draw shape = NON; // 현재 선택된 도형

POINT startPoint = { 0 }; // 시작점 좌표
POINT endPoint = { 0 }; // 끝점 좌표
POINT lastPoint = { 0 }; // 마지막 커서 좌표
POINT max = { 0 }; // 큰 좌표
POINT min = { 0 }; // 작은 좌표

RECT Box = { 8, 8, 792, 472 };
RECT drawArea = { 16, 112, 784, 464 };

bool isDrawing = false; // 좌클릭 여부
bool isMoving = false; // 우클릭 여부
bool isInBox = false; // 커서가 범위 안에 있는지 여부
bool isCircleSize = false; // 원 우클릭 여부
bool isCubeSize = false; // 큐브 좌클릭 여부
bool isSpacebar = false; // 스페이스바 여부

// 큰 좌표와 작은 좌표 구하는 함수
void MaxMin() {
    max.x = startPoint.x > endPoint.x ? startPoint.x : endPoint.x;
    max.y = startPoint.y > endPoint.y ? startPoint.y : endPoint.y;

    min.x = startPoint.x < endPoint.x ? startPoint.x : endPoint.x;
    min.y = startPoint.y < endPoint.y ? startPoint.y : endPoint.y;
}

// 드로우 영역에 있는지 확인하는 함수
bool isDrawArea() {
    MaxMin();
    return min.x >= 16 && max.x >= 16 && min.y >= 112 && max.y >= 112 &&
        min.x <= 784 && max.x <= 784 && min.y <= 464 && max.y <= 464;
}

// 마우스가 박스 범위 안에 있는지 확인하는 함수
bool IsMouseInBox(POINT last, POINT start, POINT end) {
    if (end.x > start.x && end.y > start.y) {
        return (last.x >= start.x && last.x <= end.x &&
            last.y >= start.y && last.y <= end.y);
    }
    else if (end.x > start.x && end.y < start.y) {
        return (last.x >= start.x && last.x <= end.x &&
            last.y <= start.y && last.y >= end.y);
    }
    else if (end.x < start.x && end.y > start.y) {
        return (last.x <= start.x && last.x >= end.x &&
            last.y >= start.y && last.y <= end.y);
    }
    else {
        return (last.x <= start.x && last.x >= end.x &&
            last.y <= start.y && last.y >= end.y);
    }
}

// 박스와 원 그리는 함수
void DrawBoxCircle(HDC hdc) {
    MaxMin();
    if (isDrawArea()) {
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
        SelectObject(hdc, hBrush);
        if (shape == BOX) {
            Rectangle(hdc, min.x, min.y, max.x, max.y);
        }
        else if (shape == CIRCLE) {
            Ellipse(hdc, min.x, min.y, max.x, max.y);
        }
        DeleteObject(hBrush);
    }
}

// 큐브 그리는 함수
void DrawCube(HDC hdc, const POINT start, const POINT end) {
    MaxMin();

    if (isDrawArea()) {
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
        SelectObject(hdc, hBrush);

        Rectangle(hdc, min.x, min.y, max.x, max.y);

        if (endPoint.x > startPoint.x && endPoint.y > startPoint.y) {
            MoveToEx(hdc, min.x, min.y, NULL);
            LineTo(hdc, min.x + (max.x - min.x) / 4, min.y - (max.y - min.y) / 4);
            LineTo(hdc, max.x + (max.x - min.x) / 4, min.y - (max.y - min.y) / 4);
            LineTo(hdc, max.x, min.y);

            MoveToEx(hdc, min.x, max.y, NULL);
            LineTo(hdc, min.x + (max.x - min.x) / 4, max.y - (max.y - min.y) / 4);
            LineTo(hdc, max.x + (max.x - min.x) / 4, max.y - (max.y - min.y) / 4);
            LineTo(hdc, max.x, max.y);

            MoveToEx(hdc, min.x + (max.x - min.x) / 4, min.y - (max.y - min.y) / 4, NULL);
            LineTo(hdc, min.x + (max.x - min.x) / 4, max.y - (max.y - min.y) / 4);

            MoveToEx(hdc, max.x + (max.x - min.x) / 4, min.y - (max.y - min.y) / 4, NULL);
            LineTo(hdc, max.x + (max.x - min.x) / 4, max.y - (max.y - min.y) / 4);
        }
        else if (endPoint.x > startPoint.x && endPoint.y < startPoint.y) {
            MoveToEx(hdc, min.x, min.y, NULL);
            LineTo(hdc, min.x + (max.x - min.x) / 4, min.y - (max.y - min.y) / 4);
            LineTo(hdc, max.x + (max.x - min.x) / 4, min.y - (max.y - min.y) / 4);
            LineTo(hdc, max.x, min.y);

            MoveToEx(hdc, min.x, max.y, NULL);
            LineTo(hdc, min.x + (max.x - min.x) / 4, max.y - (max.y - min.y) / 4);
            LineTo(hdc, max.x + (max.x - min.x) / 4, max.y - (max.y - min.y) / 4);
            LineTo(hdc, max.x, max.y);

            MoveToEx(hdc, min.x + (max.x - min.x) / 4, min.y - (max.y - min.y) / 4, NULL);
            LineTo(hdc, min.x + (max.x - min.x) / 4, max.y - (max.y - min.y) / 4);

            MoveToEx(hdc, max.x + (max.x - min.x) / 4, min.y - (max.y - min.y) / 4, NULL);
            LineTo(hdc, max.x + (max.x - min.x) / 4, max.y - (max.y - min.y) / 4);
        }
        else if (endPoint.x < startPoint.x && endPoint.y > startPoint.y) {
            MoveToEx(hdc, min.x, min.y, NULL);
            LineTo(hdc, min.x - (max.x - min.x) / 4, min.y - (max.y - min.y) / 4);
            LineTo(hdc, max.x - (max.x - min.x) / 4, min.y - (max.y - min.y) / 4);
            LineTo(hdc, max.x, min.y);

            MoveToEx(hdc, min.x, max.y, NULL);
            LineTo(hdc, min.x - (max.x - min.x) / 4, max.y - (max.y - min.y) / 4);
            LineTo(hdc, max.x - (max.x - min.x) / 4, max.y - (max.y - min.y) / 4);
            LineTo(hdc, max.x, max.y);

            MoveToEx(hdc, min.x - (max.x - min.x) / 4, min.y - (max.y - min.y) / 4, NULL);
            LineTo(hdc, min.x - (max.x - min.x) / 4, max.y - (max.y - min.y) / 4);

            MoveToEx(hdc, max.x - (max.x - min.x) / 4, min.y - (max.y - min.y) / 4, NULL);
            LineTo(hdc, max.x - (max.x - min.x) / 4, max.y - (max.y - min.y) / 4);
        }
        else {
            MoveToEx(hdc, min.x, min.y, NULL);
            LineTo(hdc, min.x - (max.x - min.x) / 4, min.y - (max.y - min.y) / 4);
            LineTo(hdc, max.x - (max.x - min.x) / 4, min.y - (max.y - min.y) / 4);
            LineTo(hdc, max.x, min.y);

            MoveToEx(hdc, min.x, max.y, NULL);
            LineTo(hdc, min.x - (max.x - min.x) / 4, max.y - (max.y - min.y) / 4);
            LineTo(hdc, max.x - (max.x - min.x) / 4, max.y - (max.y - min.y) / 4);
            LineTo(hdc, max.x, max.y);

            MoveToEx(hdc, min.x - (max.x - min.x) / 4, min.y - (max.y - min.y) / 4, NULL);
            LineTo(hdc, min.x - (max.x - min.x) / 4, max.y - (max.y - min.y) / 4);

            MoveToEx(hdc, max.x - (max.x - min.x) / 4, min.y - (max.y - min.y) / 4, NULL);
            LineTo(hdc, max.x - (max.x - min.x) / 4, max.y - (max.y - min.y) / 4);
        }
        DeleteObject(hBrush);
    }
}

// 보노보노 그리는 함수
void DrawBonobono(HDC hdc) {
    //MaxMin();
    min.x = 280;
    max.x = 480;
    min.y = 150;
    max.y = 350;

    //if (isDrawArea()) {
    HBRUSH hBrush = CreateSolidBrush(RGB(127, 200, 255));
    SelectObject(hdc, hBrush);
    // 얼굴 그리기
    Ellipse(hdc, min.x, min.y, max.x, max.y);

    HBRUSH hBrush2 = CreateSolidBrush(RGB(0, 0, 0));
    HBRUSH hBrushWhite = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, hBrush2);
    // 스페이스바가 안 눌렸을 때
    if (!isSpacebar) {
        Ellipse(hdc, min.x + abs(min.x - max.x) / 6, min.y + abs(min.y - max.y) / 3,
            min.x + abs(min.x - max.x) / 6 + 10, min.y + abs(min.y - max.y) / 3 + 20);
        Ellipse(hdc, max.x - abs(min.x - max.x) / 6, min.y + abs(min.y - max.y) / 3,
            max.x - abs(min.x - max.x) / 6 - 10, min.y + abs(min.y - max.y) / 3 + 20);
        SelectObject(hdc, hBrushWhite);
        Ellipse(hdc, min.x + abs(min.x - max.x) / 6 + 2, min.y + abs(min.y - max.y) / 3 + 2,
            min.x + abs(min.x - max.x) / 6 + 8, min.y + abs(min.y - max.y) / 3 + 8);
        Ellipse(hdc, max.x - abs(min.x - max.x) / 6 - 2, min.y + abs(min.y - max.y) / 3 + 2,
            max.x - abs(min.x - max.x) / 6 - 8, min.y + abs(min.y - max.y) / 3 + 8);

    }

    // 스페이스바가 눌렸을 때
    else {
        MoveToEx(hdc, min.x + (max.x - min.x) / 6, min.y + (max.y - min.y) / 3, NULL);
        LineTo(hdc, min.x + (max.x - min.x) / 6 - 10, min.y + (max.y - min.y) / 3 - 10);
        MoveToEx(hdc, min.x + (max.x - min.x) / 6, min.y + (max.y - min.y) / 3, NULL);
        LineTo(hdc, min.x + (max.x - min.x) / 6 - 10, min.y + (max.y - min.y) / 3 + 10);

        MoveToEx(hdc, max.x - (max.x - min.x) / 6, min.y + (max.y - min.y) / 3, NULL);
        LineTo(hdc, max.x - (max.x - min.x) / 6 + 10, min.y + (max.y - min.y) / 3 - 10);
        MoveToEx(hdc, max.x - (max.x - min.x) / 6, min.y + (max.y - min.y) / 3, NULL);
        LineTo(hdc, max.x - (max.x - min.x) / 6 + 10, min.y + (max.y - min.y) / 3 + 10);
    }

    // 입 그리기
    HBRUSH hBrush3 = CreateSolidBrush(RGB(255, 150, 255));
    SelectObject(hdc, hBrush3);
    Ellipse(hdc, min.x + abs(min.x - max.x) / 2 - 15, min.y + abs(min.y - max.y) / 3 + 40,
        min.x + abs(min.x - max.x) / 2 + 15, min.y + abs(min.y - max.y) / 3 + 100);

    // 코 그리기
    HBRUSH hBrush4 = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, hBrush4);
    Ellipse(hdc, min.x + abs(min.x - max.x) / 2, min.y + abs(min.y - max.y) / 3 + 40,
        min.x + abs(min.x - max.x) / 2 - 40, min.y + abs(min.y - max.y) / 3 + 80);
    Ellipse(hdc, min.x + abs(min.x - max.x) / 2, min.y + abs(min.y - max.y) / 3 + 40,
        min.x + abs(min.x - max.x) / 2 + 40, min.y + abs(min.y - max.y) / 3 + 80);

    SelectObject(hdc, hBrush2);
    Ellipse(hdc, min.x + abs(min.x - max.x) / 2 - 15, min.y + abs(min.y - max.y) / 3 + 30,
        min.x + abs(min.x - max.x) / 2 + 15, min.y + abs(min.y - max.y) / 2 + 30);

    // 수염 그리기
    MoveToEx(hdc, min.x + (max.x - min.x) / 2 - 25, min.y + (max.y - min.y) / 3 * 2 - 10, NULL);
    LineTo(hdc, min.x + (max.x - min.x) / 2 - 60, min.y + (max.y - min.y) / 3 * 2 - 20);
    MoveToEx(hdc, min.x + (max.x - min.x) / 2 - 25, min.y + (max.y - min.y) / 3 * 2, NULL);
    LineTo(hdc, min.x + (max.x - min.x) / 2 - 60, min.y + (max.y - min.y) / 3 * 2 + 10);

    MoveToEx(hdc, min.x + (max.x - min.x) / 2 + 25, min.y + (max.y - min.y) / 3 * 2 - 10, NULL);
    LineTo(hdc, min.x + (max.x - min.x) / 2 + 60, min.y + (max.y - min.y) / 3 * 2 - 20);
    MoveToEx(hdc, min.x + (max.x - min.x) / 2 + 25, min.y + (max.y - min.y) / 3 * 2, NULL);
    LineTo(hdc, min.x + (max.x - min.x) / 2 + 60, min.y + (max.y - min.y) / 3 * 2 + 10);


    DeleteObject(hBrush);
    DeleteObject(hBrush2);
    DeleteObject(hBrush3);
    DeleteObject(hBrush4);
    //}
}

// 라이언 그리는 함수
void DrawRyan(HDC hdc) {
    MaxMin();

    int lenX = max.x - min.x;
    int lenY = max.y - min.y;

    if (isDrawArea()) {
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 200, 15));
        HBRUSH hBrush2 = CreateSolidBrush(RGB(0, 0, 0));
        HBRUSH hBrush3 = CreateSolidBrush(RGB(255, 255, 255));
        if (endPoint.y > startPoint.y) {
            SelectObject(hdc, hBrush);
            // 귀 그리기
            Ellipse(hdc, min.x, min.y, min.x + lenX / 4, min.y + lenY / 4);
            Ellipse(hdc, max.x - lenX / 4, min.y, max.x, min.y + lenY / 4);
            // 얼굴 그리기
            Ellipse(hdc, min.x, min.y, max.x, max.y);

            SelectObject(hdc, hBrush2);
            // 눈썹 그리기
            MoveToEx(hdc, min.x + lenX / 4 + (lenX / 4) / 2, min.y + lenY / 4 + (lenY / 4) / 10, NULL);
            LineTo(hdc, min.x + lenX / 4 - (lenX / 4) / 2, min.y + lenY / 4 + (lenY / 4) / 10);
            MoveToEx(hdc, min.x + lenX / 4 + (lenX / 4) / 2, min.y + lenY / 4 + (lenY / 4) / 10 * 2, NULL);
            LineTo(hdc, min.x + lenX / 4 - (lenX / 4) / 2, min.y + lenY / 4 + (lenY / 4) / 10 * 2);
            MoveToEx(hdc, min.x + lenX / 4 + (lenX / 4) / 2, min.y + lenY / 4 + (lenY / 4) / 10 * 3, NULL);
            LineTo(hdc, min.x + lenX / 4 - (lenX / 4) / 2, min.y + lenY / 4 + (lenY / 4) / 10 * 3);

            MoveToEx(hdc, max.x - lenX / 4 + (lenX / 4) / 2, min.y + lenY / 4 + (lenY / 4) / 10, NULL);
            LineTo(hdc, max.x - lenX / 4 - (lenX / 4) / 2, min.y + lenY / 4 + (lenY / 4) / 10);
            MoveToEx(hdc, max.x - lenX / 4 + (lenX / 4) / 2, min.y + lenY / 4 + (lenY / 4) / 10 * 2, NULL);
            LineTo(hdc, max.x - lenX / 4 - (lenX / 4) / 2, min.y + lenY / 4 + (lenY / 4) / 10 * 2);
            MoveToEx(hdc, max.x - lenX / 4 + (lenX / 4) / 2, min.y + lenY / 4 + (lenY / 4) / 10 * 3, NULL);
            LineTo(hdc, max.x - lenX / 4 - (lenX / 4) / 2, min.y + lenY / 4 + (lenY / 4) / 10 * 3);

            // 눈 그리기
            Ellipse(hdc, min.x + lenX / 4 - (((lenX / 4) / 10 * 2) - lenX / 4 > 13 ? 2 : ((lenX / 4) / 10)),
                min.y + lenY / 4 + (lenY / 4 / 2) + (((lenY / 4) / 10 * 2) > 13 ? 5 : ((lenY / 4) / 10)),
                min.x + lenX / 4 + (((lenX / 4) / 10 * 2) - lenX / 4 > 13 ? 4 : ((lenX / 4) / 10 * 2)),
                min.y + lenY / 4 + (lenY / 4 / 2) + (((lenY / 4) / 10 * 2) > 13 ? 20 : ((lenY / 4) / 10 * 2) * 2));
            Ellipse(hdc, max.x - lenX / 4 - (((lenX / 4) / 10 * 2) - lenX / 4 > 13 ? 2 : ((lenX / 4) / 10)),
                min.y + lenY / 4 + (lenY / 4 / 2) + (((lenY / 4) / 10 * 2) > 13 ? 5 : ((lenY / 4) / 10)),
                max.x - lenX / 4 + (((lenX / 4) / 10 * 2) - lenX / 4 > 13 ? 4 : ((lenX / 4) / 10 * 2)),
                min.y + lenY / 4 + (lenY / 4 / 2) + (((lenY / 4) / 10 * 2) > 13 ? 20 : ((lenY / 4) / 10 * 2) * 2));

            SelectObject(hdc, hBrush3);

            // 코 그리기
            Ellipse(hdc, min.x + lenX / 2 - (lenX / 7),
                min.y + lenY / 2 + (lenY / 10),
                min.x + lenX / 2,
                min.y + lenY / 2 + (lenY / 10) * 2);
            Ellipse(hdc, min.x + lenX / 2 + (lenX / 7),
                min.y + lenY / 2 + (lenY / 10),
                min.x + lenX / 2,
                min.y + lenY / 2 + (lenY / 10) * 2);
        }
        else {
            SelectObject(hdc, hBrush);
            // 귀 그리기
            Ellipse(hdc, min.x, max.y, min.x + lenX / 4, max.y - lenY / 4);
            Ellipse(hdc, max.x - lenX / 4, max.y, max.x, max.y - lenY / 4);
            // 얼굴 그리기
            Ellipse(hdc, min.x, min.y, max.x, max.y);

            SelectObject(hdc, hBrush2);
            // 눈썹 그리기
            MoveToEx(hdc, min.x + lenX / 4 + (lenX / 4) / 2, max.y - lenY / 4 - (lenY / 4) / 10, NULL);
            LineTo(hdc, min.x + lenX / 4 - (lenX / 4) / 2, max.y - lenY / 4 - (lenY / 4) / 10);
            MoveToEx(hdc, min.x + lenX / 4 + (lenX / 4) / 2, max.y - lenY / 4 - (lenY / 4) / 10 * 2, NULL);
            LineTo(hdc, min.x + lenX / 4 - (lenX / 4) / 2, max.y - lenY / 4 - (lenY / 4) / 10 * 2);
            MoveToEx(hdc, min.x + lenX / 4 + (lenX / 4) / 2, max.y - lenY / 4 - (lenY / 4) / 10 * 3, NULL);
            LineTo(hdc, min.x + lenX / 4 - (lenX / 4) / 2, max.y - lenY / 4 - (lenY / 4) / 10 * 3);

            MoveToEx(hdc, max.x - lenX / 4 + (lenX / 4) / 2, max.y - lenY / 4 - (lenY / 4) / 10, NULL);
            LineTo(hdc, max.x - lenX / 4 - (lenX / 4) / 2, max.y - lenY / 4 - (lenY / 4) / 10);
            MoveToEx(hdc, max.x - lenX / 4 + (lenX / 4) / 2, max.y - lenY / 4 - (lenY / 4) / 10 * 2, NULL);
            LineTo(hdc, max.x - lenX / 4 - (lenX / 4) / 2, max.y - lenY / 4 - (lenY / 4) / 10 * 2);
            MoveToEx(hdc, max.x - lenX / 4 + (lenX / 4) / 2, max.y - lenY / 4 - (lenY / 4) / 10 * 3, NULL);
            LineTo(hdc, max.x - lenX / 4 - (lenX / 4) / 2, max.y - lenY / 4 - (lenY / 4) / 10 * 3);

            // 눈 그리기
            Ellipse(hdc, min.x + lenX / 4 - (((lenX / 4) / 10 * 2) - lenX / 4 > 13 ? 2 : ((lenX / 4) / 10)),
                max.y - lenY / 4 - (lenY / 4 / 2) - (((lenY / 4) / 10 * 2) > 13 ? 5 : ((lenY / 4) / 10)),
                min.x + lenX / 4 + (((lenX / 4) / 10 * 2) - lenX / 4 > 13 ? 4 : ((lenX / 4) / 10 * 2)),
                max.y - lenY / 4 - (lenY / 4 / 2) - (((lenY / 4) / 10 * 2) > 13 ? 20 : ((lenY / 4) / 10 * 2) * 2));
            Ellipse(hdc, max.x - lenX / 4 - (((lenX / 4) / 10 * 2) - lenX / 4 > 13 ? 2 : ((lenX / 4) / 10)),
                max.y - lenY / 4 - (lenY / 4 / 2) - (((lenY / 4) / 10 * 2) > 13 ? 5 : ((lenY / 4) / 10)),
                max.x - lenX / 4 + (((lenX / 4) / 10 * 2) - lenX / 4 > 13 ? 4 : ((lenX / 4) / 10 * 2)),
                max.y - lenY / 4 - (lenY / 4 / 2) - (((lenY / 4) / 10 * 2) > 13 ? 20 : ((lenY / 4) / 10 * 2) * 2));

            SelectObject(hdc, hBrush3);

            // 코 그리기
            Ellipse(hdc, min.x + lenX / 2 - (lenX / 7),
                max.y - lenY / 2,
                min.x + lenX / 2,
                max.y - lenY / 2 - (lenY / 10));
            Ellipse(hdc, min.x + lenX / 2 + (lenX / 7),
                max.y - lenY / 2,
                min.x + lenX / 2,
                max.y - lenY / 2 - (lenY / 10));
        }

        DeleteObject(hBrush);
        DeleteObject(hBrush2);
        DeleteObject(hBrush3);
    }
}

void DrawShape(HDC hdc, Draw shape) {
    switch (shape)
    {
    case BOX: // Box 선택
        DrawBoxCircle(hdc);
        break;
    case CIRCLE: // Circle 선택
        DrawBoxCircle(hdc);
        break;
    case CUBE: // Cube 선택
        DrawCube(hdc, startPoint, endPoint);
        break;
    case BONOBONO: // Bonobono 선택
        DrawBonobono(hdc);
        break;
    case RYAN: // Ryan 선택
        DrawRyan(hdc);
        break;
    default:
        break;
    }
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_COMMAND:
        InvalidateRect(hWnd, NULL, TRUE); // WM_PAINT 호출
        // Box 버튼 클릭
        if (LOWORD(wParam) == 1) {
            shape = BOX; // Box 선택
        }
        // Circle 버튼 클릭
        else if (LOWORD(wParam) == 2) {
            shape = CIRCLE; // Circle 선택
        }
        // Cube 버튼 클릭
        else if (LOWORD(wParam) == 3) {
            shape = CUBE; // Cube 선택
        }
        // Bonobono 버튼 클릭
        else if (LOWORD(wParam) == 4) {
            shape = BONOBONO; // Bonobono 선택
        }
        // Ryan 버튼 클릭
        else if (LOWORD(wParam) == 5) {
            shape = RYAN; // Ryan 선택
        }
        // 좌표 초기화
        startPoint = { 0 };
        endPoint = { 0 };
        SetFocus(hWnd); // 윈도우로 포커스 이동
        break;
    case WM_LBUTTONDOWN: {
        isDrawing = true;
        if (shape == CUBE && isDrawArea()) {
            lastPoint.x = LOWORD(lParam);
            lastPoint.y = HIWORD(lParam);
            if (IsMouseInBox(lastPoint, startPoint, endPoint)) {
                isCubeSize = true;
                isDrawing = false;
            }
        }
        if (isDrawing) {
            startPoint.x = LOWORD(lParam);
            startPoint.y = HIWORD(lParam);
        }
        break;
    }
    case WM_LBUTTONUP: {
        isDrawing = false;
        isCubeSize = false;
        break;
    }
    case WM_RBUTTONDOWN: {
        if (shape == BOX) {
            isMoving = true;

            // 마우스 커서 위치 받기
            lastPoint.x = LOWORD(lParam);
            lastPoint.y = HIWORD(lParam);

            // 커서가 도형 범위 안에 있는지 확인
            if (IsMouseInBox(lastPoint, startPoint, endPoint))
            {
                isInBox = true;
            }
            else
            {
                isInBox = false;
            }
        }
        else if (shape == CIRCLE) {
            isCircleSize = true;
        }
        else if (shape == CUBE) {
            isMoving = true;

            // 마우스 커서 위치 받기
            lastPoint.x = LOWORD(lParam);
            lastPoint.y = HIWORD(lParam);

            // 커서가 도형 범위 안에 있는지 확인
            if (IsMouseInBox(lastPoint, startPoint, endPoint))
            {
                isInBox = true;
            }
            else
            {
                isInBox = false;
            }
        }
        break;
    }
    case WM_RBUTTONUP: {
        if (shape == BOX) {
            isMoving = false;
        }
        else if (shape == CIRCLE) {
            isCircleSize = false;
        }
        else if (shape == CUBE) {
            isMoving = false;
        }
        break;
    }
    case WM_KEYDOWN:
        if (wParam == VK_SPACE) {
            isSpacebar = true;
            if (shape == BONOBONO) {
                InvalidateRect(hWnd, NULL, TRUE);
            }
        }
        break;
    case WM_KEYUP:
        isSpacebar = false;
        if (shape == BONOBONO) {
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 0));

        FrameRect(hdc, &Box, hBrush); // Box 테두리 그리기
        FrameRect(hdc, &drawArea, hBrush); // drawArea 테두리 그리기
        FillRect(hdc, &drawArea, CreateSolidBrush(RGB(255, 255, 255))); // 흰 배경으로 채우기

        DrawShape(hdc, shape);

        DeleteObject(hBrush);
        EndPaint(hWnd, &ps);
        break;
    }
    case WM_MOUSEMOVE: {
        POINT mousePos;
        GetCursorPos(&mousePos);
        ScreenToClient(hWnd, &mousePos);

        // 커서 바꾸기
        if (PtInRect(&drawArea, mousePos)) {
            SetCursor(LoadCursor(NULL, IDC_CROSS));
        }
        else {
            SetCursor(LoadCursor(NULL, IDC_ARROW));
        }

        if (isDrawing) {
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);
            InvalidateRect(hWnd, NULL, TRUE);
        }

        // Box 범위 안에서 우클릭 시
        if (shape == BOX && isMoving && isInBox) {
            int deltaX = LOWORD(lParam) - lastPoint.x;
            int deltaY = HIWORD(lParam) - lastPoint.y;

            startPoint.x += deltaX;
            startPoint.y += deltaY;
            endPoint.x += deltaX;
            endPoint.y += deltaY;

            lastPoint.x = LOWORD(lParam);
            lastPoint.y = HIWORD(lParam);

            InvalidateRect(hWnd, NULL, TRUE);
        }

        // Cube 범위 안에서 우클릭 시
        if (shape == CUBE && isMoving && isInBox) {
            int deltaX = LOWORD(lParam) - lastPoint.x;
            int deltaY = HIWORD(lParam) - lastPoint.y;

            startPoint.x += deltaX;
            startPoint.y += deltaY;
            endPoint.x += deltaX;
            endPoint.y += deltaY;

            lastPoint.x = LOWORD(lParam);
            lastPoint.y = HIWORD(lParam);

            InvalidateRect(hWnd, NULL, TRUE);
        }

        // Cube 범위 안에서 좌클릭 시
        if (isCubeSize) {
            int maxX = startPoint.x > endPoint.x ? startPoint.x : endPoint.x;

            int deltaX = LOWORD(lParam) - maxX;

            // 커서를 오른쪽으로 갈 때
            if (deltaX > 0) {
                if (endPoint.x > startPoint.x && endPoint.y > startPoint.y) {
                    endPoint.x = endPoint.x + (long)(endPoint.x * 0.1);
                }
                else if (endPoint.x > startPoint.x && endPoint.y < startPoint.y) {
                    endPoint.x = endPoint.x + (long)(endPoint.x * 0.1);
                }
                else if (endPoint.x < startPoint.x && endPoint.y > startPoint.y) {
                    startPoint.x = startPoint.x + (long)(startPoint.x * 0.1);
                }
                else {
                    startPoint.x = startPoint.x + (long)(startPoint.x * 0.1);
                }
            }
            // 커서를 왼쪽으로 갈 때
            else {
                if (endPoint.x > startPoint.x && endPoint.y > startPoint.y) {
                    endPoint.x = endPoint.x - (long)(endPoint.x * 0.1);
                }
                else if (endPoint.x > startPoint.x && endPoint.y < startPoint.y) {
                    endPoint.x = endPoint.x - (long)(endPoint.x * 0.1);
                }
                else if (endPoint.x < startPoint.x && endPoint.y > startPoint.y) {
                    startPoint.x = startPoint.x - (long)(startPoint.x * 0.1);
                }
                else {
                    startPoint.x = startPoint.x - (long)(startPoint.x * 0.1);
                }
            }

            lastPoint.x = LOWORD(lParam);
            lastPoint.y = HIWORD(lParam);

            InvalidateRect(hWnd, NULL, TRUE);
        }

        // Circle 범위 안에서 우클릭 시
        if (isCircleSize) {
            int maxX = startPoint.x > endPoint.x ? startPoint.x : endPoint.x;

            int deltaX = LOWORD(lParam) - maxX;

            // 커서를 오른쪽으로 갈 때
            if (deltaX > 0) {
                if (endPoint.x > startPoint.x && endPoint.y > startPoint.y) {
                    endPoint.x = endPoint.x + (long)(endPoint.x * 0.1);
                }
                else if (endPoint.x > startPoint.x && endPoint.y < startPoint.y) {
                    endPoint.x = endPoint.x + (long)(endPoint.x * 0.1);
                }
                else if (endPoint.x < startPoint.x && endPoint.y > startPoint.y) {
                    startPoint.x = startPoint.x + (long)(startPoint.x * 0.1);
                }
                else {
                    startPoint.x = startPoint.x + (long)(startPoint.x * 0.1);
                }
            }
            // 커서를 왼쪽으로 갈 때
            else {
                if (endPoint.x > startPoint.x && endPoint.y > startPoint.y) {
                    endPoint.x = endPoint.x - (long)(endPoint.x * 0.1);
                }
                else if (endPoint.x > startPoint.x && endPoint.y < startPoint.y) {
                    endPoint.x = endPoint.x - (long)(endPoint.x * 0.1);
                }
                else if (endPoint.x < startPoint.x && endPoint.y > startPoint.y) {
                    startPoint.x = startPoint.x - (long)(startPoint.x * 0.1);
                }
                else {
                    startPoint.x = startPoint.x - (long)(startPoint.x * 0.1);
                }
            }

            lastPoint.x = LOWORD(lParam);
            lastPoint.y = HIWORD(lParam);

            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {

    HWND hWnd;
    HWND hButton1, hButton2, hButton3, hButton4, hButton5;

    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(255, 240, 200)));
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"ButtonWindowClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex)) {
        return 1;
    }

    RECT rect = { 0, 0, 800, 480 };
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, 0);
    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    hWnd = CreateWindow(
        L"ButtonWindowClass", L"202207043", WS_OVERLAPPEDWINDOW & ~(WS_MAXIMIZEBOX | WS_THICKFRAME),
        0, 0, width, height, NULL, NULL, hInstance, NULL);

    if (!hWnd) {
        return FALSE;
    }

    hButton1 = CreateWindow(
        L"BUTTON", L"Box", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        32, 32, 121.6, 64, hWnd, (HMENU)1, hInstance, NULL);

    hButton2 = CreateWindow(
        L"BUTTON", L"Circle", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        185.6, 32, 121.6, 64, hWnd, (HMENU)2, hInstance, NULL);

    hButton3 = CreateWindow(
        L"BUTTON", L"Cube", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        339.2, 32, 121.6, 64, hWnd, (HMENU)3, hInstance, NULL);

    hButton4 = CreateWindow(
        L"BUTTON", L"Bonobono", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        492.8, 32, 121.6, 64, hWnd, (HMENU)4, hInstance, NULL);

    hButton5 = CreateWindow(
        L"BUTTON", L"Ryan", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        646.4, 32, 121.6, 64, hWnd, (HMENU)5, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    HWND hLastFocused = NULL;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}
#include <windows.h>

// 박스를 나타내는 변수
bool isBoxVisible = false;

// 마우스 좌표
POINT startPoint = { 0, 0 };
POINT endPoint = { 0, 0 };

// 크기 비교
POINT maxPoint = { 0, 0 };
POINT minPoint = { 0, 0 };

void maxMin(POINT start, POINT end) {
    if (start.x > end.x) {
        maxPoint.x = start.x;
        minPoint.x = end.x;
    }
    else {
        maxPoint.x = end.x;
        minPoint.x = start.x;
    }

    if (start.y > end.y) {
        maxPoint.y = start.y;
        minPoint.y = end.y;
    }
    else {
        maxPoint.y = end.y;
        minPoint.y = start.y;
    }
}

// 마우스 좌클릭 클릭을 나타내는 변수
bool isMouseLButtonPressed = false;

// 박스 그리기 함수
void DrawBox(HWND hWnd, HDC hdc) {
    RECT rect;
    GetClientRect(hWnd, &rect);

    if (isBoxVisible) {
        // 박스 그리기
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0)); // 빨간색 박스
        maxMin(startPoint, endPoint);
        SelectObject(hdc, hBrush);
        Rectangle(hdc, minPoint.x, minPoint.y, maxPoint.x, maxPoint.y);
        DeleteObject(hBrush);
    }
}

// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_COMMAND:
        if (LOWORD(wParam) == 1) {
            // 첫 번째 버튼 클릭
            isBoxVisible = true;
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    case WM_LBUTTONDOWN:
    {
        startPoint.x = LOWORD(lParam);
        startPoint.y = HIWORD(lParam);

        isMouseLButtonPressed = true;
    }
    break;
    case WM_LBUTTONUP:
    {
        isMouseLButtonPressed = false;
    }
    break;
    case WM_MOUSEMOVE:
    {
        if (isMouseLButtonPressed)
        {
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);

            if (isBoxVisible)
            {
                // 드래그 중인 경우 사각형을 그립니다.
                InvalidateRect(hWnd, NULL, TRUE);
            }
        }
    }
    break;
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        DrawBox(hWnd, hdc);
        EndPaint(hWnd, &ps);
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
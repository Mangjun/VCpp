#include <windows.h>

bool isBox = false; // 네모 버튼 클릭 여부 변수
bool isSemo = false; // 세모 버튼 클릭 여부 변수
bool isStar = false; // 별 버튼 클릭 여부 변수
bool isLine = false; // 직선 버튼 클릭 여부 변수
bool isLButtonClick = false; // 좌클릭 여부 변수
bool isRButtonClick = false; // 우클릭 여부 변수
bool isInBoxRange = false; // 네모 안 여부 변수


// 시작 좌표, 끝 좌표
POINT startPoint = { 0 };
POINT endPoint = { 0 };

// 최대 좌표, 최소 좌표
POINT max = { 0 };
POINT min = { 0 };

// 도형 움직일 때 좌표
POINT lastMousePos = { 0 };

// 큰 좌표, 작은 좌표 구하기
void MinMax() {
    if (startPoint.x > endPoint.x) {
        max.x = startPoint.x;
        min.x = endPoint.x;
    }
    else {
        min.x = startPoint.x;
        max.x = endPoint.x;
    }

    if (startPoint.y > endPoint.y) {
        max.y = startPoint.y;
        min.y = endPoint.y;
    }
    else {
        min.y = startPoint.y;
        max.y = endPoint.y;
    }
}

// 네모 범위 안에 있는 지 확인하는 함수
bool IsInBox(POINT mousePos, POINT shapeStart, POINT shapeEnd) {
    if (endPoint.x > startPoint.x && endPoint.y > startPoint.y) {
        return (mousePos.x >= shapeStart.x && mousePos.x <= shapeEnd.x &&
            mousePos.y >= shapeStart.y && mousePos.y <= shapeEnd.y);
    }
    else if (endPoint.x > startPoint.x && endPoint.y < startPoint.y) {
        return (mousePos.x >= shapeStart.x && mousePos.x <= shapeEnd.x &&
            mousePos.y <= shapeStart.y && mousePos.y >= shapeEnd.y);
    }
    else if (endPoint.x < startPoint.x && endPoint.y > startPoint.y) {
        return (mousePos.x <= shapeStart.x && mousePos.x >= shapeEnd.x &&
            mousePos.y >= shapeStart.y && mousePos.y <= shapeEnd.y);
    }
    else {
        return (mousePos.x <= shapeStart.x && mousePos.x >= shapeEnd.x &&
            mousePos.y <= shapeStart.y && mousePos.y >= shapeEnd.y);
    }
}

// 네모 그리기 함수
void DrawBox(HWND hWnd, HDC hdc, POINT start, POINT end) {
    RECT rect;
    GetClientRect(hWnd, &rect);

    if (isBox) {
        // 박스 그리기
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
        SelectObject(hdc, hBrush);
        Rectangle(hdc, start.x, start.y, end.x, end.y);
        DeleteObject(hBrush);
    }
}

// 세모 그리기 함수
void DrawSemo(HWND hWnd, HDC hdc, POINT start, POINT end) {
    // 삼각형 좌표
    POINT semoPoint[3];

    POINT midPoint;
    midPoint.x = (endPoint.x + startPoint.x) / 2;
    midPoint.y = startPoint.y;

    semoPoint[0].x = midPoint.x;
    semoPoint[0].y = midPoint.y;
    semoPoint[1].x = start.x;
    semoPoint[1].y = end.y;
    semoPoint[2].x = end.x;
    semoPoint[2].y = end.y;

    if (isSemo) {
        // 세모 그리기
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
        SelectObject(hdc, hBrush);
        Polygon(hdc, semoPoint, 3);
        DeleteObject(hBrush);
    }
}

// 별 그리기 함수
void DrawStar(HWND hWnd, HDC hdc, POINT start, POINT end) {
    POINT starPoint[5];

    // 최대, 최소 값 구하기
    MinMax();

    // 별 모양의 각 꼭짓점 좌표 계산
    starPoint[0].x = min.x + (max.x - min.x) / 2;
    starPoint[0].y = min.y;
    starPoint[1].x = min.x + (max.x - min.x) / 3;
    starPoint[1].y = max.y;
    starPoint[2].x = max.x;
    starPoint[2].y = min.y + (max.y - min.y) / 3;
    starPoint[3].x = min.x;
    starPoint[3].y = min.y + (max.y - min.y) / 3;
    starPoint[4].x = max.x - (max.x - min.x) / 3;
    starPoint[4].y = max.y;

    if (isStar) {
        // 별 그리기
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
        SelectObject(hdc, hBrush);
        Polygon(hdc, starPoint, 5);
        DeleteObject(hBrush);
    }
}

// 직선 그리기 함수
void DrawLine(HWND hWnd, HDC hdc, POINT start, POINT end) {
    POINT line[2] = { start, end };
    
    if (isLine) {
        HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
        SelectObject(hdc, hBrush);
        Polyline(hdc, line, 2);
        DeleteObject(hBrush);
    }
}

// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    // 창 크기 변경 못하게 막음
    case WM_GETMINMAXINFO:
    {
        MINMAXINFO* info = (MINMAXINFO*)lParam;
        info->ptMinTrackSize.x = 800; // 최소 가로 크기를 800으로 설정
        info->ptMinTrackSize.y = 600; // 최소 세로 크기를 600으로 설정
        info->ptMaxTrackSize.x = 800; // 최대 가로 크기를 800으로 설정
        info->ptMaxTrackSize.y = 600; // 최대 세로 크기를 600으로 설정
        break;
    }
    case WM_COMMAND: {
        if (LOWORD(wParam) == 1) {
            // 첫 번째 버튼 클릭
            isBox = true;
            isSemo = false;
            isStar = false;
            isLine = false;
        }
        else if (LOWORD(wParam) == 2) {
            // 두 번째 버튼 클릭
            isBox = false;
            isSemo = true;
            isStar = false;
            isLine = false;
        }
        else if (LOWORD(wParam) == 3) {
            isBox = false;
            isSemo = false;
            isStar = true;
            isLine = false;
        }
        else if (LOWORD(wParam) == 4) {
            isBox = false;
            isSemo = false;
            isStar = false;
            isLine = true;
        }
        else {
            isBox = false;
            isSemo = false;
            isStar = false;
            isLine = false;
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    }
    case WM_LBUTTONDOWN: {
        startPoint.x = LOWORD(lParam);
        startPoint.y = HIWORD(lParam);
        
        isLButtonClick = true;
        isRButtonClick = false;
        break;
    }
    case WM_LBUTTONUP: {
        isLButtonClick = false;
        break;
    }
    case WM_RBUTTONDOWN: {
        isRButtonClick = true;

        lastMousePos.x = LOWORD(lParam);
        lastMousePos.y = HIWORD(lParam);

        if (IsInBox(lastMousePos, startPoint, endPoint)) {
            isInBoxRange = true;
        }
        break;
    }
    case WM_RBUTTONUP: {
        isRButtonClick = false;
        isInBoxRange = false;
        break;
    }
    case WM_MOUSEMOVE: {
        if (isLButtonClick)
        {
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);
            InvalidateRect(hWnd, NULL, TRUE);
        }
        else if (isRButtonClick && isInBoxRange) {
            int deltaX = LOWORD(lParam) - lastMousePos.x;
            int deltaY = HIWORD(lParam) - lastMousePos.y;

            // 그림의 위치를 이동
            startPoint.x += deltaX;
            startPoint.y += deltaY;
            endPoint.x += deltaX;
            endPoint.y += deltaY;

            // 마우스 위치 업데이트
            lastMousePos.x = LOWORD(lParam);
            lastMousePos.y = HIWORD(lParam);

            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    }
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        
        if (isLButtonClick) {
            if (isBox) {
                DrawBox(hWnd, hdc, startPoint, endPoint);
            }
            else if (isSemo) {
                DrawSemo(hWnd, hdc, startPoint, endPoint);
            }
            else if (isStar) {
                DrawStar(hWnd, hdc, startPoint, endPoint);
            }
            else if (isLine) {
                DrawLine(hWnd, hdc, startPoint, endPoint);
            }
        }

        if (isRButtonClick) {
            if (isBox) {
                MoveToEx(hdc, startPoint.x, startPoint.y, NULL);
                DrawBox(hWnd, hdc, startPoint, endPoint);
            }
            else if (isSemo) {
                MoveToEx(hdc, startPoint.x, startPoint.y, NULL);
                DrawSemo(hWnd, hdc, startPoint, endPoint);
            }
            else if (isStar) {
                MoveToEx(hdc, startPoint.x, startPoint.y, NULL);
                DrawStar(hWnd, hdc, startPoint, endPoint);
            }
            else if (isLine) {
                MoveToEx(hdc, startPoint.x, startPoint.y, NULL);
                DrawLine(hWnd, hdc, startPoint, endPoint);
            }
        }

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


// 프로그램 진입점
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
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"ButtonWindowClass";
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex)) {
        return 1;
    }

    hWnd = CreateWindow(
        L"ButtonWindowClass", L"중간 대비", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

    if (!hWnd) {
        return FALSE;
    }

    hButton1 = CreateWindow(
        L"BUTTON", L"네모", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        20, 20, 200, 60, hWnd, (HMENU)1, hInstance, NULL);

    hButton2 = CreateWindow(
        L"BUTTON", L"세모", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        20, 120, 200, 60, hWnd, (HMENU)2, hInstance, NULL);

    hButton3 = CreateWindow(
        L"BUTTON", L"별", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        20, 220, 200, 60, hWnd, (HMENU)3, hInstance, NULL);

    hButton4 = CreateWindow(
        L"BUTTON", L"직선", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        20, 320, 200, 60, hWnd, (HMENU)4, hInstance, NULL);

    hButton5 = CreateWindow(
        L"BUTTON", L"지우기", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        20, 420, 200, 60, hWnd, (HMENU)5, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

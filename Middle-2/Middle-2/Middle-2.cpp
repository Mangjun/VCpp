#include <windows.h>
#include <vector>

// 도형 종류를 식별하기 위한 열거형
enum ShapeType { RECTANGLE, TRIANGLE, STAR, LINE, CUBE, CIRCLE, NON };

// 현재 선택된 도형 유형
ShapeType currentShape = RECTANGLE;

// 마우스 드래그 시작 위치 저장
POINT dragStartPos;

bool operator==(const RECT& left, const RECT& right) {
    return left.left == right.left && left.top == right.top && left.right == right.right && left.bottom == right.bottom;
}

// 도형 정보를 나타내는 구조체
struct Shape {
    ShapeType type;
    RECT rect;  // 도형의 위치 및 크기 정보
    bool selected; // 도형이 선택되었는지 여부

    bool operator==(const Shape& other) const {
        return type == other.type && rect == other.rect;
    }
};
// 도형 목록
std::vector<Shape> shapes;

// 현재 그릴 도형
Shape currentDrawingShape;

// 마우스 왼쪽 버튼을 누르면 도형을 그리도록 설정
bool isDrawing = false;

// 이동 중인 도형의 인덱스
int movingShapeIndex = -1;

// 사각형 그리기 함수
void DrawRectangle(HDC hdc, const Shape& shape) {
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0)); // 빨간색
    SelectObject(hdc, hBrush);
    Rectangle(hdc, shape.rect.left, shape.rect.top, shape.rect.right, shape.rect.bottom);
    DeleteObject(hBrush);
}

// 삼각형 그리기 함수
void DrawTriangle(HDC hdc, const Shape& shape) {
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 255, 0)); // 녹색
    SelectObject(hdc, hBrush);

    // 삼각형을 그리는 좌표 계산
    int x1 = shape.rect.left;
    int y1 = shape.rect.bottom;
    int x2 = shape.rect.right;
    int y2 = shape.rect.bottom;
    int x3 = (shape.rect.left + shape.rect.right) / 2;
    int y3 = shape.rect.top;

    // 삼각형의 내부를 색으로 채우기
    POINT points[3] = {
        {x1, y1},
        {x2, y2},
        {x3, y3}
    };

    // 삼각형 그리고 내부를 색칠하기
    Polygon(hdc, points, 3);

    DeleteObject(hBrush);
}

// 별 그리기 함수
void DrawStar(HDC hdc, const Shape& shape) {
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 0)); // 노란색
    SelectObject(hdc, hBrush);

    // 계산된 새로운 별의 크기 계산 (드래그한 범위의 가로 및 세로 길이 활용)
    int width = shape.rect.right - shape.rect.left;
    int height = shape.rect.bottom - shape.rect.top;
    int size = min(width, height); // 가로와 세로 중 작은 값을 크기로 사용
    int halfSize = size / 2; // 크기의 절반

    // 별의 중심 위치 계산
    int centerX = (shape.rect.left + shape.rect.right) / 2;
    int centerY = (shape.rect.top + shape.rect.bottom) / 2;

    // 별 모양을 그리는 좌표 계산 (10개의 꼭지점)
    POINT points[10] = {
        {centerX, centerY - size},           // 상단 중앙
        {centerX - size / 5, centerY - size / 5},  // 상단 왼쪽
        {centerX - size, centerY - size / 5},       // 상단 왼쪽 외부
        {centerX - size / 2, centerY + size / 5},  // 상단 왼쪽 아래
        {centerX - 4 * size / 5, centerY + 4 * size / 5},  // 중앙 왼쪽
        {centerX, centerY + 2 * size / 5},  // 중앙 왼쪽 위
        {centerX + 4 * size / 5, centerY + 4 * size / 5},  // 중앙 왼쪽 아래
        {centerX + size / 2, centerY + size / 5},  // 중앙 왼쪽 아래 위
        {centerX + size, centerY - size / 5},  // 상단 오른쪽
        {centerX + size / 5, centerY - size / 5}  // 상단 오른쪽 외부
    };

    // 별 그리기
    Polygon(hdc, points, 10);

    DeleteObject(hBrush);
}

// 직선 그리기 함수
void DrawLine(HDC hdc, const Shape& shape) {
    HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255)); // 파란색
    SelectObject(hdc, hBrush);
    MoveToEx(hdc, shape.rect.left, shape.rect.top, NULL);
    LineTo(hdc, shape.rect.right, shape.rect.bottom);
    DeleteObject(hBrush);
}

// 직육면체 그리기 함수
void DrawCube(HDC hdc, const Shape& shape) {
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 255, 255));
    SelectObject(hdc, hBrush);

    // 직육면체 그리기 (6개의 면)
    Rectangle(hdc, shape.rect.left, shape.rect.top, shape.rect.right, shape.rect.bottom);

    // 위쪽 면
    MoveToEx(hdc, shape.rect.left, shape.rect.top, NULL);
    LineTo(hdc, shape.rect.left + 50, shape.rect.top - 20);
    LineTo(hdc, shape.rect.right + 50, shape.rect.top - 20);
    LineTo(hdc, shape.rect.right, shape.rect.top);
    LineTo(hdc, shape.rect.left, shape.rect.top);

    // 아랫면
    MoveToEx(hdc, shape.rect.left, shape.rect.bottom, NULL);
    LineTo(hdc, shape.rect.left + 50, shape.rect.bottom - 20);
    LineTo(hdc, shape.rect.right + 50, shape.rect.bottom - 20);
    LineTo(hdc, shape.rect.right, shape.rect.bottom);
    LineTo(hdc, shape.rect.left, shape.rect.bottom);

    // 옆면 1
    MoveToEx(hdc, shape.rect.left, shape.rect.top, NULL);
    LineTo(hdc, shape.rect.left + 50, shape.rect.top - 20);
    LineTo(hdc, shape.rect.left + 50, shape.rect.bottom - 20);
    LineTo(hdc, shape.rect.left, shape.rect.bottom);
    LineTo(hdc, shape.rect.left, shape.rect.top);

    // 옆면 2
    MoveToEx(hdc, shape.rect.right, shape.rect.top, NULL);
    LineTo(hdc, shape.rect.right + 50, shape.rect.top - 20);
    LineTo(hdc, shape.rect.right + 50, shape.rect.bottom - 20);
    LineTo(hdc, shape.rect.right, shape.rect.bottom);
    LineTo(hdc, shape.rect.right, shape.rect.top);

    DeleteObject(hBrush);
}

// 원 그리기 함수
void DrawCircle(HDC hdc, const Shape& shape) {
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0)); // 빨간색
    SelectObject(hdc, hBrush);

    // 원을 그리는 좌표 계산
    int centerX = (shape.rect.left + shape.rect.right) / 2;
    int centerY = (shape.rect.top + shape.rect.bottom) / 2;
    int radius = min((shape.rect.right - shape.rect.left) / 2, (shape.rect.bottom - shape.rect.top) / 2);

    // 원 그리기
    Ellipse(hdc, centerX - radius, centerY - radius, centerX + radius, centerY + radius);

    DeleteObject(hBrush);
}

// 도형 그리기 함수
void DrawShapes(HDC hdc) {
    for (const auto& shape : shapes) {
        switch (shape.type) {
        case RECTANGLE:
            DrawRectangle(hdc, shape);
            break;
        case TRIANGLE:
            DrawTriangle(hdc, shape);
            break;
        case STAR:
            DrawStar(hdc, shape);
            break;
        case LINE:
            DrawLine(hdc, shape);
            break;
        case CUBE:
            DrawCube(hdc, shape);
            break;
        case CIRCLE:
            DrawCircle(hdc, shape);
            break;
        }
    }
}

// 도형 추가 함수
void AddShape(ShapeType type, int x1, int y1, int x2, int y2) {
    Shape shape;
    shape.type = type;
    shape.rect = { x1, y1, x2, y2 };
    shape.selected = false;
    shapes.push_back(shape);
}

// 도형 선택 함수
void SelectShape(int x, int y) {
    for (auto& shape : shapes) {
        shape.selected = PtInRect(&shape.rect, { x, y });
    }
}

// 현재 그리는 도형 업데이트 함수
void UpdateCurrentDrawingShape(int x, int y) {   
    currentDrawingShape.rect = {
    min(dragStartPos.x, x), min(dragStartPos.y, y),
    max(dragStartPos.x, x), max(dragStartPos.y, y)
    };
}

// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_COMMAND: {
        switch (LOWORD(wParam)) {
        case 1: // 사각형 버튼
            currentShape = RECTANGLE;
            break;
        case 2: // 삼각형 버튼
            currentShape = TRIANGLE;
            break;
        case 3: // 별 버튼
            currentShape = STAR;
            break;
        case 4: // 직선 버튼
            currentShape = LINE;
            break;
        case 5: // 직육면체 버튼
            currentShape = CUBE;
            break;
        case 6: // 원 버튼
            currentShape = CIRCLE;
            break;
        case 7:
            currentShape = NON;
            break;
        case 8: // 전체 지우기 버튼
            shapes.clear(); // 모든 도형을 삭제
            currentShape = NON;
            InvalidateRect(hWnd, NULL, TRUE); // 윈도우를 다시 그림
            break;
        }
        break;
    }
    case WM_LBUTTONDOWN: {
        // 선택 지우기 모드인 경우
        if (currentShape == NON) {
            int mouseX = LOWORD(lParam);
            int mouseY = HIWORD(lParam);

            // 클릭한 위치에 있는 도형을 찾고 삭제
            for (int i = static_cast<int>(shapes.size()) - 1; i >= 0; --i) {
                if (PtInRect(&shapes[i].rect, { mouseX, mouseY })) {
                    shapes.erase(shapes.begin() + i); // 도형 삭제
                    InvalidateRect(hWnd, NULL, TRUE); // 윈도우 다시 그림
                    break; // 하나의 도형만 삭제
                }
            }
        }
        else {
            // 선택 지우기 모드가 아닌 경우, 도형 그리기 코드를 유지
            isDrawing = true;
            currentDrawingShape.type = currentShape;
            currentDrawingShape.rect = { LOWORD(lParam), HIWORD(lParam), LOWORD(lParam), HIWORD(lParam) };
            dragStartPos.x = LOWORD(lParam);
            dragStartPos.y = HIWORD(lParam);
        }
        break;
    }
    case WM_LBUTTONUP: {
        isDrawing = false;
        shapes.push_back(currentDrawingShape);
        break;
    }
    case WM_MOUSEMOVE: {
        if (isDrawing) {
            int mouseX = LOWORD(lParam);
            int mouseY = HIWORD(lParam);

            // 계산된 새로운 사각형 영역
            int newLeft = min(dragStartPos.x, mouseX);
            int newTop = min(dragStartPos.y, mouseY);
            int newRight = max(dragStartPos.x, mouseX);
            int newBottom = max(dragStartPos.y, mouseY);

            // 새로운 별의 크기와 위치 계산
            currentDrawingShape.rect.left = newLeft;
            currentDrawingShape.rect.top = newTop;
            currentDrawingShape.rect.right = newRight;
            currentDrawingShape.rect.bottom = newBottom;
            
            UpdateCurrentDrawingShape(LOWORD(lParam), HIWORD(lParam));
            InvalidateRect(hWnd, NULL, TRUE);
        }
        if (movingShapeIndex != -1) {
            int mouseX = LOWORD(lParam);
            int mouseY = HIWORD(lParam);

            // 이동 중인 도형의 위치를 업데이트하여 마우스 위치로 이동
            int width = shapes[movingShapeIndex].rect.right - shapes[movingShapeIndex].rect.left;
            int height = shapes[movingShapeIndex].rect.bottom - shapes[movingShapeIndex].rect.top;
            shapes[movingShapeIndex].rect = { mouseX, mouseY, mouseX + width, mouseY + height };

            // 화면을 다시 그려 이동 중인 도형을 업데이트
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    }
    case WM_RBUTTONDOWN: {
        int mouseX = LOWORD(lParam);
        int mouseY = HIWORD(lParam);

        // 도형 목록에서 마우스 클릭 위치에 있는 도형을 찾고 선택
        movingShapeIndex = -1;
        for (size_t i = 0; i < shapes.size(); ++i) {
            if (PtInRect(&shapes[i].rect, { mouseX, mouseY })) {
                movingShapeIndex = i;
                shapes[i].selected = true;
            }
        }
        break;
    }
    case WM_RBUTTONUP: {
        if (movingShapeIndex != -1) {
            // 마우스 클릭 위치에 있는 도형 이동 완료
            shapes[movingShapeIndex].selected = false;

            // 이동한 도형을 새로운 위치로 업데이트
            int newLeft = LOWORD(lParam);
            int newTop = HIWORD(lParam);
            int width = shapes[movingShapeIndex].rect.right - shapes[movingShapeIndex].rect.left;
            int height = shapes[movingShapeIndex].rect.bottom - shapes[movingShapeIndex].rect.top;
            shapes[movingShapeIndex].rect = { newLeft, newTop, newLeft + width, newTop + height };

            // 이동 중인 도형을 다시 그리기
            movingShapeIndex = -1;
            InvalidateRect(hWnd, NULL, TRUE);
        }
        break;
    }
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        DrawShapes(hdc);
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
    HWND hButton1, hButton2, hButton3, hButton4, hButton5, hButton6, hButton7, hButton8;

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
        L"ButtonWindowClass", L"Win32 Button Example", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

    if (!hWnd) {
        return FALSE;
    }

    hButton1 = CreateWindow(L"BUTTON", L"사각형", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        20, 20, 100, 30, hWnd, (HMENU)1, hInstance, NULL);

    hButton2 = CreateWindow(L"BUTTON", L"삼각형", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        130, 20, 100, 30, hWnd, (HMENU)2, hInstance, NULL);

    hButton3 = CreateWindow(L"BUTTON", L"별", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        240, 20, 100, 30, hWnd, (HMENU)3, hInstance, NULL);

    hButton4 = CreateWindow(L"BUTTON", L"직선", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        350, 20, 100, 30, hWnd, (HMENU)4, hInstance, NULL);

    hButton5 = CreateWindow(L"BUTTON", L"직육면체", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        460, 20, 100, 30, hWnd, (HMENU)5, hInstance, NULL);

    hButton6 = CreateWindow(L"BUTTON", L"원", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        570, 20, 100, 30, hWnd, (HMENU)6, hInstance, NULL);

    hButton7 = CreateWindow(L"BUTTON", L"선택 지우기", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        680, 20, 100, 30, hWnd, (HMENU)7, hInstance, NULL);

    hButton8 = CreateWindow(L"BUTTON", L"전체 지우기", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        790, 20, 100, 30, hWnd, (HMENU)8, hInstance, NULL);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
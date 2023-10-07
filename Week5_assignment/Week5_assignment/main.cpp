#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif

#include <windows.h>

POINT startPoint = { 0 };
POINT endPoint = { 0 };
int isMouseLButtonPressed = 0;

POINT lastMousePos = { 0 };
int isMouseRButtonPressed = 0;

bool isMouseInRange = 0;

// 마우스가 도형 범위 내에 있는지 확인
// err: 시작 위치보다 끝 위치가 왼쪽에 있다면 이동 안 됨
bool IsMouseInsideShape(POINT mousePos, POINT shapeStart, POINT shapeEnd)
{
	return (mousePos.x >= shapeStart.x && mousePos.x <= shapeEnd.x &&
		mousePos.y >= shapeStart.y && mousePos.y <= shapeEnd.y);
}

// 판단 기준 세우기
//bool IsMouseInsideShape(POINT mousePos, POINT shapeStart, POINT shapeEnd)
//{
//	return (mousePos.x >= shapeStart.x && mousePos.x <= shapeEnd.x &&
//		mousePos.y >= shapeStart.y && mousePos.y <= shapeEnd.y);
//}

// 윈도우의 이벤트를 처리하는 콜백(Callback) 함수.
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	// 창 크기 변경 못하게 막음
	case WM_GETMINMAXINFO:
	{
		MINMAXINFO* info = (MINMAXINFO*)lParam;
		info->ptMinTrackSize.x = 800; // 최소 가로 크기를 800으로 설정
		info->ptMinTrackSize.y = 600; // 최소 세로 크기를 600으로 설정
		info->ptMaxTrackSize.x = 800; // 최대 가로 크기를 800으로 설정
		info->ptMaxTrackSize.y = 600; // 최대 세로 크기를 600으로 설정
	}
	break;

	case WM_LBUTTONDOWN:
	{
		startPoint.x = LOWORD(lParam);
		startPoint.y = HIWORD(lParam);
		isMouseLButtonPressed = 1;
	}
	break;

	//강의에 안나왔지만 마우스가 움직일때의 이벤트를 뜻합니다.
	case WM_MOUSEMOVE:
	{
		// 마우스 이동 중
		if (isMouseLButtonPressed)
		{
			endPoint.x = LOWORD(lParam);
			endPoint.y = HIWORD(lParam);

			// WM_PAINT 메시지를 유발하여 네모를 화면에 그립니다.
			InvalidateRect(hwnd, NULL, TRUE);
		} else if (isMouseRButtonPressed && isMouseInRange) {
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

			// WM_PAINT 메시지를 유발하여 그림을 다시 그립니다.
			InvalidateRect(hwnd, NULL, TRUE);
		}
	}
	break;

	case WM_LBUTTONUP:
	{
		endPoint.x = LOWORD(lParam);
		endPoint.y = HIWORD(lParam);

		isMouseLButtonPressed = 0;

		// WM_PAINT 메시지를 유발하여 네모를 화면에 그립니다.
		InvalidateRect(hwnd, NULL, TRUE);
	}
	break;

	case WM_RBUTTONDOWN:
	{
		isMouseRButtonPressed = 1;

		lastMousePos.x = LOWORD(lParam);
		lastMousePos.y = HIWORD(lParam);

		if (IsMouseInsideShape(lastMousePos, startPoint, endPoint))
		{
			isMouseInRange = 1;
		}
		else
		{
			isMouseInRange = 0;
		}

	}
	break;

	case WM_RBUTTONUP:
	{
		isMouseRButtonPressed = 0;
	}
	break;

	case WM_PAINT:
	{
		HDC hdc = GetDC(hwnd);
		HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));

		if (isMouseLButtonPressed || (isMouseRButtonPressed && isMouseInRange))
		{
			RECT rect;
			GetClientRect(hwnd, &rect);
			FillRect(hdc, &rect, (HBRUSH)(COLOR_WINDOW + 1));

			MoveToEx(hdc, startPoint.x, startPoint.y, NULL);
			rect = { startPoint.x, startPoint.y, endPoint.x, endPoint.y };
			FillRect(hdc, &rect, hBrush);
		}

		DeleteObject(hBrush);
		ReleaseDC(hwnd, hdc);
	}
	break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return S_OK;
}
#ifdef UNICODE
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
#else
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR pCmdLine, _In_ int nCmdShow)
#endif
{
	/* 윈도우 클래스 선언.*/
	WNDCLASS wc;
	ZeroMemory(&wc, sizeof(wc));	// 모두 0으로 초기화.

	// 윈도우 클래스 값 설정
	wc.hInstance = hInstance;
	wc.lpszClassName = TEXT("Computer Software");
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_CROSS);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;

	// 윈도우 클래스 등록.
	if (RegisterClass(&wc) == 0)
	{
		MessageBox(NULL, L"RegisterClass failed!", L"Error", MB_ICONERROR);
		exit(-1);	//예외
	}

	// 윈도우 생성
	HWND hwnd = CreateWindow(
		wc.lpszClassName,
		TEXT("202207043_김명준"),
		WS_OVERLAPPEDWINDOW,
		0, 0,
		800, 600,
		NULL, NULL,
		hInstance,
		NULL
	);

	// 오류 검사.
	if (hwnd == NULL)
	{
		MessageBox(NULL, L"CreateWindow failed!", L"Error", MB_ICONERROR);
		exit(-1);
	}

	// 창 보이기.
	ShowWindow(hwnd, SW_SHOW); // 창 띄우고
	UpdateWindow(hwnd); // 업데이트해야 보임. 한 쌍으로 쓴다고 보면 됨.



	// 메시지 처리 루프.
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		// 메시지 처리.
		if (GetMessage(&msg, hwnd, 0, 0))
			//if (PeekMessage(&msg, hwnd, 0, 0, PM_REMOVE)) // PM_REMOVE의 자리는 이 메세지를 쓰고 어떡할거냐.의 의미인데 지운다는 것임.
		{

			// 메시지 해석해줘.
			TranslateMessage(&msg);
			// 메시지를 처리해야할 곳에 전달해줘.
			DispatchMessage(&msg);

		}
		/*else
		{

		}*/
	}

	//종료 메시지 보내기
	return (int)msg.wParam;

}
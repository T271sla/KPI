#include <Windows.h>
#include "Header.h"

#define OnExitSoftware		1
#define OnPolyClicked		2
#define OnMultiClicked		3
#define OnNaturalClicked	4

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure);
void MainWndAddMenus(HWND hWnd);
void MainWndAddWidgets(HWND hWnd);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
	WNDCLASS SoftwareMainClass = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst,
		LoadIcon(NULL, IDI_QUESTION), L"MainWndClass", SoftwareMainProcedure);

	if (!RegisterClassW(&SoftwareMainClass)) { return -1; }
	MSG SoftwareMainMessage = { 0 };

	CreateWindow(L"MainWndClass", L"External Sort", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 270, NULL, NULL, NULL, NULL);

	while (GetMessage(&SoftwareMainMessage, NULL, NULL, NULL)) {
		TranslateMessage(&SoftwareMainMessage);
		DispatchMessage(&SoftwareMainMessage);
	}
	return 0;
}

WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure) {
	WNDCLASS NWC = { 0 };

	NWC.hIcon = Icon;
	NWC.hCursor = Cursor;
	NWC.hInstance = hInst;
	NWC.lpszClassName = Name;
	NWC.hbrBackground = BGColor;
	NWC.lpfnWndProc = Procedure;

	return NWC;
}

LRESULT CALLBACK SoftwareMainProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_COMMAND:
		switch (wp)
		{
		case OnPolyClicked:
			PolyPhaseSortStart();
			MessageBoxA(hWnd, "Polyphase Sorting Completed\nCheck the Polyphase Output File", "Done", MB_OK);
			break;
		case OnNaturalClicked:
			naturalExternalSortStart();
			MessageBoxA(hWnd, "Natural Sorting Completed\nCheck the Natural Output File", "Done", MB_OK);
			break;
		case OnMultiClicked:
			multiwaySortStart();
			MessageBoxA(hWnd, "Multiway Sorting Completed\nCheck the Multiway Output File", "Done", MB_OK);
			break;
		default:
			break;
		}
		break;
	case WM_CREATE:
		MainWndAddWidgets(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hWnd, msg, wp, lp);
	}
}

void MainWndAddWidgets(HWND hWnd)
{
	CreateWindowA("button", "Natural Merge Sort", WS_VISIBLE | WS_CHILD, 5, 5, 140, 30, hWnd, (HMENU)OnNaturalClicked, NULL, NULL);
	CreateWindowA("button", "Maltiway Sort", WS_VISIBLE | WS_CHILD, 5, 35, 140, 30, hWnd, (HMENU)OnMultiClicked, NULL, NULL);
	CreateWindowA("button", "Polyphase Sort", WS_VISIBLE | WS_CHILD, 5, 65, 140, 30, hWnd, (HMENU)OnPolyClicked, NULL, NULL);
}

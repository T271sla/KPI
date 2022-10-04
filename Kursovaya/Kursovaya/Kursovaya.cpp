#include <Windows.h>
#include "Header.h"
int num;
int num_1;
int num_2;
int num_3;
int num_4 = 0;
int num_5 = 0;
int num_6 = 0;

#define OnExitSoftware		1
#define OnPolyClicked		2
#define OnMultiClicked		3
#define OnNaturalClicked	4
#define OnFillClicked		5
#define DlgIndexNumberSize	6
#define DlgIndexNumberMin	7
#define DlgIndexNumberMax	8

#define TextBuffer			11

PTSTR Min = new TCHAR[TextBuffer];
PTSTR Max = new TCHAR[TextBuffer];

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

//клас параметрів вікна
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
	//алгоритм дій при натисканны на певну кнопку
	switch (msg)
	{
	case WM_COMMAND:
		switch (wp)
		{
		case OnPolyClicked:
			num = GetDlgItemInt(hWnd, DlgIndexNumberSize, NULL, false);
			if (num == 0)
			{
				MessageBoxA(hWnd, "Nothing to sort", "Okay", MB_OK);
				break;
			}
			num_4 = 0;
			num_3 = PolyPhaseSortStart(num, num_4, num_5, num_6);
			MessageBoxA(hWnd, ("Polyphase Sorting Completed\nCheck the Polyphase Output File\nTime: " + to_string(num_3) + "\nHow many adresses to hard drive: " + to_string(num_4)).c_str(), "Done", MB_OK);
			break;
		case OnNaturalClicked:
			num = GetDlgItemInt(hWnd, DlgIndexNumberSize, NULL, false);
			if (num == 0)
			{
				MessageBoxA(hWnd, "Nothing to sort", "Okay", MB_OK);
				break;
			}
			num_4 = 0;
			num_3 = naturalExternalSortStart(num, num_4, num_5, num_6);
			MessageBoxA(hWnd, ("Natural Sorting Completed\nCheck the Natural Output File\nTime: " + to_string(num_3) + "\nHow many adresses to hard drive: " + to_string(num_4)).c_str(), "Done", MB_OK);
			break;
		case OnMultiClicked:
			num = GetDlgItemInt(hWnd, DlgIndexNumberSize, NULL, false);
			if (num == 0)
			{
				MessageBoxA(hWnd, "Nothing to sort", "Okay", MB_OK);
				break;
			}
			num_4 = 0;
			num_3 = multiwaySortStart(num, num_4);
			MessageBoxA(hWnd, ("Multiway Sorting Completed\nCheck the Multiway Output File\nTime: " + to_string(num_3) + "\nHow many adresses to hard drive: " + to_string(num_4)).c_str(), "Done", MB_OK);
			break;
		case OnFillClicked:
			num = GetDlgItemInt(hWnd, DlgIndexNumberSize, NULL, false);
			GetDlgItemText(hWnd, DlgIndexNumberMin, Min, 10);
			GetDlgItemText(hWnd, DlgIndexNumberMax, Max, 10);
			num_1 = stoi(Min);
			num_2 = stoi(Max);
			if (num == 0)
			{
				MessageBoxA(hWnd, "Nothing to create", "Okay", MB_OK);
				break;
			}
			if (num_1 > num_2)
			{
				MessageBoxA(hWnd, "Max element is supposed to be bigger", "Umm...", MB_OK);
				break;
			}
			createInput(num, num_1, num_2, num_5, num_6);
			MessageBoxA(hWnd, "Completed\nCheck the Input File", "Done", MB_OK);
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
	//створюємо кнопки
	CreateWindowA("button", "Create Input File", WS_VISIBLE | WS_CHILD, 5, 5, 140, 30, hWnd, (HMENU)OnFillClicked, NULL, NULL);
	CreateWindowA("button", "Natural Merge Sort", WS_VISIBLE | WS_CHILD, 5, 35, 140, 30, hWnd, (HMENU)OnNaturalClicked, NULL, NULL);
	CreateWindowA("button", "Maltiway Sort", WS_VISIBLE | WS_CHILD, 5, 65, 140, 30, hWnd, (HMENU)OnMultiClicked, NULL, NULL);
	CreateWindowA("button", "Polyphase Sort", WS_VISIBLE | WS_CHILD, 5, 95, 140, 30, hWnd, (HMENU)OnPolyClicked, NULL, NULL);

	CreateWindowA("static", "How many elemnts: ", WS_VISIBLE | WS_CHILD, 250, 5, 140, 30, hWnd, NULL, NULL, NULL);
	CreateWindowA("edit", "0", WS_VISIBLE | WS_CHILD | ES_NUMBER, 400, 5, 70, 30, hWnd, (HMENU)DlgIndexNumberSize, NULL, NULL);

	CreateWindowA("static", "Min element: ", WS_VISIBLE | WS_CHILD, 250, 35, 140, 30, hWnd, NULL, NULL, NULL);
	CreateWindowA("edit", "0", WS_VISIBLE | WS_CHILD, 400, 35, 70, 30, hWnd, (HMENU)DlgIndexNumberMin, NULL, NULL);

	CreateWindowA("static", "Max element: ", WS_VISIBLE | WS_CHILD, 250, 65, 140, 30, hWnd, NULL, NULL, NULL);
	CreateWindowA("edit", "0", WS_VISIBLE | WS_CHILD, 400, 65, 70, 30, hWnd, (HMENU)DlgIndexNumberMax, NULL, NULL);
}

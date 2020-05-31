// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#include "dllmain.h"

HHOOK g_hook;
HWND g_hWnd;
HINSTANCE g_hModuleHandle;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        g_hModuleHandle = (HINSTANCE)hModule;
        break;
    }
    return TRUE;
}

// Функция, которая будет вызвана, когда сработает хук
LRESULT CALLBACK SysMsgProc(int code, WPARAM wParam, LPARAM lParam) {

    if (code < 0) { 
        // Если code < 0, то Windows хочет чтобы наша функция обработчик
        // НЕ обрабатывала этот вызов, а сразу же передала управление
        // следующему хуку
        return CallNextHookEx(g_hook, code, wParam, lParam);
    }

    // хук должен работать только в том случае, когда переменная 
    // code содержит код HC_ACTION
    if (code == HC_ACTION) {

        g_hWnd = ((MSG*)lParam)->hwnd; // получение хэндла окна
        if (((MSG*)lParam)->message == WM_RBUTTONDOWN) { // ловим только клик правой кнопкой 
			// EM_SETPASSWORDCHAR — тип сообщения, говорит о том, что надо изменить символ, который будет использоваться для того, чтобы спрятать пароль 
            // значение 0 (3-й параметр) говорит о том, чтобы не прятать пароль, а показывать символы как есть
            SendMessage(g_hWnd, EM_SETPASSWORDCHAR, 0, 0);
            // команда перерисовать окно
            InvalidateRect(g_hWnd, 0, true);
        }
    }

    return CallNextHookEx(g_hook, code, wParam, lParam);
}


// Функция вешает/убирает глобальныйы хук
DllExport void SetRemoveHook(bool doSet) {
    if (doSet) {
        g_hook = SetWindowsHookExW(WH_GETMESSAGE, &SysMsgProc, g_hModuleHandle, 0);
    }
    else {
        UnhookWindowsHookEx(g_hook);
    }
}
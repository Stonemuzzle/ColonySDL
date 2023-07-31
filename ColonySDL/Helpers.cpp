#include <string>
#include <iostream>
#include <windows.h>

std::wstring ExePath() {
    // Returns the current path of the executable.
    TCHAR buffer[MAX_PATH] = { 0 };
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
    return std::wstring(buffer).substr(0, pos);
}

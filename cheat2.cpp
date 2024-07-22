#include <iostream>
#include <windows.h>
#include <stdexcept>

using namespace std;

DWORD_PTR ammo = 0x14B67110; // Target mem addr
HANDLE handler;
int value = 30; // Ammo
int receiveValue;

void HackAmmo();

int main(int argc, char const *argv[]) {
    HWND window = FindWindow(NULL, "Zumbi blocks"); // Window name of the game
    if (!window) {
        cout << "Window not found!" << endl;
        return -1;
    }

    DWORD processId;
    GetWindowThreadProcessId(window, &processId);

    handler = OpenProcess(PROCESS_ALL_ACCESS, false, processId);
    if (!handler) {
        cout << "Process not found!" << endl;
        return -1;
    }  

    while(true) {
        ReadProcessMemory(handler, (LPVOID)ammo, &receiveValue, sizeof(int), 0);
        cout << "Ammo count: " << receiveValue << endl;
        if (receiveValue <= 0) {
            HackAmmo();
        }
    }

    return 0;
}

void HackAmmo() {
    try {
        WriteProcessMemory(handler, (LPVOID)ammo, &value, sizeof(int), 0);
        system("cls");
        cout << "Ammo hacked." << endl;
        Sleep(3000);
    } catch(const exception& e) {
        cout << "Failed to hack ammo: " << e.what() << endl;
        system("exit");
    }
}

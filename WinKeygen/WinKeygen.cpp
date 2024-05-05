#include <iostream>
#include <string>
#include <windows.h>
#include <ctime>

using namespace std;

void simulateKeyPress(const string& key) {
    INPUT inputs[2] = { 0 };
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = 0;
    inputs[0].ki.dwFlags = KEYEVENTF_UNICODE;
    inputs[0].ki.wScan = key[0];

    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = 0;
    inputs[1].ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
    inputs[1].ki.wScan = key[0];

    SendInput(2, inputs, sizeof(INPUT));
}

void simulateEnterKey() {
    INPUT input = { 0 };
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = VK_RETURN;

    SendInput(1, &input, sizeof(INPUT));
}

string generateWindowsProductKey() {
    string key;
    srand(time(0));
    const string chars = "BCDFGHJKMPQRTVWXY2346789";
    for (int i = 0; i < 20; ++i) {
        key += chars[rand() % chars.size()];
    }
    key.insert(5, "-");
    key.insert(11, "-");
    key.insert(17, "-");
    return key;
}

int main() {
    while (true) {
        string generatedKey = generateWindowsProductKey();
        simulateKeyPress(generatedKey);
        simulateEnterKey();
        Sleep(300); // Simulating a delay between key presses
    }
    return 0;
}

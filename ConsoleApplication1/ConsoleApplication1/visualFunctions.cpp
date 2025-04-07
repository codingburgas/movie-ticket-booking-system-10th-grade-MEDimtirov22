#include "./visualFunctions.h"

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void fullScreen() {
    keybd_event(VK_MENU, 0x36, 0, 0);
    keybd_event(VK_RETURN, 0x1c, 0, 0);
    keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}

void printLogo(const std::string& filename) {
    clearScreen();
    std::cout << "\n\n\n\n\n\n\n\n";

    std::ifstream file(filename);
    if (!file) {
        centerText("Error: Could not open logo file!");
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        centerText(line);
    }

    file.close();
    std::cout << "\n\n\n\n";
}

void paddingUp(int paddingSize) {
    for (int i = 0; i < paddingSize; i++) std::cout << std::endl;
}

int getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
    return consoleInfo.srWindow.Right - consoleInfo.srWindow.Left + 1;
}

void centerText(std::string text) {
    int consoleWidth = getConsoleWidth();
    int paddingLeft = (consoleWidth - text.length()) / 2;
    if (paddingLeft < 0) paddingLeft = 0;

    std::cout << std::string(paddingLeft, ' ') << text << std::endl;
}

void exitMessage() {
    clearScreen();
    paddingUp(2);
    centerText("Thank you for using the program!");
    paddingUp(2);
    system("pause >nul");
}
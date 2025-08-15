#include "application.hpp"

#if defined(__linux__) || defined(__APPLE__)
int main(int argc, char *argv[]) {
  Application application;
  application.run();
}
#else
#include <Windows.h>
#include <shellapi.h>

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPTSTR lpCmdLine, int nCmdShow) {

  // Shows a message if program is running
  CreateMutexA(0, FALSE, "Local\\$DualSenseY$");
  if (GetLastError() == ERROR_ALREADY_EXISTS) {
    int argc;
    int commmand_index;
    bool is_command = false;
    LPWSTR *argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    for (int i = 0; i < argc; i++) {
      if (!wcscmp(argv[i], L"--command")) {
        is_command = true;
        commmand_index = i + 1;
      }
    }
    if (is_command) {
      MessageBoxW(NULL, argv[commmand_index], L"Found Command", MB_OK);
    } else {
      MessageBoxW(NULL, L"Program already started", L"Error", MB_OK);
    }
    return -1;
  }

  Application application;
  application.run();
}
#endif

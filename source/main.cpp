#include "application.hpp"

#if defined(__linux__) || defined(__APPLE__)
int main(int argc, char *argv[]) {
  Application application;
  application.run();
}
#else
#include <Windows.h>

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPTSTR lpCmdLine, int nCmdShow) {

  // Shows a message if program is running
  CreateMutexA(0, FALSE, "Local\\$DualSenseY$");
  if (GetLastError() == ERROR_ALREADY_EXISTS) {
    MessageBoxW(NULL, L"Program already running", L"Failed to start", MB_OK);
    return -1;
  }

  Application application;
  application.run();
}
#endif

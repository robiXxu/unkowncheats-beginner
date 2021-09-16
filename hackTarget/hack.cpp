#include <iostream> 
#include <cstring> 
#include <Windows.h>
#include <processthreadsapi.h>
#include <handleapi.h>
#include <errhandlingapi.h>

using namespace std;

int main() {

  HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, false, 17800);
  if(pHandle == NULL) {
    cout << "Failed to open process. GetLastError() = " << dec << GetLastError() << endl;
    return EXIT_FAILURE;
  }
  int intRead = 0;
  SIZE_T bytesRead = 0;

  bool readProcMemory = ReadProcessMemory(pHandle, (LPCVOID)0x010FFA28, (LPVOID)&intRead, sizeof(int), &bytesRead);
  if(readProcMemory == 0) {
    cout << "ReadProcessMemory failed GetLastError() = " << dec << GetLastError() << endl;
    return EXIT_FAILURE;
  }
  cout << "varInt from target program = " << dec << intRead << endl;
  cout << "Bytes Read : " << dec << bytesRead << endl;

  bool closeHandleResult = CloseHandle(pHandle);
  if(closeHandleResult != 0) {
    cout << "Handle closed sucessfully" << endl;
  } else {
    cout << "Error while closing handle. GetLastError() = " <<  dec <<  GetLastError() << endl;
  }
  return 0;
}
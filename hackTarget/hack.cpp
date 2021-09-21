#include <iostream> 
#include <cstring> 
#include <Windows.h>
#include <processthreadsapi.h>
#include <handleapi.h>
#include <errhandlingapi.h>

using namespace std;

template<class T>
int getValue(HANDLE& handle, LPCVOID address, T& value) {
  SIZE_T bytesRead = 0;
  bool readProcMemory = ReadProcessMemory(handle, (LPCVOID)address, (LPVOID)&value, sizeof(T), &bytesRead);
  if(readProcMemory == 0) {
    cout << "ReadProcessMemory failed GetLastError() = " << dec << GetLastError() << endl;
    return EXIT_FAILURE;
  }
  cout << "Bytes Read : " << dec << bytesRead << endl;
  return 0;
}

int main() {
  DWORD pid = 0;
  cout << "PID: ";
  cin >> dec >> pid;

  HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
  if(pHandle == NULL) {
    cout << "Failed to open process. GetLastError() = " << dec << GetLastError() << endl;
    return EXIT_FAILURE;
  }
  cout << "VALUES FROM TARGET PROGRAM" << endl;

  int intRead = 0;

  uintptr_t intMemory = 0x0;
  cout << "Memory Address of the integer (in hex): 0x";
  cin >> hex >> intMemory;
  

  getValue<int>(pHandle, (LPCVOID)intMemory, intRead);
  cout << "varInt = " << dec << intRead << endl;
  
  uintptr_t strMemory = 0x0;
  cout << "Memory Address of the string (in hex): 0x";
  cin >> hex >> strMemory;

  string strRead = "";
  getValue<string>(pHandle, (LPCVOID)strMemory, strRead);
  cout << "strString = " << strRead << endl;

  bool closeHandleResult = CloseHandle(pHandle);
  if(closeHandleResult != 0) {
    cout << "Handle closed sucessfully" << endl;
  } else {
    cout << "Error while closing handle. GetLastError() = " <<  dec <<  GetLastError() << endl;
  }
  return 0;
}
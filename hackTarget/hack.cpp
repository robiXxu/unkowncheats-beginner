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

  HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, false, 17800);
  if(pHandle == NULL) {
    cout << "Failed to open process. GetLastError() = " << dec << GetLastError() << endl;
    return EXIT_FAILURE;
  }
  cout << "VALUES FROM TARGET PROGRAM" << endl;

  int intRead = 0;
  getValue<int>(pHandle, (LPCVOID)0x010FFA28, intRead);
  cout << "varInt = " << dec << intRead << endl;
  
  string strRead = "";
  getValue<string>(pHandle, (LPCVOID)0x010FFA2C, strRead);
  cout << "strString = " << strRead << endl;

  bool closeHandleResult = CloseHandle(pHandle);
  if(closeHandleResult != 0) {
    cout << "Handle closed sucessfully" << endl;
  } else {
    cout << "Error while closing handle. GetLastError() = " <<  dec <<  GetLastError() << endl;
  }
  return 0;
}
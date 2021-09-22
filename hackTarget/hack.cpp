#include <iostream> 
#include <cstring> 
#include <Windows.h>
#include <processthreadsapi.h>
#include <handleapi.h>
#include <errhandlingapi.h>
#include <vector>

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

uintptr_t readValueOf(uintptr_t baseAddr, vector<uintptr_t> offsets, HANDLE& handle) {
  uintptr_t addr = baseAddr;
  int status = 0;
  for(uintptr_t p : offsets) {
    status = getValue<uintptr_t>(handle, (LPCVOID) addr, addr);
    if(status != 0) return addr;
    addr += p;
  }
  return addr;
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

  uintptr_t baseAddr = 0x0;
  cout << "Memory address of a pointer: 0x";
  cin >> hex >> baseAddr;
  vector<uintptr_t> offsets {0x0, 0x0, 0x0}; 
  uintptr_t valPtr = readValueOf(baseAddr, offsets, pHandle);
  cout << "Memory address of the value: 0x" << hex << uppercase << valPtr << endl;
  int val = 0;
  getValue(pHandle, (LPCVOID)valPtr, val);
  cout << "Value : " << dec << val << endl;

  //uintptr_t ptr2IntMem = 0x0;
  //cout << "Memory address of a pointer: 0x";
  //cin >> hex >> ptr2IntMem;
  //int *ptr2Int;
  //getValue<int*>(pHandle, (LPCVOID)ptr2IntMem, ptr2Int);
  //cout << "ptr2Int(hex) = " << hex << ptr2Int << endl;
  //int intValue;
  //getValue<int>(pHandle, (LPCVOID)ptr2Int, intValue);
  //cout << "ptr2Int(value) = " << dec << intValue << endl;

  

  //uintptr_t intMemory = 0x0;
  //cout << "Memory Address of the integer (in hex): 0x";
  //cin >> hex >> intMemory;
  //int intRead = 0;
  //getValue<int>(pHandle, (LPCVOID)intMemory, intRead);
  //cout << "varInt = " << dec << intRead << endl;
  
  //uintptr_t strMemory = 0x0;
  //cout << "Memory Address of the string (in hex): 0x";
  //cin >> hex >> strMemory;
  //string strRead = "";
  //getValue<string>(pHandle, (LPCVOID)strMemory, strRead);
  //cout << "strString = " << strRead << endl;

  bool closeHandleResult = CloseHandle(pHandle);
  if(closeHandleResult != 0) {
    cout << "Handle closed sucessfully" << endl;
  } else {
    cout << "Error while closing handle. GetLastError() = " <<  dec <<  GetLastError() << endl;
  }
  return 0;
}
#include <iostream>
#include <windows.h>
#include <processthreadsapi.h>
#include <handleapi.h>

using namespace std;

int error(string message) {
  int lastErrorCode = GetLastError();
  cout << message << " GetLastError() = " << dec << lastErrorCode << endl;
  return lastErrorCode;
}

int main() {
  int pid;
  cout << "PID: ";
  cin >> dec >> pid;

  HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
  if(handle == NULL) {
    return error("OpenProcess"); 
  }


  int closeStatus = CloseHandle(handle);
  if(closeStatus == 0) {
    return error("CloseHandle");
  }
  return 0;
}
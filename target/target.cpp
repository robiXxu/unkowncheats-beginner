#include <iostream>
#include <cstring>
#include <Windows.h>

#define ARRAY_CHAR_SIZE 128
using namespace std;

int main() {

  int varInt = 123456;
  string varString = "DefaultString";
  char varChar[ARRAY_CHAR_SIZE];
  strcpy(varChar, "Long char array right there ->");
  cout << varChar << endl;
  int * ptr2int = &varInt;
  int ** ptr2ptr = &ptr2int;
  int *** ptr2ptr2 = &ptr2ptr;

  while(true) {
    cout << "Process ID: " << GetCurrentProcessId() << endl;
    cout << endl;
    cout << "varInt \t\t(0x" << &varInt << ") = " << varInt << endl;
    cout << "varString \t(0x" << &varString << ") = " << varString << endl;
    cout << "varChar \t(0x" << &varChar << ") = " << varChar << endl;
    cout << endl;
    cout << "ptr2int \t(0x" << &ptr2int << ") = " << "0x" << ptr2int << endl;
    cout << "ptr2ptr \t(0x" << &ptr2ptr << ") = " << "0x" << ptr2ptr << endl;
    cout << "ptr2ptr2 \t(0x" << &ptr2ptr2 << ") = " << "0x" << ptr2ptr2 << endl;

    cout << endl;
    cout << "Press ENTER to print again." << endl;
    system("pause > nul");
    cout << "----------------------------------------------" << endl;
  }


  return 0;
}
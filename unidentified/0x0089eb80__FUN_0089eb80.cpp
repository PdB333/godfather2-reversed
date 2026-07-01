// FUNC_NAME: SomeClass::clearArrayOfPointers
void __fastcall clearArrayOfPointers(int *param_1)
{
  int iVar1;
  
  iVar1 = 4;
  do {
    if (*param_1 != 0) {
      // Free the object pointed to by the current slot (likely a destructor or release call)
      FUN_004daf90(param_1);
      *param_1 = 0; // Null out the pointer after freeing
    }
    param_1[2] = 0; // Clear the third element of the current triple (offset +0x08)
    param_1 = param_1 + 3; // Advance to the next triple (each entry is 12 bytes: pointer + 2 ints)
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return;
}
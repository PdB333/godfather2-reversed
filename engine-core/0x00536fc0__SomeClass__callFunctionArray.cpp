// FUNC_NAME: SomeClass::callFunctionArray
void SomeClass::callFunctionArray(void) {
  int index;
  undefined4 functionPtr;
  short count; // +0x02

  functionPtr = *(undefined4 *)(this + 4);
  index = 0;
  count = *(short *)(this + 2);
  
  if (0 < count) {
    do {
      // Call the function pointer - assumed to be a function array
      FUN_00577b30(functionPtr);
      
      // Some engine update/poll function
      FUN_00414aa0();
      
      index = index + 1;
    } while (index < count);
  }
  return;
}
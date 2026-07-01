// FUNC_NAME: SomeClass::getStringProperty
void __thiscall getStringProperty(int this, undefined4 param_2, undefined4 param_3)
{
  undefined1 *strPtr;
  undefined1 *local_10;
  undefined4 local_c;
  undefined4 local_8;
  code *local_4;
  
  local_10 = (undefined1 *)0x0;
  local_c = 0;
  local_8 = 0;
  local_4 = (code *)0x0;
  // Call to get a string from some internal data structure at offset +0x1c
  FUN_00603d30(*(undefined4 *)(this + 0x1c),&local_10,1);
  strPtr = local_10;
  if (local_10 == (undefined1 *)0x0) {
    // Use a default empty string if null
    strPtr = &DAT_0120546e;
  }
  // Copy the string to the output buffer
  FUN_005c4660(param_2,strPtr,param_3,local_c);
  if (local_10 != (undefined1 *)0x0) {
    // Free the allocated string if it was dynamically allocated
    (*local_4)(local_10);
  }
  return;
}
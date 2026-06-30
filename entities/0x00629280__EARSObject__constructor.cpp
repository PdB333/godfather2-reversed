// FUNC_NAME: EARSObject::constructor
void __thiscall EARSObject::constructor(void *thisPtr, undefined4 param2)
{
  undefined *eaxReg;
  undefined1 local_24[4];
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined1 *local_14;
  undefined1 *local_10;
  undefined *local_c;
  
  local_10 = local_24;
  local_20 = param2;
  if (eaxReg == (undefined *)0x0) {
    eaxReg = &DAT_00e41518;  // Default vtable or static data
  }
  local_14 = &LAB_00629260;  // Destructor pointer
  local_1c = 0;
  local_18 = 0;
  local_c = eaxReg;
  FUN_00638520();  // Initialize base object
  FUN_006366f0(thisPtr);  // Setup vtable and member data
  return;
}
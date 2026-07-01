// FUNC_NAME: EARSObject::constructor
undefined4 * __thiscall EARSObject::constructor(undefined4 *thisObject, int param_2)

{
  undefined4 uVar1;
  
  if (param_2 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = FUN_00481610();  // Probably some allocation or initialization function
  }
  FUN_0064d390(1,1);  // Likely memory tracking or reference counting
  *thisObject = &PTR_LAB_00e317dc;  // Set vtable pointer (initial placeholder)
  thisObject[6] = 0;  // +0x18: Initialize some field to null
  FUN_00454a10(uVar1);  // Further initialization dependent on param_2
  thisObject[9] = 1;  // +0x24: Set some flag/count to 1
  *thisObject = &PTR_LAB_00d79e78;  // Replace vtable pointer with final vtable
  thisObject[10] = &PTR_LAB_00d79bd8;  // +0x28: Set secondary vtable or interface pointer
  thisObject[0xc] = &LAB_008a89e0;  // +0x30: Set function pointer or vtable entry
  thisObject[0xd] = 0;  // +0x34: Initialize to zero
  thisObject[5] = thisObject + 10;  // +0x14: Point to secondary vtable region
  return thisObject;
}
// FUNC_NAME: EARSObject::createInstance
undefined4 * EARSObject::createInstance(undefined4 param_1, undefined4 param_2, undefined4 param_3)
{
  undefined4 *puVar1;
  int iVar2;
  undefined4 unaff_retaddr;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  puVar1 = (undefined4 *)FUN_009c8f80(); // Get allocator/manager singleton
  local_c = 2;  // Alignment: 2 bytes
  local_8 = 0x10; // Size: 0x10 bytes (16 bytes)
  local_4 = 0;  // Flags: 0
  iVar2 = (**(code **)*puVar1)(0xd0, &local_c); // Allocate 0xD0 bytes with alignment/size/flags
  if (iVar2 == 0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1 = (undefined4 *)FUN_005195b0(local_4, unaff_retaddr, param_2, param_3); // Constructor call
  }
  if ((*(byte *)(puVar1 + 4) & 1) != 0) { // Check if allocation failed (bit 0 set)
    (**(code **)*puVar1)(1); // Free memory
    puVar1 = (undefined4 *)0x0;
  }
  return puVar1;
}
// FUNC_NAME: EARSObject::createInstance
undefined4 EARSObject::createInstance(void)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 unaff_retaddr;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  puVar1 = (undefined4 *)FUN_009c8f80(); // Get class registry or factory
  local_c = 2; // Class ID or type
  local_8 = 0x10; // Size of object (16 bytes)
  local_4 = 0; // Flags or constructor argument
  iVar2 = (**(code **)*puVar1)(0xb0,&local_c); // Call factory method with allocation size 0xB0 and params
  if (iVar2 != 0) {
    uVar3 = FUN_008cda10(unaff_retaddr,local_4); // Initialize object
    return uVar3;
  }
  return 0;
}
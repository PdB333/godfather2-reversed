// FUNC_NAME: EARSObject::createInstance
undefined4 EARSObject::createInstance(undefined4 param_1, undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_c = 2;  // +0x00: type ID (2 = EARSObject)
  local_8 = 0x10; // +0x04: size (0x10 bytes)
  local_4 = 0;   // +0x08: flags (0 = default)
  iVar1 = FUN_0043b980(0x70, &local_c, param_2); // allocate memory for object (0x70 bytes)
  if (iVar1 != 0) {
    uVar2 = FUN_00906930(param_1); // initialize object from template
    return uVar2;
  }
  return 0;
}
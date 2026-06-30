// FUNC_NAME: NetworkObject::createInstance
undefined4 NetworkObject::createInstance(undefined4 param_1, undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_c = 2; // NetworkObject type ID (likely)
  local_8 = 0x10; // NetworkObject subclass ID (likely)
  local_4 = 0; // Flags/reserved
  iVar1 = FUN_0043b980(0x240, &local_c, param_2); // Allocate 0x240 bytes for object
  if (iVar1 != 0) {
    uVar2 = FUN_00904710(param_1); // Call constructor/initializer
    return uVar2;
  }
  return 0; // Allocation failed, return null
}
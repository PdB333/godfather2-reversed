// FUNC_NAME: EntityManager::allocateEntity
undefined4 EntityManager::allocateEntity(undefined4 entityType, undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_c = 2;        // +0x00: entity type? (2 = some specific entity)
  local_8 = 0x10;     // +0x04: size? (0x10 = 16 bytes)
  local_4 = 0;        // +0x08: flags? (0 = default)
  iVar1 = FUN_0043b980(0xf0, &local_c, param_2);  // allocate memory block (0xf0 = 240 bytes)
  if (iVar1 != 0) {
    uVar2 = FUN_008107d0(param_1);  // initialize entity
    return uVar2;
  }
  return 0;
}
// FUNC_NAME: EARSObject::spawnOrCreate
undefined4 EARSObject::spawnOrCreate(undefined4 param_1, undefined4 param_2)
{
  int iVar1;
  undefined4 uVar2;
  undefined4 allocFlags; // local_c
  undefined4 alignment;  // local_8
  undefined4 unknown;    // local_4
  
  allocFlags = 2;      // +0x00: allocation flags (2 = ???)
  alignment = 0x10;    // +0x04: 16-byte alignment
  unknown = 0;         // +0x08: unused or reserved
  iVar1 = FUN_0043b980(0xcc, &allocFlags, param_2); // allocate 0xCC bytes from memory pool
  if (iVar1 != 0) {
    uVar2 = FUN_0086bbd0(param_1); // call constructor/init with param_1
    return uVar2;
  }
  return 0;
}
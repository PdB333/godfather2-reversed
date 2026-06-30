// FUNC_NAME: CoverHintNodeManager::constructor
undefined4 * __fastcall CoverHintNodeManager::constructor(undefined4 *this)

{
  undefined4 *puVar1;
  int iVar2;
  
  *this = &PTR_LAB_00d5fb00;
  DAT_011298a4 = this;
  this[1] = &PTR_FUN_00e2f19c;
  this[2] = 1;
  this[3] = 0;
  FUN_0049c610();
  *this = &PTR_FUN_00d5fb3c;
  this[1] = &PTR_LAB_00d5fb2c;
  this[4] = &PTR_LAB_00d5fb20;
  this[6] = 0;
  this[7] = 0;
  puVar1 = this + 8;
  iVar2 = 0x3ff;
  do {
    *puVar1 = 0;
    puVar1[1] = 0;
    puVar1 = puVar1 + 2;
    iVar2 = iVar2 + -1;
  } while (-1 < iVar2);
  this[0x808] = 0;
  FUN_006e5df0();
  FUN_0049c6e0("COVERNODETABLE",1);
  iVar2 = FUN_009c8e50(0x10);
  if (iVar2 == 0) {
    DAT_0112a99c = 0;
  }
  else {
    DAT_0112a99c = FUN_006e5fa0(0x12d,0);
  }
  iVar2 = FUN_009c8e50(0x18);
  if (iVar2 != 0) {
    DAT_0112a9a0 = FUN_006e77c0(0x7d1,0);
    return this;
  }
  DAT_0112a9a0 = 0;
  return this;
}
// FUNC_NAME: SomeClass::initFromGameState
undefined4 SomeClass::initFromGameState(undefined4 *this, int param_2)
{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  
  uVar1 = _DAT_00d5780c; // some global constant (e.g., invalid/zero value)
  this[1] = 0;
  this[2] = 0;
  this[3] = 0;
  this[4] = 0;
  this[6] = 0;
  this[7] = 0;
  this[8] = 0;
  this[9] = 0;
  this[0xb] = 0;
  *this = uVar1;
  this[5] = uVar1;
  this[10] = uVar1;
  this[0xf] = 0;
  this[0xe] = 0;
  this[0xd] = 0;
  this[0xc] = 0;
  if (param_2 != 0) {
    iVar3 = FUN_00471610(); // likely getGameState() or getCurrentGameState()
    uVar1 = *(undefined4 *)(iVar3 + 0x34);
    uVar2 = *(undefined4 *)(iVar3 + 0x38);
    this[0xc] = *(undefined4 *)(iVar3 + 0x30);
    this[0xd] = uVar1;
    uVar1 = _DAT_00d5780c;
    this[0xe] = uVar2;
    this[0xf] = uVar1;
    FUN_004b59d0(iVar3, this); // likely registerForGameStateChanges or similar
    return 1;
  }
  return 0;
}
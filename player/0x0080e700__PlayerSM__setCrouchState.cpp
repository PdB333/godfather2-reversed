// FUNC_NAME: PlayerSM::setCrouchState
void __thiscall PlayerSM::setCrouchState(int this, char param_2)
{
  int iVar1;
  uint uVar2;
  byte bVar3;
  
  iVar1 = *(int *)(this + 0x50);
  bVar3 = ~*(byte *)(iVar1 + 0x4a4) & 1;
  if (param_2 == '\0') {
    *(uint *)(iVar1 + 0x4a4) = *(uint *)(iVar1 + 0x4a4) | 1;
  }
  else {
    *(uint *)(iVar1 + 0x4a4) = *(uint *)(iVar1 + 0x4a4) & 0xfffffffe;
  }
  if (bVar3 == 0) {
    if (param_2 == '\0') {
      return;
    }
  }
  else if (param_2 != '\0') {
    return;
  }
  uVar2 = *(uint *)(this + 0x54);
  if ((uVar2 & 4) != 0) {
    *(uint *)(this + 0x54) = uVar2 & 0xfffffffb;
    return;
  }
  *(uint *)(this + 0x54) = uVar2 | 4;
  if (bVar3 == 0) {
    *(uint *)(this + 0x54) = uVar2 & 0xfffffffd | 4;
    return;
  }
  *(uint *)(this + 0x54) = uVar2 | 6;
  return;
}
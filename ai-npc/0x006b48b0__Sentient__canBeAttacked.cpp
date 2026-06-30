// FUNC_NAME: Sentient::canBeAttacked
bool __fastcall Sentient::canBeAttacked(int this)
{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(this + 0x16c);
  if (((((*(uint *)(this + 0x34) & 0x120000) == 0) && ((*(byte *)(this + 0x34) & 1) == 0)) &&
      (*(int *)(this + 0x40) != 0)) &&
     (((iVar2 = FUN_008c74d0(*(int *)(this + 0x40)), iVar2 != 0 &&
       ((~(byte)(*(uint *)(iVar2 + 0x84) >> 5) & 1) != 0)) && (iVar1 == 0)))) {
    return (*(uint *)(this + 0x34) & 0x50004) != 0;
  }
  return true;
}
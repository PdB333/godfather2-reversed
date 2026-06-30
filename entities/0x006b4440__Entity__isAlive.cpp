// FUNC_NAME: Entity::isAlive
bool __fastcall Entity::isAlive(int this)
{
  bool bAlive;
  int iVar1;
  
  bAlive = false;
  if ((*(byte *)(this + 0x34) & 1) == 0) { // +0x34: flags (bit 0 = dead/destroyed)
    bAlive = false;
    if (((*(int *)(this + 0x40) != 0) && // +0x40: pointer to health/state component
        (iVar1 = FUN_008c74d0(*(int *)(this + 0x40)), iVar1 != 0)) &&
       ((~(byte)(*(uint *)(iVar1 + 0x84) >> 5) & 1) != 0)) { // +0x84: health flags (bit 5 = dead)
      bAlive = true;
    }
  }
  return bAlive;
}
// FUNC_NAME: GodfatherGameManager::shutdownOrExit
void __thiscall GodfatherGameManager::shutdownOrExit(int *this, int param_2, int param_3, char param_4)
{
  int iVar1;
  int *piVar2;
  code *pcVar3;
  
  if (param_3 != 0) {
    FUN_009823b0(); // likely some cleanup function
    FUN_009c8eb0(param_3); // likely delete/free param_3
  }
  piVar2 = DAT_01223484; // global pointer
  if ((param_4 == '\0') && (param_2 != -1)) {
    FUN_008a2d40(0); // likely some init/start function
    iVar1 = **(int **)(DAT_012233a0 + 4); // dereference global +4
    if ((iVar1 != 0) &&
       ((iVar1 != 0x1f30 && (FUN_00907ac0(0x1e,0x3f800000), *(char *)(iVar1 + 0x11ec) != '\0')))) {
      FUN_00907a50(0x1c,0x3f800000); // set some flag/state
    }
    iVar1 = *piVar2;
    if (piVar2[2] == 0) {
      pcVar3 = *(code **)(iVar1 + 0x98); // vtable offset 0x98
    }
    else {
      pcVar3 = *(code **)(iVar1 + 0x80); // vtable offset 0x80
    }
    (*pcVar3)(); // call virtual function
    FUN_008a4ae0(0); // likely cleanup
    PostQuitMessage(0);
    (**(code **)(*this + 0x2c))(); // call virtual destructor or cleanup
    return;
  }
  *(ushort *)((int)this + 0x66) = *(ushort *)((int)this + 0x66) & 0xfffe; // clear bit 0
  (**(code **)(*this + 8))(); // call virtual function at offset 8
  *(ushort *)((int)this + 0x66) = *(ushort *)((int)this + 0x66) & 0xfffd; // clear bit 1
  return;
}
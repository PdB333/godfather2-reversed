// FUNC_NAME: NetReflectable::handleMessage
void __thiscall NetReflectable::handleMessage(uint* message)
{
  uint *puVar1;
  int iVar2;
  char netBufferInit[12];
  char netBufferWrite[12];
  
  iVar2 = (**(code **)*message)();
  if (iVar2 == 0x27a0f69c) {
    // GM_StateChange / ObjectUpdate message
    if ((*(byte *)(this + 0x90) & 1) != 0) {
      // Set dirty bit in net reflector's packet buffer flags
      puVar1 = (uint *)(*(int *)(this + 0x58) + 0x24a4);
      *puVar1 = *puVar1 | 8;
    }
    FUN_007bb630(netBufferWrite, netBufferInit);
    FUN_00754d30(netBufferWrite, netBufferInit, 1, *(undefined4 *)(*(int *)(this + 0x58) + 0x1fdc), 0, 1);
  }
  else if (iVar2 == -0x4357f21f) {
    // GM_Destroy / Detach message
    FUN_007af880();
    if (*(int *)(this + 0x188) != 0) {
      FUN_007b1250(*(int *)(this + 0x188) + -0x48);
      return;
    }
    FUN_007b1250(0);
    return;
  }
  return;
}
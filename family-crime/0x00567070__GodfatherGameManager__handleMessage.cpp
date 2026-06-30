// FUNC_NAME: GodfatherGameManager::handleMessage
void __thiscall GodfatherGameManager::handleMessage(int param_1, int param_2)
{
  if (param_2 == -0xdc) {
    // Handle special message (0xFFFFFF24 / -220)
    FUN_00566b70();
    if (*(int *)(param_1 + 0x11c) != 0) {
      FUN_009c8eb0(*(int *)(param_1 + 0x11c));
      *(undefined4 *)(param_1 + 0x11c) = 0;
    }
    *(uint *)(param_1 + 0x2c) = *(uint *)(param_1 + 0x2c) | 0x400;
    *(undefined4 *)(param_1 + 0x10) = 0xd;
    return;
  }
  if (*(code **)(param_1 + 0x58) != (code *)0x0) {
    (**(code **)(param_1 + 0x58))(param_2);
  }
  if (DAT_012234e0 != (int *)0x0) {
    (**(code **)(*DAT_012234e0 + 0xc))();
  }
  if (*(int **)(param_1 + 0xc) != (int *)0x0) {
    (**(code **)(**(int **)(param_1 + 0xc) + 4))(param_1);
    *(undefined4 *)(param_1 + 0xc) = 0;
  }
  *(int *)(param_1 + 0x18) = param_2;
  *(undefined1 *)(param_1 + 0x14) = 1;
  *(undefined4 *)(param_1 + 0x10) = 0xd;
  return;
}
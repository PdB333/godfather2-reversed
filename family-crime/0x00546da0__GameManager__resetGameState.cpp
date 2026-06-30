// FUNC_NAME: GameManager::resetGameState
void GameManager::resetGameState(void)
{
  int iVar1;
  
  TlsGetValue(DAT_01139810);
  iVar1 = FUN_00aa2680(0x1c,0xb);
  *(undefined2 *)(iVar1 + 4) = 0x1c;
  iVar1 = FUN_00549900();
  *(undefined4 *)(*(int *)(iVar1 + 0x18) + 0x14) = 0;
  *(undefined4 *)(*(int *)(iVar1 + 0x18) + 0x18) = 0;
  *(undefined1 *)(*(int *)(iVar1 + 0x18) + 0x10) = 1;
  *(undefined1 *)(*(int *)(iVar1 + 0x18) + 0x11) = 0;
  *(undefined4 *)(*(int *)(iVar1 + 0x18) + 8) = 0;
  return;
}
// FUNC_NAME: GodfatherGameManager::setAlpha
void __fastcall GodfatherGameManager::setAlpha(int param_1)

{
  undefined4 uVar1;
  char acStack_10 [16];
  
  uVar1 = (**(code **)(*(int *)(param_1 + 0x10) + 4))();
  DAT_01223564 = (undefined1)((uint)uVar1 >> 0x18);
  DAT_01223565 = (undefined1)((uint)uVar1 >> 0x10);
  DAT_01223566 = (undefined1)((uint)uVar1 >> 8);
  DAT_01223567 = (undefined1)uVar1;
  DAT_01223568 = 0;
  _sprintf(acStack_10,"%s._alpha",&DAT_01223564);
  FUN_0059ee00(acStack_10,0);
  return;
}
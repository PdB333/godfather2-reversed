// FUNC_NAME: SomeManager::shutdown
void __fastcall SomeManager::shutdown(int this)
{
  int iVar1;
  
  FUN_0096abb0();
  FUN_009c8f10(*(undefined4 *)(this + 0x6c));
  iVar1 = *(int *)(this + 0x58);
  if (iVar1 != 0) {
    FUN_009c8f10(*(undefined4 *)(iVar1 + 8));
    FUN_009c8eb0(iVar1);
  }
  if (*(int *)(this + 0x4c) != 0) {
    FUN_009c8f10(*(int *)(this + 0x4c));
  }
  FUN_005c16e0();
  return;
}
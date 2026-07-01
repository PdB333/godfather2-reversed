// FUNC_NAME: SomeQueue::pushItem
undefined4 __fastcall SomeQueue::pushItem(int this)
{
  undefined4 uVar1;
  
  uVar1 = FUN_0049c9c0();
  FUN_0088cc10();
  if (*(uint *)(this + 0x210) < 0x32) {
    *(undefined4 *)(this + 0x148 + *(uint *)(this + 0x210) * 4) = uVar1;
    *(int *)(this + 0x210) = *(int *)(this + 0x210) + 1;
  }
  return uVar1;
}
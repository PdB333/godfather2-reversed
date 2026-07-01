// FUNC_NAME: SomeClass::repeatAction
void __thiscall SomeClass::repeatAction(int this, undefined4 param2, undefined4 param3)
{
  byte counter = 0;
  if (*(int *)(this + 0x148) != 0) {
    do {
      FUN_0088c240(param2, param3);
      counter = counter + 1;
    } while ((uint)counter < *(uint *)(this + 0x148));
  }
  return;
}
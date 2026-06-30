// FUNC_NAME: SomeClass::getActionStatePtr
int __thiscall SomeClass::getActionStatePtr(int thisPtr, int param_2)
{
  int actionStatePtr;
  
  actionStatePtr = thisPtr + 0x68;  // +0x68: primary action state offset
  if (param_2 != 1) {
    actionStatePtr = thisPtr + 0x74;  // +0x74: secondary action state offset
  }
  return actionStatePtr;
}
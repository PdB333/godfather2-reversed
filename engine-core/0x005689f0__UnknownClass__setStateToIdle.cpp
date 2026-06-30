// FUNC_NAME: UnknownClass::setStateToIdle
void __thiscall UnknownClass::setStateToIdle(int this)
{
  int currentState;

  currentState = *(int *)(this + 0xc);
  if ((currentState == 3) || (currentState == 4) || (currentState == 2)) {
    // Clean up resources for non-idle states
    FUN_00c7a770(*(int *)(this + 0x4));
  }
  *(int *)(this + 0xc) = 1; // Set state to idle (1)
}
// FUNC_NAME: SomeClass::setPauseState
void __thiscall setPauseState(int this, char isPaused)
{
  if (isPaused != '\0') {
    // Increment pause count when pausing
    *(int *)(this + 0x78) = *(int *)(this + 0x78) + 1;
    return;
  }
  // Decrement pause count when unpausing, but don't go below 0
  if (0 < *(int *)(this + 0x78)) {
    *(int *)(this + 0x78) = *(int *)(this + 0x78) + -1;
  }
  return;
}
// FUNC_NAME: SomeClass::clearCurrentTarget
void __thiscall clearCurrentTarget(int this, int target)
{
  if (*(int *)(this + 0x40) == target) {
    *(undefined4 *)(this + 0x40) = 0; // Clear current target pointer at +0x40
  }
  return;
}
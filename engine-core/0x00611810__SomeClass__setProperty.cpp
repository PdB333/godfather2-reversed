// FUNC_NAME: SomeClass::setProperty
void __thiscall SomeClass::setProperty(int value)
{
  // offset +0x118: unknown property field
  *(int *)(this + 0x118) = value;

  // If this is the current global instance (g_currentInstance) and a flag at +0x114 is non-zero,
  // call a global update/notification function.
  if (g_currentInstance == this && *(int *)(this + 0x114) != 0) {
    FUN_006063b0(); // likely performs some action (e.g., state change, animation event)
  }
}
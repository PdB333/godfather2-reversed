// FUNC_NAME: PropertyManager::setPropertyLevel
void __thiscall PropertyManager::setPropertyLevel(int this, undefined4 value, uint level)
{
  uint localVar;
  processInputValue(&value);
  localVar = level;
  if (this != 0 && this != -8) {
    if (level < 4) {
      debugPrintWarning(0);
    }
    if (localVar < 2) {
      setPropertyFlag(0xff, localVar);
    }
  }
  return;
}
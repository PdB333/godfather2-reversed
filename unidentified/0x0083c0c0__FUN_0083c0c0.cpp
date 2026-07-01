// FUNC_NAME: SomeClass::processModifierList
void __thiscall SomeClass::processModifierList(int this, int modifierIndex, undefined4 param3)
{
  undefined4 *modifierEntry;
  undefined4 *currentEntry;
  undefined4 *endEntry;
  float10 accumulatedValue;
  
  modifierEntry = (undefined4 *)(this + 0x100); // +0x100: start of modifier list array
  accumulatedValue = (float10)modifierIndex;
  currentEntry = modifierEntry;
  if (modifierEntry != modifierEntry + *(int *)(this + 0x128) * 2) { // +0x128: count of modifiers
    do {
      undefined4 *nextEntry = currentEntry + 2;
      // Each entry is 8 bytes: first 4 bytes point to a vtable/function table
      // Call virtual function at offset +0xC from the vtable
      accumulatedValue = (float10)(**(code **)(*(int *)*currentEntry + 0xc))
                                 (*(undefined4 *)(this + 0xf8), param3, (float)accumulatedValue);
      currentEntry = nextEntry;
    } while (nextEntry != modifierEntry + *(int *)(this + 0x128) * 2);
  }
  return;
}
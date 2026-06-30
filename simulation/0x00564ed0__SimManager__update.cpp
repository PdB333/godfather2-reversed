// FUNC_NAME: SimManager::update
void __fastcall SimManager::update(int thisPtr)
{
  int *vtable;
  char isDestroyed;
  undefined4 *objectArray;
  uint index;

  FUN_00ab4db0(&DAT_00e2cbf4); // likely mutex lock or scope enter

  vtable = *(int **)(thisPtr + 0x20); // +0x20: processList (some list of simulation objects)
  (**(code **)(*vtable + 0x38))(0);    // vtable[0x38/4] = processList->begin
  (**(code **)(*vtable + 0x3c))();     // vtable[0x3c/4] = processList->end?
  if ((*(int *)(thisPtr + 0x20) == 0) ||
     (isDestroyed = (**(code **)(**(int **)(thisPtr + 0x20) + 8))(), isDestroyed != '\0')) {
    FUN_005651e0(thisPtr); // likely handle destroyed objects / cleanup
  }
  index = 0;
  if (*(int *)(thisPtr + 0x1c) != 0) { // +0x1c: objectCount
    objectArray = (undefined4 *)(thisPtr + 8); // +0x08: objectArray[0]
    do {
      (**(code **)(*(int *)*objectArray + 0xc))(); // vtable[0xc/4] = update (each object)
      index = index + 1;
      objectArray = objectArray + 1;
    } while (index < *(uint *)(thisPtr + 0x1c));
  }
  FUN_00ab4e70(); // likely mutex unlock or scope leave
  return;
}
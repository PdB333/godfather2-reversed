// FUNC_NAME: ObjectEntry::ObjectEntry
undefined4 * __thiscall ObjectEntry::ObjectEntry(undefined4 *this, int pManager, int pName)
{
  undefined4 *allocResult;
  int allocatedBlock;
  undefined4 newObject;
  undefined4 allocParamA; // local_5c
  undefined4 allocParamB; // local_58
  undefined4 allocParamC; // local_54
  char nameBuffer[76]; // local_50

  this[1] = 0; // +0x04: next pointer (link list)
  this[2] = pManager; // +0x08: back pointer to manager
  *this = &PTR_FUN_00e353e0; // +0x00: vtable pointer
  this[3] = 0; // +0x0C: created object handle

  if (pName != 0) {
    stringCopy(nameBuffer, pName); // copy resource name into local buffer
    allocResult = (undefined4 *)getAllocator(); // singleton allocator
    allocParamA = 2;      // allocation flags?
    allocParamB = 0x10;   // alignment?
    allocParamC = 0;      // extra parameter?
    allocatedBlock = (**(code **)*allocResult)(0xa0, &allocParamA); // allocate 160 bytes
    if (allocatedBlock == 0) {
      newObject = 0;
    }
    else {
      (**(code **)(**(int **)(pManager + 8) + 4))(); // call manager's vtable method (init alloc?)
      newObject = createObject(allocatedBlock); // FUN_004a7150
    }
    this[3] = newObject; // store created object
    initObject(newObject); // FUN_004a63a0
  }
  return this;
}
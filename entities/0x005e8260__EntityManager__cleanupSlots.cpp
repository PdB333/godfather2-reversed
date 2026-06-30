// FUNC_NAME: EntityManager::cleanupSlots
void __fastcall EntityManager::cleanupSlots(int thisPtr)
{
  int slotIndex;
  int *objectPtrArray;
  int *funcPtrArray;
  int *currentObjectPtr;
  int *currentFuncPtr;

  // Release the single object at offset +0x494 using function pointer at +0x4a0
  if (*(int *)(thisPtr + 0x494) != 0) {
    (*(void (__thiscall **)(int))(thisPtr + 0x4a0))(*(int *)(thisPtr + 0x494));
  }

  // Iterate over 4 slots, each containing 5 object/function pointer pairs
  // Slot structure: each slot is 0x6c bytes (108 bytes) and contains 5 pairs
  // Offsets are calculated relative to the slot base
  slotIndex = 3;
  objectPtrArray = (int *)(thisPtr + 0x1f0); // Points to the last slot's object area
  funcPtrArray = (int *)(thisPtr + 0x1b4);   // Points to the last slot's function area

  do {
    // Each slot has 5 object pointers and 5 corresponding function pointers
    // The pairs are stored in reverse order? Offsets are negative indices

    // Pair 1: object at offset -0x1a*4 = -0x68, function at -0x17*4 = -0x5c
    if (objectPtrArray[-0x1a] != 0) {
      (*(void (__thiscall **)(int))funcPtrArray[-0x17])(objectPtrArray[-0x1a]);
    }
    // Pair 2: object at -0x1e*4 = -0x78, function at -0x1b*4 = -0x6c
    if (objectPtrArray[-0x1e] != 0) {
      (*(void (__thiscall **)(int))funcPtrArray[-0x1b])(objectPtrArray[-0x1e]);
    }
    // Pair 3: object at -0x22*4 = -0x88, function at -0x1f*4 = -0x7c
    if (objectPtrArray[-0x22] != 0) {
      (*(void (__thiscall **)(int))funcPtrArray[-0x1f])(objectPtrArray[-0x22]);
    }
    // Pair 4: object at -0x26*4 = -0x98, function at -0x23*4 = -0x8c
    if (objectPtrArray[-0x26] != 0) {
      (*(void (__thiscall **)(int))funcPtrArray[-0x23])(objectPtrArray[-0x26]);
    }
    // Pair 5: object at *objectPtrArray (offset 0), function at -0x27*4 = -0x9c
    if (*objectPtrArray != 0) {
      (*(void (__thiscall **)(int))funcPtrArray[-0x27])(*objectPtrArray);
    }

    // Move to the next slot (slots are stored backwards in memory)
    slotIndex--;
    objectPtrArray -= 0x1b; // 0x1b * 4 = 0x6c bytes per slot
    funcPtrArray -= 0x1b;
  } while (slotIndex >= 0);
}
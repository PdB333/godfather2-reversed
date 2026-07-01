// FUNC_NAME: ControllerManager::cleanup
// 0x0092bd40 - Destructor/cleanup for ControllerManager object, frees sub-object and controller slot array

void __thiscall ControllerManager::cleanup(int thisPtr)
{
  int *pSlotCount; // pointer to controller slot count field at +0x138
  int slotCount;  // current number of slots

  // Zero out various state fields
  *(int *)(thisPtr + 0x58) = 0;   // +0x58: some integer
  *(int *)(thisPtr + 0x5c) = 0;   // +0x5c: some integer
  *(int *)(thisPtr + 0x11c) = 0;  // +0x11c: another integer

  // Destroy sub-object pointed by +0x118 (e.g., a stream or manager)
  FUN_009c8f10(*(void **)(thisPtr + 0x118));
  *(void **)(thisPtr + 0x118) = 0;

  // Zero more fields
  *(int *)(thisPtr + 0x120) = 0;  // +0x120
  *(int *)(thisPtr + 0x124) = 0;  // +0x124

  // Handle controller slot array at +0x138
  pSlotCount = (int *)(thisPtr + 0x138);
  if ((*pSlotCount != 0) && (*pSlotCount != 0x48)) { // if slot count is non‑zero and not 72
    slotCount = *pSlotCount;
    if (slotCount == 0) {
      slotCount = 0;
    } else {
      slotCount = slotCount - 0x48; // subtract default slot count (72)
    }
    FUN_004088c0(slotCount + 0x3c); // free additional slots if any
  }
  if (*pSlotCount != 0) {
    FUN_004daf90(pSlotCount); // free the slot count variable itself
    *pSlotCount = 0;
  }

  *(char *)(thisPtr + 0x17c) = 0; // zero a flag byte

  // Global cleanup debug/logging calls
  FUN_005c1b40();
  FUN_0097f2a0();
  return;
}
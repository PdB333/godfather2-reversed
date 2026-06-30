// FUNC_NAME: ResourceManager::releaseEntry
void __thiscall FUN_006a56c0(int this, int entryHandle)
{
  int slotIndex;
  undefined4 *entryArray;
  int slot;
  
  // Fast path: check the current working entry (stored at +0x6a4)
  if (entryHandle == *(int *)(this + 0x6a4)) {
    // Clear the current working entry handle and its associated data at +0x6b8
    *(undefined4 *)(this + 0x6a4) = 0;
    *(undefined4 *)(this + 0x6b8) = 0;
    return;
  }
  
  // Walk through the 0x20 (32) entry slots starting at +0x6c0
  // Each entry is 6 * 4 = 24 bytes (0x18 bytes)
  // Entry structure: [handle, index, flags, data0, data1, data2]
  entryArray = (undefined4 *)(this + 0x6c0);
  slotIndex = 0x20; // Number of slots to check (dec counter)
  do {
    // Check if the entry handle (at offset -4 from the array start? actually puVar2[-1] means puVar2[ -sizeof(uint) ])
    // Actually careful: puVar2 points to array element, puVar2[-1] is the previous element (which is the handle at the start of the entry)
    // Wait, let's recalc: puVar2 = (undefined4 *)(param_1 + 0x6c0); puVar2[-1] would be *(undefined4*)(param_1 + 0x6bc)
    // But the structure seems: each entry is 6 uints: handle, index, flags, data0, data1, data2
    // So puVar2 points to the index field (second uint), and puVar2[-1] is the handle field.
    // This indexes the slots by their handle.
    if (entryArray[-1] == entryHandle) {
      // If the entry has flags != 0 (possibly 'loaded' or 'active'), call release function
      if (*(char *)(entryArray + 4) != '\0') {
        FUN_006a54d0(entryHandle);
      }
      // Zero out the entire entry (6 uint32s)
      entryArray[-1] = 0;   // handle
      *(undefined1 *)(entryArray + 4) = 0; // flags (only byte cleared? partial)
      entryArray[0] = 0;    // index
      entryArray[1] = 0;    // data0
      entryArray[2] = 0;    // data1
      entryArray[3] = 0;    // data2
    }
    entryArray += 6;  // Move to next entry slot (6 uint32s per slot)
    slotIndex--;
  } while (slotIndex != 0);
  return;
}
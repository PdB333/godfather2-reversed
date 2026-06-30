// FUNC_NAME: ConfigManager::setOption
// Address: 0x0069fc50
// Role: Handles setting a gameplay option. If in a specific mode (e.g., single player), it directly sets a global flag and applies it.
// Otherwise, it registers a function pointer and copies the option value into a data slot.

void ConfigManager::setOption(int value)
{
  // Check if the engine is in a special mode (e.g., single player mode)
  int mode = isInSinglePlayerMode(); // FUN_00483a50

  if (mode == 1) {
    // Directly set a global byte flag (inverted logic: value == 0 enables the flag)
    g_optionFlag = (value == 0); // DAT_0120535b
    applyOption(); // FUN_00433fa0
    return;
  }

  // Otherwise, access a global configuration table (DAT_01206880) at offset +0x14
  // This offset likely holds a pointer to a function pointer array (slot index pointer)
  int** slotPtr = reinterpret_cast<int**>(g_configTable + 0x14); // piVar2
  **slotPtr = reinterpret_cast<int>(&s_defaultHandler); // PTR_FUN_00e50c48
  // Increment the slot pointer by 4 (move to next slot)
  *slotPtr = *slotPtr + 1; // *piVar2 = *piVar2 + 4 (since it's int*, increment by 4 bytes)
  // Store the option value into the slot's data area (copy 4 bytes, 4 times = 16 bytes? Actually copy 4 ints)
  int localValue = value;
  writeData(&localValue, 4, 4); // FUN_0049c430(destination? source? size? count?)
}
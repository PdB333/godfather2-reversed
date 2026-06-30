// FUNC_NAME: GenericCSA::hasCompleted
uint __fastcall GenericCSA::hasCompleted(int thisPtr)
{
  uint flags;
  
  flags = *(uint *)(thisPtr + 0x2c) >> 5;
  if ((flags & 1) != 0) {
    if (*(int *)(thisPtr + 0xc) != 0) {
      // Call virtual function at vtable+0x8 to check if animation state is 5 (completed)
      flags = (**(code **)(**(int **)(thisPtr + 0xc) + 8))();
      if (flags == 5) {
        return 1;
      }
    }
    // Clear the "completed" flag (bit 5) in flags at +0x2c
    *(uint *)(thisPtr + 0x2c) = *(uint *)(thisPtr + 0x2c) & 0xffffffdf;
  }
  return flags & 0xffffff00;
}
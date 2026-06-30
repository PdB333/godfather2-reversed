// FUNC_NAME: Entity::cleanupSubobjects (likely destructor helper)
void __fastcall Entity::cleanupSubobjects(int *thisPtr)
{
  // +0x04: byte flag indicating if subobjects are initialized
  if ((byte)thisPtr[1] != 0)
  {
    // Clear the flag
    *(byte *)(thisPtr + 1) = 0;

    // First group (e.g., components or child objects)
    // +0x08: count of first array
    for (int i = 0; i < thisPtr[2]; i++)
    {
      // Call virtual release for each element (vtable offset 0x1c)
      (**(code **)(*thisPtr + 0x1c))(*(int *)(thisPtr[5] + i * 4));
    }
    // Free the array pointer itself and an associated pointer (offsets +0x14, +0x18)
    (**(code **)(*DAT_01205590 + 0x1c))(thisPtr[5]);
    (**(code **)(*DAT_01205590 + 0x1c))(thisPtr[6]);

    // Second group
    // +0x0C: count of second array
    for (int i = 0; i < thisPtr[3]; i++)
    {
      // Virtual release at offset 0x20
      (**(code **)(*thisPtr + 0x20))(*(int *)(thisPtr[8] + i * 4));
    }
    // Free pointers at offsets +0x20, +0x24
    (**(code **)(*DAT_01205590 + 0x1c))(thisPtr[8]);
    (**(code **)(*DAT_01205590 + 0x1c))(thisPtr[9]);

    // Third group
    // +0x10: count of third array
    for (int i = 0; i < thisPtr[4]; i++)
    {
      // Virtual release at offset 0x24
      (**(code **)(*thisPtr + 0x24))(*(int *)(thisPtr[0xb] + i * 4));
    }
    // Free pointers at offsets +0x2C, +0x30
    (**(code **)(*DAT_01205590 + 0x1c))(thisPtr[0xb]);
    (**(code **)(*DAT_01205590 + 0x1c))(thisPtr[0xc]);
  }
}
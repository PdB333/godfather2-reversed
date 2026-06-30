// FUNC_NAME: EARSObject::returnToPool
void EARSObject::returnToPool(void)
{
  // If the vtable pointer (first field) is not null, the object is alive
  if (this->vtablePtr != 0)
  {
    // Obtain a base address by combining thread‑local storage and object offset
    int base = *(int *)(*(int *)(*(int *)(__readfsdword(0x2c)) + 8) + this->vtablePtr);

    // Free two dynamically allocated sub‑objects at offsets +0x10 and +0x14
    if (*(int *)(base + 0x10) != 0)
    {
      FUN_00610f90(*(int *)(base + 0x10));   // free sub‑object 1
      *(int *)(base + 0x10) = 0;             // clear pointer
    }
    if (*(int *)(base + 0x14) != 0)
    {
      FUN_00610f90(*(int *)(base + 0x14));   // free sub‑object 2
      *(int *)(base + 0x14) = 0;             // clear pointer
    }

    // Return the object to the global free list (located at g_memoryManager + 0x14)
    int vtableBackup = this->vtablePtr;               // save current vtable pointer
    int *freeListPtr = (int *)(DAT_01206880 + 0x14); // pointer to free list head

    // Update free list: store a static label as first entry,
    // then write the saved vtable pointer, and finally zero the object's first two fields
    **(int **)(DAT_01206880 + 0x14) = (int)&PTR_LAB_01123be8; // static list anchor
    *freeListPtr = *freeListPtr + 4;                           // advance free list pointer
    *(int *)(*freeListPtr) = vtableBackup;                     // store vtable (marks free slot)
    *freeListPtr = *freeListPtr + 4;                           // advance again

    // Clear first two fields of this object (vtable and flag) to indicate it's in free list
    this->vtablePtr = 0;
    this->field_4 = 0;
  }
}
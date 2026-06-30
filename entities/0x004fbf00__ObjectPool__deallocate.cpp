// FUNC_NAME: ObjectPool::deallocate

void ObjectPool::deallocate(void)
{
  // 'this' is unaff_EDI: points to an object with fields at offset 0 and 4
  if (*this != 0) // check if the object's first field is non-null
  {
    // Call a preprocessing function (likely cleans up internal state)
    this->onRelease(); // FUN_004fc520

    int objAddr = *this; // save the object's address (stored in first field)
    int* freeListPtr = (int*)(g_poolManager + 0x14); // global pool manager + 0x14 holds a pointer to the free list buffer

    // Reset the free list pointer to the start of the static free list buffer
    **(int***)(g_poolManager + 0x14) = &freeListBuffer; // PTR_LAB_01123be8
    *freeListPtr = *freeListPtr + 4; // skip the header/sentinel? move to first free slot

    // Store the object address into the free list buffer
    *(int*)(*freeListPtr) = objAddr;
    *freeListPtr = *freeListPtr + 4; // advance free list pointer for next allocation

    // Clear the object's fields (mark as unused)
    *this = 0;
    this[1] = 0; // offset 4
  }
}
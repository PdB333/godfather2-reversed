// FUNC_NAME: returnPoolBlockToAllocator
void __thiscall returnPoolBlockToAllocator(int* pThis)
{
  int* pBlock;
  int* tlsSlot0;
  int* pFreeListWritePos;
  
  // pThis is the object being freed (passed via EDI, non-standard __thiscall)
  if (*pThis != 0) {
    // Access per-thread heap data via FS:0x2C (TLS slot array)
    tlsSlot0 = *(int**)(*(int*)(__readfsdword(0x2C))); // dereference TLS slot 0
    // Compute the actual memory block from a pool base stored at [tlsSlot0+2]+8 plus offset from object's first field
    pBlock = (int*)(*(int*)((int)tlsSlot0[2] + 8) + *pThis);
    
    // Free sub-objects at offsets +0x10 and +0x14 (likely dynamic arrays or other heap allocations)
    if (pBlock[4] != 0) {        // +0x10
      FUN_00610f90(pBlock[4]);   // heapFree or destructor call
      pBlock[4] = 0;
    }
    if (pBlock[5] != 0) {        // +0x14
      FUN_00610f90(pBlock[5]);
      pBlock[5] = 0;
    }
    
    // Return the block to the global free list
    // gPoolAllocator (DAT_01206880) is a structure; offset +0x14 holds pointer to next write position in free buffer
    pFreeListWritePos = *(int**)(DAT_01206880 + 0x14);
    // Write a vtable pointer (type marker) into the current slot
    *pFreeListWritePos = (int)&PTR_LAB_01123be8; // likely vtable for freed block
    // Advance write pointer
    *(int**)(DAT_01206880 + 0x14) = pFreeListWritePos + 1;
    // Write the block address into the next slot
    **(int**)(DAT_01206880 + 0x14) = (int)pBlock;
    // Advance again
    *(int**)(DAT_01206880 + 0x14) = pFreeListWritePos + 2;
    
    // Zero out the first two fields of the original object
    *pThis = 0;
    pThis[1] = 0;
  }
}
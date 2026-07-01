// FUNC_NAME: FixedSizeAllocator::constructor
undefined4 * __fastcall FixedSizeAllocator::constructor(undefined4 *thisPtr)

{
  undefined4 allocatorResult;
  
  *thisPtr = &PTR_FUN_00d737d4;  // vtable pointer (base class?)
  thisPtr[1] = 0;                  // +0x04: allocation count
  allocatorResult = FUN_009c8e80(0x40);  // allocate memory pool (0x40 bytes per element?)
  thisPtr[2] = allocatorResult;    // +0x08: pointer to allocated memory pool
  thisPtr[3] = 0;                  // +0x0C: free list head / next available slot
  thisPtr[4] = 0x10;               // +0x10: element size (16 bytes? or max count?)
  return thisPtr;
}
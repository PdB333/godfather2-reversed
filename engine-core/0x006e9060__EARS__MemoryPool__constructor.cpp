// FUNC_NAME: EARS::MemoryPool::constructor
undefined4 * __thiscall EARS::MemoryPool::constructor(undefined4 *this, int elementSize, int *allocator, undefined4 param_4)
{
  undefined4 uVar1;
  undefined4 *poolPtr;
  
  this[1] = 0;          // +0x04: mElementCount = 0
  this[2] = elementSize; // +0x08: mElementSize = elementSize
  uVar1 = FUN_004265d0(param_4, allocator); // likely EARS::MemoryAllocator::allocate
  this[3] = uVar1;      // +0x0C: mMemoryBlock = allocated memory
  this[4] = allocator;  // +0x10: mAllocator = allocator
  (**(code **)(*allocator + 8))(); // allocator->vtable->addRef()
  poolPtr = (undefined4 *)this[3];
  if (poolPtr == (undefined4 *)0x0) {
    poolPtr = &DAT_01218a14; // fallback static empty pool
  }
  uVar1 = (*(code *)**(undefined4 **)this[4])(elementSize * 4, poolPtr); // allocator->vtable->allocate(elementSize * 4, poolPtr)
  *this = uVar1;        // +0x00: mFreeList = allocated free list
  return this;
}
// FUNC_NAME: MemoryPool::initialize
void __thiscall MemoryPool::initialize(void* parentAllocator)
{
  int* dataBuffer = (int*)allocateMemory(0, 0x1e0); // allocate 480 bytes
  if (dataBuffer == nullptr) {
    if (parentAllocator != nullptr) {
      handleAllocationError();
      return;
    }
    dataBuffer = nullptr;
  }
  else if (parentAllocator != nullptr) {
    // Track memory in parent allocator's used counter at offset +0x24 from +0x10
    int* usedCounter = (int*)(*(int*)((char*)parentAllocator + 0x10) + 0x24);
    *usedCounter += 0x1e0;
  }

  // Field offsets relative to this:
  // +0x1c: mainDataPtr
  // +0x08: dataCursor (points to current write position)
  // +0x20: someConstant (0x3c = 60)
  // +0x18: dataEndPtr (points to data + 0x138 = 312 bytes offset)
  *(int**)((char*)this + 0x1c) = dataBuffer;
  *(int**)((char*)this + 0x08) = dataBuffer;
  *(int*)((char*)this + 0x20) = 0x3c;
  *(int**)((char*)this + 0x18) = dataBuffer + 0x138;

  int* descriptor = (int*)allocateMemory(0, 0xc0); // allocate 192 bytes
  if (descriptor == nullptr) {
    if (parentAllocator != nullptr) {
      handleAllocationError();
      return;
    }
    descriptor = nullptr;
  }
  else if (parentAllocator != nullptr) {
    int* usedCounter = (int*)(*(int*)((char*)parentAllocator + 0x10) + 0x24);
    *usedCounter += 0xc0;
  }

  // +0x14: descriptorPtr
  // +0x28: descriptorPtr (again, maybe different use)
  *(int**)((char*)this + 0x14) = descriptor;
  *(int**)((char*)this + 0x28) = descriptor;

  // Initialize descriptor: set third dword to 1
  descriptor[2] = 1;

  // Initialize data buffer: clear first 8 bytes (set to 0)
  // Then advance dataCursor by 8 bytes (skip header)
  **(int**)((char*)this + 0x08) = 0; // clear first 4 bytes
  *(int**)((char*)this + 0x08) = (int*)((char*)dataBuffer + 8); // move past header

  // Store pointer to the new dataCursor in descriptor's first dword
  descriptor[0] = (int)*(int**)((char*)this + 0x08);

  // +0x0c: another copy of that pointer
  *(int**)((char*)this + 0x0c) = (int*)(descriptor[0]);

  // Set descriptor's second dword to point to dataCursor + 0xa0 (160 bytes ahead)
  descriptor[1] = (int)(*(int**)((char*)this + 0x08) + 0xa0);

  // +0x2c: some short value (8)
  *(short*)((char*)this + 0x2c) = 8;

  // +0x24: pointer to end of descriptor buffer
  *(int**)((char*)this + 0x24) = (int*)((char*)descriptor + 0xc0);
}

// External allocation function: DAT_012059dc (parameter1=0, parameter2=size)
// This is likely a custom memory manager
int* allocateMemory(int flags, int size);

// Error handling function: FUN_00635a80
void handleAllocationError(void);
// FUN_0049ac70: MemoryAllocator::createObject

uint __thiscall MemoryAllocator::createObject(int this, void *constructorParam)
{
  int *vtablePtr;
  int allocResult;
  uint lowerPart;
  uint upperPart;
  uint64_t allocatedMem;
  uint result;
  
  vtablePtr = *(int **)(this + 4);
  allocatedMem = (*(code **)(*vtablePtr + 0xc))(0x14); // call operator new(size=0x14)
  upperPart = (uint)(allocatedMem >> 32);
  allocResult = FUN_0049aad0((int)allocatedMem);
  if ((allocResult == -1) || (allocResult == 0)) {
    // If allocation failed or returned 0, try again with constructorParam? Actually this code is redundant
    allocatedMem = (*(code **)(*vtablePtr + 0xc))(constructorParam);
    FUN_0049aad0((int)allocatedMem);
    allocatedMem = (*(code **)(*vtablePtr + 0xc))(/* return address */);
    upperPart = (uint)(allocatedMem >> 32);
    result = FUN_0049aad0((int)allocatedMem);
  } else {
    allocatedMem = (*(code **)(*vtablePtr + 0xc))(constructorParam);
    FUN_0049aad0((int)allocatedMem);
    allocatedMem = (*(code **)(*vtablePtr + 0xc))(/* return address */);
    result = FUN_0049aad0((int)allocatedMem);
  }
  if ((result != 0xffffffff) && (result != 0)) {
    return upperPart & 0xff;
  }
  return result;
}
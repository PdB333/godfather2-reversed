// FUNC_NAME: DualComponent::initialize
int __thiscall DualComponent::initialize(int *this, int *outBuffer)
{
  int result = 0;
  int *allocResult = (int *)0x0;

  if (this != (int *)0x0) {
    outBuffer[1] = (int)this;                    // +0x4: store parent pointer
    (**(code **)(*this + 8))();                   // vtable+8: e.g., prepareAllocator()
    
    int subObj1Ptr = FUN_009c8e50(0x24);          // allocate 36 bytes for sub-object 1
    bool allocFailed = (subObj1Ptr == 0);
    if (allocFailed) {
      subObj1Ptr = 0;
    }
    else {
      allocResult = (int *)outBuffer[1];          // get parent pointer again
      int dummy1 = 0;
      int dummy2 = 0;
      int dummy3 = 0;
      (**(code **)(*allocResult + 8))();           // parent->vtable+8 again (redundant?)
      int handle1 = FUN_004265d0(&dummy1, allocResult); // some initialization with handle
      FUN_005df540();                              // construct sub-object 1
    }
    outBuffer[2] = subObj1Ptr;                     // +0x8: store sub-object 1 pointer
    
    if (!allocFailed) {
      if (handle1 != 0) {
        (**(code **)(*allocResult + 4))(handle1, 0);  // vtable+4: maybe release handle
      }
      (**(code **)(*allocResult + 0xc))();             // vtable+0xc: cleanup/end
    }
    
    int subObj2Ptr = FUN_009c8e50(0x24);          // allocate 36 bytes for sub-object 2
    allocFailed = (subObj2Ptr == 0);
    if (allocFailed) {
      subObj2Ptr = 0;
    }
    else {
      allocResult = (int *)outBuffer[1];          // parent pointer again
      int dummy1a = 0;
      int dummy2a = 0;
      int dummy3a = 0;
      (**(code **)(*allocResult + 8))();
      int handle2 = FUN_004265d0(&dummy1a, allocResult);
      FUN_005dfb00();                              // construct sub-object 2 (different type)
    }
    outBuffer[3] = subObj2Ptr;                     // +0xc: store sub-object 2 pointer
    
    if (!allocFailed) {
      if (handle2 != 0) {
        (**(code **)(*allocResult + 4))(handle2, 0);
      }
      (**(code **)(*allocResult + 0xc))();
    }
    
    result = 1;
  }
  return result;
}
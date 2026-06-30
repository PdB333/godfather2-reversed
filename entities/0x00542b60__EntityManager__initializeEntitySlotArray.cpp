// FUNC_NAME: EntityManager::initializeEntitySlotArray
// Address: 0x00542b60
// Role: Initializes the dynamic array of entity slots (8-byte entries) if not already initialized.
// Sets up profiling/debug scopes with hashed labels. Allocates and constructs array from stored count.

void __thiscall EntityManager::initializeEntitySlotArray(int* thisPtr, uint profileScopeId)
{
  int* elementPtr;
  uint* allocHeader;
  uint count;
  uint index;
  bool condition;
  char tempFlag;
  int tempVal1;
  int tempVal2;
  int* tempPointer;
  byte scopeStack[12];          // +0x?? local stack struct for scope push/pop
  uint scopeData1;              // +0x??
  uint scopeData2;              // +0x??
  uint scopeData3;              // +0x??
  uint scopeData4 = DAT_00e2b1a4; // global constant or singleton ID

  // Begin profiling scope
  Debug::ScopeBegin(profileScopeId);
  Debug::ScopeSetHash(profileScopeId, 0xb390b11a);
  Debug::ScopeSetActive(1);

  // Evaluate condition based on uninitialized locals (likely side effect of scope functions)
  if (tempFlag == '\0') {
    condition = (*tempPointer == 0);
  } else {
    condition = (tempVal1 == tempVal2);
  }

  // If false, construct a temporary object and call vtable methods
  if (!condition) {
    scopeData1 = 0;
    scopeData2 = 0;
    scopeData3 = 0;
    scopeData4 = DAT_00e2b1a4;
    ScopeStack::Construct(scopeStack);   // builds some debug/context stack
    (thisPtr->vtable[0x28])(scopeStack); // vcall offset 0x28 = "enterScope"?
    (thisPtr->vtable[0x194])();          // vcall offset 0x194 = "onScopeEnter"?
  }

  // End first scope, begin second
  Debug::ScopeSetHash(profileScopeId, 0xf8b45dfb);
  Debug::ScopeSetActive(0);

  // Re-evaluate condition (same logic)
  if (tempFlag == '\0') {
    condition = (*tempPointer == 0);
  } else {
    condition = (tempVal1 == tempVal2);
  }

  // If false, destroy a previously constructed object at offset 0x2c0 (0xb0*4)
  if (!condition) {
    ScopeStack::Destruct(reinterpret_cast<void*>(thisPtr + 0xb0));
  }

  // Check if array is already initialized (flag at offset 0x2d8)
  if (thisPtr[0xb6] == 0) {
    count = thisPtr[0xaf];              // number of elements (offset 0x2bc)
    if (count != 0) {
      // Allocate: each element is 8 bytes, plus 4-byte header
      uint totalSize = -(uint)((int)((ulonglong)count * 8 >> 0x20) != 0) | (uint)((ulonglong)count * 8);
      allocHeader = (uint*)Allocator::Allocate(-(uint)(0xfffffffb < totalSize) | totalSize + 4);
      if (allocHeader == nullptr) {
        thisPtr[0xae] = 0;              // array pointer at offset 0x2b8
      } else {
        uint* arrayData = allocHeader + 1;
        *allocHeader = count;           // store count in header
        _vector_constructor_iterator_(arrayData, 8, count, (_func_void_ptr_void_ptr*)&LAB_0044b200);
        thisPtr[0xae] = (int)arrayData;
      }

      // Clear existing entries (if any were previously set)
      for (index = 0; index < (uint)thisPtr[0xaf]; ++index) {
        elementPtr = (int*)(thisPtr[0xae] + index * 8);
        if (*elementPtr != 0) {
          ElementDestructor((void*)elementPtr);   // FUN_004daf90
          *elementPtr = 0;
        }
      }
    }
    thisPtr[0xb6] = 1;                  // mark as initialized
  }
  return;
}
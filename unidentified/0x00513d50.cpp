// FUNC_00513d50: ObjectPool::releaseObject
// Role: Releases an object back to the pool (free list). Stores the current free head index into the object’s “next” field,
// then pushes the object onto the free stack. Increments free count. An optional delegate is called first – if it returns false,
// the delegate’s virtual function is called and the object is NOT freed (early return).

void __thiscall ObjectPool::releaseObject(void* param_1, int param_2)
{
  void* poolBase;
  int freeHead;
  int baseOffset;          // offset within each object where “next index” is stored
  int newIndex;
  int tlsPtr;
  char delegateResult;

  if (param_1 != (void*)0x0 && this->m_poolBase != (void*)0x0) {
    // Optional delegate check
    if (this->m_delegate != (Delegate*)0x0) {
      delegateResult = FUN_00514300();                // likely a “can release?” query
      if (delegateResult == '\0') {
        // Call the third virtual function on the delegate (vtable +8)
        (**(code **)(*(int*)this->m_delegate + 8))(param_1, param_2);
        return;                                       // Delegate handled it, skip release
      }
    }

    // Retrieve the object-relative offset for the “next free index” field from TLS
    tlsPtr = **(int**)(__readfsdword(0x2c));          // Thread local storage pointer
    baseOffset = *(int*)(tlsPtr + 8);                 // offset for "next" field in object allocations

    // Write current free head index into the object's "next" field
    *(int*)((unsigned char*)param_1 + baseOffset) = this->m_freeHead;

    // Calculate the new index: (address of this object - pool base address) / size of each slot (0x2A0)
    if (this->m_poolBase != (void*)0x0) {
      newIndex = (int)((unsigned char*)param_1 - (unsigned char*)this->m_poolBase) / 0x2A0;
    } else {
      newIndex = 0;
    }
    this->m_freeHead = newIndex;                      // Object becomes new head of free list
    this->m_freeCount++;                              // Increment free object count
  }
}
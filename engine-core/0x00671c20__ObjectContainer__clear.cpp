// FUNC_NAME: ObjectContainer::clear
void ObjectContainer::clear(void)
{
  // this object structure:
  // +0x10: m_count (ushort)
  // +0x14: m_objects (pointer to array of ObjectEntry[8 bytes each])
  // +0x1e38: m_manager (pointer to shared manager structure)

  // Manager structure:
  // +0x04: m_refCount (int)
  // +0x0c: m_indexedObjects (array of pointers, indexed by object header id)

  // Each allocation from this pool has a header:
  // -0x10: header (allocator metadata)
  // -0x08: int id (index into manager's object array)

  // Global free function (operator delete equivalent)
  extern void (*s_freeFunc)(void*);

  ushort count = *(ushort*)((char*)this + 0x10);
  if (count != 0) {
    // Free each active object
    for (int i = count - 1; i >= 0; --i) {
      // Entry at m_objects[i] is 8 bytes; second dword is the object pointer
      void* objectPtr = *(void**)(*(int*)((char*)this + 0x14) + 4 + i * 8);
      if (objectPtr != nullptr) {
        int* managerBase = *(int**)((char*)this + 0x1e38);
        // Get the object's id from its header (at objectPtr - 8)
        int id = *(int*)((char*)objectPtr - 8);
        // Clear the manager's pointer for this id
        *(void**)(*(int*)((char*)managerBase + 0xc) + id * 4) = nullptr;
        // Decrement reference count in manager
        managerBase[1]--;
        // Free the allocation (header starts 0x10 bytes before object)
        s_freeFunc((char*)objectPtr - 0x10);
      }
    }
    // After freeing all objects, free the array buffer itself
    void* arrayBuffer = *(void**)((char*)this + 0x14);
    if (arrayBuffer != nullptr) {
      int* managerBase = *(int**)((char*)this + 0x1e38);
      // The array buffer also has the same header; get its id
      int id = *(int*)((char*)arrayBuffer - 8);
      *(void**)(*(int*)((char*)managerBase + 0xc) + id * 4) = nullptr;
      managerBase[1]--;
      s_freeFunc((char*)arrayBuffer - 0x10);
    }
    // Reset count to zero
    *(ushort*)((char*)this + 0x10) = 0;
  }
}
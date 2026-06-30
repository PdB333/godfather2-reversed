// FUNC_NAME: Entity::Entity(bool isHeapAllocated)
// Address: 0x005db520
// Role: Constructor that calls base constructor and, if heap-allocated, registers with memory manager.

void __thiscall Entity::Entity(bool isHeapAllocated) {
    // Call base/default constructor (address 0x005db540)
    // This likely initializes core members (vtable, ref count, etc.)
    this->baseConstructor();

    // If the object was allocated on the heap (e.g., via operator new),
    // register it with the memory manager for tracking or cleanup.
    // The callee at 0x009c8eb0 is likely MemoryManager::registerAllocation()
    if (isHeapAllocated) {
        this->registerWithMemoryManager(); // FUN_009c8eb0(this)
    }
}
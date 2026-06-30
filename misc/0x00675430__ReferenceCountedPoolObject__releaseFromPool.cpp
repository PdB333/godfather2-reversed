// FUNC_NAME: ReferenceCountedPoolObject::releaseFromPool
void __thiscall ReferenceCountedPoolObject::releaseFromPool(void)
{
    // this points to an embedded slot inside a larger pool allocation.
    // The actual object header is at (this - 16).
    // Container pointer at this[0] (offset 0x00)
    // Child object pointers at this[3] (offset 0x0C) and this[4] (offset 0x10)
    // Each child's header contains an index at offset -8 from the child pointer.

    int* container = *reinterpret_cast<int**>(this);                     // +0x00
    int* child1 = reinterpret_cast<int*>(this[3]);                       // +0x0C
    int* child2 = reinterpret_cast<int*>(this[4]);                       // +0x10

    if (child1 != nullptr)
    {
        int childIndex = *(reinterpret_cast<int*>(reinterpret_cast<char*>(child1) - 8)); // index from child header
        // Clear slot in container's array (container->array at container[3])
        *reinterpret_cast<int**>(reinterpret_cast<int*>(container[3]) + childIndex * 4) = nullptr;
        // Decrement container's reference count (container[1])
        container[1]--;
        // Delete child object header (child header starts at child1 - 16)
        (*(void (*)(void*))DAT_01206694)(reinterpret_cast<char*>(child1) - 16);
    }

    if (child2 != nullptr)
    {
        int childIndex = *(reinterpret_cast<int*>(reinterpret_cast<char*>(child2) - 8));
        *reinterpret_cast<int**>(reinterpret_cast<int*>(container[3]) + childIndex * 4) = nullptr;
        container[1]--;
        (*(void (*)(void*))DAT_01206694)(reinterpret_cast<char*>(child2) - 16);
    }

    // Now release this object itself
    int selfIndex = *(reinterpret_cast<int*>(reinterpret_cast<char*>(this) - 8)); // index from this header
    *reinterpret_cast<int**>(reinterpret_cast<int*>(container[3]) + selfIndex * 4) = nullptr;
    container[1]--;
    (*(void (*)(void*))DAT_01206694)(reinterpret_cast<char*>(this) - 16);
}
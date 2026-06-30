// FUNC_NAME: ReleasableObject::deallocateAll

void ReleasableObject::deallocateAll(void)
{
    if (this == nullptr) {
        return;
    }

    // this->m_childCount is a short at offset +6
    int numChildren = static_cast<int>(*(short*)(reinterpret_cast<int>(this) + 6));
    int* pManager = this->m_pManager; // this[0] = m_pManager
    int* pChildArray = this->m_childArray; // this[3] = array of child pointers

    // Iterate over children and release each one
    for (int i = 0; i < numChildren; i++) {
        int* pChild = reinterpret_cast<int*>(pChildArray[i]);
        if (pChild != nullptr) {
            // Clear the manager's slot at index (derived from child's header)
            // pManager+0xC is the slot array pointer, index = *(pChild - 8) ?? 
            int slotIndex = *(pChild - 8); // child->header.index at offset -8
            int* slotArray = *reinterpret_cast<int**>(reinterpret_cast<int>(pManager) + 0xC);
            slotArray[slotIndex] = 0;

            // Decrement the active count at pManager+4
            int* pActiveCount = reinterpret_cast<int*>(reinterpret_cast<int>(pManager) + 4);
            (*pActiveCount)--;

            // Actually delete the child's allocation (block starts 0x10 bytes before child? header size 0x10?)
            // DAT_01206694 is operator delete
            operator delete(reinterpret_cast<void*>(pChild - 0x10));
        }
    }

    // Release the child array itself (pChildArray)
    if (pChildArray != nullptr) {
        int slotIndex = *(pChildArray - 8);
        int* slotArray = *reinterpret_cast<int**>(reinterpret_cast<int>(pManager) + 0xC);
        slotArray[slotIndex] = 0;
        int* pActiveCount = reinterpret_cast<int*>(reinterpret_cast<int>(pManager) + 4);
        (*pActiveCount)--;
        operator delete(reinterpret_cast<void*>(pChildArray - 0x10));
    }

    // Release the secondary array (this->m_secondaryArray at offset 0x10)
    int* pSecArray = this->m_secondaryArray; // this[4]
    if (pSecArray != nullptr) {
        int slotIndex = *(pSecArray - 8);
        int* slotArray = *reinterpret_cast<int**>(reinterpret_cast<int>(pManager) + 0xC);
        slotArray[slotIndex] = 0;
        int* pActiveCount = reinterpret_cast<int*>(reinterpret_cast<int>(pManager) + 4);
        (*pActiveCount)--;
        operator delete(reinterpret_cast<void*>(pSecArray - 0x10));
    }

    // Remove this object from the manager's slot array using its own header index
    int thisSlotIndex = *(reinterpret_cast<int*>(this) - 2); // header at this-8, index at this-8? Actually this[-2] = *(int*)(this-8)
    int* slotArray = *reinterpret_cast<int**>(reinterpret_cast<int>(pManager) + 0xC);
    slotArray[thisSlotIndex] = 0;
    int* pActiveCount = reinterpret_cast<int*>(reinterpret_cast<int>(pManager) + 4);
    (*pActiveCount)--;

    // Finally delete this object's allocation (block starts at this-4)
    operator delete(reinterpret_cast<void*>(reinterpret_cast<int>(this) - 4));
}
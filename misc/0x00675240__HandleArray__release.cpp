// FUNC_NAME: HandleArray::release
// Address: 0x00675240
// Role: Destructor for a handle array object, clearing references in a manager and deallocating memory.

typedef int (*FreeFunc)(void*);
extern FreeFunc deallocate; // Freed by DAT_01206694

// Manager class with reference counting and a registry of pointers
struct Manager {
    // +0x00: unknown
    // +0x04: reference count (int)
    // +0x0C: pointer to registry array (void**)
    // other fields...
};

struct HandleArray {
    // +0x00: pointer to manager (Manager*)
    Manager* m_pManager;
    // +0x04: reference count (int)
    int m_refCount;
    // +0x06: number of items (short)
    short m_itemCount;
    // +0x08: padding
    // +0x0C: pointer to array of item pointers (void**)
    void** m_items;
    // +0x10: pointer to secondary array (void**)
    void** m_extraArray;

    void release();
};

void HandleArray::release()
{
    // Null check on this pointer
    if (this == nullptr) return;

    // Iterate over primary item array
    for (short i = 0; i < m_itemCount; i++)
    {
        void* pItem = m_items[i];
        if (pItem != nullptr)
        {
            // The allocation block's index is stored at offset -8 from the item pointer
            int index = *(int*)((char*)pItem - 8);
            // Clear the handle from the manager's registry (at +0x0C)
            void** registry = *(void***)((char*)m_pManager + 0xC);
            registry[index] = nullptr;
            // Decrement manager's reference count at +0x04
            (*(int*)((char*)m_pManager + 4))--;
            // Deallocate the item's full allocation block (base at pItem - 16)
            deallocate((char*)pItem - 16);
        }
    }

    // Free the primary array itself
    if (m_items != nullptr)
    {
        int index = *(int*)((char*)m_items - 8);
        void** registry = *(void***)((char*)m_pManager + 0xC);
        registry[index] = nullptr;
        (*(int*)((char*)m_pManager + 4))--;
        deallocate((char*)m_items - 16);
    }

    // Free the secondary array
    if (m_extraArray != nullptr)
    {
        int index = *(int*)((char*)m_extraArray - 8);
        void** registry = *(void***)((char*)m_pManager + 0xC);
        registry[index] = nullptr;
        (*(int*)((char*)m_pManager + 4))--;
        deallocate((char*)m_extraArray - 16);
    }

    // Free this object's own allocation block
    {
        int index = *(int*)((char*)this - 8);
        void** registry = *(void***)((char*)m_pManager + 0xC);
        registry[index] = nullptr;
        (*(int*)((char*)m_pManager + 4))--;
        deallocate((char*)this - 16);
    }
}
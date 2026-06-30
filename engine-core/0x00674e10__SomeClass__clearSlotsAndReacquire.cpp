// FUNC_NAME: SomeClass::clearSlotsAndReacquire
// Function at 0x00674e10 - Clears two object slots from a pool and optionally reacquires one from a manager.

class SomeClass {
public:
    // +0x00: vtable (implied)
    // +0x04: Container (array with size at +0x04, data at +0x0c)
    void* m_container;
    // +0x50, +0x54: pointers to entries in the container
    void* m_slot0;
    void* m_slot1;
    // +0x180: pointer to a manager object
    void* m_manager;

    // Reconstructed free function (DAT_01206694)
    static void (__cdecl *g_freeFunc)(void* ptr);
    // Forward declaration for acquisition function (FUN_0067b8a0)
    extern void* acquireSlot();

    void clearSlotsAndReacquire() {
        // Process first slot (m_slot0)
        void* container = m_container; // +0x04
        if (m_slot0 != nullptr) {
            // Each slot points to an entry whose index is stored at offset -8 from the slot pointer
            int entryIndex = *(int*)((char*)m_slot0 - 8);
            // Clear the entry in the container's data array (offset +0x0c, 4-byte elements)
            int* dataArray = *(int**)((char*)container + 0x0c);
            dataArray[entryIndex] = 0;
            // Decrement container size (offset +0x04)
            int* sizePtr = (int*)((char*)container + 4);
            (*sizePtr)--;
            // Free the entire allocation block (header starts at slot - 0x10)
            g_freeFunc((char*)m_slot0 - 0x10);
            m_slot0 = nullptr;
        }

        // Process second slot (m_slot1)
        if (m_slot1 != nullptr) {
            int entryIndex = *(int*)((char*)m_slot1 - 8);
            int* dataArray = *(int**)((char*)container + 0x0c);
            dataArray[entryIndex] = 0;
            int* sizePtr = (int*)((char*)container + 4);
            (*sizePtr)--;
            g_freeFunc((char*)m_slot1 - 0x10);
            m_slot1 = nullptr;
        }

        // Attempt to reacquire a new slot from the manager at +0x180
        void* sub = *(void**)((char*)m_manager + 0x20);
        if (sub != nullptr) {
            // Check flag at +0xf8 of the sub-object
            if (*(int*)((char*)sub + 0xf8) != 0) {
                void* newSlot = acquireSlot();
                m_slot0 = newSlot;
            }
        }
    }
};

// Define the free function pointer (DAT_01206694)
void (__cdecl *SomeClass::g_freeFunc)(void* ptr) = reinterpret_cast<void(__cdecl*)(void*)>(0x01206694);

// Forward declaration (actual implementation elsewhere)
void* acquireSlot() {
    // FUN_0067b8a0 - returns a new entry pointer
    return reinterpret_cast<void*>(0);
}
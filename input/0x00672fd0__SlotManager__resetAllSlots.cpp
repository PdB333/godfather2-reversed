// FUNC_NAME: SlotManager::resetAllSlots

class SlotManager {
public:
    // Offsets:
    // +0x04: int m_activeCount
    // +0x0c: int* m_indexArray          // pointer to array of ints (indices)
    // +0x34: void* m_slots[7]           // pointers to allocated objects
    // +0x50: int m_slotFlags1[7]        // e.g., "inUse" flags
    // +0x6c: int m_slotFlags2[7]        // e.g., "available" flags

    void __thiscall resetAllSlots();
};

// Global function pointer for object destruction (header at obj - 0x10)
extern void (*g_destroyObject)(void* obj);

void SlotManager::resetAllSlots() {
    int* slotPtr = reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x34); // m_slots[0]
    int count = 7;

    do {
        void* obj = reinterpret_cast<void*>(*slotPtr);
        if (obj != 0) {
            // Remove from index array: clear entry at m_indexArray[*(int*)(obj - 8)]
            int index = *reinterpret_cast<int*>(static_cast<char*>(obj) - 8);
            *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x0c + index * 4) = 0;

            // Decrement active count
            *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x04) -= 1;

            // Destroy the object (allocation header at obj - 0x10)
            g_destroyObject(static_cast<char*>(obj) - 0x10);
        }

        // Reset slot fields
        *slotPtr = 0;                     // m_slots[i] = 0
        slotPtr[7] = 0;                   // m_slotFlags1[i] = 0  (offset +0x50)
        slotPtr[0xe] = 1;                 // m_slotFlags2[i] = 1  (offset +0x6c)

        slotPtr++;
        count--;
    } while (count != 0);
}
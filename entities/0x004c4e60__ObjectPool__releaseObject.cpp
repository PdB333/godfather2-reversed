// FUNC_NAME: ObjectPool::releaseObject
// Address: 0x004c4e60
// This function removes an object from a pool by its slot index, shifting the last element into the vacated slot.
// The pool maintains multiple parallel arrays: object elements (0x20 bytes each), byte flags, short IDs, and 0x10-byte data blocks.
// Each object stores its own slot index at offset +0x2a.

struct SlotElement {
    char unknown[0x10];   // +0x00
    void* object;         // +0x10 (pointer to the actual object)
    char pad[0x0C];       // +0x14 (remaining bytes to make 0x20 total)
};

class ObjectPool {
public:
    // +0x00: vtable? (not used here)
    // +0x04: pointer to array of 0x10-byte data blocks
    char* m_dataArray;          // +0x04
    // +0x08: pointer to byte array (flags)
    char* m_byteArray;          // +0x08
    // +0x0C: pointer to short array (IDs)
    short* m_shortArray;        // +0x0C
    // +0x10: pointer to array of SlotElement (0x20 bytes each)
    SlotElement* m_elementArray; // +0x10
    // +0x18: flag (maybe dirty/modified)
    char m_flag;                // +0x18
    // +0x38: number of active elements
    int m_count;                // +0x38
    // +0x3C: flag to enable callbacks
    char m_callbacksEnabled;    // +0x3C

    // Callbacks (functions at 0x004c4870 and 0x004c4990)
    void onRemove(void* obj, int param);   // FUN_004c4870
    void onMoved(SlotElement& element);    // FUN_004c4990

    void releaseObject(void* obj);
};

void __thiscall ObjectPool::releaseObject(void* obj) {
    short slotIndex = *(short*)((char*)obj + 0x2a);  // object's slot index
    int index = (int)slotIndex;
    if (index < 0) return;

    // Mark slot as invalid (-2 = 0xFFFE)
    *(short*)((char*)obj + 0x2a) = -2;

    if (m_callbacksEnabled) {
        onRemove(obj, 0);
    }

    m_count--;

    if (index < m_count) {
        // Shift the last element into the removed slot
        // Copy 0x20-byte SlotElement
        m_elementArray[index] = m_elementArray[m_count];

        // Copy byte flag
        m_byteArray[index] = m_byteArray[m_count];

        // Copy short ID
        m_shortArray[index] = m_shortArray[m_count];

        // Copy 0x10-byte data block
        *(long long*)(m_dataArray + index * 0x10) = *(long long*)(m_dataArray + m_count * 0x10);
        *(long long*)(m_dataArray + index * 0x10 + 8) = *(long long*)(m_dataArray + m_count * 0x10 + 8);

        // Update the moved object's slot index
        void* movedObj = m_elementArray[index].object;
        *(short*)((char*)movedObj + 0x2a) = (short)index;

        if (m_callbacksEnabled) {
            onMoved(m_elementArray[index]);
        }
    }

    // Clear the last byte and flag
    m_byteArray[m_count] = 0;
    m_flag = 0;
}
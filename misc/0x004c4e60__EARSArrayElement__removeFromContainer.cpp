// FUNC_NAME: EARSArrayElement::removeFromContainer
// Address: 0x004c4e60
// Removes this element from its containing EARSArray. The element's index (stored at +0x2a) is used
// to locate its slot. If the slot is valid, the array's count is decremented, the last element
// is shifted into the removed slot, and the moved element's index is updated.

struct EARSArray; // forward declaration

// Size: 0x2c (estimated, only offset 0x2a known)
// Stored index in the container array at offset +0x2a
struct EARSArrayElement {
    // +0x2a: short m_index;
    short m_index; // own index within the array, used for quick removal
    // ... other fields not relevant to removal
};

// Structure of the dynamic container (parallel arrays)
struct EARSArray {
    // +0x00: vtable? (not used directly here)
    // +0x04: void* m_data16;     // Array of 16-byte structures (one per element)
    void*       m_data16;          // +0x04
    // +0x08: char* m_flagArray;   // Byte flags per element
    char*       m_flagArray;       // +0x08
    // +0x0c: short* m_shortArray; // Short data per element (2 bytes each)
    short*      m_shortArray;      // +0x0c
    // +0x10: void* m_data32;     // Array of 32-byte main objects (one per element)
    void*       m_data32;          // +0x10
    // +0x18: char m_removalInProgress; // cleared after element removal
    char        m_removalInProgress; // +0x18
    // +0x38: int m_count;        // Number of elements
    int         m_count;           // +0x38
    // +0x3c: char m_hasCallbacks; // If set, notify before/after removal
    char        m_hasCallbacks;    // +0x3c
};

// Callback called before removal (address 0x004c4870)
void notifyBeforeRemove(EARSArray* container, int index);
// Callback called after removal for the moved element (address 0x004c4990)
void notifyAfterRemove(EARSArray* container, void* movedElement);

// __fastcall: ECX = this (element), EDX = container
void __fastcall EARSArrayElement::removeFromContainer(EARSArray* container)
{
    short index = this->m_index;
    int idx = (int)index;
    if (idx < 0) {
        return; // already removed or invalid
    }
    // Mark this element's index as invalid (0xfffe)
    this->m_index = (short)0xfffe;

    if (container->m_hasCallbacks != 0) {
        notifyBeforeRemove(container, 0); // 0 => removal of current element?
    }

    // Decrease element count
    container->m_count--;

    // If the removed element is not the last one, shift the last element into its place
    if (idx < container->m_count) {
        // Calculate addresses
        int newCount = container->m_count;
        // 32-byte main object array
        void* data32 = container->m_data32;
        // Copy 32 bytes from last element (at newCount*0x20) to removed slot (at idx*0x20)
        // Use 8-byte moves to copy whole block
        *(unsigned long long*)((char*)data32 + idx * 0x20) =
            *(unsigned long long*)((char*)data32 + newCount * 0x20);
        *(unsigned long long*)((char*)data32 + idx * 0x20 + 8) =
            *(unsigned long long*)((char*)data32 + newCount * 0x20 + 8);
        *(unsigned long long*)((char*)data32 + idx * 0x20 + 0x10) =
            *(unsigned long long*)((char*)data32 + newCount * 0x20 + 0x10);
        *(unsigned long long*)((char*)data32 + idx * 0x20 + 0x18) =
            *(unsigned long long*)((char*)data32 + newCount * 0x20 + 0x18);

        // 1-byte flag array
        char* flagArr = container->m_flagArray;
        flagArr[idx] = flagArr[newCount];

        // 2-byte short array
        short* shortArr = container->m_shortArray;
        shortArr[idx] = shortArr[newCount];

        // 16-byte data array
        void* data16 = container->m_data16;
        *(unsigned long long*)((char*)data16 + idx * 0x10) =
            *(unsigned long long*)((char*)data16 + newCount * 0x10);
        *(unsigned long long*)((char*)data16 + idx * 0x10 + 8) =
            *(unsigned long long*)((char*)data16 + newCount * 0x10 + 8);

        // Update the moved element's own index field to reflect its new position
        // The moved element is now at the removed slot's old index.
        // The full moved object is at data32 + idx*0x20, its index is at offset +0x2a.
        EARSArrayElement* movedElement = (EARSArrayElement*)((char*)data32 + idx * 0x20);
        movedElement->m_index = index; // original index (short)

        // If container has callbacks, notify that the moved element has been updated
        if (container->m_hasCallbacks != 0) {
            notifyAfterRemove(container, movedElement);
        }
    }

    // Mark the now-unused last slot's flag as 0
    char* flagArr = container->m_flagArray;
    flagArr[container->m_count] = 0; // or false

    // Clear the in-progress flag
    container->m_removalInProgress = 0;
}
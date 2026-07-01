// FUNC_NAME: SlotMap::reserve
// Address: 0x00823ce0
// Reconstructed EA EARS engine slot map reallocation.

#include <cstdint>

// Forward declarations for allocators (EA-specific)
extern void* __cdecl customAllocate(size_t size);
extern void  __cdecl customFree(void* ptr);
extern void  __cdecl destroySlot(void* slot); // cleanup per-slot

class SlotMap {
public:
    // +0x00: m_pData (pointer to array of Pair structs)
    // +0x04: m_nCount (number of used slots)
    // +0x08: m_nCapacity (current capacity in number of slots)

    void __thiscall reserve(uint32_t newCapacity) {
        // Only grow if current capacity is insufficient
        if (m_nCapacity < newCapacity) {
            // Allocate new raw pair array (each pair = 8 bytes)
            Pair* newData = static_cast<Pair*>(customAllocate(newCapacity * sizeof(Pair)));

            // Copy existing entries if there are any
            if (m_pData != nullptr) {
                uint32_t i = 0;
                Pair* dest = newData;
                if (m_nCount != 0) {
                    do {
                        Pair* src = &m_pData[i];

                        // Copy object pointer
                        dest->object = src->object;
                        // Reset next link
                        dest->next = nullptr;

                        // If the object exists, it has a back-pointer at offset +0x04
                        // that previously pointed to the old slot; redirect it to the new slot.
                        if (dest->object != nullptr) {
                            // Save the old object's next (which pointed to the previous slot)
                            dest->next = dest->object->next;
                            // Now make the object point to the new slot
                            dest->object->next = dest;
                        }

                        // Clean up the old slot (object pointer is already moved)
                        destroySlot(src);

                        ++i;
                        ++dest;
                    } while (i < m_nCount);
                }
                // Release old memory
                customFree(m_pData);
            }

            m_pData = newData;
            m_nCapacity = newCapacity;
        }
    }

private:
    struct Pair {
        void* object; // +0x00: pointer to the owned object (may be null)
        Pair* next;   // +0x04: used for intrusive linkage; the object at +0x04 stores a pointer to this pair
    };

    Pair*    m_pData;      // +0x00
    uint32_t m_nCount;     // +0x04
    uint32_t m_nCapacity;  // +0x08
};
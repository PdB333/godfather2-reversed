// FUNC_NAME: ObjectManager::findObjectIndex
// Address: 0x006bcfa0
// Role: Searches a dynamic array of entries (pairs of pointers) for an object whose address equals the base of the containing structure (offset -0x48).
// Returns the index (slot) or 0xFFFFFFFF if not found.

#include <cstdint>

class ObjectManager {
public:
    // Offset: +0x74 - pointer to an array of Entry structs (each 8 bytes)
    // Offset: +0x78 - count of entries
    struct Entry {
        void* pObjectField; // Points to a field at offset +0x48 inside the actual object (if non-null)
        void* pUnused;      // Second 4-byte field (unused in this function)
    };

    // __thiscall: 'this' in ECX, param_1=this, param_2=objectPointer
    uint32_t __thiscall findObjectIndex(void* objectPointer) {
        uint32_t count = *(uint32_t*)((uint8_t*)this + 0x78); // m_count
        if (count == 0) {
            return 0xFFFFFFFF; // not found
        }

        Entry* entries = *(Entry**)((uint8_t*)this + 0x74); // m_entries
        for (uint32_t i = 0; i < count; i++) {
            void* pField = entries[i].pObjectField;
            void* key;
            if (pField == nullptr) {
                key = nullptr;
            } else {
                // The stored pointer is offset by +0x48 from the actual object's address.
                // Subtract 0x48 to get the owning object.
                key = (void*)((uint8_t*)pField - 0x48);
            }
            if (key == objectPointer) {
                return i;
            }
        }
        return 0xFFFFFFFF; // not found
    }
};
//FUNC_NAME: ObjectRegistry::registerObject

// Function at 0x005f6710: Registers an object in the object registry, returning its index (0-255) or 0xFF on failure.
// The registry stores entries of 12 bytes each (object pointer, next pointer, handle).
// The object's +4 field is used as a back-pointer to the entry.
// Global config at 0x01223520 provides a maximum capacity at offset 0x20.

#include <cstdint>

// Forward declaration of the helper that allocates a handle (FUN_005f7f00)
extern int allocateHandle();

// Global registry configuration (singleton)
extern uint8_t* g_registryConfig; // at 0x01223520

class ObjectRegistry {
public:
    struct Entry {
        int* object; // +0x00: pointer to the registered object
        int* next;   // +0x04: linked list pointer (from object+4)
        int handle;  // +0x08: handle allocated by allocateHandle()
    };

    // Offsets relative to this:
    // +0x24: m_entries (Entry*)
    // +0x28: m_count (uint32_t)
    // +0x2c: m_capacity (uint32_t)
    // +0x38: m_flags (uint32_t)

    Entry* m_entries;      // +0x24
    uint32_t m_count;      // +0x28
    uint32_t m_capacity;   // +0x2c
    uint32_t m_flags;      // +0x38

    // Register an object; returns its index (0-255) or 0xFF on failure.
    uint8_t registerObject(int* object) {
        uint8_t index = 0xFF;

        if (object == nullptr) {
            return 0xFF;
        }

        // Search for existing entry
        Entry* entries = m_entries;
        uint32_t count = m_count;
        bool found = false;

        for (uint32_t i = 0; i < count; i++) {
            if (entries[i].object == object) {
                index = static_cast<uint8_t>(i);
                found = true;
                break;
            }
        }

        if (found) {
            return index;
        }

        // Not found; try to add a new entry
        uint32_t maxGlobal = *reinterpret_cast<uint32_t*>(g_registryConfig + 0x20); // global max capacity
        if (count < maxGlobal && count < m_capacity) {
            int handle = allocateHandle();
            if (handle == 0) {
                // Allocation failed; set error flags (bits 2 and 4)
                m_flags |= 0x14;
                return 0xFF;
            } else {
                uint8_t newIndex = static_cast<uint8_t>(count);
                Entry* newEntry = &entries[count];
                m_count++;

                newEntry->object = object;
                // Save the object's existing next pointer (at object+4) into the entry
                newEntry->next = reinterpret_cast<int*>(*reinterpret_cast<int*>(object + 4));
                // Set the object's back pointer to this entry
                *reinterpret_cast<int**>(object + 4) = reinterpret_cast<int*>(newEntry);
                newEntry->handle = handle;

                return newIndex;
            }
        } else {
            // No room; set overflow flag (bit 8)
            m_flags |= 0x104;
            return 0xFF;
        }
    }
};
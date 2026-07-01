// FUNC_NAME: ObjBackPtrArray::reserve
// 0x009097e0 - Reserve capacity for an array of objects with back-pointers

// The class stores an array of 8-byte entries (struct Entry).
// Each entry holds a pointer to a managed object (objectPtr) and an
// "owner link" field (ownerLink) that points back to the entry itself,
// allowing the object to know its container slot.
// The class manages dynamic growth by reallocating the array and
// updating the back-pointers in each object.

class ObjBackPtrArray {
public:
    struct Entry {
        void* objectPtr;   // +0x00
        void* ownerLink;   // +0x04 - pointer to the slot that owns this object
    };

    // +0x00
    Entry* m_pData;
    // +0x04
    uint32_t m_count;
    // +0x08
    uint32_t m_capacity;

    // Reserves enough capacity to hold at least 'newCapacity' entries.
    // If m_capacity < newCapacity, a new buffer is allocated, existing
    // entries are moved (back-pointers updated), and old storage is freed.
    void reserve(uint32_t newCapacity) {
        if (m_capacity >= newCapacity) {
            return;
        }

        // Allocate new buffer: each entry is 8 bytes
        void* newRaw = FUN_009c8e80(newCapacity * 8);  // likely operator new[]
        Entry* newData = static_cast<Entry*>(newRaw);
        if (newData == nullptr) {
            return;
        }

        // Move existing entries to the new buffer
        if (m_pData != nullptr) {
            uint32_t idx = 0;
            Entry* dst = newData;
            while (idx < m_count) {
                Entry* src = &m_pData[idx];
                // Copy the object pointer
                dst->objectPtr = src->objectPtr;
                dst->ownerLink = nullptr;

                if (src->objectPtr != nullptr) {
                    // Update the object's back-pointer to point to the new slot
                    void* object = src->objectPtr;
                    // The object stores a pointer to its owning slot at offset +4
                    // Save the old link (maybe used for list linkage)
                    dst->ownerLink = *(void**)((char*)object + 4);
                    // Redirect object's back-pointer to the new slot
                    *(void**)((char*)object + 4) = dst;
                }

                // Destroy the old entry (likely a non-trivial destructor)
                FUN_004daf90(src);  // destructor for Entry

                idx++;
                dst++;
            }
            // Free old buffer
            FUN_009c8f10(m_pData);  // likely operator delete[]
        }

        // Update members
        m_pData = newData;
        m_capacity = newCapacity;
    }
};
// FUNC_NAME: ObjectSlotManager::setSlot
// Address: 0x005ab520
// Role: Assigns an object to a slot in a dynamic array with reference counting and object destruction

class ObjectSlotManager {
public:
    // Fields (offsets relative to this)
    // +0x4c: Object** m_slots        // array of object pointers
    // +0x50: int m_capacity          // allocated slot count
    // +0x54: int m_count             // highest used slot index + 1

    void validateArray();         // FUN_005ab4a0 – ensures array is ready
    void growArray();             // FUN_0059bf00 – increases m_capacity
    void addRef(Object* obj);     // FUN_0059c230 – increments reference count

    void setSlot(int slotIndex, Object* newObject)
    {
        // slotIndex must be non-negative (passed via ESI in original asm)
        if (slotIndex < 0)
            return;

        validateArray();

        if (slotIndex >= m_capacity)
            growArray();

        // Destroy the existing object in the slot if present
        Object* oldObject = m_slots[slotIndex];
        if (oldObject != nullptr)
        {
            // Global destructor table indexed by type ID (lower 15 bits)
            // Table base at 0x0103aee0
            uint16_t typeId = oldObject->m_type & 0x7FFF;
            typedef void (*DestructorFunc)(Object*);
            DestructorFunc* destructorTable = (DestructorFunc*)0x0103aee0;
            destructorTable[typeId](oldObject);
        }

        // Global null object sentinel (0x0119cbbc)
        Object* g_nullObject = (Object*)0x0119cbbc;
        bool isNewDifferent = (newObject != g_nullObject);

        m_slots[slotIndex] = newObject;

        if (isNewDifferent)
        {
            uint16_t typeId = newObject->m_type & 0x7FFF;
            // Skip addRef if:
            // - type is 0x19 (special sentinel), or
            // - flag 0x8000 is set AND type is one of {0x0B, 0x18, 0x17}
            bool skip = (typeId == 0x19);
            if (!skip)
            {
                bool bit15Clear = ((newObject->m_type & 0x8000) == 0);
                bool typeExempt = (typeId == 0x0B || typeId == 0x18 || typeId == 0x17);
                if (!(bit15Clear || !typeExempt)) // actually: skip if bit15 set AND typeExempt
                    skip = (bit15Clear == false && typeExempt == true);
                // Equivalent: skip if (newObject->m_type & 0x8000) && (typeId==0x0B||0x18||0x17)
            }
            if (!skip)
                addRef(newObject);
        }

        // Update count if this slot extends beyond current
        if (slotIndex + 1 > m_count)
            m_count = slotIndex + 1;
    }
};

// Object base structure (first 2 bytes contain type and flags)
struct Object {
    uint16_t m_type; // bits 0-14: type ID, bit 15: flag
    // ... other fields
};
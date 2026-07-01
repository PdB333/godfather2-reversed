// FUNC_NAME: ObjectList::addObject
bool ObjectList::addObject(uint* bitmask, byte slotIndex, Object* object)
{
    // Sets bit in bitmask for the given slot index
    *bitmask |= 1 << (slotIndex & 0x1f);

    // If object pointer is non-null, try to add it to the internal list
    if (object != nullptr) {
        int objectId = getObjectID();  // FUN_0043b490 -> likely returns a unique ID for the object
        uint count = m_count;  // +0x90

        // Check if the slot is free: either count==0 or the reservation array at that slot doesn't match
        if (count == 0 || m_reserved[count] != objectId) {  // m_reserved at +0x74
            if (count > 5) {
                return false;  // List full (max 6 entries)
            }

            // Store the ID in the main array
            m_list[count] = objectId;  // +0x78

            // Increment count
            m_count = count + 1;  // +0x90

            // Refresh internal pointer and length (seems redundant, likely for external access)
            m_pList = m_list;  // +0xa0
            m_length = m_count;  // +0xa4
        }
    }

    return true;
}
// FUNC_NAME: ObjectContainer::addObject
// Function address: 0x00878030
// Role: Adds an object pointer to a fixed-size array if capacity allows. Sets a registration flag (0x100000) on the object at offset 0x5C.
// Returns true on success, false if array is full or capacity is zero.

bool __thiscall ObjectContainer::addObject(uint objectId) {
    bool result = false;
    uint index = 0;

    // m_maxObjects at this+0x2BC (offset 700)
    if (this->m_maxObjects != 0) {
        // m_objects array at this+0xA4C (offset 2636)
        int* slotPtr = this->m_objects; // start of array

        // Find first empty slot (value == 0)
        while (*slotPtr != 0) {
            index++;
            slotPtr++;
            if (index >= this->m_maxObjects) {
                return result; // array full, return false
            }
        }

        // Store object ID in the empty slot
        this->m_objects[index] = objectId;

        // Call some global function (possibly reference counting or notification)
        FUN_00790110(1);

        // Set the "registered" flag on the object at its offset 0x5C
        uint* flagPtr = (uint*)(this->m_objects[index] + 0x5C);
        *flagPtr |= 0x100000;

        result = true;
    }

    return result;
}
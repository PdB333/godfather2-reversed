// FUNC_NAME: ObjectManager::removeObject
void __thiscall ObjectManager::removeObject(Object* pObject)
{
    uint32_t currentTime = Time::getCurrentMs(); // FUN_006b18a0
    if (currentTime <= this->field_140) {
        this->field_140 -= currentTime;
        int result = someCheck(pObject->field_38); // FUN_006b0ee0, field_38 likely object type/ID
        if (result != 0) {
            uint32_t newTime = Time::getCurrentMs(); // FUN_006b18a0 again
            if (currentTime <= newTime) {
                scheduleDeletion(currentTime); // FUN_006b64b0, maybe updates timer
            }
        }
    }

    if (pObject->type == 0) { // +0xc4
        // Remove from array of type 0 objects (pointers at +0x114, count at +0x118)
        uint32_t count = this->numObjectsType0; // +0x118
        int index = -1;
        if (count != 0) {
            int* array = this->objectsType0; // +0x114
            for (uint32_t i = 0; i < count; i++) {
                if (array[i] == pObject) {
                    index = i;
                    break;
                }
            }
        }
        if (index != (int)(count - 1)) {
            // Swap last element into removed slot
            this->objectsType0[index] = this->objectsType0[count - 1];
        }
        this->numObjectsType0--;
    } else if (pObject->type == 1) {
        // Remove from array of type 1 objects (pointers at +0x108, count at +0x10c)
        int index = findObjectIndex(&pObject); // FUN_00849140, returns index or something
        if (index != this->numObjectsType1 - 1) {
            this->objectsType1[index] = this->objectsType1[this->numObjectsType1 - 1];
        }
        this->numObjectsType1--;
    }

    // Post-removal handling
    int isPaused = checkPaused(); // FUN_006b4860
    if (isPaused == 0) {
        notifyObjectDestroyed(pObject); // FUN_008c3e00
    }

    // If both lists empty and flag bit 5 is clear, trigger cleanup
    if (this->numObjectsType0 == 0 && this->numObjectsType1 == 0 &&
        ((~(this->flags >> 5) & 1) != 0)) { // +0x84, bit5
        if (this->someId != 0x637b907 && ((this->flags >> 6 & 1) == 0)) { // +0x54, bit6
            this->flags |= 0x40; // set bit6
            setState(0); // FUN_008c63b0
        }
        // Zero out a small structure at +0x20c (likely a GUID or timestamp)
        uint8_t localBuffer[12]; // local_c, local_8, local_4
        // Copy from this->field_20c into local (12 bytes)
        memcpy(localBuffer, &this->field_20c, 12);
        // Clear that structure (size 12 but function takes size param?)
        clearBuffer(&localBuffer, 0); // FUN_00408a00, note: second param 0 might indicate zeroing
    }
}
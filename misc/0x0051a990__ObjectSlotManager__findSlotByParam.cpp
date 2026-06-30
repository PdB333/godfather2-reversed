// FUNC_NAME: ObjectSlotManager::findSlotByParam
int ObjectSlotManager::findSlotByParam(void* param2) const {
    int result = -1;
    if (m_slotCount != 0) {
        for (int i = 0; i < (int)(unsigned char)m_slotCount; ++i) {
            // Each slot is 36 bytes, start at +0x30, contains a pointer to an object at offset 0.
            void* objPtr = *(void**)(m_slots + i * 36);
            if (objPtr != nullptr) {
                // Call vtable function at offset 0x30 (12th function) with (param2, objPtr+12)
                // This function likely compares param2 against a value at offset 12 of the object.
                if ((*(bool(__thiscall**)(void*, void*))(*(int*)objPtr + 0x30))(param2, (char*)objPtr + 12)) {
                    result = i;
                    break;
                }
            }
        }
    }
    return result;
}
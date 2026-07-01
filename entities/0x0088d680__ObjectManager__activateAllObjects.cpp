// FUNC_NAME: ObjectManager::activateAllObjects
void ObjectManager::activateAllObjects() {
    uint32_t count = *(uint32_t*)((uint8_t*)this + 0x148); // +0x148: number of objects
    if (count != 0) {
        uint32_t i = 0;
        do {
            // +0x80: array of object pointers (4 bytes each)
            uint8_t* obj = *(uint8_t**)((uint8_t*)this + 0x80 + i * 4);
            *(uint8_t*)(obj + 0x280) = 1; // +0x280: activation flag (0 = inactive, 1 = active)
            i++;
        } while (i < count);
    }
}
// FUNC_NAME: HandleManager::allocateHandle
uint32_t __fastcall HandleManager::allocateHandle(void* self, HandleManager* container, void* object) {
    int capacity = *(int*)((uint8_t*)container + 0x6034);
    int count = *(int*)((uint8_t*)container + 0x6030);
    if (count == capacity) {
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity *= 2;
        }
        FUN_005e70b0(capacity); // resize internal array
    }
    // Get pointer to new slot (8 bytes per entry)
    uint32_t* slot = (uint32_t*)(*(int*)((uint8_t*)container + 0x602c) + count * 8);
    *(int*)((uint8_t*)container + 0x6030) = count + 1; // increment count
    if (slot != nullptr) {
        slot[0] = (uint32_t)&LAB_004c9720; // vtable/type marker
        slot[1] = (uint32_t)object;         // stored object pointer
    }
    // Build handle: high byte = 1 (generation), low 3 bytes = slot address >> 8
    return ( (reinterpret_cast<uint32_t>(slot) >> 8) & 0x00FFFFFF ) | 0x01000000;
}
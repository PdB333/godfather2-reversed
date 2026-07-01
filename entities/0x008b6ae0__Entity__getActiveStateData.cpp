// FUNC_NAME: Entity::getActiveStateData
// 0x008b6ae0 - Returns the value at +0x194 (activeStateData) if bit 0x10 of flags at +0x290 is set, otherwise 0.
uint32_t __thiscall Entity::getActiveStateData(void* entity) {
    uint32_t result = 0;
    // +0x290: flags bitfield
    // +0x194: active state data (valid only when bit 0x10 is set)
    if ((*(uint8_t*)((uintptr_t)entity + 0x290) & 0x10) != 0) {
        result = *(uint32_t*)((uintptr_t)entity + 0x194);
    }
    return result;
}
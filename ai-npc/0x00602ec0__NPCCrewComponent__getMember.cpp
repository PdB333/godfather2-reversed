// FUNC_NAME: NPCCrewComponent::getMember
void* __thiscall NPCCrewComponent::getMember(uint index) {
    // If index is 0xFFFFFFFF (default), use the current index stored at this+0x3C
    if (index == 0xFFFFFFFF) {
        index = *(uint *)(this + 0x3C);
    }

    // Manager pointer at this+0x20; it contains the array info.
    uint32_t managerPtr = *(uint32_t *)(this + 0x20); // +0x20: pointer to CrewManager

    // Bounds check: array size is stored at manager+0xA4
    uint32_t count = *(uint32_t *)(managerPtr + 0xA4); // +0xA4: number of slots
    if (index < count) {
        // Array base is at manager+0xAC, plus an offset of 0x40.
        // Each element is 0x61 bytes (97 bytes).
        uint32_t base = *(uint32_t *)(managerPtr + 0xAC); // +0xAC: pointer to raw data block
        return (void *)(base + 0x40 + index * 0x61); // +0x40: start of first element
    }

    // Out-of-range: return a sentinel global object (invalid/null placeholder)
    return (void *)&DAT_012222a0;
}
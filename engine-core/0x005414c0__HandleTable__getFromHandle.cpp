// FUNC_NAME: HandleTable::getFromHandle
uint __thiscall HandleTable::getFromHandle(uint handle)
{
    // Handle format: bits 31-30 encode type, lower bits encode index
    uint type = handle & 0xC0000000; // high 2 bits
    if (type == 0) {
        // Type 0: use low 5 bits as index into small array at +0x34 (max 32 entries)
        uint index = handle & 0x1F;
        return *(uint *)(this + 0x34 + index * 4);
    }
    if (type == 0x40000000) {
        // Type 1: use full handle as index into table starting at +4
        return *(uint *)(handle * 4 + 4) | 1; // Set bit 0 as valid flag
    }
    if (type == 0xC0000000) {
        // Type 3 (bits 11): use full handle as index into table starting at +0x50
        return *(uint *)(handle * 4 + 0x50) | 1;
    }
    // Invalid type (0x80000000) returns -1
    return 0xFFFFFFFF;
}
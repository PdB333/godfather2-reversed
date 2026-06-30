// FUNC_NAME: SimObjectHandle::toOffset
// Function address: 0x00541370
// Converts a 32-bit handle (top 2 bits encode object type) to a memory offset.
// Type 0x40000000 (01) -> dynamic objects: offset = index * 4
// Type 0xC0000000 (11) -> static objects: offset = index * 4 + 0x4C
// Other types return 0 (invalid).
int SimObjectHandle::toOffset(uint handle)
{
    uint type = handle & 0xC0000000;
    if (type == 0x40000000) {
        return (int)(handle * 4);
    }
    if (type == 0xC0000000) {
        return (int)(handle * 4 + 0x4C);
    }
    return 0;
}
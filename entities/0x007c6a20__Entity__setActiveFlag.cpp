// FUNC_NAME: Entity::setActiveFlag
void __thiscall Entity::setActiveFlag(int thisPtr, bool enable)
{
    // Offset +0x128: uint32 flags word; bit 0x10 is "active" flag
    if (enable) {
        *(uint32_t*)(thisPtr + 0x128) |= 0x10;
        // Call enable handler
        FUN_007f63e0();
    } else {
        *(uint32_t*)(thisPtr + 0x128) &= ~0x10;
        // Call disable handler
        FUN_007f6420();
    }
}
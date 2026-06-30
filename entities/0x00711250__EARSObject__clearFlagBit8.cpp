// FUNC_NAME: EARSObject::clearFlagBit8
void __thiscall EARSObject::clearFlagBit8(EARSObject* this)
{
    // Clear bit 8 (0x100) of the flags field at offset +0x10.
    // This likely disables a specific state flag (e.g., paused, hidden, or marked).
    *(uint32_t*)((uint8_t*)this + 0x10) &= ~0x100;
}
// FUNC_NAME: SomeObject::checkAndExecuteFlaggedAction
void __fastcall SomeObject::checkAndExecuteFlaggedAction(SomeObject* this)
{
    // Check bit 3 of flags at offset 0x18c
    if ((*(uint32_t*)((uint8_t*)this + 0x18c) >> 3) & 1)
    {
        // Execute the associated action
        handleFlaggedAction(this);
        // Clear bit 3
        *(uint32_t*)((uint8_t*)this + 0x18c) &= ~(1 << 3);
    }
}
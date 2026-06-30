// FUNC_NAME: EARSObject::markDirtyAndClearProcessing
// Function address: 0x004df590
// Sets bit 0x20000 (dirty) if not already set, calls a global handler, then clears bit 0x40000 (busy/processing).
// mData points to an internal data block (offset +0x00) with flags at offset +0x0C.
void __fastcall EARSObject::markDirtyAndClearProcessing()
{
    if (this->mData != nullptr)
    {
        uint32_t* pFlags = (uint32_t*)((char*)this->mData + 0xC); // +0x0C: flags bitfield

        if (!(*pFlags & 0x20000))
        {
            *pFlags |= 0x20000;                        // Set dirty flag
            FUN_0051b120();                            // Notify global state manager
        }
        *pFlags &= 0xfffbffff;                         // Clear busy/processing flag (bit 0x40000)
    }
}
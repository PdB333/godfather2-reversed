// FUNC_NAME: SimObject::getAssociatedPointerStatus

// Function at 0x00481620
// Returns the pointer value (as int) stored at +0x0C, but with the low byte modified:
// - If the pointer is non-null and the pointed-to object has bit 1 at +0x30 or bit 0 at +0x3C set, low byte is cleared (0).
// - Otherwise, low byte is set to 1.
// This is used as a safe getter that packs a small error/status code into the pointer value.

int __fastcall SimObject::getAssociatedPointerStatus(void)
{
    void* associatedObj = *(void**)((char*)this + 0x0C);  // +0x0C: pointer to associated object
    uintptr_t base = (uintptr_t)associatedObj & 0xFFFFFF00;

    if (associatedObj != nullptr)
    {
        uint flags1 = *(uint*)((char*)associatedObj + 0x30); // +0x30: flag word (bit1 tested)
        byte flags2 = *(byte*)((char*)associatedObj + 0x3C);  // +0x3C: flag byte (bit0 tested)
        
        if ((flags1 & 2) != 0 || (flags2 & 1) != 0)
        {
            // Associated object exists and has at least one flag set → return with low byte 0
            return (int)base;
        }
    }

    // No associated object or flags not set → return with low byte 1
    return (int)(base | 1);
}
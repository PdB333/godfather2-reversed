// FUNC_NAME: validateHandle
void __fastcall validateHandle(uint handle)
{
    uint index = handle & 0xFFFF;
    // Lower 16 bits are index into a 0x30-byte table at DAT_012234bc
    // Each entry has a pointer at +0x10 and the handle at +0x2c
    // If the index is valid and the entry pointer and stored handle match, return (valid).
    // Otherwise, also return. Likely a debug assert that would trigger a break if invalid.
    if ((index < 0x200) &&
        (char* entry = (char*)DAT_012234bc + index * 0x30 + 0x10) &&
        (*(uint*)(entry + 0x2c) == handle) &&
        (entry != nullptr && *(int*)(entry + 0x10) != 0))
    {
        return;
    }
    return;
}
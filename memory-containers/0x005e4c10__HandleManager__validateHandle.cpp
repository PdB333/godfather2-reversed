// FUNC_NAME: HandleManager::validateHandle
// Address: 0x005e4c10
// Handles a 16-bit index from a handle (param_2 low word), validates against an entry array at EDI+0x10 (each entry 0x30 bytes),
// checks the stored full handle at offset 0x2c, then calls a release/process function with 3 arguments from ESI.
// Returns 1 on success, 0 on failure.

bool __fastcall HandleManager::validateHandle(uint handle)
{
    uint index = handle & 0xFFFF;                 // Low 16 bits are index
    if (index >= 0x200)                           // Array size 512 entries
        return false;

    // unaff_EDI likely points to a base structure; +0x10 is the array start
    Entry* entry = reinterpret_cast<Entry*>(reinterpret_cast<uint>(this) + 0x10 + index * 0x30);
    if (entry == nullptr)
        return false;

    // Verify that the entry's stored handle matches the full handle
    if (entry->handle != handle)                 // +0x2c
        return false;

    // unaff_ESI points to a triplet of data passed to the release function
    uint* data = reinterpret_cast<uint*>(esi);   // ESI register
    FUN_00414aa0(data[0], data[1], data[2]);     // Call release/process callback
    return true;
}
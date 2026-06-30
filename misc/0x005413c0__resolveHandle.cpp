// FUNC_NAME: resolveHandle
// Function at 0x005413c0: Resolves a handle (uint) to a pointer.
// Top two bits of handle indicate storage type:
//   0x80000000 -> direct offset (multiply by 4) - e.g., small object table
//   0xC0000000 -> indexed into a global table at offset 0x60 (likely a member of some global object)
//   otherwise  -> returns 0 (invalid handle)

int __fastcall resolveHandle(unsigned int handle)
{
    // Check handle type via top 2 bits (mask 0xC0000000)
    if ((handle & 0xC0000000) == 0x80000000) {
        // Direct index: return handle * 4 (likely a small offset table)
        return handle * 4;
    }
    if ((handle & 0xC0000000) == 0xC0000000) {
        // Use global table: base address (some global variable?) + 0x60, index = handle * 4
        // *(int*)(handle * 4 + 0x60) dereferences the table entry
        return *(int *)(handle * 4 + 0x60);
    }
    // Invalid handle
    return 0;
}
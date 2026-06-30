// FUNC_NAME: GlobalState::readTLSArrayIndexed
int __fastcall GlobalState::readTLSArrayIndexed(void* thisPtr)
{
    // Access thread-local storage at fs:[0x2c] (TEB field, points to a global structure)
    uint32_t* tlsTable = *(uint32_t**)(__readfsdword(0x2c)); // +0x2c in TEB

    // Offset +8 in that structure gives the base of an array
    uint32_t arrayBase = *(tlsTable + 2); // *(tlsTable + 8 bytes)

    // Offset from thisPtr+0x68 is the index into the array (byte offset)
    int elementOffset = *(int*)((uint8_t*)thisPtr + 0x68); // +0x68

    // Return the dword at (arrayBase + 4 + elementOffset)
    // The +4 constant suggests this might skip a header or padding
    return *(int*)((uint8_t*)arrayBase + 4 + elementOffset);
}
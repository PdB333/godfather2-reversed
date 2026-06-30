// FUNC_NAME: FUN_0065b3c0: copy8ByteArray
// Function address: 0x0065b3c0
// Copies an array of 8-byte elements from source to a global buffer (DAT_01223354).
// Count is passed in ESI (not saved by this function).

void __fastcall copy8ByteArray(void* this, void* source)
{
    // this pointer is unused; count is assumed to be in ESI from caller
    uint count = unaff_ESI; // Register ESI holds the number of 8-byte elements to copy

    if (count != 0) {
        for (uint i = 0; i < count; i++) {
            // Destination pointer from global DAT_01223354 (array of 8-byte elements)
            uint* dest = (uint*)(DAT_01223354 + i * 8);
            if (dest != nullptr) {
                dest[0] = *(uint*)((uint8*)source + i * 8);      // Copy first 4 bytes
                dest[1] = *(uint*)((uint8*)source + i * 8 + 4);  // Copy next 4 bytes
            }
        }
    }
}
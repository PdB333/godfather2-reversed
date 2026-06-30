// FUNC_NAME: copyStructArray12
// Function address: 0x0065b420
// Copies an array of 12-byte structures (8 bytes + 4 bytes) from source to a global buffer.
// Parameters:
//   count - number of elements to copy
//   source - pointer to source array (each element 12 bytes)
// The global buffer is at a static address (DAT_01223360). The function checks for null on each element destination,
// which is likely a dead check from legacy code or the buffer address could be zero in some configurations.
void __fastcall copyStructArray12(int count, void* source) {
    if (count != 0) {
        int offset = 0;
        do {
            // Destination pointer for current element (12 bytes)
            uint8_t* dest = (uint8_t*)0x01223360 + offset;
            if (dest != nullptr) { // Legacy null-check (likely always true)
                *(uint64_t*)dest = *(uint64_t*)((uint8_t*)source + offset);
                *(uint32_t*)(dest + 8) = *(uint32_t*)((uint8_t*)source + offset + 8);
            }
            offset += 0xC;
            count--;
        } while (count != 0);
    }
}
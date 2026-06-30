// FUNC_NAME: Fixed8ByteArray::destroyAll
void __thiscall Fixed8ByteArray::destroyAll(int *this) {
    int count = this[1]; // +0x04: number of entries
    // Iterate backwards through the array
    while (count > 0) {
        count--;
        // Check if the first 4 bytes of the entry (a pointer) is non-null
        if (*(int *)(this[0] + count * 8) != 0) {
            // Release the object at the entry address
            FUN_004daf90(this[0] + count * 8);
        }
    }
    this[1] = 0; // Reset count
    FUN_009c8f10(this[0]); // Free the array memory
    this[0] = 0; // Nullify array pointer
    this[2] = 0; // +0x08: clear some other field
}
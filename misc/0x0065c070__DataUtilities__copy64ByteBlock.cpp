// FUNC_NAME: DataUtilities::copy64ByteBlock
// Address: 0x0065c070
// Copies a 64-byte data block from source to destination. The 'this' pointer is unused.
void DataUtilities::copy64ByteBlock(void* this, void* dest, void* src) {
    // Copy 64 bytes (0x40) from source to destination
    memcpy(dest, src, 0x40);
}
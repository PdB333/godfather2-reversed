// FUNC_NAME: copyDataBlocks
// Address: 0x005dab00
// Role: Copies 40-byte blocks from source range to destination. Used for bulk data transfer (e.g., packet slot replication).
void __fastcall copyDataBlocks(void *dest, void *srcEnd, void *srcStart)
{
    // Copy 40-byte (5 * 8) blocks from srcStart to dest until srcStart reaches srcEnd.
    if (srcStart != srcEnd) {
        do {
            if (dest != NULL) {
                *(uint64_t*)dest = *(uint64_t*)srcStart;
                *(uint64_t*)((char*)dest + 8) = *(uint64_t*)((char*)srcStart + 8);
                *(uint64_t*)((char*)dest + 16) = *(uint64_t*)((char*)srcStart + 16);
                *(uint64_t*)((char*)dest + 24) = *(uint64_t*)((char*)srcStart + 24);
                *(uint64_t*)((char*)dest + 32) = *(uint64_t*)((char*)srcStart + 32);
            }
            srcStart = (char*)srcStart + 40;
            dest = (char*)dest + 40;
        } while (srcStart != srcEnd);
    }
}
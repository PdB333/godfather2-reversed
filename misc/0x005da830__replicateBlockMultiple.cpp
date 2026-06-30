// FUNC_NAME: replicateBlockMultiple
void __fastcall replicateBlockMultiple(int count, const uint64_t* source, uint64_t* dest)
{
    if (count != 0) {
        do {
            // Copy a 40-byte block from source to dest
            dest[0] = source[0];
            dest[1] = source[1];
            dest[2] = source[2];
            dest[3] = source[3];
            dest[4] = source[4];
            // Advance dest by 40 bytes (5 uint64_t)
            dest += 5;
            count--;
        } while (count != 0);
    }
}
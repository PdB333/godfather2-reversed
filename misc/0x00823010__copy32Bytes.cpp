// FUNC_NAME: copy32Bytes
// Copies exactly 32 bytes from source to destination.
// Original uses a loop with modulo indexing that simplifies to a straight copy.
void copy32Bytes(void* dest, void* src) {
    uint32_t* d = (uint32_t*)dest;
    uint32_t* s = (uint32_t*)src;
    d[0] = s[0];
    d[1] = s[1];
    d[2] = s[2];
    d[3] = s[3];
    d[4] = s[4];
    d[5] = s[5];
    d[6] = s[6];
    d[7] = s[7];
}
// FUNC_NAME: DataBuffer::copyTo
// Address: 0x004cdee0
// Copies raw bytes from this internal buffer to an external buffer structure.
// this+0x00: pointer to source data (char*)
// param1+0x00: pointer to destination buffer (char*)
// param1+0x08: number of bytes to copy (unsigned short)
void __thiscall DataBuffer::copyTo(void* dest)
{
    // Source pointer from this object (typically start of a packet or memory chunk)
    char* src = *(char**)this;
    // Destination pointer from the passed structure
    char* dst = *(char**)dest;
    // Count field at offset 8 in the destination descriptor
    unsigned short count = *(unsigned short*)((char*)dest + 8);
    // Copy loop, only if count is non-zero
    if (count != 0) {
        unsigned short i = 0;
        do {
            dst[i] = src[i];
            i++;
        } while (i < count);
    }
}
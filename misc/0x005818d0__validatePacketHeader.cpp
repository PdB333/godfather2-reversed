// FUNC_NAME: validatePacketHeader
// Function at 0x005818d0: validates a packet header structure.
// Returns 1 if the structure passes all sanity checks, 0 otherwise.
// The structure is assumed to have the following layout:
//   +0x00: byte  type (< 0x23)
//   +0x01: byte  subtype (1-7)
//   +0x02: short size (0-127)
//   +0x0C: byte* dataPointer (must point within a 512-byte buffer starting at the structure)

int __cdecl validatePacketHeader(void* headerPtr)  // pointer passed in eax
{
    unsigned char* h = (unsigned char*)headerPtr;

    // Validate type and subtype
    if (h[0] >= 0x23)          return 0;
    if (h[1] <= 0 || h[1] >= 8) return 0;

    // Validate short field at +0x02
    short field2 = *(short*)(h + 2);
    if (field2 < 0 || field2 >= 0x80) return 0;

    // Validate pointer at +0x0C
    unsigned char* dataPtr = *(unsigned char**)(h + 0x0C);
    if (dataPtr <= h || dataPtr >= h + 0x200) return 0;

    return 1;
}
// FUNC_NAME: NetGhostArray::copyDirtyEntries
// Address: 0x0057cd30
// Role: Copies an array of 32-byte entries from a source pointer into the object's internal array,
//   but only for indices where the corresponding mask byte equals 0x02 (or if mask pointer is null).
//   This is likely used for network replication of ghost state: 'dirty' flags indicate which entries need updating.
//   The object is assumed to hold a contiguous array of 32-byte (8 uint32) structures; the 'this' pointer
//   points to the start of that array.

void __thiscall NetGhostArray::copyDirtyEntries(int count, char* mask, uint32_t* source)
{
    uint32_t* dest = (uint32_t*)this; // +0x00: base of destination array
    uint32_t* endDest = dest + count * 8; // each entry is 8 uint32s (32 bytes)

    while (dest != endDest)
    {
        // If no mask is provided, or the current mask byte is exactly 0x02, this entry is "dirty" and should be copied
        if (mask == (char*)0x0 || *mask == '\x02')
        {
            // Copy the entire 32-byte structure (8 uint32s)
            dest[0] = source[0];
            dest[1] = source[1];
            dest[2] = source[2];
            dest[3] = source[3];
            dest[4] = source[4];
            dest[5] = source[5];
            dest[6] = source[6];
            dest[7] = source[7];
            source += 8; // advance source only when copy occurs (source not advanced for skipped entries)
        }
        // Always advance destination and mask to the next slot
        dest += 8;
        mask++;
    }
}
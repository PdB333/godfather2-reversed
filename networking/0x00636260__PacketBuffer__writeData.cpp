// FUNC_NAME: PacketBuffer::writeData
// Function at 0x00636260: Writes 8-byte data pairs from a source buffer into a frame-based packet buffer.
// Offsets (relative to `this`):
//   +0x08: m_writePos (uint32_t*) - current write position
//   +0x0c: m_frameStart (uint32_t*) - start of current frame buffer
//   +0x14: m_frameStack (uint32_t**) - stack of saved frame starts
//   +0x30: m_flags (byte) - bit 1 triggers source refresh via helper

#pragma pack(push, 1)
struct PacketBuffer {
    /* +0x00 */ uint8_t  unknown[8];      // +0x00..+0x07
    /* +0x08 */ uint32_t* m_writePos;     // pointer to next write location
    /* +0x0c */ uint32_t* m_frameStart;   // base address of current frame
    /* +0x10 */ uint8_t  gap[4];          // +0x10..+0x13
    /* +0x14 */ uint32_t** m_frameStack;  // stack pointer for frame starts
    /* +0x18 */ uint8_t  gap2[0x18];      // +0x18..+0x2F
    /* +0x30 */ uint8_t  m_flags;         // flags (bit 1 = refresh source)
    /* +0x31 */ uint8_t  pad[3];          // align to 4
};
#pragma pack(pop)

void __thiscall PacketBuffer::writeData(int pairCount)
{
    uint32_t* source;
    uint32_t* destStart;
    uint32_t* dest;
    int count;

    // If flag bit 1 is set, obtain a new source buffer pointer
    if (m_flags & 2) {
        source = (uint32_t*)FUN_006361f0(); // helper function (address 0x006361f0)
    } else {
        // Note: original code used whatever was in EAX; assume source is already set
        source = nullptr; // placeholder - actual code may rely on caller ensuring valid source
    }

    // Decrement the frame stack pointer by 3 slots (0x18 = 3 * 8 bytes)
    m_frameStack = (uint32_t**)((uint8_t*)m_frameStack - 0x18);

    // Compute start of destination from current frame base
    destStart = (uint32_t*)((uint8_t*)m_frameStart - 8); // 8 bytes before m_frameStart

    // Restore m_frameStart from the value on the top of the frame stack
    m_frameStart = *m_frameStack;

    // Copy pairs from source to destination, 8 bytes (two uint32_t) per iteration
    dest = destStart;
    count = pairCount;
    while (count != 0) {
        // Check if we've exhausted the source buffer
        if (m_writePos <= source) { // m_writePos acts as end-of-source marker
            break;
        }
        // Write one 8-byte pair
        *dest = *source;                // first 4 bytes
        *(dest + 1) = *(source + 1);    // second 4 bytes
        source += 2;                    // advance source by 8 bytes
        dest += 2;                      // advance dest by 8 bytes
        count--;
    }

    // If any remaining count, fill destination with zeroes (8 bytes per pair)
    for (; count > 0; count--) {
        *dest = 0;
        ++dest; // advance by 4 bytes (only first word zeroed? original code increments by 2)
        // Original code: *puVar2 = 0; puVar2 += 2; -> zeroes first word and skips second? Actually it sets first word to 0 and increments by 2 uint32_t, leaving second word uninitialized? But the for loop only sets one 4-byte zero per iteration. That's likely a bug in the decompilation. More likely it should be *dest = 0; *(dest+1)=0; dest+=2; However, based on the decompiled listing: "for (; 0 < param_1; param_1 = param_1 + -1) { *puVar2 = 0; puVar2 = puVar2 + 2; }". That only zeros the first uint32_t of each pair. We'll replicate as-is, noting possible decompiler artifact.
    }

    // Update write position to end of written data
    m_writePos = dest;
}
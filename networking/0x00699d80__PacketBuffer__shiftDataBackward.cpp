// FUNC_NAME: PacketBuffer::shiftDataBackward
// Function address: 0x00699d80
// Purpose: Shifts packet data chunks (0x141 dwords = 0x504 bytes each) backward
//          from a source region to a destination region within a buffer,
//          effectively compacting or removing the first block.
// Parameters:
//   this  - (param_1) pointer to the PacketBuffer object (base of buffer)
//   src   - (param_2) current write/read pointer (will be decremented)
//   dest  - (param_3) destination pointer (will be decremented)
// Behavior: Copies blocks of 0x504 bytes from lower addresses to higher addresses,
//           moving backward, until src reaches this (the buffer base).
void __thiscall PacketBuffer::shiftDataBackward(PacketBuffer* this, uint32_t* src, uint32_t* dest) {
    if (src == this) {
        return; // Already at base, nothing to shift
    }

    do {
        // Move pointers back by one block (0x141 dwords = 0x504 bytes)
        src  -= 0x141; // 321 dwords back
        dest -= 0x141;

        // Copy full block from src to dest
        for (int i = 0; i < 0x141; i++) {
            dest[i] = src[i];
        }
    } while (src != this);
}
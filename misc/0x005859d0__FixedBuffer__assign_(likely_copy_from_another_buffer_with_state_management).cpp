// FUNC_NAME: FixedBuffer::assign (likely copy from another buffer with state management)
// Function address: 0x005859d0
// Role: Copies 32-byte data between fixed-size buffer objects, handling state flags (0=empty, 2=valid).
// The third parameter is used when both buffers are in state 2, possibly as an extra argument for a memcpy variant.

struct FixedBuffer {
    char state;      // +0x00: 0 = empty, 2 = valid
    char pad[3];     // alignment padding
    uint8_t* data;   // +0x04: pointer to 32-byte buffer
};

void __thiscall FixedBuffer::assign(FixedBuffer* this, const FixedBuffer* other, uint32_t extra) {
    char otherState = *(char*)&other->state; // first byte of other object

    if (*(char*)&this->state != 2) {
        // This buffer is not in valid state
        if (otherState == 2) {
            // Take ownership and copy data from other
            this->state = 2;
            uint32_t* src = (uint32_t*)other->data;
            uint32_t* dst = (uint32_t*)this->data;
            dst[0] = src[0];
            dst[1] = src[1];
            dst[2] = src[2];
            dst[3] = src[3];
            dst[4] = src[4];
            dst[5] = src[5];
            dst[6] = src[6];
            dst[7] = src[7];
        } else {
            // Other is also invalid, mark this as empty
            this->state = 0;
        }
    } else {
        // This buffer is already valid
        uint32_t* dst = (uint32_t*)this->data;
        this->state = 2; // redundant set
        if (otherState == 2) {
            // Both valid – call helper with extra parameter (likely memcpy with size)
            FUN_005781f0(dst, extra);
        } else {
            // Other is invalid – Ghidra shows self-copy (likely decompilation bug).
            // Based on context, probably copy from other's data (if any) or clear.
            // We emulate the decompiled logic as-is (self-copy does nothing).
            uint32_t* src = (uint32_t*)this->data; // Note: using this->data per Ghidra
            dst[0] = src[0];
            dst[1] = src[1];
            dst[2] = src[2];
            dst[3] = src[3];
            dst[4] = src[4];
            dst[5] = src[5];
            dst[6] = src[6];
            dst[7] = src[7];
        }
    }
}
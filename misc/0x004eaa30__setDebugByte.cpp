// FUNC_NAME: setDebugByte
// Function at 0x004eaa30 - Stores a debug byte either into a global variable or a dynamic buffer.
// The buffer is used for per-thread logging? If the TLS field is zero, pushes onto a stack (incrementing pointer).
// Otherwise writes to a static byte.

#include <cstdint>

// Assume these are defined elsewhere (global addresses)
extern uint32_t DAT_01206880;   // Base address of some structure
extern uint8_t  DAT_012054fe;   // Global debug byte storage
extern void*    PTR_LAB_01124c34; // Some vtable or type descriptor

void setDebugByte(uint8_t value)
{
    // Access thread-local storage via FS segment (x86)
    // FS:[0x2c] points to a per-thread structure; offset 0x34 is checked for zero
    int* tlsBase = *reinterpret_cast<int**>(__readfsdword(0x2c));
    if (tlsBase[0x34 / sizeof(int)] == 0)  // offset 0x34 = 13th int (0x34/4=13)
    {
        // Buffer pointer is stored at DAT_01206880+0x14
        int*& bufferPtr = *reinterpret_cast<int**>(DAT_01206880 + 0x14);
        // Write a type descriptor (vtable? constant) at current position
        *reinterpret_cast<void**>(bufferPtr) = &PTR_LAB_01124c34;
        // Advance pointer by 4 bytes (size of a pointer)
        bufferPtr += 1;
        // Write the byte value as a zero-extended 32-bit integer
        *reinterpret_cast<uint32_t*>(bufferPtr) = value;
        // Advance pointer again
        bufferPtr += 1;
    }
    else
    {
        // Use direct global storage
        DAT_012054fe = value;
    }
}
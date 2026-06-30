// FUNC_NAME: DataReader::readTypedValue
#include <cstdint>

// Reads a typed value from the internal data buffer.
// EAX: type code (1,3,4,5)
// ECX: this (DataReader*)
// EDX: outBuffer (void** to store result)
// The data buffer pointer is stored at offset +0x8 (uint8_t*).
void __fastcall DataReader::readTypedValue(void* outBuffer) {
    // Offset 0x8 holds a pointer to the current read position in the buffer.
    uint8_t*& currentPos = *reinterpret_cast<uint8_t**>(reinterpret_cast<uint8_t*>(this) + 0x8);
    void** out = reinterpret_cast<void**>(outBuffer);

    // Type code is passed in EAX (not visible in C++ signature)
    switch (eaxType) {
    case 1:
    case 3: {
        // Read 8-byte value (e.g., double, int64) - two 32-bit words
        uint32_t low  = *reinterpret_cast<uint32_t*>(currentPos - 8);
        uint32_t high = *reinterpret_cast<uint32_t*>(currentPos - 4);
        out[0] = reinterpret_cast<void*>(low);
        out[1] = reinterpret_cast<void*>(high);
        break;
    }
    case 4:
    case 5: {
        // Read a 4‑byte size header and then a string via readString()
        out[0] = reinterpret_cast<void*>(4);                          // size field
        out[1] = reinterpret_cast<void*>(readString());               // FUN_00638920
        // Advance the internal pointer to after the output structure.
        currentPos = reinterpret_cast<uint8_t*>(out) + 8;             // out + 2 * sizeof(void*)
        return;
    }
    default:
        break;
    }
    // For cases 1, 3, and default, advance the pointer.
    currentPos = reinterpret_cast<uint8_t*>(out) + 8;
}
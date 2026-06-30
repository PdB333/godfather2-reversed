// FUNC_NAME: initArrayDescriptor
// Address: 0x00582620
// Role: Initializes a small array descriptor structure (typically 16 bytes), sets magic, count, pointers, and zeroes the data array.
// The descriptor structure is passed via EAX (not a regular parameter). This is a common EA pattern for inline or internal helper.
// Structure layout:
//   +0x00: int m_maxIndex;  // always set to -1 (sentinel)
//   +0x04: int m_count;      // number of elements
//   +0x08: int* m_data;      // pointer to the actual array
//   +0x0C: int m_unknown;    // stored but not used in this function (maybe element size or flags)

// Note: The actual calling convention is non‑standard: the address of the descriptor is passed in EAX,
// the count in EDX, and the remaining two parameters on the stack.
void __fastcall initArrayDescriptor(int* desc, int count, int* data, int unknown)
{
    // desc is passed in EAX, but Ghidra decompiles as first register param (ECX) – we ignore it.
    // We use the pointer from the compiler's perspective.

    desc[2] = (int)data;      // +0x08: m_data
    desc[3] = unknown;        // +0x0C: m_unknown
    desc[0] = -1;             // +0x00: m_maxIndex = -1
    desc[1] = count;          // +0x04: m_count

    // Zero out the data array
    if (count > 0) {
        for (int i = 0; i < count; i++) {
            data[i] = 0;
        }
    }
}
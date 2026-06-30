// FUNC_NAME: copyStructArray (helper function copying 20-byte structures)
// Address: 0x00654690
// Role: Copies an array of 20-byte structures from a source buffer into a destination array.
// Destination array pointer is stored at offset +0x8 of an object pointed by hidden EDI.
// Count is passed in EAX, source pointer in EDX (fastcall convention).
// The function is called from FUN_00654620.

// Note: The original decompiler signature does not expose EDI; we reconstruct as a member
// function where 'this' (EDI) contains a pointer to the destination array at offset +0x8.

class StructArrayContainer {
public:
    void* m_pArray; // +0x8: pointer to array of 20-byte structures

    // Copies 'count' elements of 20 bytes from source to the internal array.
    // This function expects the calling convention: count in EAX, source in EDX,
    // and 'this' (EDI) pointing to the StructArrayContainer.
    void __fastcall copyFromSource(int count, const void* source) {
        if (count != 0) {
            int offset = 0;
            do {
                char* dest = static_cast<char*>(m_pArray) + offset;
                if (dest != nullptr) {
                    // Copy 20 bytes: two 8-byte values and one 4-byte value
                    *reinterpret_cast<uint64_t*>(dest) = *reinterpret_cast<const uint64_t*>(static_cast<const char*>(source) + offset);
                    *reinterpret_cast<uint64_t*>(dest + 8) = *reinterpret_cast<const uint64_t*>(static_cast<const char*>(source) + offset + 8);
                    *reinterpret_cast<uint32_t*>(dest + 16) = *reinterpret_cast<const uint32_t*>(static_cast<const char*>(source) + offset + 16);
                }
                offset += 20; // 0x14
                count--;
            } while (count != 0);
        }
    }
};
// FUN_004dba80: WideString::constructFromAscii
// Address: 0x004dba80
// Role: Constructor/initializer for a wide (short-based) string from a narrow ASCII string.
// The class stores:
//   +0x00: short* m_pBuffer    (pointer to wide character buffer)
//   +0x04: uint32 m_length     (number of characters, not counting null terminator)
//   +0x08: uint32 m_capacity   (allocated byte size of buffer)
//   +0x0C: void* m_pDeallocator (pointer to deallocation function)
void __thiscall WideString::constructFromAscii(WideString* thisPtr, const char* source, uint32 length)
{
    uint32 allocSize;
    short* bufferPtr;
    uint32 i;

    if (length == 0) {
        // Empty string: zero everything
        thisPtr->m_pBuffer = nullptr;
        thisPtr->m_capacity = 0;
        thisPtr->m_length = 0;
        return;
    }

    thisPtr->m_capacity = length * 2;               // allocate bytes for each char as short
    thisPtr->m_length = length;

    // Calculate allocation size: (length + 1) * 2 bytes (to add null wide terminator)
    // Original code uses a complicated sign-extended expression to avoid overflow.
    // (uint)((length & 0x7fffffff) + 1) * 2
    allocSize = (length + 1) * 2;                   // simplified

    // Allocate memory via engine allocator (FUN_009c8e50)
    bufferPtr = (short*)FUN_009c8e50(allocSize);
    thisPtr->m_pBuffer = bufferPtr;

    // Copy each ASCII character into the wide buffer (sign-extended to short)
    for (i = 0; i < length; i++) {
        bufferPtr[i] = (short)(unsigned char)source[i];
    }

    // Null-terminate the wide string
    bufferPtr[length] = 0;

    // Set deallocator function pointer (thunk_FUN_009c8eb0)
    thisPtr->m_pDeallocator = (void*)thunk_FUN_009c8eb0;
}
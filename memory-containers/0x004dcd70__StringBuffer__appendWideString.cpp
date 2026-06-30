// FUNC_NAME: StringBuffer::appendWideString
// Address: 0x004dcd70
// Reconstructed member function that appends a null-terminated wide string to a buffer
// if the buffer's last allocated block aligns with the insertion point.

typedef unsigned short wchar;  // 16-bit wide char (UTF-16)

// Forward declaration: pool allocator that returns next available block address, or 0 if none
wchar* allocatorGetNextBlock(void);  // FUN_004dc860

// Class representing a growable wide-character buffer with pre-allocated blocks
class StringBuffer {
public:
    wchar* buffer;      // +0x00: pointer to buffer start
    int    usedShorts;  // +0x04: number of wchar elements currently stored (including null?)

    // Append a null-terminated wide string only if the last allocated block ends exactly
    // where the new string would be placed. Otherwise no-op.
    // Returns pointer to this for chaining.
    StringBuffer* __thiscall appendWideString(const wchar* src) {
        if (buffer == nullptr) {
            return this;
        }

        // Get first block from allocator
        wchar* block = allocatorGetNextBlock();
        if (block == nullptr) {
            return this;
        }

        // Compute length of src string (excluding the first character? Actually starts at src+1)
        // This suggests src may have a leading term that is skipped (e.g. length prefix?)
        const wchar* p = src;
        const wchar* startPlusOne = src + 1;  // skip first element
        while (*p != L'\0') {
            ++p;
        }
        // Number of wchar elements from second element to null terminator inclusive
        int length = (p - startPlusOne);  // pointer difference in elements

        // Walk to the last allocated block
        wchar* lastBlock = nullptr;
        while (block != nullptr) {
            lastBlock = block;
            block = allocatorGetNextBlock();
        }

        // Check if the last block ends exactly at the position where the new string would start
        // Condition: lastBlock + length == buffer + usedShorts
        if (lastBlock + length == buffer + usedShorts) {
            // Null-terminate the new string at the end of the buffer
            *lastBlock = L'\0';
            // Update used count to reflect the new string's contribution
            usedShorts = (lastBlock - buffer) / 1;  // pointer diff in wchar units
        }

        return this;
    }
};
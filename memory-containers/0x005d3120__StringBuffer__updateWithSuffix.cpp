// FUNC_NAME: StringBuffer::updateWithSuffix
// Function address: 0x005d3120
// Role: Replaces the internal string buffer with a new string (possibly from an external source) appended with "_dne" suffix,
//       or reallocates a copy of the current string if the external source is unavailable.
// Structure offsets:
//   +0x00: char* m_pData       - pointer to the string data
//   +0x04: char* m_pPrevData   - previous data pointer (used for tracking)
//   +0x08: uint8_t m_bFlag     - flag (always set to 1 after update)
//   +0x0C: size_t m_nCapacity  - capacity of the buffer

#include <cstring>
#include <cstdint>

// Forward declarations of helper functions (from the same module)
int retrieveStringInfo(char* outBuffer, size_t* outSize, char* unknown); // FUN_005d4130
void* allocateAligned(size_t size, int alignment); // FUN_005c4410

void StringBuffer::updateWithSuffix()
{
    size_t newSize = 0;
    char localBuffer[4]; // unknown purpose, possibly temporary output
    char unknownBuffer[4]; // unknown purpose

    int result = retrieveStringInfo(localBuffer, &newSize, unknownBuffer);
    size_t size = newSize;

    if (result != 0) {
        // External string retrieval succeeded: allocate new buffer with extra space for "_dne" suffix
        void* newData = allocateAligned(size + 4, 0x10);
        memcpy(newData, m_pData, size);
        // Append "_dne" suffix (0x5f = '_', 100 = 'd', 0x6e = 'n', 0x65 = 'e')
        ((char*)newData)[size] = '_';
        ((char*)newData)[size + 1] = 'd';
        ((char*)newData)[size + 2] = 'n';
        ((char*)newData)[size + 3] = 'e';

        char* oldData = m_pData;
        m_pData = (char*)newData;
        m_pPrevData = oldData; // store old pointer
        m_bFlag = 1;
    } else {
        // External retrieval failed: reallocate a copy of the current string
        void* newData = allocateAligned(m_nCapacity, 0x10);
        memcpy(newData, m_pData, m_nCapacity);
        m_pData = (char*)newData;
        m_pPrevData = nullptr;
        m_bFlag = 1;
    }
}
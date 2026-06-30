// FUNC_NAME: resolveHashEntry

// Function at 0x004b18a0 - looks up data by a 128-bit hash and processes the result
// The hash is a 128-bit value (4 ints). Certain sentinel values indicate invalid/empty hash.
// If hash is valid and found, reads field at offset 0x24 from the looked-up data.
// Then constructs a result struct and passes it to a finalization function.

// Calling convention: __cdecl (no this pointer used)
// Parameters:
//   param1: unused (might be hidden this or void)
//   param2: pointer to 4-int hash (128-bit)
//   param3: a byte that becomes the last field of the result struct

#include <cstdint>

// Forward declarations of called functions (decompiled elsewhere)
void* FUN_00455f50(int* hash, int arg2, int arg3);
void FUN_005e2040(void* resultStruct);

// Constants for invalid/empty hash values
static const int kHashSentinel0 = 0xBABDB9BA;
static const int kHashSentinel1 = 0xBEEFBEEF;
static const int kHashSentinel2 = 0xEAC15A55;
static const int kHashSentinel3 = 0x91100911;

struct HashResult {
    int m_typeFlag;      // +0x00 : always set to 1
    int m_dataValue;     // +0x04 : result from lookup (value at offset 0x24)
    int m_unused;        // +0x08 : always 0
    uint8_t m_byteParam; // +0x0C : copy of param3
};

void resolveHashEntry(int* hash, uint8_t byteParam) {
    HashResult result;
    result.m_typeFlag = 1;
    result.m_unused = 0;
    result.m_byteParam = byteParam;
    result.m_dataValue = 0;

    // Check if hash is non-zero and not matching the sentinel set
    bool hashNonZero = (hash[0] != 0) || (hash[1] != 0) || (hash[2] != 0) || (hash[3] != 0);
    if (hashNonZero) {
        bool notSentinel = (hash[0] != kHashSentinel0) || (hash[1] != kHashSentinel1) ||
                          (hash[2] != kHashSentinel2) || (hash[3] != kHashSentinel3);
        if (notSentinel) {
            void* dataPtr = FUN_00455f50(hash, 0, 0);
            if (dataPtr != nullptr) {
                result.m_dataValue = *reinterpret_cast<int*>(static_cast<uint8_t*>(dataPtr) + 0x24);
            }
        }
    }

    FUN_005e2040(&result);
}
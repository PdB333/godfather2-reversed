// FUNC_NAME: caseInsensitiveHash
// Function address: 0x004db3a0
// Role: Case-insensitive string hashing (likely used for hash tables or string lookups).
// Algorithm: seed = seed * 0x1003f + lowercased_byte

#include <cstdint>

int caseInsensitiveHash(int seed, const unsigned char* data, int length)
{
    if (data == nullptr) {
        return seed;
    }

    const unsigned char* end = data + length;
    for (const unsigned char* p = data; p < end; ++p) {
        uint32_t ch = *p;
        // Convert uppercase ASCII letters (A-Z) to lowercase by adding 0x20
        if (ch - 0x41 < 0x1a) {
            ch += 0x20;
        }
        seed = seed * 0x1003f + ch;
    }

    return seed;
}
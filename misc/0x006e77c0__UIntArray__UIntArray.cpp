// FUNC_NAME: UIntArray::UIntArray
// Address: 0x006e77c0
// Role: Constructor for a fixed-size array of 32-bit unsigned integers.
//        Allocates memory for 'size' elements (each 4 bytes), zero-fills them,
//        and stores a flag byte (param_3) at offset 0x14.

#include <cstdint>
#include <cstring>  // memset

// Forward declarations for external functions
void* __fastcall allocMemory(size_t size); // FUN_009c8e80
void  __fastcall initBase();               // FUN_006e73f0

class UIntArray {
public:
    uint32_t* m_pData;      // +0x00: pointer to allocated array
    uint32_t  m_nSize;      // +0x04: number of elements
    uint32_t  m_unknown08;  // +0x08: uninitialized (set to 0)
    uint32_t  m_unknown0C;  // +0x0C: uninitialized (set to 0)
    uint32_t  m_unknown10;  // +0x10: uninitialized (set to 0)
    uint8_t   m_flags;      // +0x14: stored from constructor parameter (purpose unknown)

    // Constructor
    // param_2 = number of elements (size), param_3 = flag byte
    __thiscall UIntArray(uint32_t size, uint8_t flags)
    {
        m_flags = flags;
        m_nSize = size;

        // Initialize all other fields to 0
        m_pData      = nullptr;
        m_unknown08  = 0;
        m_unknown0C  = 0;
        m_unknown10  = 0;

        // Allocate memory for size * 4 bytes (32-bit elements)
        // Overflow protection: if (size * 4) overflows 32-bit, the upper 32 bits are OR'd
        // to produce a huge value (likely triggering allocation failure).
        uint64_t allocSize = static_cast<uint64_t>(size) * 4;
        size_t   finalSize;
        if (allocSize > 0xFFFFFFFFULL) {
            finalSize = 0xFFFFFFFF;  // or some overflow indicator
        } else {
            finalSize = static_cast<size_t>(allocSize);
        }
        m_pData = static_cast<uint32_t*>(allocMemory(finalSize));

        // Zero-fill the allocated memory
        if (m_pData) {
            memset(m_pData, 0, m_nSize * 4);
        }

        // Call base class initializer (unknown purpose)
        initBase();
    }
};
```
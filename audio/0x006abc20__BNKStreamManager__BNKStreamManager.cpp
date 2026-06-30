// FUNC_NAME: BNKStreamManager::BNKStreamManager

#include <cstdint>

// Global pointer to singleton instance
extern BNKStreamManager* g_bnkStreamManager;  // DAT_01129900

// External data source for initial bank data (0x8000 bytes)
extern uint8_t g_defaultBankData[0x8000];  // DAT_012069c4

// Vtable symbols from binary
// *this -> PTR_FUN_00d5da74 (vtable)
// this->m_pCallbackVtable -> PTR_LAB_00d5da64 (second vtable or function table)

class BNKStreamManager {
public:
    // +0x00: vtable (base)
    // +0x04: m_pCallbackVtable (function table pointer)
    // +0x08: m_nRefCount (set to 1)
    // +0x0C: m_nFlags (set to 0)
    // +0x10..0x20: m_Reserved1[5] (set to 0)
    // +0x24: m_bByteFlag1 (set to 0)
    // +0x29: m_bByteFlag2 (set to 0)
    // +0x2C: m_nSomeCounter (set to 0)
    // Note: The constructor copies 0x8000 bytes from g_defaultBankData into the region starting at +0x04

    // Constructor
    __thiscall BNKStreamManager() {
        g_bnkStreamManager = this;

        // Initialize vtable and function table pointers
        this->m_pCallbackVtable = reinterpret_cast<void**>(0x00e2f19c); // initial default
        this->m_nRefCount = 1;
        this->m_nFlags = 0;
        this->vtable = reinterpret_cast<void**>(0x00d5da74);

        // Override callback vtable with actual table
        this->m_pCallbackVtable = reinterpret_cast<void**>(0x00d5da64);

        // Clear reserved fields
        this->m_Reserved1[0] = 0;
        this->m_Reserved1[1] = 0;
        this->m_Reserved1[2] = 0;
        this->m_Reserved1[3] = 0;
        this->m_Reserved1[4] = 0;

        // Copy initial bank data if available
        if (g_defaultBankData != nullptr) {
            // memcpy(this->m_pCallbackVtable, g_defaultBankData, 0x8000)
            // Actually copies into the buffer starting at offset 4 (this+1 word)
            uint32_t* dest = reinterpret_cast<uint32_t*>(&this->m_pCallbackVtable);
            const uint32_t* src = reinterpret_cast<const uint32_t*>(g_defaultBankData);
            for (int i = 0; i < 0x2000; ++i) {
                dest[i] = src[i];
            }
        }

        // Set byte flags and counter
        *(reinterpret_cast<uint8_t*>(&this->m_nFlags) + 0x24) = 0;  // +0x24 byte
        *(reinterpret_cast<uint8_t*>(&this->m_nFlags) + 0x29) = 0;  // +0x29 byte
        this->m_nSomeCounter = 0;
    }

private:
    // Assume vtable pointer is first member
    void** vtable;               // +0x00
    void** m_pCallbackVtable;    // +0x04
    int32_t m_nRefCount;         // +0x08
    int32_t m_nFlags;            // +0x0C
    int32_t m_Reserved1[5];      // +0x10..0x20
    // Bytes at +0x24 and +0x29 are separate (possibly bitfields)
    int32_t m_nSomeCounter;      // +0x2C
};
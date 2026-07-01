// FUNC_NAME: EARSBaseObject::release

// Address: 0x0090a9f0
// Role: Cleanup / release method for an EARS base object.
// Clears flags, releases a sub-object (if present and valid), zeros fields, and sets sentinel values for memory debugging.

#include <cstdint>

// Forward declarations of callee functions
extern void FUN_00791a70(uint32_t arg);
extern void FUN_004daf90(uint32_t* ptr);

class EARSBaseObject {
public:
    // __thiscall reconstructed as __fastcall with this in ecx
    void __thiscall release();

private:
    // Structure fields (offsets from this):
    // +0x00: m_flags (uint32_t)
    // +0x04: m_unknown (uint32_t)
    // +0x08: m_subObject (uint32_t*) - pointer to sub-object, may be nullptr or a magic value 0x48 indicating no destructor needed
    // +0x0C: m_unknown2 (uint32_t)
    // +0x10: m_field4 (uint32_t, zeroed)
    // +0x14: m_sentinel1 (0xbadbadba)
    // +0x18: m_sentinel2 (0xbeefbeef)
    // +0x1C: m_sentinel3 (0xeac15a55)
    // +0x20: m_sentinel4 (0x91100911)

    uint32_t m_flags;
    uint32_t m_unknown;      // offset +0x04
    uint32_t* m_subObject;   // offset +0x08
    uint32_t m_unknown2;     // offset +0x0C
    uint32_t m_field4;       // offset +0x10
    uint32_t m_sentinel1;    // offset +0x14
    uint32_t m_sentinel2;    // offset +0x18
    uint32_t m_sentinel3;    // offset +0x1C
    uint32_t m_sentinel4;    // offset +0x20
};

void __thiscall EARSBaseObject::release() {
    // Clear bit 2 (value 0x02) in m_flags
    m_flags &= ~0x02;

    uint32_t* pSub = m_subObject;
    if (pSub != nullptr && pSub != (uint32_t*)0x48) {
        // Call some function with argument 0 (likely a destructor check or debug output)
        FUN_00791a70(0);
    }

    // If sub-object pointer is non-null, call its release function and nullify it
    if (m_subObject != nullptr) {
        FUN_004daf90(m_subObject);  // likely a destructor or cleanup on the sub-object
        m_subObject = nullptr;
    }

    // Zero out field at +0x10
    m_field4 = 0;

    // Fill subsequent fields with sentinel values for debugging (freed memory markers)
    m_sentinel1 = 0xbadbadba;
    m_sentinel2 = 0xbeefbeef;
    m_sentinel3 = 0xeac15a55;
    m_sentinel4 = 0x91100911;

    // Clear bit 4 (value 0x08) in m_flags
    m_flags &= ~0x08;
}
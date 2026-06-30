// FUNC_NAME: BaseSimObject::constructor
// Address: 0x00549b60
// Role: Initializes base simulation object with identifier, value, and flag.
// Structure layout deduced from byte/word/dword accesses at known offsets.
// Offsets: +0x00: id, +0x04: handle (-1), +0x08: value, +0x0C: flags0,
// +0x10: byte0, +0x11: byte1, +0x12: word0, +0x14: flags1, +0x18: byte2,
// +0x19: byte3, +0x1A: word1, +0x1C: flags2, ... +0x48: globalPtr.

// Forward declaration of an external global used as default data.
extern uint32_t DAT_00e2eff4;

// Global initialization function – likely registers class or performs engine‑wide setup.
extern void FUN_00a64fd0();

class BaseSimObject {
public:
    // Core fields
    uint32_t m_id;          // +0x00
    int32_t m_handle;       // +0x04 (always -1 after init)
    uint32_t m_value;       // +0x08
    uint32_t m_flags0;      // +0x0C

    // Byte/word flags (likely flags for state, network, etc.)
    uint8_t m_byte0;        // +0x10
    uint8_t m_byte1;        // +0x11
    uint16_t m_word0;       // +0x12
    uint32_t m_flags1;      // +0x14
    uint8_t m_byte2;        // +0x18
    uint8_t m_byte3;        // +0x19 (overwritten twice)
    uint16_t m_word1;       // +0x1A
    uint32_t m_flags2;      // +0x1C
    // ... additional fields up to +0x48
    uint32_t m_globalData;  // +0x48 (index 0x12 * 4)
};

__thiscall BaseSimObject* BaseSimObject::constructor(BaseSimObject* this,
                                                      uint32_t someId,
                                                      uint32_t someValue,
                                                      uint8_t someFlag)
{
    this->m_value   = someValue;
    this->m_id      = someId;
    this->m_handle  = -1;
    this->m_byte0   = 0;
    this->m_flags0  = 0;
    this->m_flags1  = 0;
    this->m_byte2   = someFlag;
    this->m_flags2  = 0;
    this->m_word1   = 0;
    this->m_byte3   = 0x7f;               // initial value

    FUN_00a64fd0();                       // engine‑wide initialization

    this->m_globalData = DAT_00e2eff4;    // store pointer to shared data
    this->m_byte3   = 0xec;               // override with new value
    this->m_word0   = 0;
    this->m_byte1   = 0;

    return this;
}
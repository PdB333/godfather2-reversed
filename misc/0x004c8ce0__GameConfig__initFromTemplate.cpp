// FUNC_NAME: GameConfig::initFromTemplate
// Reconstructed constructor for a game configuration structure.
// Address: 0x004c8ce0
// Initializes a large config object by setting header fields, copying a template,
// zeroing a large buffer, and initializing two sub-objects.

#include <cstring>

// Assuming these globals are defined elsewhere
extern uint32_t DAT_00e2eff4;

struct GameConfig {
    // +0x00: uint32_t m_version;          // initially 0
    // +0x04: uint8_t m_flags;             // initially 0
    // +0x05-[0x0F]: padding? (zeroed later)
    // +0x10: uint8_t m_mainBuffer[0x280]; // zeroed (offsets 0x10 to 0x290)
    // +0x290: uint32_t m_header0;         // initially 0
    // +0x294: uint32_t m_header1;         // from global1
    // +0x298: uint32_t m_header2;         // from global1
    // +0x29C: uint32_t m_header3;         // from global1
    // +0x2A0: uint32_t m_header4;         // from global2
    // +0x2A4: uint32_t m_header5;         // from global1
    // +0x2A8: uint32_t m_header6;         // 0
    // +0x2AC: uint32_t m_header7;         // 0
    // +0x2B0: uint32_t m_magic1;          // 1
    // +0x2B4: uint32_t m_magic2;          // 0xbadbadba
    // +0x2B8: uint32_t m_magic3;          // 0xbeefbeef
    // +0x2BC: uint32_t m_magic4;          // 0xeac15a55
    // +0x2C0: uint32_t m_magic5;          // 0x91100911
    // +0x2C4: uint8_t m_unusedByte;       // 0
    // +0x2C8: uint32_t m_maxValue;        // 96000
    // +0x2CC: uint32_t m_templateData[44]; // copied from source (176 bytes)
    // +0x2DC: uint32_t m_subObj1;         // handle from FUN_004dafd0
    // +0x2FC: uint32_t m_subObj2;         // handle from FUN_004dafd0
    //          struct is larger; exact size unknown but at least 0x30C bytes
};

// Forward declarations
void FUN_004c8c10();          // global config init?
uint32_t FUN_004dafd0(void* addr); // creates sub-object, returns handle

// Constructor-like function
GameConfig* __thiscall GameConfig::initFromTemplate(GameConfig* this, uint32_t* source)
{
    uint32_t globalVal1 = DAT_00e2eff4;              // from global at 0x00e2eff4
    uint32_t globalVal2 = DAT_00e2b1a4;              // from global at 0x00e2b1a4

    // Initialize header fields
    this->m_version = 0;                             // +0x00
    *(uint8_t*)((uint8_t*)this + 4) = 0;            // +0x04 byte
    this->m_header0 = 0;                             // +0x290
    this->m_header1 = globalVal1;                    // +0x294
    this->m_header2 = globalVal1;                    // +0x298
    this->m_header3 = globalVal1;                    // +0x29C
    this->m_header4 = globalVal2;                    // +0x2A0
    this->m_header5 = globalVal1;                    // +0x2A4
    this->m_header6 = 0;                             // +0x2A8
    this->m_header7 = 0;                             // +0x2AC
    this->m_maxValue = 96000;                        // +0x2C8
    this->m_magic1 = 1;                              // +0x2B0
    this->m_magic2 = 0xbadbadba;                     // +0x2B4
    this->m_magic3 = 0xbeefbeef;                     // +0x2B8
    this->m_magic4 = 0xeac15a55;                     // +0x2BC
    this->m_magic5 = 0x91100911;                     // +0x2C0
    *(uint8_t*)((uint8_t*)this + 0x2C4) = 0;        // +0x2C4 byte

    // Global initialization step
    FUN_004c8c10();

    // Copy 44 dwords (176 bytes) from source to m_templateData
    uint32_t* dest = &this->m_templateData[0];       // +0x2CC
    for (int i = 0; i < 44; i++) {
        *dest++ = *source++;
    }

    // Zero out the large main buffer (offset 0x10 to 0x290)
    memset((uint8_t*)this + 0x10, 0, 0x280);

    // Initialize two sub-objects and store their handles
    // The addresses point to the sub-object locations within this
    uint32_t handle1 = FUN_004dafd0((uint8_t*)this + 0x2DC);
    this->m_subObj1 = handle1;                       // stored at +0x08 (offset 8)

    uint32_t handle2 = FUN_004dafd0((uint8_t*)this + 0x2FC);
    this->m_subObj2 = handle2;                       // stored at +0x0C (offset 12)

    return this;
}
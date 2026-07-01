// Xbox PDB: EARS_Apt_UICredits_UICredits
// FUNC_NAME: CreditsManager::CreditsManager

#include <cstdint>

// Forward declarations of assumed external functions
void __fastcall sub_5bf9b0(); // base class constructor or global init
void __fastcall setStringField(uint32_t *field, const char *str); // FUN_00408980
void __fastcall registerEventHandler(uint32_t *vtablePtr, uint32_t *field, uint32_t flags); // FUN_00408900

// Global singleton pointer
CreditsManager *g_CreditsManager; // DAT_0113006c

// Function: CreditsManager constructor at 0x00926070
// Initializes credits playback state and message handlers.
CreditsManager *__thiscall CreditsManager::CreditsManager(CreditsManager *this)
{
    uint32_t *vtableBase;
    uint32_t *fieldPtr;
    uint32_t val1, val2, val3;

    sub_5bf9b0(); // base constructor / global setup

    // Set primary vtable pointer at +0x4C (0x13 * 4)
    this->vtable0 = &CREDITS_VTABLE_1; // PTR_FUN_00e2f19c

    // Load global configuration values
    val1 = DAT_00d5ef88; // some default time/color
    val2 = _DAT_00d5780c; // another default
    val3 = DAT_00d5f18c; // etc.

    this->field_0x54 = 0;       // +0x54 (0x15)
    this->field_0x50 = 1;       // +0x50 (0x14)
    this->vtable1 = &CREDITS_VTABLE_2; // +0x58 (0x16) e.g. PTR_LAB_00d87738

    // Set global singleton reference
    g_CreditsManager = this;

    // Store additional configuration
    this->field_0x74 = val1;                 // +0x74 (0x1d)
    this->field_0x78 = _DAT_00d5cf70;        // +0x78 (0x1e)
    this->field_0x7c = DAT_00d5f18c;         // +0x7c (0x1f)
    this->field_0x80 = DAT_00d58cbc;         // +0x80 (0x20)
    val1 = DAT_00d5ddec;                     // another default
    this->field_0x5c = 0;                    // +0x5c (0x17)
    this->field_0x60 = 0;                    // +0x60 (0x18)
    this->field_0x6c = val2;                 // +0x6c (0x1b)
    this->field_0x70 = val2;                 // +0x70 (0x1c)
    this->field_0x88 = 0;                    // +0x88 (0x22)

    // Set multiple vtable pointers (multiple inheritance / interface tables)
    this->baseVtable = &CREDITS_VTABLE_3;    // +0x00 (0x0) PTR_FUN_00d87778
    this->vtable4 = &CREDITS_VTABLE_4;       // +0x10 (0x4) PTR_LAB_00d87750
    vtableBase = reinterpret_cast<uint32_t*>(&this->vtable0);
    *vtableBase = &CREDITS_VTABLE_5;         // overwrite +0x4C with PTR_LAB_00d87740
    this->vtable1 = &CREDITS_VTABLE_6;       // +0x58 again? Actually +0x58 already set, but reassign PTR_LAB_00d8773c

    this->field_0x64 = 0;                    // +0x64 (0x19)
    this->field_0x68 = 0;                    // +0x68 (0x1a)
    this->field_0x84 = val1;                 // +0x84 (0x21)
    this->field_0x8c = 0;                    // +0x8c (0x23)

    // Initialize word fields
    *reinterpret_cast<uint16_t*>(&this->field_0x90) = 0;   // +0x90 (0x24) word
    *reinterpret_cast<uint16_t*>(reinterpret_cast<uint32_t>(this) + 0x92) = 0; // +0x92 byte offset, but treated as word? Actually +0x92 is within same dword? Ghidra shows ambiguous; we'll do uint16_t at offset 0x90 and 0x92
    this->field_0x94 = 0;                    // +0x94 (0x25)
    *reinterpret_cast<uint16_t*>(&this->field_0x98) = 0;   // +0x98 (0x26)
    *reinterpret_cast<uint16_t*>(reinterpret_cast<uint32_t>(this) + 0x9a) = 0; // +0x9a
    this->field_0x9c = 0;                    // +0x9c (0x27)
    *reinterpret_cast<uint16_t*>(&this->field_0xa0) = 0;   // +0xa0 (0x28)
    *reinterpret_cast<uint16_t*>(reinterpret_cast<uint32_t>(this) + 0xa2) = 0; // +0xa2

    // Set message field and register message handlers
    fieldPtr = &this->field_0x8c;            // +0x23 slot
    this->field_0xa4 = val2;                 // +0xa4 (0x29) – note: using val2 from earlier
    this->field_0xa8 = 0;                    // +0xa8 (0x2a)
    this->field_0xb0 = 0;                    // +0xb0 (0x2c)
    this->field_0x1380 = 0;                  // +0x1380 (0x4e6)
    this->field_0x13a8 = 0;                  // +0x13a8 (0x4ea)
    val2 = DAT_00d5ccf8;                     // another config value
    this->field_0xac = DAT_00d5ef84;         // +0xac (0x2b)
    this->field_0x1380_alt = 0;              // +0x1380? Actually 0x4e0:0x4e1:0x4e2:0x4e3:0x4e4: these are separate fields, but we'll treat as sequential
    // Initialize many flag/state fields
    this->flag0 = 0;          // +0x1380 (0x4e0)
    this->flag1 = 0;          // +0x1384 (0x4e1)
    this->flag2 = 0;          // +0x1388 (0x4e2)
    this->flag3 = 0;          // +0x138c (0x4e3)
    this->flag4 = 0;          // +0x1390 (0x4e4)
    this->flag5 = 1;          // +0x1394 (0x4e5)
    this->flag6 = 0;          // +0x1398 (0x4e7)
    this->flag7 = 0;          // +0x13a0 (0x4e8)
    *reinterpret_cast<uint8_t*>(&this->flag8) = 0;   // +0x13a4 (0x4e9) byte
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uint32_t>(this) + 0x13a5) = 0; // +0x13a5 byte
    this->field_0x13ac = val2;               // +0x13ac (0x4eb)
    *reinterpret_cast<uint8_t*>(&this->field_0x13b0) = 0; // +0x13b0 (0x4ec) byte
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uint32_t>(this) + 0x13b1) = 0; // +0x13b1 byte
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uint32_t>(this) + 0x13b2) = 0; // +0x13b2 byte

    // Set string fields for message identifiers
    setStringField(fieldPtr, "iMsgStartCredits");            // set field at +0x8c
    setStringField(&this->field_0x94, "iMsgCreditsHaveFinished"); // set field at +0x94 (0x25)
    setStringField(&this->field_0x9c, "play_credits_movie");     // set field at +0x9c (0x27)

    // Register message handlers with the object's vtable
    if (*fieldPtr != 0) {
        registerEventHandler(&this->vtable0, fieldPtr, 0x8000); // register with first vtable
    }
    if (DAT_01130074 != 0) { // some global handler pointer?
        registerEventHandler(&this->vtable0, &DAT_01130074, 0x8000);
    }

    return this;
}
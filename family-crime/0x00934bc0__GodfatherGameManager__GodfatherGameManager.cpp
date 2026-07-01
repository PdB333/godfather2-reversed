// FUNC_NAME: GodfatherGameManager::GodfatherGameManager

#include <cstdint>

// Forward declarations (actual function addresses unknown)
void __fastcall sub_5bf9b0();  // Some init routine
void __fastcall sub_6a2bb0();  // Some init routine

// Global singleton pointer
GodfatherGameManager* g_pGodfatherGameManager = nullptr; // DAT_01129928

// Global flags (bitmask)
uint32_t g_gameManagerFlags = 0; // DAT_01130590

class GodfatherGameManager {
public:
    // Vtable pointer at +0x00
    void** vtable;
    // +0x04: some other function pointer?
    void* field_4;
    // ... many unknown fields ...
    // +0x4C (0x13 * 4): vtable-like pointer
    void* field_4C;
    // +0x50 (0x14 * 4): int
    int32_t field_50;
    // +0x54 (0x15 * 4): int
    int32_t field_54;
    // +0x58 (0x16 * 4): pointer
    void* field_58;
    // +0x5C (0x17 * 4): int (set to 5)
    int32_t field_5C;
    // +0x60 (0x18 * 4): int
    int32_t field_60;
    // +0x68 (0x1A * 4): int
    int32_t field_68;
    // +0x6C (0x1B * 4): int
    int32_t field_6C;
    // +0x70 (0x1C * 4): byte
    uint8_t field_70;
    // +0x71: byte
    uint8_t field_71;
    // +0x74 (0x1D * 4): int
    int32_t field_74;
    // +0x78 (0x1E * 4): int
    int32_t field_78;
    // +0x7C (0x1F * 4): int
    int32_t field_7C;
    // +0x80 (0x20 * 4): int
    int32_t field_80;
    // +0x84 (0x21 * 4): int
    int32_t field_84;
    // +0x88 (0x22 * 4): int
    int32_t field_88;
    // +0x8C (0x23 * 4): int
    int32_t field_8C;
    // +0x90 (0x24 * 4): int
    int32_t field_90;
    // +0x94 (0x25 * 4): int
    int32_t field_94;
    // +0x98 (0x26 * 4): int
    int32_t field_98;
    // +0x9C (0x27 * 4): int
    int32_t field_9C;
    // +0xA0 (0x28 * 4): int
    int32_t field_A0;
    // +0xA4 (0x29 * 4): int
    int32_t field_A4;
    // +0xA8 (0x2A * 4): int
    int32_t field_A8;
    // +0xAC (0x2B * 4): byte
    uint8_t field_AC;
    // +0xB0 (0x2C * 4): ??? Not set
    // +0xB4 (0x2D * 4): byte (set to 0 after sub_6a2bb0 call)
    uint8_t field_B4;
};

// Constructor at 0x00934bc0
void __fastcall GodfatherGameManager_ctor(GodfatherGameManager* thisObj) {
    sub_5bf9b0(); // Base initialization

    // Set vtable-like pointers (multiple stages)
    thisObj->field_4C = &g_vtable_00e2f19c; // Initial placeholder
    thisObj->field_50 = 1;
    thisObj->field_54 = 0;
    thisObj->field_58 = &g_label_00d89644;

    // Store global singleton
    g_pGodfatherGameManager = thisObj;

    // Assign main vtable (first pointer)
    thisObj->vtable = &g_vtable_00d89680;
    // Second vtable-like field
    thisObj->field_4 = &g_label_00d8965c;

    // Overwrite earlier pointers
    thisObj->field_4C = &g_label_00d8964c;
    thisObj->field_58 = &g_label_00d89648;

    // Initialize numeric fields
    thisObj->field_5C = 5;
    thisObj->field_60 = 0;
    thisObj->field_68 = 0;
    thisObj->field_6C = 0;
    thisObj->field_70 = 0;
    thisObj->field_71 = 0;
    thisObj->field_74 = 0;
    thisObj->field_78 = 0;
    thisObj->field_7C = 0;
    thisObj->field_80 = 0;
    thisObj->field_84 = 0;
    thisObj->field_88 = 0;
    thisObj->field_8C = 0;
    thisObj->field_90 = 0;
    thisObj->field_94 = 0;
    thisObj->field_98 = 0;
    thisObj->field_9C = 0;
    thisObj->field_A0 = 0;
    thisObj->field_A4 = 0;
    thisObj->field_A8 = 0;
    thisObj->field_AC = 0;

    // Second sub-initializer
    sub_6a2bb0();

    // Post-init field
    thisObj->field_B4 = 0;

    // Clear some global flags (bits 0,1,3,4,5,8? Actually 0xfffdffe9 = ~0x00020016)
    g_gameManagerFlags &= 0xfffdffe9;
}
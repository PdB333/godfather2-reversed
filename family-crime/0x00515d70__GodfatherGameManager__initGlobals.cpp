// FUNC_NAME: GodfatherGameManager::initGlobals
// Address: 0x00515d70
// Purpose: Initializes static global state (likely crime/family manager data)
// The structure base is at 0x012191e0, size 0x60+ bytes.
// External initial values: DAT_00e2b1a4, DAT_00e2eb58

#include <cstdint>

// Global references to initial values (from other modules)
extern int32_t g_initialCount;      // DAT_00e2b1a4
extern int32_t g_initialFlag;       // DAT_00e2eb58

void GodfatherGameManager::initGlobals()
{
    // Zero-initialize first 8 words (offsets 0x00-0x1C)
    *reinterpret_cast<int32_t*>(0x012191e0) = 0; // +0x00: field_00
    *reinterpret_cast<int32_t*>(0x012191e4) = 0; // +0x04: field_04
    *reinterpret_cast<int32_t*>(0x012191e8) = 0; // +0x08: field_08
    *reinterpret_cast<int32_t*>(0x012191ec) = 0; // +0x0C: field_0C
    *reinterpret_cast<int32_t*>(0x012191f0) = 0; // +0x10: field_10
    *reinterpret_cast<int32_t*>(0x012191f4) = 0; // +0x14: field_14
    *reinterpret_cast<int32_t*>(0x012191f8) = 0; // +0x18: field_18
    *reinterpret_cast<int32_t*>(0x012191fc) = 0; // +0x1C: field_1C

    // Set triple identical values from g_initialCount
    *reinterpret_cast<int32_t*>(0x01219200) = g_initialCount; // +0x20: field_20
    *reinterpret_cast<int32_t*>(0x01219204) = g_initialCount; // +0x24: field_24
    *reinterpret_cast<int32_t*>(0x01219208) = g_initialCount; // +0x28: field_28

    // Zero-initialize next words (offsets 0x2C-0x40)
    *reinterpret_cast<int32_t*>(0x0121920c) = 0; // +0x2C: field_2C
    *reinterpret_cast<int32_t*>(0x01219210) = 0; // +0x30: field_30
    *reinterpret_cast<int32_t*>(0x01219214) = 0; // +0x34: field_34
    *reinterpret_cast<int32_t*>(0x01219218) = 0; // +0x38: field_38
    *reinterpret_cast<int32_t*>(0x0121921c) = 0; // +0x3C: field_3C
    *reinterpret_cast<int32_t*>(0x01219220) = 0; // +0x40: field_40

    // Set double identical values from g_initialFlag
    *reinterpret_cast<int32_t*>(0x01219224) = g_initialFlag; // +0x44: field_44
    *reinterpret_cast<int32_t*>(0x01219228) = g_initialFlag; // +0x48: field_48

    // Zero-initialize remaining fields
    *reinterpret_cast<int32_t*>(0x0121922c) = 0; // +0x4C: field_4C
    *reinterpret_cast<int32_t*>(0x01219230) = 0; // +0x50: field_50
    *reinterpret_cast<int32_t*>(0x01219240) = 0; // +0x60: field_60 (offset may be padding)
}
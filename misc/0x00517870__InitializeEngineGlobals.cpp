// FUNC_NAME: InitializeEngineGlobals
// Address: 0x00517870
// Role: Initializes the global engine state structure (g_engineGlobals) with default values from other engine globals.

// Forward declarations of the referenced global variables (likely defined elsewhere)
extern uint32_t DAT_00e39f98;   // Some engine constant/pointer
extern uint32_t DAT_00e2b1a4;   // Another engine constant/pointer (repeated many times)
extern uint32_t DAT_00e445ac;   // Yet another engine constant/pointer

// Definition of the engine global structure (size: 0x48 bytes, base address 0x012192b0)
// Offsets are relative to the base (0x012192b0)
struct EngineGlobals {
    uint32_t field_0x00;    // +0x00: DAT_00e2b1a4
    uint32_t field_0x04;    // +0x04: DAT_00e2b1a4
    uint32_t field_0x08;    // +0x08: DAT_00e2b1a4
    uint32_t field_0x0C;    // +0x0C: DAT_00e2b1a4
    uint32_t field_0x10;    // +0x10: 0
    uint32_t field_0x14;    // +0x14: 0
    uint32_t field_0x18;    // +0x18: 0
    uint32_t field_0x1C;    // +0x1C: DAT_00e2b1a4
    uint32_t field_0x20;    // +0x20: DAT_00e39f98
    uint32_t field_0x24;    // +0x24: DAT_00e39f98
    uint32_t field_0x28;    // +0x28: DAT_00e445ac
    uint32_t field_0x2C;    // +0x2C: 0
    uint32_t field_0x30;    // +0x30: 0
    uint32_t field_0x34;    // +0x34: 0
    uint32_t field_0x38;    // +0x38: DAT_00e2b1a4
    uint32_t field_0x3C;    // +0x3C: DAT_00e2b1a4
    uint32_t field_0x40;    // +0x40: 0
    uint32_t field_0x44;    // +0x44: 0
};

// Global instance of the engine state structure
EngineGlobals g_engineGlobals;

void InitializeEngineGlobals()
{
    // Assign fields from engine constants/globals.
    // Multiple fields are initialized to the same values, suggesting a common default state.

    g_engineGlobals.field_0x20 = DAT_00e39f98;  // +0x20: Copy of engine pointer/constant
    g_engineGlobals.field_0x24 = DAT_00e39f98;  // +0x24: Second copy of same value

    // Zero-initialize three sequential fields (likely a small sub-structure or flags)
    g_engineGlobals.field_0x10 = 0;
    g_engineGlobals.field_0x14 = 0;
    g_engineGlobals.field_0x18 = 0;

    // Assign many fields to DAT_00e2b1a4 (common default)
    g_engineGlobals.field_0x1C = DAT_00e2b1a4;  // +0x1C
    g_engineGlobals.field_0x00 = DAT_00e2b1a4;  // +0x00
    g_engineGlobals.field_0x04 = DAT_00e2b1a4;  // +0x04
    g_engineGlobals.field_0x08 = DAT_00e2b1a4;  // +0x08
    g_engineGlobals.field_0x0C = DAT_00e2b1a4;  // +0x0C

    // Assign one field to another distinct constant
    g_engineGlobals.field_0x28 = DAT_00e445ac;  // +0x28: Different engine value

    // Zero-initialize remaining fields
    g_engineGlobals.field_0x2C = 0;
    g_engineGlobals.field_0x30 = 0;
    g_engineGlobals.field_0x34 = 0;
    g_engineGlobals.field_0x40 = 0;
    g_engineGlobals.field_0x44 = 0;

    // Assign last pair to DAT_00e2b1a4 again
    g_engineGlobals.field_0x38 = DAT_00e2b1a4;  // +0x38
    g_engineGlobals.field_0x3C = DAT_00e2b1a4;  // +0x3C

    return;
}
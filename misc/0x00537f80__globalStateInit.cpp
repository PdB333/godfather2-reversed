// FUNC_NAME: globalStateInit
// Initializes a large global state structure at 0x0121b740.
// Called once at startup after subsystem init (FUN_006126d0).
// Zeros most fields, sets some to a default constant (likely an identity quaternion or null vector).

#include <cstdint>

// Forward declaration, the actual structure layout is not fully known.
// This function initializes the block at g_globalStateBase.
// Many fields are individually zeroed; some are set to a constant (DAT_00e2b1a4).
// The pattern suggests an array of 12 structs (each 0x28 bytes?) followed by more fields.

extern void FUN_006126d0(); // engine-wide initializer

// Globals defined in .data or .bss
extern uint32_t DAT_00e2b1a4; // default constant, possibly NaN or identity quaternion
extern uint32_t DAT_0121b740; // base of the global state structure
extern uint32_t DAT_0121b740; // same, used as pointer below

// The function returns the base address of the initialized structure.
uint32_t* globalStateInit(void)
{
    // Call top-level subsystem initializer (likely memory, threading, etc.)
    FUN_006126d0();

    // Zero out a series of 32-bit fields at consecutive addresses.
    // Based on offsets, these look like part of a larger struct or array.
    // Using the observed pattern: many zeros, then some set to DAT_00e2b1a4.
    
    // Offsets from DAT_0121b740:
    // +0x094? Actually, we see specific global addresses; let's map them to relative offsets.
    // For clarity, we will reference the globals directly as in the original code.
    
    // First group: zeros for 6 fields (0x0121bbd4, 0x0121bbdc, 0x0121bbe4, 0x0121bbec, 0x0121bbf4, 0x0121bbfc)
    _DAT_0121bbd4 = 0;
    _DAT_0121bbdc = 0;
    _DAT_0121bbe4 = 0;
    _DAT_0121bbec = 0;
    _DAT_0121bbf4 = 0;
    _DAT_0121bbfc = 0;
    
    // Then set the vtable-like pointer at 0x0121b740 to a static table
    DAT_0121b740 = &PTR_LAB_00e38b64;  // likely vtable or default function table
    
    // Zero more fields
    DAT_0121bbb0 = 0;
    DAT_0121bbb4 = 0;
    DAT_0121bc0c = 0;
    DAT_0121bbbc = 0;
    DAT_0121bbc0 = 0;
    DAT_0121bbc4 = 0;
    DAT_0121bbc8 = 0;
    DAT_0121bbcc = 0;
    DAT_0121bbd0 = 0;
    DAT_0121b7e4 = 0;
    DAT_0121b820 = 0;
    _DAT_0121b860 = 0;
    DAT_0121b8c0 = 0;
    DAT_0121b8c4 = 0;
    _DAT_0121b900 = 0;
    DAT_0121b970 = 0;
    DAT_0121b990 = 0;
    _DAT_0121b880 = 0;
    _DAT_0121b884 = 0;
    _DAT_0121b888 = 0;
    _DAT_0121b88c = 0;
    _DAT_0121b7f0 = 0;
    _DAT_0121b7f4 = 0;
    _DAT_0121b7f8 = 0;
    
    // Now fields that are set to the default constant (DAT_00e2b1a4)
    _DAT_0121b7fc = DAT_00e2b1a4;
    _DAT_0121b800 = DAT_00e2b1a4;
    _DAT_0121b804 = DAT_00e2b1a4;
    _DAT_0121b808 = DAT_00e2b1a4;
    _DAT_0121b80c = 0;
    _DAT_0121b810 = 0;
    _DAT_0121b814 = 0;
    _DAT_0121b818 = 0;
    _DAT_0121b81c = DAT_00e2b1a4;
    _DAT_0121b850 = 0;
    _DAT_0121b854 = 0;
    _DAT_0121b858 = 0;
    _DAT_0121b85c = DAT_00e2b1a4;
    _DAT_0121b890 = 0;
    _DAT_0121b894 = 0;
    _DAT_0121b898 = 0;
    _DAT_0121b89c = DAT_00e2b1a4;
    _DAT_0121b8a0 = 0;
    _DAT_0121b8a4 = 0;
    _DAT_0121b8a8 = 0;
    _DAT_0121b8ac = 0;
    _DAT_0121b8d0 = 0;
    _DAT_0121b8d4 = 0;
    _DAT_0121b8d8 = 0;
    _DAT_0121b8dc = DAT_00e2b1a4;
    _DAT_0121b8e0 = 0;
    _DAT_0121b8e4 = 0;
    _DAT_0121b8e8 = 0;
    _DAT_0121b8ec = 0;
    _DAT_0121b8f0 = 0;
    _DAT_0121b8f4 = 0;
    _DAT_0121b8f8 = 0;
    _DAT_0121b8fc = 0;
    _DAT_0121b980 = 0;
    _DAT_0121b984 = 0;
    _DAT_0121b988 = 0;
    _DAT_0121b98c = 0;
    _DAT_0121b910 = 0;
    _DAT_0121b914 = 0;
    _DAT_0121b918 = 0;
    _DAT_0121b91c = DAT_00e2b1a4;
    _DAT_0121b930 = 0;
    _DAT_0121b934 = 0;
    _DAT_0121b938 = 0;
    _DAT_0121b93c = DAT_00e2b1a4;
    _DAT_0121b950 = 0;
    _DAT_0121b954 = 0;
    _DAT_0121b958 = 0;
    _DAT_0121b95c = DAT_00e2b1a4;
    _DAT_0121b92c = 0;
    _DAT_0121b928 = 0;
    _DAT_0121b924 = 0;
    _DAT_0121b920 = 0;
    _DAT_0121b94c = 0;
    _DAT_0121b948 = 0;
    _DAT_0121b944 = 0;
    _DAT_0121b940 = 0;
    _DAT_0121b96c = 0;
    _DAT_0121b968 = 0;
    _DAT_0121b964 = 0;
    _DAT_0121b960 = 0;

    // Return the base pointer of the initialized state
    return &DAT_0121b740;
}
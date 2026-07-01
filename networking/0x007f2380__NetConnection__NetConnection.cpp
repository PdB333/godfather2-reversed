// FUNC_NAME: NetConnection::NetConnection

#include <cstdint>

// Represents a network connection packet buffer (likely from TNL)
class NetConnection {
public:
    // Vtable pointers for multiple inheritance
    void* vtable0;   // +0x00
    void* vtable1;   // +0x04

    // Flags / state
    uint32_t flags0; // +0x08
    uint32_t flags1; // +0x0C

    // Debug magic numbers (set and then cleared)
    uint32_t magicBad;   // +0x24 (0xbadbadba)
    uint32_t magicBeef;  // +0x28 (0xbeefbeef)
    uint32_t magicCafe;  // +0x2C (0xeac15a55)
    uint32_t magic911;   // +0x30 (0x91100911)

    // Zero fields after magic
    uint32_t zero1;      // +0x34
    uint32_t zero2;      // +0x38
    uint32_t zero3;      // +0x3C

    // Connection parameters from global defaults
    uint32_t paramA;     // +0x40
    uint32_t paramB;     // +0x44
    uint32_t paramC;     // +0x48
    uint32_t paramD;     // +0x4C
    uint32_t paramE;     // +0x50
    uint32_t paramF;     // +0x54
    uint32_t paramG;     // +0x58
    uint32_t paramH;     // +0x5C
    uint32_t paramI;     // +0x60
    uint32_t paramJ;     // +0x64
    uint32_t paramK;     // +0x68
    uint32_t paramL;     // +0x6C
    uint32_t paramM;     // +0x70

    // Constructor
    __fastcall NetConnection(uint32_t* param_1) {
        // Store the pointer globally for debugging
        DAT_0112bb50 = param_1;

        // Zero out flags
        param_1[2] = 0; // flags0
        param_1[3] = 0; // flags1

        // Set the second vtable pointer early (likely for a base interface)
        param_1[1] = &PTR_FUN_00e30eec; // vtable1

        // Zero out the first batch of fields (indices 4-8)
        param_1[4] = 0;
        param_1[5] = 0;
        param_1[6] = 0;
        param_1[7] = 0;
        param_1[8] = 0;

        // Write debug magic numbers (for later validation?)
        param_1[9]  = 0xbadbadba;  // magicBad
        param_1[10] = 0xbeefbeef;  // magicBeef
        param_1[11] = 0xeac15a55;  // magicCafe
        param_1[12] = 0x91100911;  // magic911

        // Zero out some fields that follow the magic
        param_1[13] = 0;  // zero1
        param_1[14] = 0;  // zero2
        param_1[15] = 0;  // zero3

        // Immediately clear the magic numbers (leaving zeros)
        param_1[12] = 0;  // magic911
        param_1[11] = 0;  // magicCafe
        param_1[10] = 0;  // magicBeef
        param_1[9]  = 0;  // magicBad

        // Fetch global defaults
        uint32_t uVar1 = DAT_00e445ac; // some global
        uint32_t uVar2 = DAT_00d5eee4; // another global

        // Assign connection parameters from globals
        param_1[0x10] = uVar1;          // paramA
        param_1[0x12] = uVar1;          // paramC
        param_1[0x17] = _DAT_00d5780c;  // paramG
        param_1[0x18] = DAT_00d5f520;   // paramH

        uVar1 = _DAT_00d5cf70;          // another global

        param_1[0x11] = uVar2;          // paramB
        param_1[0x13] = uVar2;          // paramD
        param_1[0x14] = uVar2;          // paramE
        param_1[0x15] = uVar2;          // paramF
        param_1[0x16] = uVar2;          // paramF (repeated? likely a different field)
        param_1[0x19] = uVar1;          // paramI

        uVar1 = DAT_00d58cbc;           // another global
        param_1[0x1b] = uVar2;          // paramK
        uVar2 = DAT_00d5ef70;           // another global

        // Set the primary vtable pointers (done last to ensure object is fully constructed)
        param_1[0] = &PTR_FUN_00d70288; // vtable0
        param_1[1] = &PTR_LAB_00d70278; // vtable1 overwritten

        param_1[0x1a] = uVar1;          // paramJ
        param_1[0x1c] = uVar2;          // paramL
    }
};
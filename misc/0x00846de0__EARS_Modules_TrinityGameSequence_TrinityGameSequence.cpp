// Xbox PDB: EARS_Modules_TrinityGameSequence_TrinityGameSequence
// FUNC_NAME: SequenceInstance::constructor

// SequenceInstance constructor (0x00846de0).
// Initializes sequence instance object with vtable pointers, debug markers, flags, and data buffer.
// Part of EA EARS engine sequence system.

#include <cstdint>

class SequenceInstance { // size > 0x144 bytes
public:
    // Constructor (__thiscall)
    // param_2: sequence type identifier
    SequenceInstance(int param_2) {
        // Call base class constructor (FUN_0046c590)
        BaseClass::BaseClass(param_2); // base constructor at 0x0046c590

        // Set up multiple vtable pointers (multiple inheritance)
        *(void**)(this + 0x50) = &PTR_LAB_00e32854;   // offset 0x50
        *(void**)this = &PTR_LAB_00d74c4c;             // primary vtable
        *(void**)(this + 0x3c) = &PTR_LAB_00d74c3c;   // offset 0x3c
        *(void**)(this + 0x48) = &PTR_LAB_00d74c38;   // offset 0x48
        *(void**)(this + 0x50) = &PTR_LAB_00d74c34;   // override offset 0x50

        // Clear an array of 7 8-byte entries (0x54 to 0x8b)
        for (int i = 0; i < 7; ++i) {
            *(int*)(this + 0x54 + i * 8) = 0;           // int at offset
            *(int16_t*)(this + 0x58 + i * 8) = 0;       // first short
            *(int16_t*)(this + 0x5a + i * 8) = 0;       // second short
        }

        // Set debug magic markers (first block: offset 0x8c - 0xab)
        *(int*)(this + 0x8c) = 0xbadbadba;
        *(int*)(this + 0x90) = 0xbeefbeef;
        *(int*)(this + 0x94) = 0xeac15a55;
        *(int*)(this + 0x98) = 0x91100911;
        *(int*)(this + 0x9c) = 0xbadbadba;
        *(int*)(this + 0xa0) = 0xbeefbeef;
        *(int*)(this + 0xa4) = 0xeac15a55;
        *(int*)(this + 0xa8) = 0x91100911;

        // More zeroing of fields
        *(int*)(this + 0xbc) = 0;
        *(int*)(this + 0xcc) = 0;
        *(int*)(this + 0xdc) = 0;
        *(int*)(this + 0xec) = _DAT_00d5780c;  // copy global value to offset 0xec
        *(int*)(this + 0xf0) = 0;
        *(int*)(this + 0xf4) = 0;
        *(int*)(this + 0xf8) = 0;
        *(int*)(this + 0x100) = 0;
        *(int*)(this + 0x104) = 0;
        *(int*)(this + 0x108) = 0;
        *(int*)(this + 0x10c) = 0;
        *(int*)(this + 0x110) = 0;
        *(int*)(this + 0x114) = 0;

        // Set flags: bits at offset 0x118
        *(int*)(this + 0x118) = (*(int*)(this + 0x118) & 0xfffe0040) | 0x40;

        // Zero more fields
        *(int*)(this + 0x120) = 0;
        *(int*)(this + 0x124) = 0;
        *(int*)(this + 0x128) = 0;
        *(int*)(this + 0x12c) = 0;
        *(int*)(this + 0x130) = 0;

        // Second set of debug magic markers (offset 0x134 - 0x143)
        *(int*)(this + 0x134) = 0xbadbadba;
        *(int*)(this + 0x138) = 0xbeefbeef;
        *(int*)(this + 0x13c) = 0xeac15a55;
        *(int*)(this + 0x140) = 0x91100911;

        // Zero some more at offset 0x148, 0x14c, 0x150, 0x152 (partial word)
        *(int*)(this + 0x148) = 0;
        *(int*)(this + 0x14c) = 0;
        *(int*)(this + 0x150) = 0;
        *(int16_t*)(this + 0x154) = 0;

        // Internal initialization calls
        FUN_008463f0(0x20);   // unknown init
        FUN_00846d10(8);      // unknown init
        FUN_007e25b0(0x10);   // unknown init

        // Clear debug markers after initialization
        *(int*)(this + 0x140) = 0;
        *(int*)(this + 0x13c) = 0;
        *(int*)(this + 0x138) = 0;
        *(int*)(this + 0x134) = 0;

        // Initialize sub-object at offset 0x144
        FUN_004b1720(this + 0x144);

        // Copy data from global buffer if available
        if (DAT_012069c4 != 0) {
            FUN_00408900(this + 0x3c, &DAT_012069c4, 0x8000); // copy 0x8000 bytes
        }

        // Register message strings
        FUN_00408240(&DAT_0112dce4, "iMsgSequenceInstanceCreate");
        FUN_00408240(&DAT_0112dcec, "iMsgSequenceInstanceReady");
    }
};
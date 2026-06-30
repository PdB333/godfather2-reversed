// FUNC_NAME: PlayerGroundSM::constructor
// Address: 0x006bb750
// This function initializes the PlayerGroundSM state machine object, including
// vtable pointers, default state values, and health/stamina fields.

class PlayerGroundSM {
public:
    void constructor(uint param_2) {
        // Call base class constructor (likely PlayerSM::constructor)
        FUN_006bd1d0(param_2);

        // Set vtable pointers (overwriting order from Ghidra)
        this[0x20] = &PTR_LAB_00d5e71c;   // +0x80: temporary vtable
        this[0]    = &PTR_FUN_00d5e76c;   // +0x00: primary vtable
        this[0xf]  = &PTR_LAB_00d5e75c;   // +0x3C: secondary vtable
        this[0x12] = &PTR_LAB_00d5e758;   // +0x48: tertiary vtable
        this[0x20] = &PTR_LAB_00d5e73c;   // +0x80: final vtable (overwrites temp)

        // Initialize state machine variables
        this[0x21] = 7;                    // +0x84: number of states or max transitions

        // Zero out state flags (32-bit chunks)
        this[0x24] = 0;                    // +0x90
        this[0x25] = 0;                    // +0x94
        this[0x26] = 0;                    // +0x98
        this[0x27] = 0;                    // +0x9C
        this[0x22] = 0;                    // +0x88
        this[0x23] = 0;                    // +0x8C
        this[0x28] = 0;                    // +0xA0
        this[0x29] = 0;                    // +0xA4
        this[0x2a] = 0;                    // +0xA8
        this[0x2b] = 0;                    // +0xAC
        this[0x2c] = 0;                    // +0xB0
        this[0x2d] = 0;                    // +0xB4
        this[0x2f] = 0;                    // +0xBC
        this[0x32] = 0;                    // +0xC8

        // Zero out 16-bit state fields (shorts)
        *(short*)((char*)this + 0xC0) = 0;
        *(short*)((char*)this + 0xC2) = 0;
        *(short*)((char*)this + 0xCC) = 0;
        *(short*)((char*)this + 0xCE) = 0;
        this[0x35] = 0;                    // +0xD4

        *(short*)((char*)this + 0xD8) = 0;
        *(short*)((char*)this + 0xDA) = 0;
        this[0x38] = 0;                    // +0xE0

        *(short*)((char*)this + 0xE4) = 0;
        *(short*)((char*)this + 0xE6) = 0;
        this[0x3b] = 0;                    // +0xEC

        *(short*)((char*)this + 0xF0) = 0;
        *(short*)((char*)this + 0xF2) = 0;
        this[0x3e] = 0;                    // +0xF8

        *(short*)((char*)this + 0xFC) = 0;
        *(short*)((char*)this + 0xFE) = 0;
        this[0x41] = 0;                    // +0x104

        *(short*)((char*)this + 0x108) = 0;
        *(short*)((char*)this + 0x10A) = 0;
        this[0x44] = 0;                    // +0x110

        *(short*)((char*)this + 0x114) = 0;
        *(short*)((char*)this + 0x116) = 0;
        this[0x47] = 0;                    // +0x11C

        *(short*)((char*)this + 0x120) = 0;
        *(short*)((char*)this + 0x122) = 0;
        this[0x4a] = 0;                    // +0x128

        *(short*)((char*)this + 0x12C) = 0;
        *(short*)((char*)this + 0x12E) = 0;

        // Default values (e.g., health = 100)
        this[0x2e] = 100;                  // +0xB8: default health/stamina
        this[0x31] = 0;                    // +0xC4
        this[0x34] = 0;                    // +0xD0
        this[0x37] = 0;                    // +0xDC
        this[0x3a] = 0;                    // +0xE8
        this[0x3d] = 0;                    // +0xF4
        this[0x40] = 0;                    // +0x100
        this[0x43] = 0;                    // +0x10C
        this[0x46] = 0;                    // +0x118
        this[0x49] = 0;                    // +0x124
    }
};
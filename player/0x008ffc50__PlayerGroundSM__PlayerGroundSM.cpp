// FUNC_NAME: PlayerGroundSM::PlayerGroundSM

// Constructor for PlayerGroundSM (state machine for ground movement)
// Initializes vtable pointers, zeroes state flags, and sets global references
// Address: 0x008ffc50

#include <cstring> // for memset

class PlayerGroundSM {
public:
    // Offsets (in bytes):
    // +0x00: vtable for PlayerGroundSM
    // +0x3C: secondary vtable (interface)
    // +0x48: tertiary vtable
    // +0x50: vtable (likely for additional interface)
    // +0x54: vtable
    // +0x58: vtable
    // +0x180-0x1AD: array of state flags/shorts (46 bytes)
    // +0x1B0: global pointer 1 (from _DAT_00d5cf70)
    // +0x1B4: global pointer 2 (from DAT_00d5ccf8)
    // +0x1D0: some counter/state

    // Constructor takes a parameter that might be a memory block size
    PlayerGroundSM(uint32 param_2) {
        // Initialize some memory block? (param_2 is size, second arg 0x4000 flags)
        // FUN_0046e6b0 is likely a proprietary memory clear/memset variant
        System::memoryClear((void*)param_2, 0x4000);  // placeholder name

        // Set up vtable pointers (addresses from .rdata section)
        this->vtable[0] = &PTR_FUN_00d817e8;         // primary vtable
        *(void**)((uint8*)this + 0x3C) = &PTR_LAB_00d817d8; // secondary
        *(void**)((uint8*)this + 0x48) = &PTR_LAB_00d817d4;
        *(void**)((uint8*)this + 0x50) = &PTR_LAB_00d817d0;
        *(void**)((uint8*)this + 0x54) = &PTR_LAB_00d81770;
        *(void**)((uint8*)this + 0x58) = &PTR_LAB_00d81708;

        // Zero out the state flag region (0x180 to 0x1AD, 46 bytes)
        // The decompiled does this with individual halfword/word writes,
        // but a single memset is equivalent.
        memset((uint8*)this + 0x180, 0, 46);

        // Set two global references into the object
        // _DAT_00d5cf70 and DAT_00d5ccf8 are likely global objects or configurations
        *(uint32*)((uint8*)this + 0x1B0) = g_someGlobal1; // (from _DAT_00d5cf70)
        *(uint32*)((uint8*)this + 0x1B4) = g_someGlobal2; // (from DAT_00d5ccf8)

        // Call additional initialization
        FUN_00903a00(); // might be secondary constructor or setup

        // Final zeroing
        *(uint32*)((uint8*)this + 0x1D0) = 0;
    }

private:
    // Placeholder vtable struct (actual layout unknown)
    typedef void* VTable;
    VTable vtable; // at +0x00, actually a pointer to vtable array
    // Other members not explicitly declared due to complex layout
};

// External functions (to be defined elsewhere)
void System::memoryClear(void* addr, uint32 flags);
void FUN_00903a00();

// Global variables
extern uint32 g_someGlobal1; // address 0x00d5cf70
extern uint32 g_someGlobal2; // address 0x00d5ccf8

// Vtable symbols (addresses from the binary)
extern void* PTR_FUN_00d817e8;
extern void* PTR_LAB_00d817d8;
extern void* PTR_LAB_00d817d4;
extern void* PTR_LAB_00d817d0;
extern void* PTR_LAB_00d81770;
extern void* PTR_LAB_00d81708;
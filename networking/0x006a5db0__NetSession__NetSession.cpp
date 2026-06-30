// FUNC_NAME: NetSession::NetSession
// Constructor for NetSession at 0x006a5db0
// Initializes packet windows, ghost slots, and other network state.
// Uses debug fill constants for uninitialized memory.

class NetSession {
public:
    // Vtable pointer: +0x00 -> &PTR_FUN_00d5d7a8
    // Vtable pointer 2: +0x0C -> &PTR_LAB_00d5d7a4 (secondary vtable?)
    // +0x04: mSlotCount (int)
    // +0x08: mSomeFlags (int)
    // +0x10: mPacketSlots[32] (each 10 ints = 40 bytes) starting at +0x20 (offset 8)
    // +0x524: mReliableSlots[8] (10 ints each) starting at +0x53C (offset 0x14f)
    // +0x6BC: mGhostSlots[32] (6 ints each) starting at +0x6BC? Actually param_1 + 0x1af
    // +0x5A4: mObjectSlots[32] (6 ints each) starting at param_1 + 0x1b0 (offset 0x1b0)
    // Many other fields
};

NetSession* __fastcall NetSession_constructor(NetSession* this) {
    int* pSlot;
    int i;

    // Initialize basic members
    this->mSlotCount = 1;          // param_1[1] = 1
    this->mSomeFlags = 0;          // param_1[2] = 0

    // Set vtable pointer
    this->vtable = &PTR_FUN_00d5d7a8;   // param_1[0] (implicit)
    this->vtableSecondary = &PTR_LAB_00d5d7a4; // param_1[3] = &PTR_LAB_00d5d7a4

    // Store global reference to this instance
    g_pNetSession = this;               // DAT_011299b0 = param_1

    // Initialize 32 packet slots (each 10 ints = 40 bytes)
    // Starting at offset 0x20 (param_1[8])
    pSlot = &this->packetSlots[0];      // param_1 + 8
    for (i = 31; i >= 0; i--) {
        pSlot[0] = 0xFE16702F;         // Debug fill
        pSlot[1] = 0;
        pSlot[2] = 0;
        pSlot += 10;                   // Next slot (10 ints)
    }

    // Initialize reliable slots area (8 slots, each 10 ints)
    // Starting at offset 0x53C (param_1[0x14f])
    // Also clear some adjacent fields
    this->reliableSlotCount = 0;        // param_1[0x149] = 0
    this->reliableSlotIndex = 0;        // param_1[0x14a] = 0
    this->reliableSlotFlags1 = 0xFE16702F; // param_1[0x14d]
    this->reliableSlotFlags2 = 0xFE16702F; // param_1[0x14e]
    this->someReliablePtr = 0;          // param_1[0x14f] = 0
    this->someReliablePtr2 = 0;         // param_1[0x150] = 0
    this->reliableSlotArray[0] = 0xFE16702F; // param_1[0x158]
    this->reliableSlotArray[1] = 0;     // param_1[0x159]
    this->reliableSlotArray[2] = 0;     // param_1[0x15a]
    this->reliableSlotArray[3] = 0xFE16702F; // param_1[0x162]
    // ... etc. Actually a pattern: every 10 ints we have fill, 0,0

    // Another block of 8 slots at offset 0x14f (param_1[0x14f] base)
    // First, clear some pointers
    pSlot = &this->reliableSlots;       // param_1 + 0x14f
    for (i = 7; i >= 0; i--) {
        // Clear a pointer before each block? Actually code does:
        // piVar5[-1] = 0   => clear preceding slot's something
        // if (*piVar5 != 0) call FUN_004daf90(piVar5)
        // then piVar5[7] = 0, piVar5[8] = 0
        // piVar5 += 10
        pSlot[-1] = 0;                  // Clear previous slot's flag
        if (pSlot[0] != 0) {
            FUN_004daf90(pSlot);        // Release resource
            pSlot[0] = 0;
        }
        pSlot[7] = 0;                   // Clear two integers
        pSlot[8] = 0;
        pSlot += 10;                    // Next block (10 ints)
    }

    // Call sub-initializer
    FUN_006a5740();

    // Initialize 32 ghost slots (each 6 ints = 24 bytes)
    // Starting at offset 0x6BC (param_1[0x1af])
    pSlot = &this->ghostSlots;          // param_1 + 0x1af
    for (i = 31; i >= 0; i--) {
        pSlot[-1] = 0;                  // Clear previous field
        *(byte*)(pSlot + 4) = 0;        // Clear byte at offset 16
        pSlot[0] = 0;
        pSlot[1] = 0;
        pSlot[2] = 0;
        pSlot[3] = 0;
        pSlot += 6;                     // Next slot (6 ints)
    }

    // Initialize object slots (32 slots, each 6 ints) at offset 0x6C0 (param_1[0x1b0])
    pSlot = &this->objectSlots;         // param_1 + 0x1b0
    // Using a different loop structure: it sets puVar2[-1] = 0, then byte at puVar2+4, then zeros
    // Actually the code after the ghost loop does another loop for 0x1f times on param_1+0x1b0.
    // Let's do it similarly:
    for (i = 31; i >= 0; i--) {
        pSlot[-1] = 0;
        *(byte*)(pSlot + 4) = 0;
        pSlot[0] = 0;
        pSlot[1] = 0;
        pSlot[2] = 0;
        pSlot[3] = 0;
        pSlot += 6;
    }

    // Additional fields near the end
    this->someFlagA = 0;                // param_1[0x1aa]
    this->someFlagB = 0;                // param_1[0x1ab]
    this->someFlagC = 0;                // param_1[0x1ac]
    this->reliableSentinel = 0;         // param_1[0x1a9] = 0 (overwritten)
    *(byte*)(this + 0x26f) = 1;         // Set byte at offset 0x26f to 1
    this->someGlobal = g_SomeGlobal;    // param_1[0x1ad] = _DAT_00d5780c
    this->magic1 = 0;                   // param_1[0x1a2] = 0 (was 0x91100911)
    this->magic2 = 0;                   // param_1[0x1a1] = 0 (was 0xeac15a55)
    this->magic3 = 0;                   // param_1[0x1a0] = 0 (was 0xbeefbeef)
    this->magic4 = 0;                   // param_1[0x19f] = 0 (was 0xbadbadba)

    return this;
}
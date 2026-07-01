// FUNC_NAME: initializeSystemWithData
// Function address: 0x00932c60
// Role: Initializes a global system with three data parameters, sets version/state, and registers a callback.

extern void FUN_008a18d0(int param);   // unknown initializer for param3
extern void FUN_008a1870(int param);   // unknown initializer for param2
extern void FUN_008a1850(int param);   // unknown initializer for param1
extern void FUN_005c0d50(void* base, void (*callback)(), int param); // register callback

extern int DAT_00e5672c;         // global version/state field
extern void* DAT_01129928;       // global singleton pointer
extern int DAT_01130590;         // bitfield flag (bit 0 checked)

extern void LAB_00931e00();      // callback function at this address

void initializeSystemWithData(int param1, int param2, int param3)
{
    // Initialize three sub-objects using the provided parameters (order reversed)
    FUN_008a18d0(param3);
    FUN_008a1870(param2);
    FUN_008a1850(param1);

    // Access the global singleton structure
    unsigned char* basePtr = (unsigned char*)DAT_01129928;

    // Set version/state to 12 (0xC)
    DAT_00e5672c = 12;

    // Clear field at offset +0x60 (likely a pointer or count)
    *(int*)(basePtr + 0x60) = 0;

    // If callback not yet registered, register it
    if ((DAT_01130590 & 1) == 0)
    {
        // Pass pointer to sub-structure at offset +0x14 as first parameter
        FUN_005c0d50(basePtr + 0x14, &LAB_00931e00, 0);
        DAT_01130590 |= 1;
    }
}
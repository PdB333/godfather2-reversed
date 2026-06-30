// FUNC_NAME: SimManager::~SimManager
// Address: 0x005e43d0
// Destructor for SimManager (EARS engine). Frees three dynamically allocated buffers,
// zeros related fields, then invokes the parent destructor through a global vtable.

void SimManager::~SimManager() {
    // Call base class destructor or cleanup method (0x005e4d30).
    FUN_005e4d30(this);

    // Cleanup first buffer group: field at +0x6018 is a counter/flag, freed pointer at +0x6014
    *(int*)(this + 0x6018) = 0;                // +0x6018: flag or size
    FUN_009c8f10(*(int*)(this + 0x6014));      // +0x6014: first buffer pointer
    *(int*)(this + 0x6014) = 0;                // Null the pointer

    // Zero fields +0x601c and +0x6024, then free and null pointer at +0x6020
    *(int*)(this + 0x601c) = 0;                // +0x601c: some state
    *(int*)(this + 0x6024) = 0;                // +0x6024: another state
    FUN_009c8f10(*(int*)(this + 0x6020));      // +0x6020: second buffer pointer
    *(int*)(this + 0x6020) = 0;                // Null the pointer

    // Zero fields +0x6028 and +0x6030, then free and null pointer at +0x602c
    *(int*)(this + 0x6028) = 0;                // +0x6028: state
    *(int*)(this + 0x6030) = 0;                // +0x6030: state
    FUN_009c8f10(*(int*)(this + 0x602c));      // +0x602c: third buffer pointer
    *(int*)(this + 0x602c) = 0;                // Null the pointer

    // Zero field at +0x6034
    *(int*)(this + 0x6034) = 0;                // +0x6034: final state

    // Invoke parent virtual destructor through global vtable pointer DAT_01223510.
    // The parent's destructor slot is at offset 0xc (index 3).
    int* piVar1 = DAT_01223510;                // global pointer to vtable entry
    (**(code**)(*piVar1 + 0xc))();            // call parent destructor
}
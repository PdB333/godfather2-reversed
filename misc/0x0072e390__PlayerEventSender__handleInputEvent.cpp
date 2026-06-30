// FUNC_NAME: PlayerEventSender::handleInputEvent
void __thiscall PlayerEventSender::handleInputEvent(int this, int player) {
    int iVar1;
    int iVar2;
    struct {
        undefined4 field0;
        undefined3 filler1[?]; // not fully known
    } eventData; // local_30 plus more
    void (*vtable_placeholder)(); // not needed
    int eventType = 0xbd2a751; // constant event identifier
    void* pAlloc = 0; // local_1c[0]
    void* pAlloc2 = 0; // local_14?
    uint flag;

    // conditions for processing: player != 0, global manager present, and either mode != 3 or IDs match
    if ( (player != 0) &&
         (*(int**)(*(int*)DAT_012233a0 + 4) != 0) ) {
        iVar2 = *(int**)(*(int*)DAT_012233a0 + 4) + -0x1f30; // offset to some subsystem
        if ( (iVar2 != 0) &&
             ( (iVar1 = FUN_00806440(), iVar1 != 3) ||
               (*(int*)(player + 0xb90) == *(int*)(this + 0x1ed4)) ) ) {

            // Initialize temporary structures
            eventData = 0;
            // Set vtable pointer for event data
            eventData.field0 = (undefined4)&PTR_FUN_00d5dbbc;
            pAlloc = 0;
            flag = 0;
            // Additional constants
            // local_20 = eventType, local_4 = DAT_01205228 (unknown global)
            // Actually need to map local variables:
            // local_20 = eventType, local_4 = DAT_01205228
            // But Ghidra decompilation is messy; we structure similarly.
            // Assume a struct 'EventMsg' defined somewhere.

            FUN_0044b210(iVar2); // initialize event sender on iVar2

            // Get player info (position etc.)
            int* pPlayerInfo = (int*)FUN_00471610();
            void* posVec = (void*)(pPlayerInfo + 0x30 / 4);
            eventData.someVector = *(undefined8*)posVec;
            eventData.someFloat = *(undefined4*)((int)posVec + 0x8);

            // Set flag after extraction
            flag = 1;

            // Prepare event data structure pointer
            // Note: local_30 is the start of eventData, local_2c points to it
            // Complex structure, we approximate.

            // Adjust this pointer: if non-null, use offset 0x3c
            int adjustedThis = (this != 0) ? (this + 0x3c) : 0;

            // Send event
            FUN_00408bf0(&eventData, adjustedThis, 0);

            // Cleanup if allocation was made
            if (pAlloc != 0) {
                FUN_004daf90(pAlloc);
            }
        }
    }
}
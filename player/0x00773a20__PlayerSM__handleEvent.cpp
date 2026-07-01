// FUNC_NAME: PlayerSM::handleEvent
// Function address: 0x00773a20
// Handles state machine events for player state machine (PlayerSM)
// param_2-4,6 are event data; param_5 is event ID (offset by 0x23 in switch)
// Uses offsets: this+0x9c (flags), this+0xa0 (state context pointer), this+0xb8 (vtable pointer)

char __thiscall PlayerSM::handleEvent(int this, int eventData1, int eventData2, int eventData3, int eventId, int eventData4)
{
    int playerObj;
    uint flags;
    uint* flagPtr;

    switch (eventId - 0x23) {
    case 0: // Event ID 0x23
        startAnimation(); // FUN_00773360
        *(uint*)(this + 0x9c) |= 8; // Set bit 3 (0x8) in flags
        return 1;

    case 1: // Event ID 0x24
        setInputState(1); // FUN_007f63b0(1)
        updateCamera(); // FUN_007f6460
        updateUI(); // FUN_00800670
        playerObj = getPlayer(); // FUN_00772f10
        if ((playerObj != 0) && ((*(byte*)(playerObj + 0x1d0) & 1) != 0)) {
            *(uint*)(playerObj + 0x1d0) &= 0xfffffffe; // Clear bit 0
        }
        *(char*)(*(int*)(this + 0xa0) + 0xa20) = 1; // Set state context flag at +0xa20
        return 1;

    case 2: // Event ID 0x25
    case 5: // Event ID 0x28
        return 1;

    case 3: // Event ID 0x26
        *(char*)(*(int*)(this + 0xa0) + 0xa20) = 0; // Clear state context flag
        return 1;

    case 4: // Event ID 0x27
        setTimer(0x30); // FUN_007f6420(0x30)
        updateUI(); // FUN_00800670
        return 1;

    case 6: // Event ID 0x29
        handleSpecialEvent(); // FUN_00773560
        return 1;

    case 7: // Event ID 0x2A
        // Check state via vtable call
        playerObj = (**(code**)(**(int**)(this + 0xb8) + 0x34))(); // vtable call at offset 0x34
        if (*(int*)(playerObj + 0x30) != 4) {
            playerObj = (**(code**)(**(int**)(this + 0xb8) + 0x34))();
            flags = checkFlag(*(int*)(playerObj + 0x30)); // FUN_0084d420
            if ((flags & 8) == 0) {
                return 1;
            }
        }
        // Set flag at state context +0x1f5c
        flagPtr = (uint*)(*(int*)(this + 0xa0) + 0x1f5c);
        *flagPtr |= 0x100;
        return 1;

    case 8: // Event ID 0x2B
        resetState(); // FUN_007729f0
        return 1;

    default:
        return defaultHandler(eventData1, eventData2, eventData3, eventId, eventData4); // FUN_0073e610
    }
}
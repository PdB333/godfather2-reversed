// FUNC_NAME: PlayerStateController::transitionToState

void PlayerStateController::transitionToState(int playerIndex, int stateId) {
    char cVar1;
    int* someObjPtr;
    int iVar3;
    uint uVar6;
    void* stateData;

    // Lock maybe critical section
    criticalSectionEnter(1);

    // Get a pointer from a global array indexed by playerIndex and stateId, then +0x178
    stateData = *(void**)(*(int*)(DAT_01163820 + (playerIndex * 0x84 + stateId)) + 0x178);

    // Clamp global state durations
    if (DAT_012058d0 < 0x1b) {
        DAT_012058d0 = 0x1b;
    }
    if (0x1a < DAT_00f15988) {
        DAT_00f15988 = 0x1b;
    }

    // Read a byte from another global array (stride 0x210)
    cVar1 = *(char*)(DAT_01163841 + playerIndex * 0x210);

    _DAT_011f3a44 = 0;
    iVar3 = 2;
    if (cVar1 == '\0') {
        iVar3 = DAT_00e79c18;
    }

    FUN_00412f90(iVar3); // set some global flag

    iVar3 = DAT_012233a8; // pointer to some object
    uVar6 = 1;
    if (iVar3 != 0) {
        uVar6 = (-(uint)(iVar3 != 2) & 0xffff0000) + 0x20000 | 1;
    }

    DAT_0120546c = 1; // loading flag on

    if (cVar1 == '\0') {
        uint uVar4 = 0x800;
        if ((*(uint*)(*(int*)(DAT_012233a8 + 4) + 0x3af8) >> 3 & 1) != 0) {
            uVar4 = 0xc00;
        }
        // Initialize a stream with size parameters
        FUN_0042fc70(*(int*)(DAT_012233a8 + 4) + 0x1230, 0, uVar6, uVar4);
    }

    if (stateId < 2) {
        // Start something for state transitions 0 and 1
        FUN_00430180(*(int*)(DAT_012233a8 + 4), 0, uVar6, *(int*)(DAT_012233a8 + 4) + 0x18d0, 1, 0);
    }

    DAT_0120546c = 0; // loading flag off

    // Call a virtual callback if set
    if (DAT_012058e8 != (int*)0x0) {
        (**(code**)(*DAT_012058e8 + 0x20))(); // vtable offset 0x20
    }

    // Clamp again
    if (DAT_012058d0 < 0x1b) DAT_012058d0 = 0x1b;
    if (0x1a < DAT_00f15988) DAT_00f15988 = 0x1b;
    _DAT_011f3a44 = 0;

    if (DAT_012058d0 < 0x19) DAT_012058d0 = 0x19;
    if (0x19 < DAT_00f15988) DAT_00f15988 = 0x19;
    _DAT_011f3a3c = 7;

    if (DAT_012058d0 < 0x18) DAT_012058d0 = 0x18;
    if (0x18 < DAT_00f15988) DAT_00f15988 = 0x18;
    _DAT_011f3a38 = 0;

    if (DAT_012058d0 < 0xf) DAT_012058d0 = 0xf;
    if (0xf < DAT_00f15988) DAT_00f15988 = 0xf;
    _DAT_011f3a14 = 0;

    if (DAT_012058d0 < 0x16) DAT_012058d0 = 0x16;
    if (0x16 < DAT_00f15988) DAT_00f15988 = 0x16;
    _DAT_011f3a30 = 1;

    criticalSectionLeave(1);

    // Set a flag at offset +0x85 of the object to indicate transition
    *(char*)(*(int*)(iVar3 + 4) + 0x85) = 1;

    // Initialize state data with functions
    FUN_00434940(stateData); // init state
    uVar6 = 0xd;
    do {
        FUN_004349b0(stateData, uVar6); // per-substate init
        uVar6 = uVar6 + 1;
    } while (uVar6 < 0x17);

    // Clear transition flag
    *(char*)(*(int*)(iVar3 + 4) + 0x85) = 0;
}
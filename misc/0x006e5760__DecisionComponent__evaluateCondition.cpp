// FUNC_NAME: DecisionComponent::evaluateCondition
void DecisionComponent::evaluateCondition(int *outResult) {
    // +0x100 pointer to state manager
    int *stateManager = *(int **)((uint)this + 0x100);
    int localZero = 0;
    char resultChar;
    char tempChar;

    // Virtual call at vtable offset 0x10 with ID 0x55859efa
    // Likely a resource/game state query (e.g., check game mode)
    tempChar = (**(code **)(*stateManager + 0x10))(0x55859efa);

    // Conditional assignment: if tempChar != 0, use outResult pointer; else null
    int *dataPtr = (tempChar != 0) ? outResult : (int *)0;

    // Virtual call with enum result (0-4)
    char enumResult = (**(code **)(*dataPtr + 0x270))();
    switch (enumResult) {
        case 0: break;
        case 1: break;
        case 2: break;
        case 3: break;
        case 4: break;
    }

    // Check offset 0x1d3 of dataPtr (likely a timer or state counter)
    int offsetValue;
    if (dataPtr[0x1d3] == 0) {
        offsetValue = 0;
    } else {
        offsetValue = dataPtr[0x1d3] + -0x48; // subtract standard header size
    }

    // Second virtual call with different constant and a stack variable reference
    tempChar = (**(code **)(*stateManager + 0x10))(0x383225a1, &localZero);

    if (tempChar == '\0') {
        resultChar = '\0';
        localZero = 0;
    } else {
        // Check if localZero (now a pointer?) and its +0x30c0 field is valid
        if (localZero == 0 || *(int *)(localZero + 0x30c0) == 0 || *(int *)(localZero + 0x30c0) == 0x48) {
            resultChar = '\0';
            localZero = 0;
        } else {
            resultChar = '\x01';
        }
    }

    // Main decision path
    if (offsetValue != 0) {
        if (resultChar != '\0') {
            goto finalizeTrue;
        }
        // Check bit at offset 0x1d0: bit 2
        if ((*(uint *)(offsetValue + 0x1d0) >> 2 & 1) == 0) {
            goto finalizeFalse;
        }
        // Check additional bits from dataPtr[0x238] and dataPtr[0x239]
        if ((((uint)dataPtr[0x238] >> 10 & 1) != 0) || (((uint)dataPtr[0x239] >> 5 & 1) != 0)) {
            goto finalizeTrue;
        }
        if (localZero == 0) {
            goto finalizeFalse;
        }
        // External function call with constant 0x1f
        resultChar = FUN_00690210(0x1f);
    }

    if (resultChar == '\0') {
finalizeFalse:
        *outResult = (int)&localZero;   // Address of local zero (likely placeholder)
        return;
    }
finalizeTrue:
    *outResult = DAT_00d5779c;   // Global positive token
    return;
}
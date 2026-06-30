// FUNC_NAME: NetConnection::canTransmitPacket

// Function at 0x0070a2a0: Determines if a packet transmission is allowed based on bandwidth/throttle
// Uses global gNetManager (DAT_012233a0) for engine state validation

uint8_t __fastcall NetConnection::canTransmitPacket(NetConnection* this) {
    int* pConnectionState;
    int iVar1;
    uint8_t bCanTransmit;
    uint uLocal;
    uint uCurrentTick;
    int* piTarget;

    bCanTransmit = 0;

    // Check global net manager state: ensure it's initialized and not a specific invalid state (0x1f30 = 7984)
    if (*(int**)(gNetManager + 4) == nullptr) {
        return 0;
    }
    if (*(int**)(gNetManager + 4) == (int*)0x1f30) {
        return 0;
    }

    uLocal = (uint)this;  // save this pointer

    // Get the connection state object from this+0x50
    pConnectionState = (int*)FUN_00705ab0(*(undefined4*)(this + 0x50));
    if (pConnectionState != nullptr) {
        iVar1 = *(int*)(this + 0x50);
        // Check if category is 0-4 (likely a channel/priority enum)
        if (((iVar1 == 0) || (iVar1 == 1)) || (iVar1 == 2) || ((iVar1 == 3) || (iVar1 == 4))) {
            uLocal = 0;
            // Call virtual function at vtable+0x10 (likely getThrottleData or similar)
            // Hash 0x332d5a20 may identify the method
            uint8_t bSuccess = (**(code**)(*pConnectionState + 0x10))(0x332d5a20, &uLocal);
            // Compute index: if bSuccess is true, use uLocal; else use 0
            iVar1 = *(int*)(( -(uint)(bSuccess != 0) & uLocal) + 0x328);
            uCurrentTick = FUN_00701340();  // get current tick count
            uLocal = uCurrentTick + iVar1;   // compute next allowed time
        }
        else {
            // For other categories, get time directly from connection state
            uLocal = FUN_007049a0(pConnectionState);
        }

        // Compare with throttle threshold at this+0x58
        if (*(uint*)(this + 0x58) <= uLocal) {
            bCanTransmit = 1;
            piTarget = (int*)(this + 0x6c);
            goto LAB_0070a33f;
        }
    }

    piTarget = (int*)(this + 0x74);

LAB_0070a33f:
    // If the target pointer is non-null, clear/reset it (likely a pending send buffer)
    if (*piTarget != 0) {
        FUN_00440590(piTarget, 0, 0, 0, 0);
    }
    return bCanTransmit;
}
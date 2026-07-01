// FUNC_NAME: PlayerDonControlManager::updateDonActionState

void __thiscall PlayerDonControlManager::updateDonActionState(int this, int playerIndex, int* outData, bool* outFlag) {
    bool* ppuVar1; // local copy of outFlag
    char cVar2; // char result from virtual call
    int iVar3; // state machine pointer
    int* piVar4; // component pointer
    int ebx; // placeholder for uninitialized EBX register (likely stored by caller)
    int retAddr; // placeholder for uninitialized return address (likely stack artifact)

    ppuVar1 = outFlag;
    *outData = *(int*)(this + 0x754); // offset 0x1d5*4 = 0x754
    *outFlag = false;

    // Call virtual method on an object at this+0x5F4 (0x17d*4)
    iVar3 = (**(int (__thiscall**)(int))(**(int**)(this + 0x5F4) + 0x34))(*(int*)(this + 0x5F4));

    // Look for a component with GUID 0x55859efa (likely DonControlGadget)
    piVar4 = (int*)FUN_0084daa0((void*)this, 0x55859efa);
    if ((piVar4 == (int*)0x0) || (piVar4 == (int*)this)) {
        // Component not found or is self – handle state machine logic
        if ((*(int*)(iVar3 + 0x30) == 3) &&
            (*(int*)(iVar3 + 4) != 0 && *(int*)(iVar3 + 4) != 0x48)) {
            // Get container from state machine (offset -0x48)
            if (*(int*)(iVar3 + 4) == 0) {
                piVar4 = (int*)0x0;
            } else {
                piVar4 = (int*)(*(int*)(iVar3 + 4) - 0x48);
            }
            // Query the component via virtual method (index 0x10) with GUID 0xa5975eb2
            cVar2 = (**(char (__thiscall**)(int, uint, bool**))(*piVar4 + 0x10))((int)piVar4, 0xa5975eb2, &outFlag);
            if ((cVar2 != '\0') && (playerIndex != 0)) {
                iVar3 = FUN_007ff880(); // Get current player ID
                if (playerIndex == iVar3) {
                    // This player: trigger action (callback)
                    FUN_008786b0(ebx, &retAddr, ppuVar1); // likely shows Don action
                    if (ebx != 0) {
                        *(int*)retAddr = ebx; // write-back
                    }
                } else {
                    // Other player's state
                    if ((*(uint*)(playerIndex + 0xc88) >> 0x15 & 1) != 0) {
                        // Player can takeover? Show hint
                        FUN_0079ee00(ebx, retAddr);
                        *ppuVar1 = true;
                        return;
                    }
                    if (((*(uint*)(playerIndex + 0xc88) >> 0x16 & 1) != 0) &&
                        (*(int*)(this + 0x1ED4) != *(int*)(playerIndex + 0xb90))) {
                        // Different target? Hide hint
                        FUN_0079ee40(ebx, retAddr);
                        return;
                    }
                }
            }
        }
    } else {
        // Component found and is external
        cVar2 = (**(char (__thiscall**)(int, uint, bool**))(*piVar4 + 0x10))((int)piVar4, 0x383225a1, &outFlag);
        if ((cVar2 != '\0') && (playerIndex != 0)) {
            FUN_0079ee40(ebx, retAddr);
            return;
        }
        // Get game state from some manager
        iVar3 = FUN_00806440();
        if (iVar3 == 2) {
            // State 2: Show hint
            FUN_0079ee00(ebx, retAddr);
            *ppuVar1 = true;
            return;
        }
        if (iVar3 == 3) {
            // State 3: Hide hint
            FUN_0079ee40(ebx, retAddr);
            return;
        }
    }
    return;
}
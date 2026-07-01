// FUNC_NAME: GodfatherGameManager::processEvent

// Address: 0x007a3b20
// Role: Processes an incoming event (input, state change, or network packet) 
//       and updates game state accordingly. Handles event type dispatch,
//       temporary object construction for event processing, and cleanup.
// Known classes: GodfatherGameManager (this), Event (param_2, likely 
//       EARS::Modules::PlayerInputEvent or similar)
// Offsets: this+0x2e1c, 0x2e24 - smart pointer fields (RefPtr)
//          this+0x2c20 - debug context
//          this+0x2110 - flags (bitfield)
//          this+0x2dcc - pointer to some object (e.g., UI manager)
//          this-0x33c - another object (parent? vtable call)
//          this+0x1b40 - some ID (player or vehicle)
//          this+0x394 - base offset for temporary state

void __thiscall GodfatherGameManager::processEvent(int this, int event)
{
    char cVar1;
    int iVar2;
    int iVar3;
    int *piVar4;
    int iVar5;
    bool bVar6;
    float fVar7;
    int iVar8;
    undefined *puVar9;
    uint queryResult;
    float timeDelta;
    uint queryOut;
    undefined4 uStack_54;
    undefined4 uStack_50;
    undefined1 uStack_4c;
    undefined1 auStack_48[4]; // Temporary event structure
    int smartPtrA;             // RefPtr to some object (iStack_3c)
    undefined4 uStack_40;
    int smartPtrB;             // RefPtr (iStack_44)
    undefined4 uStack_38;
    undefined8 uStack_34;      // 8-byte state copy
    undefined4 uStack_2c;      // 4-byte state copy

    bVar6 = false;
    cVar1 = isGameActive(); // FUN_00481660
    if (cVar1 == '\0') goto LAB_007a3cab;

    iVar5 = 0;
    // Event type check: 0 or 0x48 are simple dispatch cases
    if ((*(int *)(event + 0xc) == 0) || (*(int *)(event + 0xc) == 0x48)) {
LAB_007a3c63:
        applyEventState(this + -0x394, event); // FUN_008a6750
    }
    else {
        // Complex event: get the object inside the event
        if (*(int *)(event + 0xc) == 0) {
            piVar4 = (int *)0x0;
        }
        else {
            piVar4 = (int *)(*(int *)(event + 0xc) + -0x48); // Event data offset -0x48
        }
        queryResult = 0;
        // Query interface with GUID 0x55859efa (probably IID_PlayerAction or similar)
        cVar1 = (**(code **)(*piVar4 + 0x10))(0x55859efa, &queryResult);
        bVar6 = ((-(uint)(cVar1 != '\0') & queryResult) == 0) ? false : true;
        if (!bVar6) goto LAB_007a3c63;

        processInputEvent(event); // FUN_0079d210
        iVar8 = this + -0x394;
        if (iVar8 != 0) {
            iVar5 = this + -0x34c; // Offset to another object
        }

        // Smart pointer assignment for smartPtrA
        if (smartPtrA != iVar5) {
            if (smartPtrA != 0) {
                releaseSmartPtr(&smartPtrA); // FUN_004daf90
            }
            smartPtrA = iVar5;
            if (iVar5 != 0) {
                uStack_38 = *(undefined4 *)(iVar5 + 4);
                *(int **)(iVar5 + 4) = &smartPtrA; // Link back to smart pointer
            }
        }

        if (iVar8 == 0) {
            iVar5 = 0;
        }
        else {
            iVar5 = this + -0x34c;
        }

        // Smart pointer assignment for smartPtrB
        if (smartPtrB != iVar5) {
            if (smartPtrB != 0) {
                releaseSmartPtr(&smartPtrB);
            }
            smartPtrB = iVar5;
            if (iVar5 != 0) {
                uStack_40 = *(undefined4 *)(iVar5 + 4);
                *(int **)(iVar5 + 4) = &smartPtrB;
            }
        }

        iVar5 = getInputManager(); // FUN_00471610 - returns pointer to state
        uStack_34 = *(undefined8 *)(iVar5 + 0x30); // Copy 8 bytes of input state
        uStack_2c = *(undefined4 *)(iVar5 + 0x38); // Copy 4 bytes
        applyEventState(iVar8, auStack_48); // FUN_008a6750 - pass local event struct

        if (smartPtrA != 0) {
            releaseSmartPtr(&smartPtrA);
        }
        if (smartPtrB != 0) {
            releaseSmartPtr(&smartPtrB);
        }
    }

    // Cleanup after processing
LAB_007a3cab:
    if (*(int *)(this + 0x2e1c) != 0) {
        releaseSmartPtr((undefined4 *)(this + 0x2e1c));
        *(undefined4 *)(this + 0x2e1c) = 0;
    }
    if (*(int *)(this + 0x2e24) != 0) {
        releaseSmartPtr((undefined4 *)(this + 0x2e24));
        *(undefined4 *)(this + 0x2e24) = 0;
    }

    cVar1 = isMenuOpen(); // FUN_00481620 - likely checks pause/menu
    if (cVar1 != '\0') {
        pushDebugContext(this + 0x2c20); // FUN_007fff40
        if ((*(uint *)(this + 0x2110) >> 0xe & 1) == 0) {
            puVar9 = &DAT_0112b904; // "Game" or similar string
        }
        else {
            puVar9 = &DAT_0112b384; // "Menu" or similar
        }
        pushDebugContext(puVar9);
    }

    if ((*(int *)(this + 0x2dcc) != 0) && (cVar1 = isMenuOpen(), cVar1 != '\0')) {
        showDebugOverlay(0); // FUN_0079f4c0
        (**(code **)(*(int *)(this + -0x33c) + 0x28))(0x20000); // Vtable call to parent
    }

    // Build a string from constant DAT_0112e124
    uStack_54 = DAT_0112e124;
    uStack_50 = 0;
    uStack_4c = 0;
    stringCopy(&uStack_54, 0); // FUN_00408a00

    // Additional event processing for certain types
    if ((*(int *)(event + 0xc) != 0) && (*(int *)(event + 0xc) != 0x48)) {
        if (*(int *)(event + 0xc) == 0) {
            piVar4 = (int *)0x0;
        }
        else {
            piVar4 = (int *)(*(int *)(event + 0xc) + -0x48);
        }
        queryResult = 0;
        cVar1 = (**(code **)(*piVar4 + 0x10))(0x55859efa, &queryResult);
        if ((cVar1 != '\0') && (queryOut = queryResult, queryResult != 0)) {
            iVar5 = *(int *)(queryResult + 0x1ed4); // Get some ID from queried object
            iVar2 = getCurrentGameMode(); // FUN_00806440
            iVar8 = *(int *)(this + 0x1b40); // Local ID
            iVar3 = getCurrentGameMode(); // FUN_00806440 (again?)
            if ((iVar5 != iVar8) && ((iVar2 == 3 && (iVar3 == 3)))) {
                timeDelta = 0.0f;
                getTimeDelta(0x3bb7ccd2, &timeDelta); // FUN_008934e0 - get time since last frame?
                fVar7 = DAT_00e44564 - timeDelta; // Global time
                applyVehicleSpeed(iVar8, fVar7); // FUN_006ebfd0
                playSound(iVar8, fVar7); // FUN_008c0e60
            }
        }
    }

    if (bVar6) {
        processInputEvent(event); // FUN_0079d210
        // Reset smart pointer chain for this and event
        if (this == 0x394) {
            iVar5 = 0;
        }
        else {
            iVar5 = this + -0x34c;
        }
        // ... (similar smart pointer assignment as above but with 'this' offset)
        if (smartPtrA != iVar5) {
            if (smartPtrA != 0) {
                releaseSmartPtr(&smartPtrA);
            }
            smartPtrA = iVar5;
            if (iVar5 != 0) {
                uStack_38 = *(undefined4 *)(iVar5 + 4);
                *(int **)(iVar5 + 4) = &smartPtrA;
            }
        }
        if (this == 0x394) {
            this = 0;
        }
        else {
            this = this + -0x34c;
        }
        if (smartPtrB != this) {
            if (smartPtrB != 0) {
                releaseSmartPtr(&smartPtrB);
            }
            smartPtrB = this;
            if (this != 0) {
                uStack_40 = *(undefined4 *)(this + 4);
                *(int **)(this + 4) = &smartPtrB;
            }
        }
        iVar5 = getInputManager();
        uStack_34 = *(undefined8 *)(iVar5 + 0x30);
        uStack_2c = *(undefined4 *)(iVar5 + 0x38);
        applyEventState(auStack_48); // FUN_0080b690 - different apply function
        if (smartPtrA != 0) {
            releaseSmartPtr(&smartPtrA);
        }
        if (smartPtrB != 0) {
            releaseSmartPtr(&smartPtrB);
            return;
        }
    }
    else {
        applyEventState(event); // FUN_0080b690
    }
    return;
}
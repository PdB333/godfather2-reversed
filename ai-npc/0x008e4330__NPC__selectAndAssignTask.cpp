// FUNC_NAME: NPC::selectAndAssignTask
// Function address: 0x008e4330
// Purpose: Evaluate and assign a task (action) to an NPC based on current state and available action data.
// The NPC has a slot array (3 slots, each 0x5c bytes) for holding action assignments.
// Uses magic numbers (0xbadbadba, 0xbeefbeef, 0xeac15a55, 0x91100911) as sentinel values for empty/invalid data.
// Returns 1 on success (task assigned), 0 on failure.

int __thiscall NPC::selectAndAssignTask(uint thisPtr, uint *pActionData, int mode)
{
    uint *puVar1;
    undefined3 uVar2;
    char cVar3;
    int *pManager;
    uint uVar5;
    uint uVar6;
    int iVar7;
    int iVar8;
    int iVar9;
    int iVar10;
    undefined8 *puVar11;
    int unaff_ESI; // Possibly another NPC pointer from caller
    int *unaff_EDI; // Pointer to a vtable (task manager?)
    int iStack_1c; // Local temp
    int iStack_18; // Local - appears to hold slot index (0,1,2) or state
    int iStack_14; // Local - secondary slot index
    int iStack_10; // Local - boolean flag?

    uint uStack_258; // might be locals but used as bitfield
    char cStack_25b;
    char cStack_25a;
    uint auStack_21c[5];
    undefined1 auStack_1f8[68];
    undefined1 auStack_1b4[16];
    undefined1 auStack_1a4[392];
    int iStack_1c2; // actually iStack_1c from above? renaming needed
    int iStack_18_dup; // Actually iStack_18 used again - careful

    // Offset layout:
    // +0x5c: flags (bitfield)
    // +0x84: additional flags (bit 16 used)
    // +0x98: pointer to array of slot data (size 0x5c * nSlots)
    // +0x50 (within slot): some sub-object
    // +0x20: position/rotation (referred by some functions)
    // +0xd4: pointer to action task object
    // +0xc0: flags (bit0, bit1, bit2)
    // +0xd8, +0xe0: quaternion (two 64-bit halves)

    // Check for sentinel values in action data
    if ((((*pActionData == 0) && (pActionData[1] == 0)) && 
         (pActionData[2] == 0) && (pActionData[3] == 0)) ||
        ((((*pActionData == 0xbadbadba) && (pActionData[1] == 0xbeefbeef)) &&
          ((pActionData[2] == 0xeac15a55) && (pActionData[3] == 0x91100911))))) 
    {
        if (mode == 2) {
            return 1; // Accept empty/invalid data if mode is 2?
        }
        return 0;
    }

    // Initialize some variables
    auStack_21c[1] = 0; // clear second element
    pManager = (int *)FUN_00446100(); // Get global task manager? (returns NULL if not available)
    if (pManager == (int *)0x0) {
        return 0;
    }

    // Setup iterator/stream reading pattern (typical EA serialization)
    // Use function pointer at vtable offset 0x10
    cVar3 = (**(code **)(*pManager + 0x10))(); // Begin reading?
    uStack_258 = 0x4cd663c2; // Some key?
    uStack_258._1_1_ = 'c';
    uStack_228 = -(uint)(cVar3 != '\0') & auStack_21c[0]; // ???
    (**(code **)(*pManager + 0x10))(); // continue?
    (**(code **)(*pManager + 0x10))(0xf23a79d5); // read with magic ID?
    uStack_228 = 0;
    cVar3 = (**(code **)(*pManager + 0x10))(0x43c8ec5b, &uStack_228); // read integer into local variable

    iVar7 = iStack_18;
    uVar5 = -(uint)(cVar3 != '\0') & thisPtr;
    iVar9 = 0;

    // Main state machine based on slot index (iStack_18 appears to be loaded from caller or global state)
    if (iStack_18 == 0) {
        // Slot 0 specific logic
        if (iStack_14 == 0) {
            // Clear flag bit 16 at offset 0x84
            *(uint *)(thisPtr + 0x84) &= 0xfffeffff;
            uStack_22c = 0;
            uVar6 = FUN_00446100(thisPtr + 0x98, 0); // Get pointer to slot array (size 0x5c per slot)
            if (uVar6 != 0) {
                uStack_22c = uVar6;
            }
            // Iterate over all slots (likely 3 slots)
            FUN_006bea20(&LAB_008e2c20); // Init iterator?
            uStack_254 = 0;
            if (uStack_228 != 0) {
                do {
                    iVar9 = *(int *)(uStack_22c + uStack_254 * 4); // Get slot pointer from array
                    iVar7 = FUN_00791300(); // Get some global player/NPC reference
                    if (iVar7 != 0) {
                        FUN_0043b870(DAT_0112af58); // Load some audio/data?
                    }
                    // Condition checks for this slot:
                    // +0x5c >> 1 & 1: bit 1 must be 0 (some flag)
                    // +0x5c >> 0x14 & 1: bit 20 must be 0
                    // Various other checks
                    if (((((((~(byte)(*(uint *)(iVar9 + 0x5c) >> 1) & 1) != 0) &&
                           ((*(uint *)(iVar9 + 0x5c) >> 0x14 & 1) == 0)) &&
                          ((cVar3 = FUN_008e6510(iVar9 + 0x20), cVar3 == '\0' && // Check some spatial condition
                           ((cVar3 = FUN_00782ce0(), cVar3 == '\0' && 
                            (cVar3 = FUN_00690150(5), cVar3 == '\0')))))) && 
                         (iVar8 = FUN_0077dd80(), iVar8 < 3)) && // Check some count
                        (((uStack_22c == 0 || (cVar3 = FUN_0078f170(iVar7), cVar3 != '\0')) && // Check player relation
                         (cVar3 = FUN_007f47a0(), cVar3 == '\0')))) && // Check some blocked condition
                       (((*(uint *)(iVar9 + 0x5c) >> 0x13 & 1) == 0 && // Bit 19 must be 0
                        (cVar3 = FUN_008e2be0(), cVar3 == '\0')))) {
                        // All conditions met: assign this slot
                        FUN_008e6af0(iVar9 + 0x20); // Update spatial data?
                        iVar7 = iStack_18;
                        break;
                    }
                    uStack_254 = uStack_254 + 1;
                    iVar7 = iStack_18;
                    iVar9 = 0;
                } while (uStack_254 < uStack_22c[1]); // until index < count (maybe num slots)
            }
        }
        else {
            // If iStack_14 != 0 (apparently another slot index), set flag
            *(uint *)(thisPtr + 0x84) |= 0x10000;
            iVar9 = FUN_00791300(); // Get player/NPC?
            iVar7 = iStack_18;
            if (((iVar9 != 0) && (cVar3 = FUN_007f47a0(), iVar7 = iStack_18, cVar3 == '\0')) &&
               (((*(uint *)(iStack_14 + 0x5c) >> 0x13 & 1) == 0 && // Bit 19 must be 0
                (cVar3 = FUN_008e2be0(), iVar7 = iStack_18, cVar3 == '\0')))) {
                uStack_258 = 0x4cd601c2;
                iVar9 = iStack_14; // Use this slot
            }
        }
    }
    else if ((iStack_18 == 1) || (iStack_18 == 2)) {
        // Slots 1 and 2
        if (unaff_EDI == (int *)0x0) {
            // No external action manager pointer: handle allocation
            if (uVar5 == 0) {
                return 0;
            }
            // Set flags based on slot index
            if (iStack_18 == 1) {
                iVar10 = 0x20000; // Flag for slot 1
            }
            else {
                iVar10 = 0x40000; // Flag for slot 2
            }
            FUN_00508f40(iVar10, iStack_10 != 0); // Set flag on something (maybe another NPC)

            if (iStack_10 == 0) {
                // Allocate new slot data
                iVar9 = FUN_00446100(iStack_18 * 0x5c + 0x98 + thisPtr, 0); // Get slot memory
                if (iVar9 == 0) {
                    // If allocation failed, use stack buffer
                    FUN_006b8040(); // Push/preserve context?
                    auStack_21c[0] = auStack_21c[0] | 1; // Mark used
                    iVar9 = FUN_008e3ee0(auStack_21c); // Allocate from stack pool?
                    FUN_006b8060(); // Pop context?
                }
                else {
                    iVar9 = FUN_008e3ee0(iVar9 + 0x50); // Allocate sub-object?
                }
            }
            else {
                // Use existing pointer from iStack_10?
                iVar9 = FUN_006b0ee0(iStack_10); // Create or get from pool?
                uStack_258._1_1_ = '\x01'; // Mark as used
            }

            if (iVar9 != 0) {
                FUN_006b4ac0(thisPtr); // Initialize some game state?
                *(int *)(iStack_18 * 0x5c + 0xd4 + thisPtr) = iVar9; // Store action pointer in slot
                // Also store in a local alias
                // _uStack_238 = iVar9 (not clear from decompiled)
                // store effectively: slot->actionPtr = iVar9
            }
            goto LAB_008e4977;
        }

        // If unaff_EDI is not null (external task manager present)
        // Set flags again
        if (iStack_18 == 1) {
            iVar10 = 0x20000;
        }
        else {
            iVar10 = 0x40000;
        }
        FUN_00508f40(iVar10, iStack_14 != 0);

        if (iStack_14 == 0) {
            // Allocate from same pattern
            iVar9 = FUN_00446100(iVar7 * 0x5c + 0x98 + thisPtr, 0);
            if (iVar9 == 0) {
                // Use stack buffer
                FUN_0078ec90(0, 0); // Clear something?
                iVar9 = FUN_00792900(auStack_1f8); // Allocate from another pool?
                FUN_0078ecf0(); // End?
            }
            else {
                iVar9 = FUN_00792900(iVar9 + 0x50);
            }
        }
        else {
            uStack_258 = 0x4cd601c2;
            iVar9 = iStack_14; // Use provided pointer
        }

        if (iVar9 != 0) {
            if (((*(uint *)(iVar9 + 0x5c) >> 0x13 & 1) == 0) && // Bit 19 not set
                (cVar3 = FUN_008e6510(iVar9 + 0x20), cVar3 == '\0')) {
                // Condition passes
                if (iStack_14 == 0) {
                    // Random chance (50%) to assign this action
                    uVar2 = (uint3)uStack_258;
                    uStack_258 &= 0xffffff;
                    int randVal = _rand();
                    if ((uint)(randVal % 100) < 0x32) { // 50% chance
                        iVar9 = iVar7 * 0x5c + thisPtr; // pointer to slot
                        uStack_258._0_3_ = CONCAT12(1, (undefined2)uStack_258);
                        uStack_258 = (uint)(uint3)uStack_258;
                        cVar3 = FUN_00445250();
                        if ((((cVar3 == '\0') || (cVar3 = FUN_004209a0(), cVar3 != '\0')) ||
                            (iVar7 = FUN_00446100(iVar9 + 0xa8, 0), iVar7 == 0)) ||
                            (iVar8 = FUN_008e3ee0(iVar7 + 0x50), iVar8 == 0)) {
                            // Fallback: allocate using stack pool
                            FUN_006b8040();
                            auStack_21c[0] = auStack_21c[0] | 1;
                            uStack_208 = 0x20;
                            iVar8 = FUN_008e3ee0(auStack_21c);
                            FUN_006b8060();
                            iVar7 = iStack_18;
                            if (iVar8 == 0) goto LAB_008e48b2;
                        }
                        // Success: store the action
                        FUN_006b4ac0(thisPtr);
                        FUN_00790c80(iVar8 + 0x1c); // Initialize some sub-object?
                        *(int *)(iVar9 + 0xd4) = iVar8; // Set action pointer in slot
                        iVar7 = iStack_18;
                    }
                    else {
                        // 50% chance to do different path using data from external sources
                        FUN_006b8040();
                        auStack_21c[0] = auStack_21c[0] | 1;
                        int tmpAlloc = FUN_008e3ee0(auStack_21c);
                        if (tmpAlloc != 0) {
                            // Loop over 2 entries in some global array (DAT_00d60c60)
                            uint *arrayPtr = DAT_00d60c60;
                            uVar6 = 0;
                            do {
                                puVar1 = (&arrayPtr)[uVar6];
                                FUN_009a3ea0(puVar1, 8, DAT_00d5ccf8); // Copy data?
                                FUN_005fcf80(tmpAlloc + 0x1c, auStack_1b4, puVar1); // Apply
                                FUN_005f6600(auStack_1a4); // Finalize?
                                // Check some inner condition
                                if (uStack_228 != 0) {
                                    if (iStack_220 != 0) {
                                        FUN_00790c80(iStack_220);
                                        uStack_258 = CONCAT13(1, uVar2);
                                        if (uStack_228 != 0) {
                                            FUN_004daf90(&uStack_228); // Release?
                                        }
                                        FUN_006a8490(); // Cleanup?
                                        iVar7 = iStack_18;
                                        break;
                                    }
                                    FUN_004daf90(&uStack_228);
                                }
                                FUN_006a8490();
                                uVar6 = uVar6 + 1;
                                iVar7 = iStack_18;
                            } while (uVar6 < 2);
                        }
                        FUN_006b8060();
                        if (uStack_258._3_1_ == '\0') {
                            iVar9 = 0; // Mark as failed
                        }
                    }
                }
            }
            else {
LAB_008e48b2:
                iVar9 = 0;
            }
        }
    }

    if ((unaff_EDI != (int *)0x0) && (iVar9 != 0)) {
        // Call vtable method at offset 0x14c on the external manager
        (**(code **)(*unaff_EDI + 0x14c))(iVar9 + 0x20);
        // Set up some timer/event
        if (thisPtr == 0) {
            iVar9 = 0;
        }
        else {
            iVar9 = thisPtr + 0x50;
        }
        FUN_00791e70(iVar9); // Set up timing?
        // Set bit 0x80000 (flag indicating task is active)
        *(uint *)(thisPtr + 0x5c) |= 0x80000;
        FUN_00790110(1);
        int player = FUN_00791300();
        int slotBase = iStack_1c * 0x5c + thisPtr; // slotBase pointer
        FUN_008e2560(unaff_ESI); // Update something
        FUN_006e61a0(player); // Play sound?
        puVar11 = (undefined8 *)FUN_00790cd0();
        // Copy quaternion data from some source
        *(undefined8 *)(slotBase + 0xd8) = *puVar11;
        *(undefined4 *)(slotBase + 0xe0) = *(undefined4 *)((char*)puVar11 + 8);
        // Set flags at +0xc0
        *(uint *)(slotBase + 0xc0) |= 4;
        cStack_25b = (char)((uint)&stack0xfffffdc4 >> 8);
        if (cStack_25b != '\0') {
            *(uint *)(slotBase + 0xc0) |= 1;
        }
        cStack_25a = (char)((uint)&stack0xfffffdc4 >> 0x10);
        if (cStack_25a != '\0') {
            *(uint *)(slotBase + 0xc0) |= 2;
        }
        return 1;
    }

LAB_008e4977:
    if ((uVar5 != 0) && (/* _uStack_238 from earlier */ actionPtr != 0)) {
        FUN_008e9860(*(undefined4 *)(actionPtr + 0x38)); // Process something
        FUN_008e2560(uVar5); // Update NPC?
        if (uStack_258._1_1_ != '\0') {
            uint *slotFlags = (uint *)(thisPtr + iVar7 * 0x5c + 0xc0);
            *slotFlags |= 1; // Set bit 0
        }
        return 1;
    }
    return 0;
}
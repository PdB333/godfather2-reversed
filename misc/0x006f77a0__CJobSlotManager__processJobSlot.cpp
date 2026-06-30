// FUNC_NAME: CJobSlotManager::processJobSlot
// Function at 0x006f77a0 - Handles a job/mission slot request, state machine for job execution
// Reconstructed from Ghidra decompile

bool __thiscall CJobSlotManager::processJobSlot(
    int param_2,           // some object (likely job data owner)
    int param_3,           // job hash/id
    uint param_4,          // unique job instance id
    undefined4 *param_5,   // pointer to vector (2 ints)
    uint param_6,          // flags
    undefined4 param_7,    // extra byte (packed into param_8 check)
    int *param_8           // pointer used as flag (char check)
) {
    // +0x00: vtable?
    // +0x04: signature part 1 (int)
    // +0x08: signature part 2 (int)
    // +0x0C: signature part 3 (int)
    // +0x10: signature part 4 (int)
    // +0x14: copied vector X (int)
    // +0x18: copied vector Y (int)
    // +0x1C: ? (not used)
    // +0x20: ? (not used)
    // +0x24: pointer to some timer/object (float at +0x04)
    // +0x28: slot index (0xFF means none)
    // +0x2C: state (0=idle, 1=waiting, 2=active, 3=?)

    bool bVar1;
    char cVar2;
    int iVar3;
    uint uVar4;
    undefined4 uVar5;
    int iVar6;
    uint uVar7;
    undefined4 uVar8;
    bool bResult = false; // local_29

    // local_20: seems to be a global pointer that may be freed
    // local_28: used as temp for param_4 or adjusted value
    // local_24: used for linked list manipulation

    uint local_28 = param_4;
    undefined4 local_24;
    int local_20[4];
    int local_10; // part of signature check
    int local_c;
    int local_8;
    int local_4;

    // Initialize local_20 with global data (likely a pointer to some alloc)
    local_20[0] = DAT_0112a9f4; // some global

    // Check if param_8 (as char) is 0 and if param_6 has bit 5 set (0x20)
    // Also check a global pointer from DAT_012233a0+4
    if ((((char)param_8 == '\0') && ((param_6 & 0x20) != 0)) &&
        (iVar6 = **(int **)(DAT_012233a0 + 4), iVar6 != 0) &&
        ((iVar6 != 0x1f30 && ((*(byte *)(iVar6 + -0x164a) & 1) != 0)))) {
        // If conditions met, clear bit 5 from param_6
        param_6 = param_6 & 0xffffffdf;
    }

    // Copy signature from this+4,8,0xC,0x10
    local_c = *(int *)(this + 8);
    local_8 = *(int *)(this + 0xc);
    local_4 = *(int *)(this + 0x10);
    local_10 = *(int *)(this + 4);

    iVar6 = 0; // reset flag
    uVar7 = param_4; // save original param_4

    // Signature validation: Check if signature matches known pattern
    if (local_10 == -0x45245246) {
        // Check the other three parts
        if (((local_c != -0x41104111) || (local_8 != -0x153ea5ab)) || (local_4 != -0x6eeff6ef)) {
            // Not the expected job type, try fallback check
            goto LAB_006f78c4;
        }
    } else if (((local_10 != 0) || (local_c != 0)) || ((local_8 != 0 || (local_4 != 0)))) {
        // Non-zero signature that doesn't match the known one
        goto LAB_006f78c4;
    }
    // If we reach here, signature is either known pattern or all zeros (idle slot)

    // Check timer condition: this+0x24 points to some object with float at +0x04
    iVar3 = *(int *)(this + 0x24);
    bVar1 = true;
    if (((iVar3 != 0) && (DAT_01205214 < *(float *)(iVar3 + 4))) &&
        (((char)param_8 == '\0' &&
          ((((param_3 != -0x1246afbe && (param_3 != 0x7860a0fb)) && (param_3 != 0x13bd7494)) &&
            (param_3 != 0x5901c818)))))) {
        bVar1 = false; // Disallow if timer expired and not for specific job hashes
    }

    // If iVar6 is 0 (some prior check failed), return 0
    if (iVar6 == 0) {
        return 0;
    }

    if (!bVar1) {
        return 0;
    }

    // State machine
    switch (*(undefined4 *)(this + 0x2c)) {
    case 0: // IDLE
        break; // Do nothing (fall through to later code)

    case 1: // WAITING for response
        param_8 = (int *)0x0; // reuse param_8 as temp pointer
        if (*(int *)(this + 0x28) == 0xff) {
            // No slot assigned
            FUN_006f7680(); // reset slot
            *(undefined4 *)(this + 0x2c) = 0;
            return 0;
        }
        // Get slot info by index
        FUN_006f0870(&param_8, *(int *)(this + 0x28));
        if (param_8 == (int *)0x0) {
            // Slot not found
            FUN_006f7680();
            FUN_006f7300(); // deactivate
            *(undefined4 *)(this + 0x2c) = 0;
            return 0;
        }
        // Check if request matches the already pending job
        if ((param_3 == *(int *)((int)param_8 + 0xc)) && (param_4 == *(uint *)((int)param_8 + 0x10))) {
            return 0; // Already pending, ignore
        }
        // Different job: cancel current
        FUN_006f7300();
        FUN_006fc4c0(&LAB_006f7670, this); // set up callback
        break;

    case 2:
    case 3:
        // Check if enough time has passed since last operation
        uVar4 = FUN_006f0970(iVar3); // get elapsed time
        if (uVar7 <= uVar4) {
            return 0; // Not enough time
        }
        FUN_006f76b0(); // acknowledge completion
        break;

    default:
        goto switchD_006f78ad_default;
    }

    // Prepare to execute the job
    if (param_2 == 0) {
        local_28 = 0; // No object
    } else {
        local_28 = param_2 + 0x48; // Some offset in param_2 object (maybe a linked list node)
    }

    local_24 = 0;
    if (local_28 == 0) {
LAB_006f79d9:
        iVar6 = 0;
    } else {
        local_24 = *(undefined4 *)(local_28 + 4);
        *(uint **)(local_28 + 4) = &local_28; // Insert into linked list
        if (local_28 == 0) goto LAB_006f79d9;
        iVar6 = local_28 - 0x48; // Get back to original object
    }

    // Execute the job operation
    iVar6 = FUN_006fe120(iVar6, uVar7, DAT_00e445ac, &LAB_006f7670, this);

    // Remove from linked list if was inserted
    if (local_28 != 0) {
        FUN_004daf90(&local_28); // free or remove node
    }

    if (iVar6 == 2) { // SUCCESS
        // Copy vector from param_5 into this+0x14/+0x18
        if ((undefined4 *)(this + 0x14) != param_5) {
            *(undefined4 *)(this + 0x14) = *param_5;
            *(undefined4 *)(this + 0x18) = param_5[1];
        }

        uVar8 = 0;
        uVar5 = FUN_004618f0(param_2); // Get some id from param_2 object
        cVar2 = FUN_006f73a0(uVar5, param_3, param_4, param_6, param_7, uVar8);
        if (local_20[0] != 0) {
            FUN_004daf90(local_20); // free
        }
        if (cVar2 != '\0') {
            // Activation succeeded
            *(undefined4 *)(this + 0x2c) = 2; // Set state to ACTIVE
            FUN_006f7300(); // deactivate something? (misnomer, maybe start)
            return 1;
        }

        // Activation failed
        uVar5 = FUN_006fbc40(0, 0); // Create error
        FUN_006f04e0(uVar5); // set error data
        FUN_006fbc70(); // submit error
        *(undefined4 *)(this + 0x2c) = 0; // Back to IDLE
        FUN_006f7300();
        return 0;
    }

    if (iVar6 == 1) { // PENDING (will wait for callback)
        param_8 = (int *)0x0;
        if (*(int *)(this + 0x28) == 0xff) {
            // No slot index, allocate new slot
            FUN_006f0820(&param_8, this + 0x28);
        } else {
            // Get existing slot by index
            FUN_006f0870(&param_8, *(int *)(this + 0x28));
        }

        if (param_8 != (int *)0x0) {
            // Fill slot with job data
            *param_8 = this; // back pointer to manager
            FUN_0046bae0(param_2); // reference object?
            param_8[3] = param_3; // job hash
            param_8[4] = param_4; // instance id
            FUN_006f04e0(param_5); // copy vector?
            param_8[9] = param_6; // flags
            *(undefined1 *)(param_8 + 10) = (undefined1)param_7; // extra byte
            *(undefined4 *)(this + 0x2c) = 1; // Set state to WAITING
            bResult = true;
        }
    }

switchD_006f78ad_default:
    return bResult;
}
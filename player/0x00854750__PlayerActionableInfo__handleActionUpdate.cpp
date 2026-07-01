// FUNC_NAME: PlayerActionableInfo::handleActionUpdate
// Address: 0x00854750
// Handles player action processing: manages active grenade/throw list, checks input, distance, and spawns effects.
// The function seems to manage a linked list of active items (maybe grenades or tools) and processes player input to trigger actions.

void __thiscall PlayerActionableInfo::handleActionUpdate(PlayerActionableInfo *this, int *param_2, undefined4 param_3)
{
    char cVar1;
    float fVar7;
    float fVar8;
    float fVar9;
    int iVar3;
    uint uVar4;
    undefined4 uVar5;
    int *piVar6;
    int unaff_EBX; // uninitialized in decompilation, likely from register reuse
    int unaff_EBP; // uninitialized in decompilation, likely from register reuse
    int unaff_ESI; // uninitialized in decompilation, likely from register reuse
    int unaff_EDI; // uninitialized in decompilation, likely from register reuse
    undefined8 *unaff_retaddr; // decompiler artifact, likely used as stack base
    undefined4 uVar10;

    // Local "linked list" nodes stored as float* due to decompilation artifact
    // They are actually pointers to heap-allocated structures (ActiveItem nodes)
    float *pfStack_b8;
    float fStack_a4; // temp
    int iStack_a0;   // used as pointer
    float fStack_98; // local head pointer for first list (from param_1[1])
    undefined4 uStack_94; // next pointer of node
    float fStack_90; // local head pointer for second list (from param_1[0])
    float fStack_8c; // next pointer of node
    float fStack_88; // position component (from global state)
    undefined4 uStack_84;
    undefined4 uStack_80;
    undefined4 uStack_7c;
    float fStack_78; // action parameter (damage? multiplier?)
    undefined4 uStack_70; // action type
    undefined4 uStack_6c; // counter?
    int *piStack_68; // hold param_2
    undefined4 uStack_64;
    undefined4 uStack_60; // hold param_3
    undefined1 auStack_5c [88]; // buffer for synchronization
    int *piStack_4; // decompiler alias for this? actually unknown

    pfStack_b8 = (float *)0x85476c; // debug string placeholder

    // Check if action is allowed via virtual function on param_2 (likely InputManager or PlayerSM)
    cVar1 = (**(code **)(*param_2 + 0x78))(); // virtual call: canPerformAction?
    if (cVar1 == '\0') {
        pfStack_b8 = (float *)0x854778;
        cVar1 = FUN_00481640(); // possibly another permission check
        if (cVar1 == '\0') {
            return; // action not allowed
        }
    }

    pfStack_b8 = (float *)0x854789;
    FUN_0084dd20(); // some pre-action logic (maybe begin action sequence)

    // Manage first linked list: active items attached to this->+0x04 (param_1[1])
    // The list is stored at offset 0x48 from the item? Actually param_1[1] points to an object, and +0x48 is the list head.
    if (this[1] == 0) {
        fVar7 = 0.0f;
    }
    else {
        fVar7 = (float)(this[1] + 0x48); // treat pointer as float
    }
    // fStack_98 is local head pointer. Insert/remove node from list.
    if (fStack_98 != fVar7) {
        if (fStack_98 != 0.0f) {
            pfStack_b8 = &fStack_98;
            FUN_004daf90(); // remove from list (maybe free node)
        }
        fStack_98 = fVar7;
        if (fVar7 != 0.0f) {
            uStack_94 = *(undefined4 *)((int)fVar7 + 4); // save next pointer
            *(float **)((int)fVar7 + 4) = &fStack_98; // set next to local head
        }
    }

    // Manage second linked list: active items from this->+0x00 (param_1[0])
    if (*this == 0) {
        fVar7 = 0.0f;
    }
    else {
        fVar7 = (float)(*this + 0x48);
    }
    if (fStack_90 != fVar7) {
        if (fStack_90 != 0.0f) {
            pfStack_b8 = &fStack_90;
            FUN_004daf90();
        }
        fStack_90 = fVar7;
        if (fVar7 != 0.0f) {
            fStack_8c = *(float *)((int)fVar7 + 4);
            *(float **)((int)fVar7 + 4) = &fStack_90;
        }
    }

    pfStack_b8 = (float *)0x854805;
    iVar3 = FUN_00471610(); // get global state (e.g., GameManager or Player)
    fStack_88 = (float)*(undefined8 *)(iVar3 + 0x30); // double at offset 0x30 (position X?)
    uStack_84 = (undefined4)((ulonglong)*(undefined8 *)(iVar3 + 0x30) >> 0x20);
    uStack_80 = *(undefined4 *)(iVar3 + 0x38); // position Z?
    uStack_6c = 2;

    // Check input state from second list head (fStack_90 points to an ActiveItem node)
    if (fStack_90 == 0.0f) {
        piVar6 = (int *)0x0;
    }
    else {
        piVar6 = (int *)((int)fStack_90 + -0x48); // backlink to owning item (offset -0x48 from the node)
    }
    pfStack_b8 = &fStack_a4;
    fStack_a4 = 0.0f;
    cVar1 = (**(code **)(*piVar6 + 0x10))(); // virtual call on the item (e.g., isActive?)
    if ((cVar1 != '\0') && (unaff_EBP != 0)) { // unaff_EBP is probably a condition from earlier
        uVar2 = FUN_00800be0(); // get input type (maybe enum for action)
        switch(uVar2) {
        case 0x14: // button hash? 20 decimal
            uStack_70 = 1; // action type 1
            break;
        case 0x15:
            uStack_70 = 2;
            break;
        case 0x16:
            uStack_70 = 3;
            break;
        case 0x17:
            uStack_70 = 4;
            break;
        case 0x18:
            uStack_70 = 5;
            break;
        }
    }

    fStack_78 = (float)this[4]; // damage/strength from this->+0x10
    uStack_64 = DAT_01205224; // global constant?
    uStack_7c = *(undefined4 *)(unaff_retaddr + 1); // decompiler artifact, likely part of stack
    uStack_6c = 3; // counter or type
    uStack_84 = (undefined4)*unaff_retaddr; // low part of double from earlier?
    uStack_80 = (undefined4)((ulonglong)*unaff_retaddr >> 0x20); // high part
    piStack_68 = param_2;
    uStack_60 = param_3;

    // Get current position from global state
    iVar3 = FUN_00471610();
    fVar7 = *(float *)(iVar3 + 0x30) - fStack_90; // delta X
    fVar8 = *(float *)(iVar3 + 0x34) - fStack_8c; // delta Y
    fVar9 = *(float *)(iVar3 + 0x38) - fStack_88; // delta Z

    // Check if within range (squared distance <= radius from this->+0x50?)
    if (fVar9 * fVar9 + fVar8 * fVar8 + fVar7 * fVar7 <= (float)this[0x14]) {
        fStack_78 = (float)this[0x15] * fStack_78; // apply multiplier
    }

    // Query player state via hash-based message passing (typical EA EARS pattern)
    cVar1 = (**(code **)(*piStack_4 + 0x10))(0x383225a1, &stack0xffffff54); // hash 0x383225a1 = ? (maybe "isThrowing")
    if ((cVar1 == '\0') || (unaff_EDI == 0)) {
        cVar1 = (**(code **)(*piStack_4 + 0x10))(0x369ac561, &stack0xffffff4c); // hash 0x369ac561 = ? (maybe "isFiring")
        if (cVar1 != '\0') {
            // handle firing
            if (unaff_EBX == 0) {
                piVar6 = (int *)0x0;
            }
            else {
                piVar6 = (int *)(unaff_EBX + -0x48);
            }
            pfStack_b8 = (float *)0x0;
            cVar1 = (**(code **)(*piVar6 + 0x10))(0x383225a1, &pfStack_b8);
            uVar4 = -(uint)(cVar1 != '\0') & (uint)pfStack_b8; // conditional result
            if (unaff_EBX == 0) {
                iVar3 = 0;
            }
            else {
                iVar3 = unaff_EBX + -0x48;
            }
            cVar1 = FUN_0072f180(iVar3); // check if object is valid/alive
            if (cVar1 != '\0') {
                if (**(int **)(DAT_012233a0 + 4) == 0) {
                    iVar3 = 0;
                }
                else {
                    iVar3 = **(int **)(DAT_012233a0 + 4) + -0x1f30; // offset to player component
                }
                cVar1 = FUN_0072f180(iVar3);
                if (cVar1 != '\0') {
                    uVar10 = 0;
                    uVar5 = FUN_006fbc40(0, 0); // get some state (maybe player ID)
                    if (uVar4 == 0) {
                        // Spawn effect (hash 0x487b57e1 = ? "effect_throw_miss"?)
                        FUN_007f96a0(0x487b57e1, 100, uVar5, uVar10);
                        FUN_006fbc70(); // cleanup
                    }
                    else {
                        // Spawn effect (hash 0x68269bd7 = ? "effect_throw_hit"?)
                        FUN_007f96a0(0x68269bd7, 100, uVar5, uVar10);
                        FUN_006fbc70();
                    }
                }
            }
        }
    }
    else {
        // Throwing case
        if (iStack_a0 == 0) {
            piVar6 = (int *)0x0;
        }
        else {
            piVar6 = (int *)(iStack_a0 + -0x48);
        }
        cVar1 = (**(code **)(*piVar6 + 0x10))(0x369ac561, &stack0xffffff4c);
        if ((cVar1 != '\0') && ((uRam5585be4e >> 9 & 1) != 0)) {
            goto LAB_00854aff;
        }
    }

    // Networking/ synchronization steps
    cVar1 = FUN_00481660(); // check if server?
    if (cVar1 != '\0') {
        FUN_0084d330(); // start network sync
        FUN_0084dda0(&stack0xffffff4c); // pack data
        FUN_0070b6a0(auStack_5c); // send buffer
        FUN_004a8ec0(piStack_4 + 0x16); // increment sequence?
        FUN_0084e1c0(); // end sync
    }

    FUN_00408bb0(&DAT_0112dd94, piStack_4 + 0xf, &stack0xffffff4c, 0); // some accumulation or log

LAB_00854aff:
    if (unaff_EBX != 0) {
        FUN_004daf90(&stack0xffffff58); // cleanup list node
    }
    if (unaff_ESI != 0) {
        FUN_004daf90(&stack0xffffff50); // cleanup list node
    }
    return;
}
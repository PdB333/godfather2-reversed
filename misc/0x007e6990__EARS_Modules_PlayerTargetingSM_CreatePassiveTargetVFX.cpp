// Xbox PDB: EARS_Modules_PlayerTargetingSM_CreatePassiveTargetVFX
// FUNC_NAME: PlayerTargetingManager::updateLockIndicators

void __thiscall PlayerTargetingManager::updateLockIndicators(
    PlayerTargetingManager* this,
    undefined4 param2_unused,
    int* pTargetEntity,
    const char* lockIconName)
{
    float* pfVar1;
    char cVar2;
    int* piVar3;
    undefined4* puVar4;
    undefined4 uVar5;
    int iVar6;
    undefined4* puVar7;
    float* pfVar8;
    int iStack_c0;
    int local_b8;
    float afStack_b4[3];
    undefined4 local_a8;
    int* local_a4;                      // pointer to this->m_targetListHead.next
    undefined1 auStack_a0[16];
    undefined1 local_90[64];
    undefined4 local_50[19];

    local_a4 = (int*)(this + 0x26c);   // +0x26c: list head next pointer

    // Get the current target entity from the list head node
    if (*local_a4 == 0) {
        piVar3 = (int*)0x0;
    } else {
        piVar3 = (int*)(*local_a4 - 0x48); // entity is at list node + 0x48
    }

    // Only update if the target changed
    if (pTargetEntity != piVar3) {
        local_b8 = (int)this;

        // Copy current camera/view transform (likely world-to-screen)
        puVar4 = (undefined4*)FUN_00471610(); // returns pointer to 16 floats (4x4 matrix)
        puVar7 = local_50;
        for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
            *puVar7 = *puVar4;
            puVar4 = puVar4 + 1;
            puVar7 = puVar7 + 1;
        }
        FUN_0044b4e0(local_90, local_50); // convert to some internal format?

        // Initialize lock indicator data
        afStack_b4[1] = 0.0;
        local_a8 = 0;
        afStack_b4[2] = (float)DAT_00d6fa5c; // some constant
        FUN_004df590(); // Reset/init something (could be matrix identity)
        pfVar8 = (float*)(iVar6 + 0x268); // this+0x268: head lock indicator handle
        FUN_004df590(); // Reset again

        cVar2 = FUN_00481660(); // Check if we should show lock indicators?
        if (cVar2 == '\0') {
            // --- Update body lock indicator ---
            local_b8 = (**(code**)(*pTargetEntity + 0x58))(); // target's vfunc: get world position?
            FUN_004eacb0(lockIconName); // set icon asset name
            FUN_004df420(afStack_b4, auStack_a0, local_90, local_b8,
                        0, pTargetEntity, 0xffffffff, afStack_b4 + 1);
            // afStack_b4[0] now holds new lock indicator handle (float*)

            // Remove old body lock indicator if present
            if (*pfVar1 != 0.0) {
                *(undefined4*)((int)*pfVar1 + 8) = 0; // clear next pointer? Actually it's a node removal
                *pfVar1 = 0.0;
            }
            *pfVar1 = afStack_b4[0]; // store new indicator handle
            if (afStack_b4[0] != 0.0) {
                *(float**)((int)afStack_b4[0] + 8) = pfVar1; // link back to list
            }

            // Check if passive lock head condition is met
            local_b8 = 0;
            cVar2 = (**(code**)(*pTargetEntity + 0x10))(0x369ac561, &local_b8); // hash check
            if (((cVar2 != '\0') && (iStack_c0 != 0)) &&
                (*(char*)(iStack_c0 + 0x211c) != '\0')) {
                afStack_b4[0] = DAT_00e53424 + afStack_b4[0]; // offset for head lock
            }

            // --- Update head lock indicator ---
            uVar5 = (**(code**)(*pTargetEntity + 0x58))(); // again get world position
            FUN_004eacb0("hud_passivelock_head");
            FUN_004df420(afStack_b4, auStack_a0, local_90, uVar5,
                        0, pTargetEntity, 0xffffffff, afStack_b4 + 1);

            // Remove old head lock indicator
            if (*pfVar8 != 0.0) {
                *(undefined4*)((int)*pfVar8 + 8) = 0;
                *pfVar8 = 0.0;
            }
            *pfVar8 = afStack_b4[0];
            if (afStack_b4[0] != 0.0) {
                *(float**)((int)afStack_b4[0] + 8) = pfVar8;
            }
        }

        // Update the target list
        piVar3 = local_a4;
        if (pTargetEntity == (int*)0x0) {
            pTargetEntity = (int*)0x0;
        } else {
            pTargetEntity = pTargetEntity + 0x12; // offset to list node inside entity (+0x48 bytes)
        }

        // Check if list head needs updating
        if ((int*)*local_a4 != pTargetEntity) {
            // Remove old list head entity if present
            if ((int*)*local_a4 != (int*)0x0) {
                FUN_004daf90(local_a4); // unlink node from list
            }
            *piVar3 = (int)pTargetEntity; // set new list head
            if (pTargetEntity != (int*)0x0) {
                // Link new node: node->prev = address of list head, list head->next = node
                piVar3[1] = pTargetEntity[1]; // set head->prev = node->prev?
                pTargetEntity[1] = (int)piVar3; // node->next = &list head
            }
        }
    }
}
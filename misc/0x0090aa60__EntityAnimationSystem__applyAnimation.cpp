// FUNC_NAME: EntityAnimationSystem::applyAnimation
// Function address: 0x0090aa60
// This function applies an animation to an entity, managing state, linking, and possibly setting a target pose.
void __thiscall EntityAnimationSystem::applyAnimation(uint *this, int entity, int manager, int animationId, int *targetData)
{
    uint uVar1;
    uint uVar2;
    char cVar3;
    int iVar4;
    int iVar5;
    uint *puVar6;

    if (entity != 0) {
        // Set flag bit 1 (0x2) in this->flags
        *this = *this | 2;

        iVar4 = FUN_00791300(); // Get some global state (maybe time or frame counter)

        if (animationId == 0) {
            // If no specific animation, maybe use something from a global entity data
            if ((iVar4 != 0) && (iVar5 = FUN_0043b870(DAT_01131040), iVar5 != 0)) {
                // Read byte from entity + 0x44, mask with 0xFC, store in this[4] (this->byteMask)
                this[4] = *(byte *)(iVar5 + 0x44) & 0xfc;
            }
        } else {
            // If animation ID provided, play that animation (via another function)
            FUN_0090a610(animationId);
        }

        // Manage a linked list node at this[2] (offset +8)
        puVar6 = this + 2;
        uVar1 = entity + 0x48; // Expected value for the node pointer
        if (this[2] != uVar1) {
            if (this[2] != 0) {
                FUN_004daf90(puVar6); // Release old node
            }
            *puVar6 = uVar1; // Set new node pointer
            if (uVar1 != 0) {
                this[3] = *(uint *)(entity + 0x4c); // Copy next pointer from entity's linked list
                *(uint **)(entity + 0x4c) = puVar6; // Insert this as new head of entity's list
            }
        }

        FUN_00791670(this[1], 1); // Notify something with handle (this[1])

        uVar2 = *(uint *)(manager + 0x1ed4); // Get some manager-specific ID or state
        *(uint *)(entity + 0x5c) = *(uint *)(entity + 0x5c) & 0xffffffbf; // Clear bit 6 in entity flags
        FUN_007913f0(uVar2, 1); // Another notification/callback

        iVar5 = FUN_008c12a0(entity); // Check entity state
        if (iVar5 == 0) {
            FUN_008c5460(entity); // Perform some initialization or reset
        }

        // If target data is provided and not all zeros, and some global condition passes, apply target
        if (((targetData != (int *)0x0) &&
            (((*targetData != 0 || (targetData[1] != 0)) || (targetData[2] != 0) || (targetData[3] != 0)))) &&
            (cVar3 = FUN_00445250(), cVar3 != '\0')) {
            FUN_0090a7e0(targetData); // Set target pose/position
            return;
        }

        if (iVar4 == 0) {
            // If global state is zero, try to evaluate a pose from entity's sub-component
            iVar4 = FUN_004461c0(entity + 0x7c, 0); // Get something from entity sub-object
            if (iVar4 != 0) {
                FUN_0043aff0(iVar4, 0xa0d329d6); // Start evaluation with a hash (maybe animation ID)
                cVar3 = FUN_0043b120(); // Check if evaluation is possible
                if (cVar3 == '\0') {
                    // Loop until evaluation settles or becomes impossible
                    while( true ) {
                        FUN_0043b210(); // Advance evaluation step
                        iVar4 = FUN_0043ab70(); // Check evaluation status (1 = done)
                        if (iVar4 == 1) break;
                        FUN_0043b1a0(); // Handle intermediate step
                        cVar3 = FUN_0043b120(); // Recheck possibility
                        if (cVar3 != '\0') {
                            return;
                        }
                    }
                    FUN_0043b210(); // Finalize evaluation
                    puVar6 = (uint *)FUN_0043abc0(); // Get result pose (likely a quaternion)
                    // Copy 4 uint result into this[5..8]
                    this[5] = *puVar6;
                    this[6] = puVar6[1];
                    this[7] = puVar6[2];
                    this[8] = puVar6[3];
                }
            }
        } else {
            // If global state is non-zero, read pose from a different data source
            iVar4 = *(int *)(iVar4 + 0x74c); // Dereference chain (iVar4 was from FUN_00791300)
            if ((iVar4 != 0) && (iVar4 != 0x48)) {
                // Copy 4 uint from (iVar4 - 0x28) into this[5..8] (offset from some structure)
                this[5] = *(uint *)(iVar4 + -0x28);
                this[6] = *(uint *)(iVar4 + -0x24);
                this[7] = *(uint *)(iVar4 + -0x20);
                this[8] = *(uint *)(iVar4 + -0x1c);
                return;
            }
        }
    }
    return;
}
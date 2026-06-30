// FUNC_NAME: InteractionManager::checkProximityInteraction
// Address: 0x007321e0
// Role: Checks if the player is within a certain distance of a target (e.g., NPC or object) and triggers an interaction if so.

void InteractionManager::checkProximityInteraction(void)
{
    int iVar1;
    int iVar2;
    float fVar3;
    float fVar4;
    float fVar5;

    // Dereference global pointer to get the player object (or active entity) from DAT_012233a0 + 4
    iVar1 = **(int **)(DAT_012233a0 + 4);

    // Check if the pointer is valid and not an invalid sentinel (0x1f30 = 7984)
    if (((iVar1 != 0) && (iVar1 != 0x1f30)) && ((*(uint *)(iVar1 + 0x574) >> 7 & 1) != 0)) {
        // Get two objects (likely the player and a target/NPC) using some manager function
        iVar1 = FUN_00471610();  // probably returns pointer to player
        iVar2 = FUN_00471610();  // probably returns pointer to target (e.g., interactable object)

        // Compute difference in position (offset 0x30 = x, 0x34 = y, 0x38 = z)
        fVar3 = *(float *)(iVar2 + 0x30) - *(float *)(iVar1 + 0x30);  // dx
        fVar4 = *(float *)(iVar2 + 0x34) - *(float *)(iVar1 + 0x34);  // dy
        fVar5 = *(float *)(iVar2 + 0x38) - *(float *)(iVar1 + 0x38);  // dz

        // Squared distance check against a global threshold (DAT_00d62b60)
        if (fVar5 * fVar5 + fVar4 * fVar4 + fVar3 * fVar3 < DAT_00d62b60) {
            // Within range, trigger the interaction action
            FUN_00806090();
            return;
        }
    }
    return;
}
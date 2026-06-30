// FUNC_NAME: CMissionManager::createOrActivateObjective
// Address: 0x00717730
// Role: Creates or activates an objective, optionally including initialization of a definition.
// Handles both new objectives (param_3 != 0) and existing ones by searching and setting state.

int __thiscall CMissionManager::createOrActivateObjective(int thisPtr, undefined4 objectiveId, char isNewObjective)
{
    undefined4 tempGlobal;
    int activeObjective;
    char creationContext[8];       // +0x00, 8-byte buffer for objective creation
    int tempObject[7];            // +0x08, 28-byte buffer for temporary objective data

    if (isNewObjective != '\0') {
        // Look up objective definition by hash (0x88886a27)
        int objDef = FUN_007295e0(0x88886a27);
        // Copy the objective ID from the definition's field at +0x50
        FUN_006ada80(objectiveId, *(undefined4 *)(objDef + 0x50));
        // Create a new objective instance using the definition and global data
        FUN_00721aa0(objDef, DAT_00d61a98, creationContext);
        // Cleanup temporary object if it was allocated
        if (tempObject[0] != 0) {
            FUN_004daf90(tempObject);
        }
    }

    // Find existing active objective by ID, or create a default one
    activeObjective = FUN_0071ce70(objectiveId);
    if ((activeObjective == 0) && ((activeObjective = FUN_0071ce20(), activeObjective == 0))) {
        // No objective available
        return 0;
    }

    // Objective is valid; register it and set its state
    tempGlobal = DAT_01205228;             // Global current objective or state
    FUN_0071c720(*(int *)(thisPtr + 0x18), objectiveId, DAT_01205228); // Add to list at this+0x18
    *(int *)(activeObjective + 0x2c) = tempGlobal;  // Set objective's current state
    FUN_0071bfd0(tempGlobal);                       // Add reference
    *(ushort *)(activeObjective + 0x3c) |= 2;       // Set flag bit 1

    // Repeat assignment (likely second field or redundant; keep as decompiled)
    tempGlobal = DAT_01205228;
    *(int *)(activeObjective + 0x2c) = DAT_01205228;
    FUN_0071bfd0(tempGlobal);
    *(ushort *)(activeObjective + 0x3c) |= 2;

    if (isNewObjective != '\0') {
        // Mark as new objective (flag bit 3)
        *(ushort *)(activeObjective + 0x3c) |= 8;
    }

    return activeObjective;
}
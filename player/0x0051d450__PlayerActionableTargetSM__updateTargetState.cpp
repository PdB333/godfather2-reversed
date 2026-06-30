// FUNC_NAME: PlayerActionableTargetSM::updateTargetState
void __fastcall PlayerActionableTargetSM::updateTargetState(int this)
{
    int targetNodePtr = *(int *)(this + 0xc4); // +0xC4: pointer to target node in action tree
    int* targetList = nullptr;

    // If no valid target node, or node offset resolved to null
    if (targetNodePtr == 0 || (targetList = (int*)(targetNodePtr - 0x48), targetList == (int*)0x0)) {
        // Check if owner has the INTERACT flag (0x1000) and we have an active target
        if ((*(uint *)(*(int *)(this + 0x10) + 0x14) & 0x1000) != 0 &&
            *(int *)(this + 0xb4) != 0) {
            // Set flag to indicate we're performing an interaction (0x20000)
            if ((*(uint *)(this + 0xc) & 0x20000) == 0) {
                *(uint *)(this + 0xc) |= 0x20000;
                startInteraction(); // FUN_0051b120
            }
            // Clear the "ready for interaction" flag (0x40000)
            *(uint *)(this + 0xc) &= 0xFFFBFFFF;
        }
        // Reset active target pointer
        *(undefined4 *)(this + 0xb4) = 0;
        clearTarget(0); // FUN_0051d230
    }
    else {
        // We have a valid target candidate
        *(int **)(this + 0xb4) = targetList;
        // Call virtual function at vtable[22] (0x58/4) - returns some value related to target
        uVar3 = (**(code **)(*targetList + 0x58))();
        *(undefined4 *)(this + 0x84) = uVar3;

        // Prepare output parameter block for query
        int paramBlock[15] = {0}; // auStack_94

        // Call virtual function at vtable[4] with a hash to get target info
        bool hasTarget = (bool)(**(code **)(*targetList + 0x10))(0xAE986323, paramBlock);

        // Check if target exists, player global is valid, and player is not already in a critical state
        if (hasTarget && thePlayer != 0 &&
            *(int *)(thePlayer + 0x218) != 0 &&
            (*(uint *)(*(int *)(thePlayer + 0x218) + 0x10) & 0x4480000) == 0) {
            // Copy target transform/matrix from target node (offset +0x88) to local buffer
            copyTransform((char*)&stack_local_58, targetNodePtr + 0x88); // FUN_0044b4e0
            // Launch something using our member at +0xB8 and the transformed data
            launchProjectileOrAction(*(undefined4 *)(this + 0xb8), &stack); // FUN_0051cfb0
            finalizeAction(); // FUN_00417560
            return;
        }

        // If owner still has INTERACT flag active, restart the interaction
        if ((*(uint *)(*(int *)(this + 0x10) + 0x14) & 0x1000) != 0) {
            if ((*(uint *)(this + 0xc) & 0x20000) == 0) {
                *(uint *)(this + 0xc) |= 0x20000;
                startInteraction(); // FUN_0051b120
            }
            *(uint *)(this + 0xc) &= 0xFFFBFFFF;
            return;
        }
    }
    return;
}
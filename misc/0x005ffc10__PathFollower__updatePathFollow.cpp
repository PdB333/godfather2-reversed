// FUNC_NAME: PathFollower::updatePathFollow
// Address: 0x005ffc10
// Role: Updates path following logic: moves entity along path node list, handles target transitions, and computes velocity.

int PathFollower::updatePathFollow(
    Navigation* navManager,
    float* currentPos, // +0x00 current world position (x, z? possibly 2D)
    float* targetPos,  // +0x00 desired position (x, z) to steer toward; also used for velocity input
    void* userData     // opaque context, likely timeStep or game state
) {
    float fVar9;
    float fVar10, fVar11;
    float local_18, local_14;
    bool bVar5;
    char cVar6;
    int iVar7, iVar8;
    undefined4 *puVar1;

    // Global time step constant (probably seconds per tick)
    fVar9 = DAT_00e448bc;

    // Accumulate time for movement (unaff_EDI[1] is a float array, likely velocity accumulator)
    unaff_EDI[1] = unaff_EDI[1] + fVar9;
    targetPos[1] = targetPos[1] + fVar9; // update second element of targetPos (maybe time?)

    // Read current target position stored in this object (+0x20 = x, +0x28 = z)
    local_18 = *(float*)(this + 0x20); // targetX
    local_14 = *(float*)(this + 0x28); // targetZ

    bVar5 = false;
    // If target position is zero vector ((0,0,0)) 
    // OR squared distance from currentPos to target < threshold, then set target to input targetPos
    if (((((local_18 == 0.0f) && (*(float*)(this + 0x24) == 0.0f)) && (local_14 == 0.0f)) &&
        (*(float*)(this + 0x2c) == 0.0f)) ||
        ((currentPos[0] - local_18) * (currentPos[0] - local_18) +
         (currentPos[1] - local_14) * (currentPos[1] - local_14) < DAT_00e2b1a4)) {
        // Update stored target to input targetPos (3 components)
        *(float*)(this + 0x20) = targetPos[0];
        *(float*)(this + 0x24) = targetPos[1];
        *(float*)(this + 0x28) = targetPos[2];
        *(float*)(this + 0x2c) = targetPos[3]; // likely 4th component (unused?)
        bVar5 = true;
    }

    // Query nearest path node given current position and accumulated time
    iVar7 = navManager->findClosestNode(currentPos, 0, userData, unaff_EDI[1]); // 0 = flag?

    // If a node was found and we just set a new target, check distance to node
    if (((iVar7 == 0) || (!bVar5)) ||
        (fVar10 = currentPos[0] - *(float*)(iVar7 + 0x10), 
         fVar9 = currentPos[1] - *(float*)(iVar7 + 0x14),
         *(float*)(iVar7 + 0x18) * *(float*)(iVar7 + 0x18) <= fVar10 * fVar10 + fVar9 * fVar9)) {
        // Clear bit 0x1000 (4096) in flags +0xB4
        *(uint*)(this + 0xB4) &= 0xFFFFEFFF;
    } else {
        // Set bit 0x1000
        *(uint*)(this + 0xB4) |= 0x1000;
    }

    if (iVar7 != 0) {
        if ((!bVar5) && 
            (iVar8 = navManager->findClosestNode(&local_18, 0, userData, unaff_EDI[1]), iVar8 == 0)) {
            // If we didn't set a new target and the old target has no node, revert to old target position
            currentPos[0] = local_18;
            currentPos[1] = local_14;
            *(float*)(this + 0x10) = currentPos[0]; // +0x10 = own position x
            *(float*)(this + 0x18) = currentPos[1]; // +0x18 = own position z
            iVar7 = 0;
            cVar6 = (*(code**)(this + 0xA8))(); // call a function pointer (callback)
            if (cVar6 == '\0') {
                return 1;
            }
        }

        *(undefined1*)(this + 0x40) = 1; // path active flag

        iVar8 = *(int*)(this + 0x44); // current node pointer (linked list)
        if (iVar8 != iVar7) {
            if (iVar8 != 0) {
                navManager->removeNodeFromList((int*)(this + 0x44)); // unlink old node
            }
            *(int*)(this + 0x44) = iVar7; // store new node
            if (iVar7 != 0) {
                *(undefined4*)(this + 0x48) = *(undefined4*)(iVar7 + 4); // link to next node
                *(int**)(iVar7 + 4) = (int*)(this + 0x44); // back-link
            }
        }

        // Move along path: return 0 if path ended
        cVar6 = navManager->moveAlongPath(currentPos, unaff_EDI, targetPos, 
                                          (undefined4*)(this + 0x20), 4, 0, userData);
        if (cVar6 == '\0') {
            // Path complete, reset stored target
            *(float*)(this + 0x2c) = 0.0f;
            *(float*)(this + 0x28) = 0.0f;
            *(float*)(this + 0x24) = 0.0f;
            *(float*)(this + 0x20) = 0.0f;
            return 2;
        }

        // Update own position from computed target
        *(float*)(this + 0x10) = *(float*)(this + 0x20);
        *(float*)(this + 0x18) = *(float*)(this + 0x28);

        // Decrement time accumulator (unaff_EDI[1])
        unaff_EDI[1] = unaff_EDI[1] - DAT_00e448bc;

        // Copy unaff_EDI (velocity/acceleration) into +0x60 .. +0x6C
        *(float*)(this + 0x60) = unaff_EDI[0];
        *(float*)(this + 0x64) = unaff_EDI[1];
        *(float*)(this + 0x68) = unaff_EDI[2];
        *(float*)(this + 0x6C) = unaff_EDI[3];

        // Compute speed magnitude from velocity field
        fVar11 = *(float*)(this + 0x68) - *(float*)(this + 0x18); // vz - ownZ
        fVar10 = *(float*)(this + 0x64) - *(float*)(this + 0x14); // vy - ownY
        fVar9  = *(float*)(this + 0x60) - *(float*)(this + 0x10); // vx - ownX
        *(float*)(this + 0xC4) = sqrt(fVar11 * fVar11 + fVar10 * fVar10 + fVar9 * fVar9);

        // Reset some timers
        *(float*)(this + 0xC0) = 0.0f;
        *(float*)(this + 0xE0) = 0.0f;
    }
    return 1;
}
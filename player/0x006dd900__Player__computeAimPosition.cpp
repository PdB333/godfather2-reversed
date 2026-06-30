// FUNC_NAME: Player::computeAimPosition
// Address: 0x006dd900
// Reconstructed from Ghidra decompilation for The Godfather 2 (EARS engine)
// This function computes the player's desired aim position based on camera and target data.

void __thiscall Player::computeAimPosition(Player *this, Vector3 *outPos, TargetInfo *targetInfo, float deltaTime)
{
    float *pfVar1;
    char result;
    int iVar3;
    int iVar4;
    int *objectBase;
    float fVar6;
    float local_c, local_8, local_4; // stack variables for intermediate offset

    iVar4 = targetInfo;

    // Check if targetInfo has a valid child object and it's not a special type (0x48)
    if ((*(int *)(targetInfo + 8) != 0) && (*(int *)(targetInfo + 8) != 0x48)) {
        iVar3 = FUN_00471610(); // Likely getCameraManager() or getCameraPosition()
        pfVar1 = outPos;
        *(Vector3 *)outPos = *(Vector3 *)(iVar3 + 0x30); // Copy camera's "aim" or "offset" vector
        outPos->z = *(float *)(iVar3 + 0x38);

        // Compute base of child object (reverse offset of 0x48 from pointer at +8)
        if (*(int *)(iVar4 + 8) == 0) {
            objectBase = 0x0;
        } else {
            objectBase = (int *)(*(int *)(iVar4 + 8) - 0x48);
        }

        // Call virtual function on child object (likely "getTargetLead")
        // Using a hash ID 0x55859efa to query information
        outPos = 0x0; // Reset local pointer (will be passed as output)
        result = (**(code **)(*objectBase + 0x10))(0x55859efa, &outPos);

        // If successful and the returned float (local_4) is non-zero, apply lead
        if ((result != 0) && (local_4 != 0.0f)) {
            // Check a flag in the Player object at +0x8E3 (bit 0)
            if ((*(byte *)(*(int *)(this + 0x2D0) + 0x8E3) & 1) == 0) {
                // Interpolate between targetInfo->minLead and maxLead using returned factor
                fVar6 = (*(float *)(iVar4 + 0x5C) - *(float *)(iVar4 + 0x7C)) * outPos + *(float *)(iVar4 + 0x7C);
            } else {
                // Use fixed lead value
                fVar6 = *(float *)(iVar4 + 0x150);
            }
            pfVar1->y = pfVar1->y + fVar6; // Apply vertical lead
        }
        return;
    }

    // Default path: compute offset from targetInfo and add to camera position
    FUN_006dd6d0(&local_c, targetInfo, deltaTime); // Compute offset vector
    iVar4 = FUN_00471610();
    outPos->x = *(float *)(iVar4 + 0x20) + local_c; // Camera position + offset
    outPos->y = *(float *)(iVar4 + 0x24) + local_8;
    outPos->z = *(float *)(iVar4 + 0x28) + local_4;
    FUN_006ca5e0(&local_c, outPos, outPos); // Possibly clamp or normalize the result
    return;
}
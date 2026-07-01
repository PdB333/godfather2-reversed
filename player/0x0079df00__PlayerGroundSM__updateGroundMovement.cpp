// FUNC_NAME: PlayerGroundSM::updateGroundMovement
void __thiscall PlayerGroundSM::updateGroundMovement(int *this, char *footstepPlayed) {
    char isGrounded;
    int playerPosPtr;
    float10 vecLen;
    float adjustedY;
    float posX, posY, posZ;
    float diffX, diffY, diffZ;
    float stepTimer;
    float unknownFloat;
    // Stack variables for position conversion
    float local_100, fStack_fc, local_f8, local_f4, local_f0, local_ec;
    undefined8 local_dc; // double? 64-bit position component
    float local_d4;
    char pad0[32];
    float local_b0; // derived from random?
    int randomResult; // from FUN_009e5ed0 return (local_70)
    char pad1[92];

    if (*footstepPlayed == '\0') {
        // Check movement condition: bit15 of m_flags set, bit5 of m_flags2 clear
        if ((((uint)this[0x928] >> 0xf & 1) != 0) && (((uint)this[0x927] >> 5 & 1) == 0)) {
            isGrounded = FUN_00842870(); // likely isPlayerGrounded()
            if ((isGrounded == '\0') && ((*(uint *)(DAT_01129948 + 0x4c) >> 5 & 1) == 0)) {
                // Not cutscene
                playerPosPtr = FUN_00471610(); // get player position pointer
                // Read player position (possibly double-precision)
                local_dc = *(undefined8 *)(playerPosPtr + 0x30); // low 32 bits as double? Actually 64-bit value
                local_f8 = *(float *)(playerPosPtr + 0x38); // z component
                // Split into two floats
                local_100 = (float)local_dc; // low part as float (x)
                fStack_fc = (float)((ulonglong)local_dc >> 0x20); // high part as float (y)
                // Store backup
                local_e8 = local_dc; // not used directly
                local_d4 = local_f8;
                // Convert coordinate system (2, 0x80000000 flag)
                FUN_00542650(&local_100, &local_dc, 2, 0x80000000, 0, 0);
                FUN_0046d6a0(); // advance time or get delta
                // Generate random number/seed (local_60, local_d0 are buffers)
                FUN_009e5ed0(pad1, pad0);
                if (randomResult == 0) {
                    // Decrement step timer
                    this[0xc45] = this[0xc45] + -1;
                    if (0 < this[0xc45]) goto LAB_0079e0ef;
                } else {
                    // Compute difference between original and converted position
                    diffX = (float)local_dc - local_100;
                    diffY = local_dc._4_4_ - fStack_fc; // high 32 bits as float (y diff)
                    diffZ = local_d4 - local_f8;
                    // Compute length
                    vecLen = (float10)FUN_0043a210(&diffX, &diffY); // likely returns sqrt(diffX^2+diffY^2+diffZ^2)
                    // Adjusted Y = some factor * vector length * diffY + original Y + offset
                    adjustedY = local_b0 * (float)vecLen * diffY + fStack_fc + DAT_00d5ef84;
                    // Get player position again
                    playerPosPtr = FUN_00471610();
                    // Construct new position (x,y,z) and call virtual function at vtable+0x1c (setPosition?)
                    local_e0 = *(undefined4 *)(playerPosPtr + 0x38); // original z
                    local_e8 = CONCAT44(adjustedY, (int)*(undefined8 *)(playerPosPtr + 0x30)); // pack new x and adjusted y
                    (**(code **)(*this + 0x1c))(&local_e8); // likely setPosition
                }
                // Reset timer
                this[0xc45] = 0;
                // Play footstep sound 0x2f (47)
                FUN_006901e0(0x2f);
                *footstepPlayed = '\x01';
                goto LAB_0079e0ef;
            }
        }
        if (*footstepPlayed == '\0') goto LAB_0079e0ef;
    }
    // Clear movement flag if still set
    if (((uint)this[0x928] >> 0xf & 1) != 0) {
        this[0xc45] = 0;
        this[0x928] = this[0x928] & 0xffff7fff; // clear bit15
    }
LAB_0079e0ef:
    // Reset footstep flag (output)
    FUN_007ff850(footstepPlayed);
    // If footstep was played and not in vehicle, play extra sounds
    if ((*footstepPlayed != '\0') && (((uint)this[0x927] >> 5 & 1) == 0)) {
        isGrounded = FUN_00842870();
        if ((isGrounded == '\0') && ((*(uint *)(DAT_01129948 + 0x4c) >> 5 & 1) == 0)) {
            FUN_006901e0(0x24); // sound 0x24 (36)
            FUN_006901e0(0x49); // sound 0x49 (73)
        }
    }
    return;
}
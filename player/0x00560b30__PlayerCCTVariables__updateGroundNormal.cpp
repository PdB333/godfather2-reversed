// FUNC_NAME: PlayerCCTVariables::updateGroundNormal

void PlayerCCTVariables::updateGroundNormal(void)
{
    float fVar1;
    float fVar2;
    float fVar3;
    float fVar4;
    float *pfVar5;
    float *pfVar6;
    int iVar7;
    int iVar8;
    float10 fVar9;
    float fVar10;
    float fVar11;
    float fVar12;

    // Original vector (likely velocity or movement direction)
    fVar1 = *(float *)(this + 0xe0); // +0xe0: x component
    fVar2 = *(float *)(this + 0xe4); // +0xe4: y component
    fVar3 = *(float *)(this + 0xe8); // +0xe8: z component

    iVar8 = 0;
    if (0 < *(int *)(this + 0x4c)) { // +0x4c: number of contact points
        pfVar5 = *(float **)(this + 0x48); // +0x48: pointer to contact point array
        iVar7 = *(int *)(this + 0x4c);
        pfVar6 = pfVar5 + 9; // start at offset 9 (float index) within first point
        do {
            if (*pfVar6 != 0.0) { // check if point has non-zero weight (or flag)
                iVar8 = iVar8 + 1;
            }
            pfVar6 = pfVar6 + 0x30; // each contact point is 0x30 floats (0xC0 bytes)
            iVar7 = iVar7 + -1;
        } while (iVar7 != 0);

        if (1 < iVar8) { // at least two valid contact points
            // Compute normal from three points (indices 0x30, 0x60, 0x90 relative to base)
            // These are likely the first three contact points with non-zero weight
            fVar10 = ((pfVar5[0x32] - pfVar5[0x92]) * (pfVar5[0x60] - pfVar5[0x90]) -
                     (pfVar5[0x62] - pfVar5[0x92]) * (pfVar5[0x30] - pfVar5[0x90])) +
                     ((pfVar5[0x62] - pfVar5[2]) * (pfVar5[0x30] - *pfVar5) -
                     (pfVar5[0x32] - pfVar5[2]) * (pfVar5[0x60] - *pfVar5));
            fVar11 = ((pfVar5[0x61] - pfVar5[0x91]) * (pfVar5[0x30] - pfVar5[0x90]) -
                     (pfVar5[0x31] - pfVar5[0x91]) * (pfVar5[0x60] - pfVar5[0x90])) +
                     ((pfVar5[0x31] - pfVar5[1]) * (pfVar5[0x60] - *pfVar5) -
                     (pfVar5[0x61] - pfVar5[1]) * (pfVar5[0x30] - *pfVar5));
            fVar12 = ((pfVar5[0x62] - pfVar5[0x92]) * (pfVar5[0x31] - pfVar5[0x91]) -
                     (pfVar5[0x61] - pfVar5[0x91]) * (pfVar5[0x32] - pfVar5[0x92])) +
                     ((pfVar5[0x32] - pfVar5[2]) * (pfVar5[0x61] - pfVar5[1]) -
                     (pfVar5[0x31] - pfVar5[1]) * (pfVar5[0x62] - pfVar5[2]));

            // Store computed normal (cross product of edges)
            *(float *)(this + 0xe8) = fVar11; // z component
            fVar4 = DAT_00e2fc48; // threshold for squared length
            *(float *)(this + 0xe0) = fVar12; // x component
            *(float *)(this + 0xe4) = fVar10; // y component
            *(undefined4 *)(this + 0xec) = 0; // +0xec: w component (set to 0)

            // Normalize if squared length exceeds threshold
            if (fVar4 < fVar11 * fVar11 + 0.0 + fVar12 * fVar12 + fVar10 * fVar10) {
                fVar4 = *(float *)(this + 0xe8);
                fVar11 = fVar12 * fVar12 + fVar10 * fVar10 + fVar4 * fVar4;
                if (fVar11 == 0.0) {
                    fVar11 = 0.0;
                }
                else {
                    // Inverse square root (FUN_00414a80 is likely sqrt or rsqrt)
                    fVar9 = (float10)FUN_00414a80(fVar11);
                    fVar11 = (float)((float10)1 / fVar9);
                }
                *(float *)(this + 0xe0) = fVar12 * fVar11;
                *(float *)(this + 0xe4) = fVar10 * fVar11;
                *(float *)(this + 0xe8) = fVar4 * fVar11;
                *(undefined4 *)(this + 0xec) = 0;
                goto LAB_00560e11;
            }
        }
    }
    // Fallback: use default normal from global constants
    *(undefined4 *)(this + 0xe0) = DAT_01126060;
    *(undefined4 *)(this + 0xe4) = DAT_01126064;
    *(undefined4 *)(this + 0xe8) = DAT_01126068;
    *(undefined4 *)(this + 0xec) = DAT_0112606c;

LAB_00560e11:
    // Check if y component of normal is >= threshold (likely ground normal check)
    if (DAT_00e2cd1c < *(float *)(this + 0xe4) || DAT_00e2cd1c == *(float *)(this + 0xe4)) {
        // Compute dot product of original vector with computed normal
        if (DAT_00e2cd18 <=
            *(float *)(this + 0xe8) * fVar3 + *(float *)(this + 0xe4) * fVar2 +
            *(float *)(this + 0xe0) * fVar1) {
            // Dot product above threshold -> likely on ground
            if ((*(uint *)(this + 0x110) >> 3 & 1) != 0) {
                // Already in ground state? Set sliding flag, clear ground flag
                *(uint *)(this + 0x110) = *(uint *)(this + 0x110) | 0x10; // set bit 4 (sliding?)
                *(uint *)(this + 0x110) = *(uint *)(this + 0x110) & 0xfffffff7; // clear bit 3 (ground?)
                return;
            }
            // Not in ground state: clear both flags
            *(uint *)(this + 0x110) = *(uint *)(this + 0x110) & 0xffffffef; // clear bit 4
            *(uint *)(this + 0x110) = *(uint *)(this + 0x110) & 0xfffffff7; // clear bit 3
            return;
        }
        // Dot product below threshold -> not on ground
        if ((*(uint *)(this + 0x110) >> 3 & 1) != 0) {
            // Was on ground: set sliding and ground flags
            *(uint *)(this + 0x110) = *(uint *)(this + 0x110) | 0x10; // set bit 4
            *(uint *)(this + 0x110) = *(uint *)(this + 0x110) | 8;    // set bit 3
            return;
        }
    }
    else {
        // y component below threshold (normal pointing down?)
        if ((*(uint *)(this + 0x110) >> 3 & 1) != 0) {
            // Was on ground: set sliding and ground flags
            *(uint *)(this + 0x110) = *(uint *)(this + 0x110) | 0x10;
            *(uint *)(this + 0x110) = *(uint *)(this + 0x110) | 8;
            return;
        }
    }
    // Default: clear sliding flag, set ground flag
    *(uint *)(this + 0x110) = *(uint *)(this + 0x110) & 0xffffffef; // clear bit 4
    *(uint *)(this + 0x110) = *(uint *)(this + 0x110) | 8;          // set bit 3
    return;
}
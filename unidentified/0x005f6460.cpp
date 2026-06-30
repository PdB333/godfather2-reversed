// FUN_NAME: SteeringUtility::calcGroundProjection
undefined4 * __thiscall SteeringUtility::calcGroundProjection(undefined4 param_1, undefined4 *param_2, undefined4 param_3)
// param_1: this pointer (in_EAX), points to Vector3 (x,y,z)
// param_2: output Vector3* (result stored here)
// param_3: some scalar/flag (pass-through to helper)
// unaff_EDI: another input, possibly a scalar or flag (e.g., maxSpeed)
{
    undefined4 uVar1;
    undefined4 *in_EAX;
    int iVar2;
    undefined4 *puVar3;
    undefined4 *unaff_ESI;      // another vector pointer (maybe EDX)
    undefined4 unaff_EDI;       // extra scalar/flag
    undefined4 local_18;        // temp x (result)
    undefined4 local_14;        // temp z (result)
    undefined4 local_10;        // this->x
    undefined4 local_c;         // this->z
    undefined1 local_8 [8];     // temporary buffer for helper

    // Extract x and z from this vector (ignore y for now)
    local_10 = *in_EAX;        // this->x
    local_c = in_EAX[2];       // this->z

    // Extract x and z from the second vector (unaff_ESI)
    local_18 = *unaff_ESI;     // other->x
    local_14 = unaff_ESI[2];   // other->z

    // Compute projection using the x/z components, a zero, the extra scalar, and this->y
    iVar2 = computeProjection(&local_10, &local_18, 0, unaff_EDI, in_EAX[1]);

    if (iVar2 != 0) {
        // Apply correction/callback using the temporary buffer, previous operands, the return value, and extra scalar
        puVar3 = (undefined4 *)applyCorrection(local_8, &local_10, &local_18, iVar2, unaff_EDI, 0, 0, param_3);
        local_18 = *puVar3;      // new x result
        local_14 = puVar3[1];    // new z result
    }

    // Keep y from the second vector (original y of target/source)
    uVar1 = unaff_ESI[1];       // other->y

    // Build output vector: (local_18, other->y, local_14)
    *param_2 = local_18;
    param_2[1] = uVar1;
    param_2[2] = local_14;

    return param_2;
}
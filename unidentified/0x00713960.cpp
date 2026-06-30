// FUN_NAME: NPC::evaluatePointInDetectionCone
int __thiscall NPC::evaluatePointInDetectionCone(int* this, float* checkPos, char param_3) {
    // Virtual call at vtable offset 0x3c to get transform (position + forward vector)
    float posX, posY, posZ;
    float forwardX, forwardY, forwardZ; // Note: output order may differ based on implementation
    (*(void (**)(float*, float*))(*(int*)this + 0x3c))(&posY, &posX); // Param order? Actually the call is (&local_28, local_1c) but we reassign to meaningful locals.

    // Actually reconstructing proper transform extraction:
    // The virtual call fills 6 floats: fStack_30=posX, fStack_2c=posY, local_28=posZ,
    // then fStack_24=forwardX? fStack_20=forwardY, local_1c[0]=forwardZ.
    // So after the call we have:
    float myPosX = posX; // fStack_30
    float myPosY = posY; // fStack_2c
    float myPosZ = posZ; // local_28
    float fwdX = forwardX; // fStack_24
    float fwdY = forwardY; // fStack_20
    float fwdZ = forwardZ; // local_1c[0]

    // Get current state index (used to index into threshold arrays)
    int stateIdx = __thiscall FUN_0077dd80(); // returns 0..n-1, possibly state context

    // Global scale factor (probably meters per unit)
    float g_scale = * (float*)0x00d5780c; // _DAT_00d5780c
    // Absolute value mask for float bits (0x7ffffff)
    unsigned int absMask = * (unsigned int*)0x00e44680; // DAT_00e44680

    // Height difference (absolute y delta)
    float local_yDelta = checkPos[1] - myPosY;
    float yDeltaAbs = *(float*)&(((unsigned int)local_yDelta) & absMask); // fabsf via bitmask
    float heightTolerance = * (float*)&this[stateIdx + 0x0f]; // param_1[iVar1+0xf] as float

    // Check if target exists and use its radius
    float radiusScale = g_scale;
    if (((*(unsigned int*)(this[4] + 0x8e0) >> 10) & 1) != 0) {
        int* target = __thiscall FUN_00800a90(); // getTargetEntity()
        if (target != 0) {
            radiusScale = * (float*)(target + 0x338); // target's radius scale
        }
    }

    // If height difference exceeds threshold, early out
    if (yDeltaAbs > heightTolerance * radiusScale) {
        return 0;
    }

    // Compute squared 3D distance
    float dx = *checkPos - myPosX;
    float dy = checkPos[1] - myPosY;
    float dz = checkPos[2] - myPosZ;
    float distSqr = dx*dx + dy*dy + dz*dz;

    // Get inner radius threshold
    float innerRadius = * (float*)&this[stateIdx + 0x13]; // param_1[iVar1+0x13]
    float innerRadiusScaled = innerRadius * radiusScale;
    if ((param_3 == 0) && (distSqr > innerRadiusScaled * innerRadiusScaled)) {
        return 0;
    }

    // Dot product of delta vector with forward direction
    float dot = dx * fwdX + dy * fwdY + dz * fwdZ; // Note: careful about order; as per code: dy*fStack_20 + dx*fStack_24 + dz*local_1c[0]

    // Flags: bit 2 of param_1[3] (1<<2 = 0x4)
    bool flagIgnoreCone = ((*(unsigned int*)(this + 3) >> 2) & 1) != 0;

    // Ambient cone thresholds
    float minCos = * (float*)&this[stateIdx + 0x17]; // outer cone cos angle
    float strictCos = * (float*)&this[stateIdx + 0x1b]; // inner cone cos angle

    if ((dot < minCos) || flagIgnoreCone) {
        if ((dot < strictCos) || flagIgnoreCone) {
            // Inside strict cone
            float outerRadius = * (float*)&this[stateIdx + 0x23]; // param_1[iVar1+0x23]
            if (outerRadius * outerRadius < distSqr) {
                return 0;
            }
            return 3;
        } else {
            // Between strict and min cones
            int actionState = * (int*)(this[4] + 0x24c4);
            if ((actionState == 0) || (actionState == 0x48)) {
                return 2;
            }
            // Fall through to return 1
        }
    }
    return 1;
}
// FUNC_NAME: ChaseCamera::updateOrbitSmoothing

void __fastcall ChaseCamera::updateOrbitSmoothing(ChaseCamera* thisPtr)
{
    // +0xd8 : pointer to a follow target descriptor
    // +0xb4 : offset within that descriptor to a "look at" node (or zero)
    int nodePtr = 0;
    if (thisPtr->followTargetDescriptor != 0) {
        nodePtr = *(int*)(thisPtr->followTargetDescriptor + 0xb4);
        if (nodePtr == 0) {
            nodePtr = 0;
        }
        else {
            nodePtr -= 0x48; // subtract size of some base struct to get actual node
        }
    }

    if (nodePtr != 0) {
        // Get two position sources (probably player character and some other point)
        void* src1 = FUN_00471610();
        void* src2 = FUN_00471610();

        // Vector difference between the two sources (likely to determine if close enough)
        float dx = *(float*)(src2 + 0x30) - *(float*)(src1 + 0x30);
        float dy = *(float*)(src2 + 0x34) - *(float*)(src1 + 0x34);
        float dz = *(float*)(src2 + 0x38) - *(float*)(src1 + 0x38);
        float distSq = dx*dx + dy*dy + dz*dz;

        static float kMinDistSq = DAT_00e51b48; // global minimum distance squared

        if (distSq < kMinDistSq) {
            // Compute step size for interpolation
            float maxStep = (float)FUN_00763750(nodePtr); // maximum allowed step per frame
            float currentDelta = (float)FUN_005fe710(); // some time delta or dynamic value
            float threshold = DAT_00e44564 - currentDelta; // another global threshold

            // Clamp step to range [0, maxStep]
            float step;
            if (threshold < maxStep) {
                step = threshold;
                if (currentDelta <= maxStep) {
                    step = currentDelta;
                }
            }
            else {
                step = maxStep;
            }
            thisPtr->currentOrbitStep = step; // +0xd4
        }
    }

    // Check bit1 of flags (0x02)
    if ((thisPtr->flags >> 1 & 1) != 0) {
        FUN_007636a0(); // may reset or update some state
    }

    // Update active flag based on step value
    if (thisPtr->currentOrbitStep >= 0.0f) {
        thisPtr->flags |= 1; // bit0 set = active
    }
    else {
        thisPtr->flags &= ~1;
    }

    // Copy desired target position from the object pointed by thisPtr->targetDescriptor (+0x78)
    // The target struct has a Vector3 at offset 0 (two floats x,y as a double) and another float at +8 (z)
    // Also an angle at offset 0xf8 used for rotation
    {
        TargetInfo* target = *(TargetInfo**)&thisPtr->targetDescriptor; // +0x78
        // Read desired position (Vec3) from target
        thisPtr->currentPosition.x = target->position.x; // 8 bytes (x,y) actually stored as double, but then used as float separately
        thisPtr->currentPosition.y = target->position.y; // implicit from double copy
        thisPtr->currentPosition.z = target->position.z; // +0x08

        // If stepping is active, interpolate current position toward target
        float step = thisPtr->currentOrbitStep;
        if (step != 0.0f) {
            float angle = target->yaw; // +0xf8
            double cosAngle = (double)angle;
            FUN_00b99e20(); // likely cos routine
            double sinAngle = (double)angle;
            FUN_00b99fcb(); // likely sin routine

            // Adjust position using a rotation around Y? (subtract cos*step from x, add sin*step to z)
            thisPtr->currentPosition.x -= (float)cosAngle * step;
            thisPtr->currentPosition.z += (float)sinAngle * step;
        }
    }
}
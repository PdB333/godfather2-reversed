// FUNC_NAME: WheeledVehicle::updateSuspension
// Address: 0x0055f950
// This function updates suspension forces for each wheel, handling contact and non-contact cases.
// It computes velocity, applies damping, and integrates forces.

void WheeledVehicle::updateSuspension(const float* frameData)
{
    // frameData: pointer to frame data, dt at +0x08
    float dt = *(frameData + 2); // +0x08 = offset 8 / 4

    // Time since last frame?
    float timeStep = DAT_00e44564 - *(float*)(this + 0xbc); // stored at +0xbc

    // Check if bit1 is set in flags at +0x110
    if ((*(uint*)(this + 0x110) >> 1) & 1)
    {
        // Count wheels with non-zero contact force
        int wheelCount = *(int*)(this + 0x4c);
        int nonZeroCount = 0;
        if (wheelCount > 0)
        {
            int* wheelContactPtr = (int*)(*(int*)(this + 0x48) + 0x24); // +0x24 might be contact flag offset
            for (int i = 0; i < wheelCount; i++)
            {
                if (*wheelContactPtr != 0)
                    nonZeroCount++;
                wheelContactPtr += 0x30 / 4; // 0x30 per wheel struct
            }
            if (nonZeroCount != 0)
                goto LAB_0055fb75; // process contact forces
        }

        // No wheel contacts? Compute free-body velocity (airborne)
        // Get chassis transform/velocity
        int chassis = *(int*)(this + 0x18);
        float vx = *(float*)(chassis + 0x1a0);
        float vy = *(float*)(chassis + 0x1a4);
        float vz = *(float*)(chassis + 0x1a8);
        float speed = sqrtf(vx*vx + vy*vy + vz*vz);

        // Compute new velocity direction from global constants and member data
        float local_f10 = *(float*)(this + 0xec) * DAT_00e2b118 + DAT_0113982c;
        float local_20 = DAT_01126060 * DAT_00e448d0 + *(float*)(this + 0xe0) * DAT_00e2b118 + DAT_01139820;
        float local_1c = DAT_01126064 * DAT_00e448d0 + *(float*)(this + 0xe4) * DAT_00e2b118 + DAT_01139824;
        float local_18 = DAT_01126068 * DAT_00e448d0 + *(float*)(this + 0xe8) * DAT_00e2b118 + DAT_01139828;
        float fVar11 = DAT_0112606c * DAT_00e448d0;

        float sumSq = local_18*local_18 + local_1c*local_1c + local_20*local_20;
        float invLen = (sumSq == 0.0f) ? 0.0f : 1.0f / sqrtf(sumSq);

        // Store normalized direction
        *(float*)(this + 0xe4) = invLen * local_1c;
        *(float*)(this + 0xe0) = invLen * local_20;
        *(float*)(this + 0xe8) = invLen * local_18;
        *(float*)(this + 0xec) = invLen * (fVar11 + local_f10);
        goto LAB_0055fcd0;
    }

LAB_0055fb75:
    // Process wheel contacts
    {
        int wheelData = *(int*)(this + 0x9c); // pointer to per-wheel data?
        float fVar9 = *(float*)(wheelData + 0x14);
        if (*(char*)(wheelData + 0x10) != '\0')
            fVar9 = 0.0f;

        int chassis = *(int*)(this + 0x18);
        // Dot product of chassis velocity with some direction?
        float dot = *(float*)(chassis + 0x1a8) * *(float*)(chassis + 0x108) +
                    *(float*)(chassis + 0x1a4) * *(float*)(chassis + 0x104) +
                    *(float*)(chassis + 0x1a0) * *(float*)(chassis + 0x100);
        // Mask with some value? (bitwise AND reinterpreted as float)
        if ((float)((uint)dot & (uint)DAT_00e44680) < DAT_00e2e210)
            dot = 0.0f;

        if (*(char*)(wheelData + 0x11) != '\0')
            fVar9 = DAT_00e44564 - fVar9;

        float fVar11 = dot;
        if (dot <= 0.0f)
        {
            if (dot < 0.0f)
                fVar9 = *(float*)(wheelData + 0x18) + fVar9;
        }
        else
        {
            fVar9 = fVar9 - *(float*)(wheelData + 0x18);
            if (dot < 0.0f)
                fVar11 = 0.0f;
        }

        float suspensionForce = ((*(float*)(this + 0xf8) - fVar11) / *(float*)(this + 0xf8)) *
                                 *(float*)(this + 0xfc) * fVar9 * dt + dot;

        // Clamp to prevent sign change
        if ((suspensionForce < 0.0f && dot > 0.0f) || (suspensionForce > 0.0f && dot < 0.0f))
            suspensionForce = 0.0f;

        // If wheel is touching ground (char at +0x10 != 0?), apply friction?
        if (*(char*)(wheelData + 0x10) != '\0')
        {
            float absForce = fabsf(suspensionForce);
            if (absForce >= DAT_00e3ac58)
            {
                float dtScaled = dt * DAT_00e2b04c;
                if (dtScaled > DAT_00e2b1a4)
                    dtScaled = DAT_00e2b1a4;
                suspensionForce = (DAT_00e2b1a4 - dtScaled) * suspensionForce;
            }
            else
            {
                suspensionForce = 0.0f;
            }
        }
    }

LAB_0055fcd0:
    // Update each wheel's force based on contact state
    int wheelArray = *(int*)(this + 0x1c); // pointer to wheel array? Or another structure?
    int wheelCount = *(char*)(wheelArray + 0x20);
    if (wheelCount > 0)
    {
        int local_28 = 0; // offset into some table
        int local_2c = 0; // offset into wheel array (0xc0 step)
        for (int i = 0; i < wheelCount; i++)
        {
            int wheelPtr = *(int*)(this + 0x48) + local_2c;
            // Check if contact flag is zero?
            if (*(char*)(i + *(int*)(this + 0xa0)) == '\0')
            {
                // Call some transform function
                FUN_00aa2cd0(*(int*)(this + 0x18) + 0xe0, wheelArray + 0x40);
                int chassis = *(int*)(this + 0x18);
                float fVar9 = (*(float*)(chassis + 0x1a4) * local_1c +
                               *(float*)(chassis + 0x1a8) * local_18 +
                               *(float*)(chassis + 0x1a0) * local_20 +
                               *(float*)(wheelPtr + 0xb0)) /
                              *(float*)(*(int*)(*(int*)(this + 0x1c) + 0x8c) + local_28);
                *(float*)(wheelPtr + 0xa0) = fVar9;
                *(float*)(wheelPtr + 0xa4) = dt * fVar9 + *(float*)(wheelPtr + 0xa4);
            }
            else
            {
                *(int*)(wheelPtr + 0xa0) = 0;
            }
            wheelArray = *(int*)(this + 0x1c);
            local_2c += 0xc0;
            local_28 += 0x28;
        }
    }

    // Clamp suspensionForce to limits
    float minForce = DAT_00e44564 - *(float*)(this + 0xf4);
    float maxForce = *(float*)(this + 0xf0);
    if (suspensionForce < minForce || suspensionForce > maxForce)
        suspensionForce = (suspensionForce < minForce) ? minForce : maxForce;

    // Pass to another update function
    FUN_0055fe80(this, frameData, suspensionForce, timeStep);

    // Clear impulse accumulator for each wheel
    int wheelCount2 = *(int*)(*(int*)(this + 0x1c) + 0x9c);
    if (wheelCount2 > 0)
    {
        float* impulsePtr = (float*)(this + 0x5c); // impulse array, 6 floats per entry?
        for (int i = 0; i < wheelCount2; i++)
        {
            impulsePtr[0] = 0.0f;
            impulsePtr[1] = 0.0f;
            impulsePtr[2] = 0.0f;
            impulsePtr[3] = 0.0f;
            impulsePtr[4] = 0.0f;
            impulsePtr[5] = 0.0f;
            impulsePtr += 9; // 9 floats per entry? Actually 6 floats? But increment by 9*4=36 bytes => 9 floats.
        }
    }
    return;
}
// FUNC_NAME: VehicleBrain::computeSteerAngle
float __thiscall VehicleBrain::computeSteerAngle(void* thisPtr, float* currentPos, float* targetPos)
{
    // thisPtr offsets used:
    // +0x7c  (124) - bool: driveable? (something enabling steering)
    // +0xe8  (232) - pointer to some component (engine? physics?)
    // +0x2bc (700) - bool: inAir? (alt steering logic)
    // +0x2c0 (704) - previous steer angle
    // +0x2c4 (708) - current target steer angle

    float steerAngle = 0.0f;
    float blendFactor = DAT_00d5ef90; // default blend factor (probably 1.0 or similar)

    if (*(char*)((int)thisPtr + 700) == '\0') // not inAir?
    {
        // Normal ground steering
        if (*(char*)((int)thisPtr + 0x7c) != '\0') // driveable?
        {
            float speed = FUN_006c93c0(*(int*)((int)thisPtr + 0xe8) ? *(int*)((int)thisPtr + 0xe8) - 0x48 : 0);
            float threshold = DAT_00d58cbc; // min speed threshold for steering

            steerAngle = 0.0f;
            if ((float)threshold < (float)speed)
            {
                // Get player camera/forward direction
                int playerInfo = FUN_00471610(); // returns player info struct
                float fwdX = *(float*)(playerInfo + 0x28); // camera forward X?
                float fwdZ = *(float*)(playerInfo + 0x20); // camera forward Z?

                // Vector from current to target
                float toTargetX = *targetPos - *currentPos;
                float toTargetZ = targetPos[2] - currentPos[2];
                float zero = 0.0f;

                // Some rotation/normalization (probably aligns to forward direction)
                FUN_0043a210(&fwdZ, &fwdZ); // maybe normalize?
                FUN_0043a210(&toTargetX, &toTargetX); // maybe normalize?

                // Dot product between target direction and forward direction
                float dot = toTargetX * fwdZ + zero * fwdX + toTargetZ * fwdX; // Hmm: actually indexing is off

                // This branching is messy; probably clamp dot product and compute steer angle
                if (dot <= _DAT_00d5efe0) // some negative threshold
                {
                    steerAngle = DAT_00d5efd4; // maybe max steer angle
                    if (_DAT_00d577a0 < dot)
                    {
                        float t = (float)(double)dot;
                        FUN_00b9b988(); // some trig function (sin? cos?)
                        steerAngle = (t - _DAT_00d5efdc) * _DAT_00d5efd8; // linear interpolation
                    }
                }
                else
                {
                    steerAngle = 0.0f;
                }
            }
            blendFactor = DAT_00d5c454;
        }
    }
    else
    {
        // In-air steering
        float dx = *targetPos - *currentPos;
        float dz = targetPos[2] - currentPos[2];
        float distance2D = sqrt(dz * dz + dx * dx);

        int physicsPtr = *(int*)((int)thisPtr + 0xe8) ? *(int*)((int)thisPtr + 0xe8) - 0x48 : 0;
        (*(code**)*(int*)physicsPtr)[0x13](&someVec); // VTable call (maybe getVelocity)

        // ... complex air control math ...
        // ... uses vectors, dot products, clamping ...

        // Some condition for applying air control
        if (/* dot product between forward and some direction >= 0 */)
        {
            if (/* some threshold */ < blendFactor)
            {
                // Calculate target angle and clamp
                // ...
                float targetAngle = (float)FUN_006c3d70(); // get current steer angle from somewhere
                blendFactor = (float)targetAngle;
                *(float*)((int)thisPtr + 0x2c4) = (float)targetAngle;
                // Possibly apply interpolation
            }
        }
        else
        {
            *(uint*)((int)thisPtr + 0x2c0) = 0; // reset previous steer
            // some other reset
        }

        // Another condition check for additional steering influence
        bool hasSomeProperty = (**(code**)*(int*)physicsPtr)(0x197c1972, &blendFactor) != '\0';
        if (hasSomeProperty && /* angle != 0 */ && /* some other condition */)
        {
            // Compute final steer angle with interpolation
            float t = FUN_006c91c0(...);
            steerAngle = ...; // blend
            goto LAB_006c4369;
        }
    }

    // Final result: blend between previous steer angle and new computed angle
    float previousSteer = *(float*)((int)thisPtr + 0x2c0);
    return blendFactor * steerAngle + (1.0f - blendFactor) * previousSteer;
}
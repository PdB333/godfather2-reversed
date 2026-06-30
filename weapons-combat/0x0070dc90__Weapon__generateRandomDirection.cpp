// FUNC_NAME: Weapon::generateRandomDirection

// Reconstructed from address 0x0070dc90
// This function generates a random direction vector for a projectile based on 
// spread parameters stored at offsets +0x210, +0x214, +0x218.
// Output is an array of 8 floats (param_2) representing velocity/direction components.
// Globals are used for random number generation and scaling constants.

void __thiscall Weapon::generateRandomDirection(void* this, float* outVelocity)
{
    float baseSpeed;           // fVar3, base forward speed
    float speedConstant1;      // fVar4, used in lateral spread subtraction
    float speedConstant2;      // fVar1, used in vertical spread multiplication
    uint randomIndex;          // index into random table
    float randomFloat;         // random value from table
    float magnitude;           // temporary for normalization

    baseSpeed = sGlobalBaseSpeed;   // _DAT_00d5780c

    // Compute primary vertical velocity if base vertical component is nonzero
    if (*(float*)((char*)this + 0x210) != 0.0f)
    {
        randomIndex = sRandomMask & sRandomIndexCounter;
        sRandomIndexCounter++;
        randomFloat = *(float*)(&sRandomTable[randomIndex]);
        *outVelocity = randomFloat * *(float*)((char*)this + 0x210) + (baseSpeed - *(float*)((char*)this + 0x210));
    }

    speedConstant1 = sGlobalAngleBias;   // _DAT_00d5c458

    // If horizontal or vertical spread values are nonzero, compute the spread direction
    if ((*(float*)((char*)this + 0x214) != 0.0f) || (*(float*)((char*)this + 0x218) != 0.0f))
    {
        // Lateral spread component (X)
        randomIndex = sRandomMask & sRandomIndexCounter;
        sRandomIndexCounter++;
        randomFloat = *(float*)(&sRandomTable[randomIndex]);
        outVelocity[1] = (randomFloat - speedConstant1) * *(float*)((char*)this + 0x214);

        // Vertical spread components (Y, Z) – first two axes
        randomIndex = sRandomMask & sRandomIndexCounter;
        sRandomIndexCounter++;
        randomFloat = *(float*)(&sRandomTable[randomIndex]);
        outVelocity[2] = (randomFloat - speedConstant1) * *(float*)((char*)this + 0x214);

        speedConstant2 = sGlobalVerticalScale;   // _DAT_00d5eee4
        randomIndex = sRandomMask & sRandomIndexCounter;
        sRandomIndexCounter++;
        randomFloat = *(float*)(&sRandomTable[randomIndex]);
        outVelocity[3] = (randomFloat - speedConstant1) * *(float*)((char*)this + 0x214);

        // Forward velocity components (W, X, Y of quaternion?) – scaled differently
        randomIndex = sRandomMask & sRandomIndexCounter;
        sRandomIndexCounter++;
        randomFloat = *(float*)(&sRandomTable[randomIndex]);
        outVelocity[4] = randomFloat * speedConstant2 - baseSpeed;

        randomIndex = sRandomMask & sRandomIndexCounter;
        sRandomIndexCounter++;
        randomFloat = *(float*)(&sRandomTable[randomIndex]);
        outVelocity[5] = randomFloat * speedConstant2 - baseSpeed;

        randomIndex = sRandomMask & sRandomIndexCounter;
        sRandomIndexCounter++;
        randomFloat = *(float*)(&sRandomTable[randomIndex]);
        outVelocity[6] = randomFloat * speedConstant2 - baseSpeed;

        // Normalize the forward direction vector (outVelocity[4..6]) if too long
        magnitude = sqrtf(outVelocity[6] * outVelocity[6] + 
                         outVelocity[5] * outVelocity[5] + 
                         outVelocity[4] * outVelocity[4]);

        if (sMagnitudeThreshold <= magnitude) // _DAT_00d5f168
        {
            float scale = baseSpeed / magnitude;
            outVelocity[4] *= scale;
            outVelocity[5] *= scale;
            outVelocity[6] *= scale;
        }
        else
        {
            outVelocity[4] = 0.0f;
            outVelocity[5] = baseSpeed;
            outVelocity[6] = 0.0f;
        }

        // Final component – scaled by vertical spread value
        randomIndex = sRandomMask & sRandomIndexCounter;
        sRandomIndexCounter++;
        randomFloat = *(float*)(&sRandomTable[randomIndex]);
        outVelocity[7] = randomFloat * *(float*)((char*)this + 0x218);
    }
}

// Globals: 
// sRandomMask (0x010c2678) – bitmask for random index
// sRandomIndexCounter (0x012054b4) – incrementing counter
// sRandomTable (0x010c2680) – array of precomputed random floats
// sGlobalBaseSpeed (0x00d5780c) – base forward speed
// sGlobalAngleBias (0x00d5c458) – bias for spread angle
// sGlobalVerticalScale (0x00d5eee4) – vertical spread scale
// sMagnitudeThreshold (0x00d5f168) – magnitude threshold for normalization
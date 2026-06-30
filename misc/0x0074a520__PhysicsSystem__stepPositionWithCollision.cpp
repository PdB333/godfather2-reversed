// FUNC_NAME: PhysicsSystem::stepPositionWithCollision
// Address: 0x0074a520
// Updates a world position by integrating with a velocity (from random table) over deltaTime,
// performs a line trace collision check, and adjusts position accordingly.
// param_1: pointer to float[3] position (in/out)
// param_2: delta time (seconds)

void PhysicsSystem::stepPositionWithCollision(float *position, float deltaTime)
{
    char boolResult; // cVar1
    float randScaled; // fVar2
    double dVar3;
    float newPosX; // local_ec
    float newPosY; // fStack_e8
    float newPosZ; // local_e4
    float finalNewPosX; // local_dc
    float finalNewPosZ; // local_d4
    float hitFraction; // local_b0
    undefined4 unused1; // local_ac
    undefined4 unused2; // local_a0
    undefined4 hitResultFlags; // local_80
    int hitFound; // local_70
    undefined1 hitResultBuffer[92]; // local_60
    float *hitResult; // local_d0  // pointer to function table for hit processing

    // Random index into a table (procedural noise generator)
    int noiseIndex = DAT_012054b4; // global counter
    float noiseValue = *(float *)((uint)(DAT_010c2678 & DAT_012054b4) * 4 + (int)&DAT_010c2680);
    noiseValue = noiseValue * DAT_00d5d70c; // global scale
    DAT_012054b4++; // advance counter

    // Convert to double and back (possibly to ensure single-precision rounding)
    dVar3 = (double)noiseValue;
    FUN_00b99fcb(); // noise/random helper
    float valZ = (float)dVar3; // local_d4

    dVar3 = (double)noiseValue;
    FUN_00b99e20(); // another noise helper
    float valX = (float)dVar3; // local_dc

    // Compute candidate new position = old position + (random velocity * deltaTime)
    newPosX = valX * deltaTime + position[0];
    newPosY = deltaTime * _DAT_00d577a0 + position[1]; // _DAT_00d577a0 likely constant velocity (e.g. gravity)
    newPosZ = valZ * deltaTime + position[2];

    // Normalize the new position (or clamp to unit length? Not clear)
    FUN_00717070(&newPosX, &newPosX);

    // Check if new position is inside valid world bounds (or some collision query)
    boolResult = FUN_00718d40(&newPosX);
    if (boolResult != '\0')
    {
        // Perform a raycast from old position to new position with flags 0x40102 (likely includes dynamic/static)
        // The return is stored in param_1 after processing? Actually the call modifies param_1 via side effect?
        FUN_00542650(position, &newPosX, 0x40102, 0x20000, 0, 0);

        // Setup hit result storage
        unused1 = 0xffffffff;
        unused2 = 0xffffffff;
        hitResult = &PTR_FUN_00e32a8c; // function pointer table for hit result callbacks
        hitFound = 0;
        hitFraction = _DAT_00d5780c; // initial hit fraction (or stop distance)
        hitResultFlags = 0;
        float initialFraction = _DAT_00d5780c; // local_cc

        // Process hit result using callback table
        FUN_009e5ed0(hitResultBuffer, &hitResult);

        if (hitFound != 0)
        {
            // Hit detected: adjust position based on hit fraction and a constant
            float adjustment = hitFraction * deltaTime - _DAT_00d6438c;
            position[0] = adjustment * valX + position[0];
            position[1] = adjustment * _DAT_00d577a0 + position[1];
            position[2] = adjustment * valZ + position[2];

            // Normalize final position
            FUN_00717070(position, position);
            return;
        }
        // No hit: use the candidate new position
        *(ulonglong *)position = CONCAT44(newPosY, newPosX); // store X and Y as a 64-bit value
        position[2] = newPosZ;
    }
    return;
}
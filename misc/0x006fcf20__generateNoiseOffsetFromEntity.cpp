// FUNC_NAME: generateNoiseOffsetFromEntity

int generateNoiseOffsetFromEntity(float* outVector) {
    // Get the entity with ID 0 (likely the player)
    int* entity = reinterpret_cast<int*>(FUN_004262f0(0));
    if (entity == nullptr) {
        return 0;
    }

    float entityX = *(float*)(entity + 0x60); // +0x60: position.x
    float entityY = *(float*)(entity + 0x68); // +0x68: position.y
    float entityZ = *(float*)(entity + 0x74); // +0x74: position.z

    // Compute squared distance from entity to a global target (maybe objective or threat)
    float diffX = DAT_00e44564 - entityX;
    float distanceSq = entityY * entityY + diffX * diffX; // Note: only Y and diffX used — possibly a 2D calculation

    float invDistanceFactor;
    if (distanceSq <= DAT_00d5f2b4) {
        invDistanceFactor = 0.0f;
    } else {
        invDistanceFactor = _DAT_00d5780c / sqrtf(distanceSq); // constant / distance
    }

    // Generate random offset using rand()
    int randVal = _rand();
    float randOffset = (float)randVal * DAT_00e44590 * DAT_00d5f6d0 - DAT_00d60c64;

    // Fold negative/positive values to always positive (unclear intent)
    if (randOffset >= 0.0f) {
        randOffset += DAT_00d60c64;
    } else {
        randOffset -= DAT_00d60c64;
    }

    // Compute output vector: x and z get entityY scaled by random and factor, plus entityX? No, the code adds entity's something at +0x70
    float scaledY = randOffset * invDistanceFactor * entityY;
    float newX = scaledY + *(float*)(entity + 0x70); // +0x70: possibly additional component
    float newZ = newX; // same as newX? Suspicious

    outVector[0] = newX;
    outVector[1] = randOffset * invDistanceFactor * 0.0f + entityZ; // y component stays as entityZ (since multiplied by 0)
    outVector[2] = newZ; // z gets same as x

    return 1;
}
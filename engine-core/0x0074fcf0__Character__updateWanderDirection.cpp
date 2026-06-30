// FUNC_NAME: Character::updateWanderDirection
// Address: 0x0074fcf0
// Role: Calculates a random wander direction for a character, updates target position and angle.
// Uses random, navigation check, and player position for direction deviation.

void __fastcall Character::updateWanderDirection(Character* thisObj) {
    // +0x110: pointer to navigation/behavior data
    // +0x24cc: offset in that data for current node/waypoint
    int navDataPtr = *(int*)(*(int*)((char*)thisObj + 0x110) + 0x24cc);
    if (navDataPtr == 0) return;
    navDataPtr -= 0x48; // adjust to base of target node struct
    if (navDataPtr == 0) return;

    // +0x10c: base speed/deceleration
    float speed = *(float*)((char*)thisObj + 0x10c);
    
    // +0x60: flags (bit 4 = maybe sprint modifier)
    if ((*(unsigned int*)((char*)thisObj + 0x60) >> 4) & 1) {
        speed *= DAT_00d5c454; // sprint multiplier
    }
    speed *= DAT_00d5c458; // global speed multiplier

    // +0x54: random step counter (increments each call, used for seed)
    int* stepCounter = (int*)((char*)thisObj + 0x54);
    if (*stepCounter != 0) {
        // Apply random variation to speed
        float randomFactor = (float)_rand() * DAT_00e44590;
        speed *= randomFactor;
        if (speed < DAT_00d5780c) {
            speed = DAT_00d5780c; // clamp minimum speed
        }
    }
    *stepCounter += 1;

    float dirX;
    float dirY;
    float dirZ;
    // Attempt to find a navigable direction from navDataPtr with given speed
    bool found = computeRandomDirection(navDataPtr, speed, DAT_00d5d934, &dirX, &dirY, &dirZ);
    if (found && isDirectionValid(&dirX, &dirY, &dirZ)) {
        // Store new target direction (packed as X,Y in 64-bit slot)
        *(unsigned long long*)((char*)thisObj + 100) = ((unsigned long long)*(unsigned int*)&dirY << 32) | *(unsigned int*)&dirX;
        *(float*)((char*)thisObj + 0x6c) = dirZ; // Z at +0x6c

        // Set flag bit 0 (target updated)
        *(unsigned int*)((char*)thisObj + 0x60) |= 1;

        // Get player/entity position for deviation calculation
        int playerPtr = getPlayerPosition(); // returns pointer to player object
        float dx = dirX - *(float*)(playerPtr + 0x30);
        float dy = dirY - *(float*)(playerPtr + 0x34);
        float dz = dirZ - *(float*)(playerPtr + 0x38);
        normalizeVector(&dx, &dy, &dz);
        
        // Store angle to player (for facing/aiming)
        *(float*)((char*)thisObj + 0x70) = calculateAngle(&dx, &dy, &dz);
        
        // Copy/transform target vector (likely into internal format)
        copyVector((Vector3*)((char*)thisObj + 100), (Vector3*)((char*)thisObj + 100));
    }
}
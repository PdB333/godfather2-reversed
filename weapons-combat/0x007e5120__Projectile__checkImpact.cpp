// FUNC_NAME: Projectile::checkImpact
// Address: 0x007E5120
// Role: Performs line-of-sight collision check for a projectile/weapon. Computes hit point, validates against camera orientation, and triggers impact effects.

void Projectile::checkImpact(float* startPos, float* targetPos, int teamId, WeaponData* weaponData)
{
    float fVar1;
    int local_11c;
    float* hitPos;
    float length;
    float t;
    int allocIdx;
    int randVal0, randVal1, randVal2;
    float diff[3];
    float cameraVec[3];
    float cameraDelta[3];
    float dotResult;
    float camUp[3];
    float theta;
    int* allocBuffer;
    int count;

    // Determine manager based on team flag
    if (teamId == 0) {
        local_11c = 0;
    } else {
        local_11c = (int)FUN_0043b870(*(int*)0x01130fa0); // GetTeamManager
    }

    // Allocate buffer for some IDs
    allocBuffer = (int*)FUN_009c8e80(-((int)((longlong)(FUN_009a9460() + 1) * 4 >> 0x20) != 0) | (int)((FUN_009a9460() + 1) * 4));
    randVal0 = FUN_009a9460();
    float randFloat0 = (float)(randVal0 + 1);
    randVal1 = FUN_009a9460();
    float randFloat1 = (float)(randVal0 + 1);
    if (randVal1 != 0) {
        int managerPtr = *(int*)(local_11c + 0x28);
        int managerCount = *(int*)(local_11c + 0x2c) * 4;
        count = 0;
        while (managerPtr != *(int*)(local_11c + 0x28) + managerCount) {
            allocBuffer[count] = FUN_0043b490(); // GetSomeID
            managerPtr += 4;
            count++;
        }
        allocBuffer[count] = FUN_0043b490();
        // Debug log
        FUN_00540bc0(0x64522, 0x100005, allocBuffer, randFloat0);
    }

    // Compute direction and distance from start to target
    diff[0] = *startPos - *targetPos;
    diff[1] = startPos[1] - targetPos[1];
    diff[2] = startPos[2] - targetPos[2];

    length = 0.0f;
    float lenResult = (float)FUN_0056afa0(diff, diff); // Returns Euclidean distance
    float clampedLen = 0.0f;
    if (0.0f < lenResult) {
        clampedLen = lenResult;
    }

    float maxDist = *(float*)(weaponData + 0x2C); // Actually offset 0xA0 from param_4
    if (maxDist < clampedLen) {
        // Clamp position to max range
        *startPos = diff[0] * maxDist + *targetPos;
        startPos[1] = diff[1] * maxDist + targetPos[1];
        startPos[2] = diff[2] * maxDist + targetPos[2];
    }

    // Store origin, target, and some constant
    float origin[3] = { targetPos[0], targetPos[1], targetPos[2] };
    float target[3] = { startPos[0], startPos[1], startPos[2] };
    float zero = 0.0f;
    zero = 0.0f;
    float local_c4 = 0.0f; // _DAT_00d5780c
    float local_b4 = 0.0f;
    int dummy = 0;
    int* ptrToFuncTable = &PTR_FUN_00e32a8c; // Function pointer table

    // Perform collision query
    FUN_009e5ed0(origin, &ptrToFuncTable); // Likely cast ray or sphere
    FUN_009c8f10(allocBuffer); // Free allocated buffer

    int hitHandle = dummy;
    if (dummy == 0) {
        // No hit: store target position as hit point
        float hitPosZ = startPos[2];
        float hitPosX = startPos[0];
        float hitPosY = startPos[1];
        *(float*)(weaponData + 0x24) = hitPosX; // +0x90? Actually offsets: 0x78,0x7c,0x80 for hit point
        *(float*)(weaponData + 0x28) = hitPosY;
        *(float*)(weaponData + 0x2C) = hitPosZ;
        *(float*)(weaponData + 0x30) = 0.0f; // +0x9c
    } else {
        // Hit: interpolate from start to target using some factor
        float interpX = (startPos[0] - targetPos[0]) * 0.0f + targetPos[0];
        float interpY = (startPos[1] - targetPos[1]) * 0.0f + targetPos[1];
        float interpZ = (startPos[2] - targetPos[2]) * 0.0f + targetPos[2];
        // Store interpolated hit position (from local_90, local_8c, local_88, local_84)
        *(float*)(weaponData + 0x24) = interpX; // Actually there is local_90 etc, but simplified
        *(float*)(weaponData + 0x28) = interpY;
        *(float*)(weaponData + 0x2C) = interpZ;
        *(float*)(weaponData + 0x30) = 0.0f;
    }

    // Store the impact point (vector at +0x78)
    *(float*)(weaponData + 0x1E) = *(float*)(weaponData + 0x24); // Actually +0x78 is vector, but offsets simplified
    *(float*)(weaponData + 0x22) = *(float*)(weaponData + 0x28);
    *(float*)(weaponData + 0x26) = *(float*)(weaponData + 0x2C);

    // Check if we hit something and validate via camera dot product
    if (hitHandle != 0 && *(char*)(hitHandle + 0x10) + (char)hitHandle != 0) {
        int lookupResult = (int)FUN_004af8c0((void*)(&hitPos), 0x2001);
        int handle = (lookupResult != 0) ? lookupResult : 0;
        if (handle != 0) {
            int manager2 = (int)FUN_0043b870(*(int*)0x0112af98);
            if (manager2 != 0 && (~*(byte*)(manager2 + 0x50) & 1) != 0) {
                int camObj1 = (int)FUN_00471610(); // GetCamera
                camUp[0] = *(float*)(camObj1 + 0x20); // Camera up vector
                camUp[1] = *(float*)(camObj1 + 0x24);
                camUp[2] = *(float*)(camObj1 + 0x28);
                float camUpLen = (float)FUN_0056afa0(camUp, camUp);
                int camObj2 = (int)FUN_00471610();
                int camObj3 = (int)FUN_00471610();
                cameraDelta[0] = *(float*)(camObj3 + 0x30) - *(float*)(camObj2 + 0x30);
                cameraDelta[1] = *(float*)(camObj3 + 0x34) - *(float*)(camObj2 + 0x34);
                cameraDelta[2] = *(float*)(camObj3 + 0x38) - *(float*)(camObj2 + 0x38);
                FUN_0056afa0(cameraDelta, cameraDelta); // Used for normalization
                dotResult = (double)(cameraDelta[1] * camUp[1] + cameraDelta[0] * camUp[0] + cameraDelta[2] * camUp[2]);
                // Some acos/debug?
                FUN_00b9b988();
                if (*(float*)(handle + 0x20) <= (float)dotResult && (float)dotResult <= *(float*)(handle + 0x24)) {
                    FUN_009ab250(handle); // Process hit
                    goto LAB_007e5616;
                }
            }
            // Check if handle is a specific type
            if (FUN_009a98b0(handle) || FUN_009a9b80(handle)) {
                LAB_007e5616:
                FUN_009ab9c0(handle); // Apply damage/effect
                FUN_0081efa0(handle); // Spawn FX
                return;
            }
        }
    }

    LAB_007e564c:
    FUN_009ab9c0(0);
    FUN_0081efa0(0);
}
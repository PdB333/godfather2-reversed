// FUNC_NAME: SteeringController::updateSteering

void __thiscall SteeringController::updateSteering(float deltaTime, float* steeringParams)
{
    // Constants (from globals)
    const float cOne = 1.0f;                    // _DAT_00d5780c
    const float cPI = 3.1415927f;               // _DAT_00d5ccf8 (probably pi)
    const float cEpsilon = 0.00001f;             // assume

    // Game instance pointer (DAT_012233a0 + 4)
    int* gameInstance = *(int**)(DAT_012233a0 + 4);
    if (gameInstance == 0)
        return;

    // Subtract 0x1f30 to get managed object base (piVar12)
    int* managerBase = (int*)(gameInstance + (-0x1f30 / 4)); // offset in dwords
    if (managerBase == 0)
        return;
    int* localManagerBase = managerBase;

    // Check game state: expecting state 2 (maybe in-game)
    int gameState = FUN_007a5f40();
    if (gameState != 2)
        return;

    // Check some flag (maybe pause, cutscene)
    bool isActive = FUN_00481660();
    if (isActive)
        return;

    float param7 = steeringParams[7];   // some parameter

    // Get source transform (likely player/camera)
    int unused = 0;
    float local_44 = 0.0f, local_34 = 0.0f, local_24 = 0.0f;
    float local_14 = cOne;  // constant

    // Call FUN_00425060 with 0 index to get source position
    int* sourceTransformData = (int*)FUN_00425060(&unused, 0);  // returns pointer to 12 bytes?
    float sourceY = *(float*)(sourceTransformData + 1);         // second float (y)
    double sourcePosDouble = *(double*)sourceTransformData;      // packed x,z?
    float sourceX = (float)(uint)sourcePosDouble;
    float sourceZ = (float)((ulonglong)sourcePosDouble >> 32);

    // Transform to world coordinates via FUN_0056b8a0
    float worldPos[3];
    FUN_0056b8a0(sourceZ, sourceX, sourceY, &worldPos);   // note: order may be swapped

    // Get target transform (likely destination)
    int* destTransformData = (int*)FUN_00424fb0(&unused, 0);
    double destPosDouble = *(double*)destTransformData;
    float destY = *(float*)(destTransformData + 1);
    float destX = (float)(uint)destPosDouble;
    float destZ = (float)((ulonglong)destPosDouble >> 32);

    // Store target direction/position for later
    // local_c4 is the target direction vector (x,z,y)
    float targetDirX = worldPos[0] - destX;   // actually inverse? depends on conventions
    float targetDirY = worldPos[1] - destY;
    float targetDirZ = worldPos[2] - destZ;

    // local_d0 = target position (destX, destZ destY)
    // local_c8 = destY
    // Mix of variables from earlier code...

    // Source object pointer (offset 0x5cc from gameInstance)
    int* sourceObj = 0;
    if (*(int*)(gameInstance + 0x5cc) != 0) {
        sourceObj = (int*)(*(int*)(gameInstance + 0x5cc) - 0x48);
    }

    int* targetObjA = 0; // local_f0

    // Get object position via FUN_006c8620 (needs object pointer and some constant)
    float objPos[3];
    FUN_006c8620(objPos, localManagerBase, DAT_00e533e8);

    float dotProduct = targetDirX * (objPos[0] - destX) +
                       targetDirY * (objPos[1] - destY) +
                       targetDirZ * (objPos[2] - destZ);

    // Static state for steering (two buffers)
    // DAT_0112a7bc, DAT_0112a7b4 => pointers to previous target objects?
    // DAT_0112a7b0, DAT_0112a7ac => accumulated forces

    // Initialize static variables (first call)
    if ((DAT_0112a7c4 & 1) == 0) {
        DAT_0112a7c4 |= 1;
        DAT_0112a7bc = 0;
        DAT_0112a7c0 = 0;
        _atexit(&LAB_00d51830);  // cleanup function
    }
    if ((DAT_0112a7c4 & 2) == 0) {
        DAT_0112a7c4 |= 2;
        DAT_0112a7b4 = 0;
        DAT_0112a7b8 = 0;
        _atexit(&LAB_00d51810);
    }

    // Update first steering force (DAT_0112a7b0)
    if (DAT_0112a7bc == 0 || DAT_0112a7bc - 0x48 == 0) {
        DAT_0112a7b0 = 0.0f;
    } else {
        int* objA = DAT_0112a7bc - 0x48;
        float objAPos[3];
        FUN_006c8620(objAPos, objA, DAT_00e533e8);
        float dotA = targetDirX * (objAPos[0] - destX) +
                     targetDirY * (objAPos[1] - destY) +
                     targetDirZ * (objAPos[2] - destZ);
        // Compare dot with threshold (DAT_00e533ec * DAT_00d5f040)
        if ((DAT_00e533ec * DAT_00d5f040) <= (float)((uint)dotA & DAT_00e44680)) {
            DAT_0112a7b0 -= DAT_00e50fd0 * deltaTime;
        } else {
            if (((objAPos[0]-destX)*targetDirX + (objAPos[1]-destY)*targetDirY + (objAPos[2]-destZ)*targetDirZ <= dotProduct) || (dotProduct <= 0.0f)) {
                DAT_0112a7b0 -= DAT_00e50fd0 * deltaTime;
            } else {
                DAT_0112a7b0 += DAT_00e50fd4 * deltaTime;
            }
        }
        // Clamp force
        if (DAT_0112a7b0 > 0.0f) {
            if (DAT_0112a7b0 > DAT_00e50fcc)
                DAT_0112a7b0 = DAT_00e50fcc;
        } else {
            DAT_0112a7b0 = 0.0f;
        }
    }

    // Update second steering force (DAT_0112a7ac)
    if (DAT_0112a7b4 == 0 || DAT_0112a7b4 - 0x48 == 0) {
        DAT_0112a7ac = 0.0f;
        if (DAT_0112a7b4 != 0) {
            FUN_004daf90(&DAT_0112a7b4);
            DAT_0112a7b4 = 0;
        }
    } else {
        int* objB = DAT_0112a7b4 - 0x48;
        float objBPos[3];
        FUN_006c8620(objBPos, objB, DAT_00e533e8);
        float dotB = targetDirX * (objBPos[0] - destX) +
                     targetDirY * (objBPos[1] - destY) +
                     targetDirZ * (objBPos[2] - destZ);
        if ((DAT_00e533ec * DAT_00d5f040) <= (float)((uint)dotB & DAT_00e44680)) {
            DAT_0112a7ac -= DAT_00e50fd0 * deltaTime;
        } else {
            if (((objBPos[0]-destX)*targetDirX + (objBPos[1]-destY)*targetDirY + (objBPos[2]-destZ)*targetDirZ <= dotProduct) || (dotProduct <= 0.0f)) {
                DAT_0112a7ac -= DAT_00e50fd0 * deltaTime;
            } else {
                DAT_0112a7ac += DAT_00e50fd4 * deltaTime;
            }
        }
        if (DAT_0112a7ac > 0.0f) {
            if (DAT_0112a7ac > DAT_00e50fcc)
                DAT_0112a7ac = DAT_00e50fcc;
        } else {
            DAT_0112a7ac = 0.0f;
        }
        if (DAT_0112a7ac <= 0.0f) {
            if (DAT_0112a7b4 != 0) {
                FUN_004daf90(&DAT_0112a7b4);
                DAT_0112a7b4 = 0;
            }
        }
    }

    // Decide which force to use based on magnitude
    if (((DAT_0112a7bc == 0) || ((int*)(DAT_0112a7bc - 0x48) == 0)) || (DAT_0112a7b0 < DAT_0112a7ac)) {
        if (DAT_0112a7b4 != 0) {
            int* objB2 = (int*)(DAT_0112a7b4 - 0x48);
            if ((objB2 != 0) && (DAT_0112a7b0 < DAT_0112a7ac)) {
                // Swap buffers
                FUN_006bf990(&DAT_0112a7bc);   // move from bc to ?
                FUN_0044b210(objB2);            // attach
                float temp = DAT_0112a7ac;
                DAT_0112a7ac = DAT_0112a7b0;
                DAT_0112a7b0 = temp;
                targetObjA = objB2;
            }
        } else {
            // Use source object if no target
            FUN_0044b210(sourceObj);
            DAT_0112a7b0 = 0.0f;
        }
    } else {
        // DAT_0112a7b0 >= DAT_0112a7ac
        int* objB3 = (DAT_0112a7b4 != 0) ? (int*)(DAT_0112a7b4 - 0x48) : 0;
        targetObjA = (int*)(DAT_0112a7bc - 0x48);
        if ((sourceObj != objB3) && (sourceObj != 0) && (sourceObj != targetObjA)) {
            float srcPos[3];
            FUN_006c8620(srcPos, sourceObj, DAT_00e533e8);
            float dotSrc = targetDirX * (srcPos[0] - destX) +
                           targetDirY * (srcPos[1] - destY) +
                           targetDirZ * (srcPos[2] - destZ);
            if ((float)((uint)dotSrc & DAT_00e44680) < DAT_00e533ec * DAT_00d5f040) {
                if ((dotProduct < (srcPos[0]-destX)*targetDirX + (srcPos[1]-destY)*targetDirY + (srcPos[2]-destZ)*targetDirZ) && (_DAT_00d577a0 < dotProduct)) {
                    FUN_0044b210(sourceObj);
                    DAT_0112a7ac = 0.0f;
                }
            }
        }
        if ((DAT_0112a7b4 == 0) || (DAT_0112a7b4 == 0x48)) {
            FUN_0044b210(sourceObj);
            DAT_0112a7b0 = 0.0f;
        }
    }

    // Compute local acceleration factors
    float turnDir, moveDir;
    FUN_006c9eb0(0, &turnDir, &moveDir, param7, param7);
    float lateral, vertical;
    FUN_006ca770(&lateral, &vertical, steeringParams);

    bool hasMovement = (lateral != 0.0f || vertical != 0.0f || turnDir != 0.0f || moveDir != 0.0f);

    // Store processed flags (uStack_f4 and uStack_e8 used as bitfields)
    uint processedFlags = 0;
    uint directionFlags = 0;

    if (hasMovement) {
        if (targetObjA == 0)
            return;
        int targetObjEntity = FUN_006c9440(targetObjA, 0x55859efa);
        if (targetObjEntity != 0) {
            if (((*(uint*)(targetObjEntity + 0x820) >> 5 & 1) == 0) && (FUN_007f47a0() == 0)) {
                int playerIndex = FUN_00471610();
                bool isPlayerSteering = FUN_006c0050(playerIndex + 0x30, 0, 0);
                if (!isPlayerSteering) {
                    // Compute vector from target to source
                    double srcDouble = *(double*)(localManagerBase + 0x23c);
                    float srcY = *(float*)(localManagerBase + 0x23e);
                    double dstDouble = *(double*)(localManagerBase + 0x947);
                    float dstY = *(float*)(localManagerBase + 0x949);
                    float vecX = (float)(uint)srcDouble - (float)(uint)dstDouble;
                    float vecY = srcY - dstY;
                    float vecZ = (float)((ulonglong)srcDouble >> 32) - (float)((ulonglong)dstDouble >> 32);
                    float normalizedVec[3];
                    FUN_0054ba20(&unused, &vecX, &normalizedVec);  // normalize

                    float targetPos[3];
                    FUN_006c8620(targetPos, targetObjEntity, DAT_00e533e8);

                    float proj = normalizedVec[0] * (targetPos[0] - destX) +
                                 normalizedVec[1] * (targetPos[1] - destY) +
                                 normalizedVec[2] * (targetPos[2] - destZ);
                    float threshold = DAT_00e53408;
                    float result = normalizedVec[1] + proj * local_58; // local_58 from earlier
                    if ((result <= targetPos[1] + threshold) && (targetPos[1] - DAT_00e50fc0 * threshold <= result)) {
                        if (result <= DAT_00e50fc4 * threshold + targetPos[1]) {
                            if (result < targetPos[1] - threshold) {
                                directionFlags |= 1; // set bit 0
                            }
                        } else {
                            processedFlags |= 1; // set bit 0
                        }
                    } else {
                        hasMovement = false;
                    }
                }
            }
        }
    }

    if (targetObjA == 0)
        return;

    // Compute final steering forces
    float posDiff[3];
    FUN_006c8620(posDiff, targetObjA, DAT_00e533e8);
    float diffX = posDiff[0] - destX;
    float diffY = posDiff[1] - destY;
    float diffZ = posDiff[2] - destZ;

    float dot1 = diffX * targetDirX + diffY * targetDirY + diffZ * targetDirZ;
    float dot2 = diffX * (sourceY?) + diffY * (something) + diffZ * (something); // messy

    float maskedDot2 = (float)((uint)dot2 & DAT_00e44680);

    // Check thresholds
    if ((DAT_00e533ec * DAT_00d5f040 <= maskedDot2) &&
        (DAT_00e53408 * DAT_00d5f040 <= (float)((uint)(someDot) & DAT_00e44680))) {
        return;
    }
    if (dot1 <= dotProduct)
        return;
    if (dotProduct <= 0.0f)
        return;

    float chosenAccel;
    if (dot2 <= 0.0f)
        chosenAccel = cPI; // negative or pi
    else
        chosenAccel = cOne;

    float baseAccel = lateral;
    if (DAT_0112a7a5 == 0)
        baseAccel = DAT_00e44564 - lateral;

    float accelFactor = (baseAccel * dot2 < 0.0f) ? DAT_00e53404 : DAT_00e53400;
    if (processedFlags & 1)
        accelFactor = DAT_00e53404; // override?

    // Apply damping factors from global multipliers
    if (DAT_0112bb18 != 0.0f) {
        float damping = cOne - (lateral*lateral + vertical*vertical) * DAT_0112bb18;
        if (damping < 0.0f) damping = 0.0f;
        if (damping > cOne) damping = cOne;
        accelFactor *= damping;
    }
    if (DAT_0112bb1c != 0.0f) {
        float damping = cOne - dot1 * DAT_0112bb1c * DAT_00d5ef84;
        if (damping < 0.0f) damping = 0.0f;
        if (damping > cOne) damping = cOne;
        accelFactor *= damping;
    }
    if (DAT_0112bb20 != 0.0f && DAT_00e533f0 < DAT_00e533ec) {
        float range = (maskedDot2 - DAT_00e533f0 * DAT_00d5f040) / (DAT_00e533ec * DAT_00d5f040 - DAT_00e533f0 * DAT_00d5f040);
        float damping = cOne - range * DAT_0112bb20;
        if (damping < 0.0f) damping = 0.0f;
        if (damping > cOne) damping = cOne;
        accelFactor *= damping;
    }

    // Apply to this->mSteeringForce (offset +0xa8)
    this->mSteeringForce = (cOne - accelFactor) * this->mSteeringForce;

    // Vertical steering (angular?)
    float vertAccel;
    if (DAT_0112a7a4 == 0)
        vertAccel = DAT_00e44564 - vertical;
    else
        vertAccel = vertical;
    float vertFactor = (vertAccel < 0.0f) ? DAT_00e53410 : DAT_00e5340c;
    this->mVerticalForce = (cOne - vertFactor) * this->mVerticalForce;

    if (!hasMovement)
        goto applyClamping;

    // Check if special ability (FUN_00690210 with 0x17) is active
    bool isSpecialActive = FUN_00690210(0x17) != 0;
    float specialMod = isSpecialActive ? DAT_00e53418 : cOne;

    float thresholdLow = DAT_00e533f0 * DAT_00d5f040;
    float finalAccel = 0.0f;
    if (thresholdLow <= maskedDot2) {
        finalAccel = DAT_0112bb10;
        if (directionFlags & 1) {
            finalAccel = specialMod * _DAT_00e533f4;
        }
        if (dot1 * DAT_00e533fc <= finalAccel)
            finalAccel = DAT_00e533fc;
        else
            finalAccel = finalAccel / dot1;
    }

    float f = maskedDot2 - thresholdLow;
    if (f < 0.0f) f = 0.0f;
    float range = f / (DAT_00e533ec * DAT_00d5f040 - thresholdLow);
    float blend = (range < 1.0f) ? range : cOne;
    float adjustFactor = (DAT_0112bb14 - DAT_00e533f8) * blend + DAT_00e533f8;

    // Call methods on manager and target (virtual dispatch)
    (*(code**)(*localManagerBase + 0x4c))(&someVector);
    (*(code**)(*targetObjA + 0x4c))(&finalAccel);

    float verticalDot = ... // complex expression
    // Simplified: apply adjusted factors
    float tempForce = steeringParams[1] * DAT_00e445c8 * (directionFlags * something + adjustFactor) + this->mSteeringForce;
    if (tempForce >= 0.0f || (this->mSteeringForce * tempForce >= 0.0f) || ((uint)someFlags >> 8) == 0) {
        this->mSteeringForce = tempForce;
    } else {
        this->mSteeringForce = 0.0f;
    }

    tempForce = steeringParams[3] * DAT_00e445c8 * (something) + this->mVerticalForce;
    if (tempForce >= 0.0f || (this->mVerticalForce * tempForce >= 0.0f) || ((uint)someFlags >> 24) == 0) {
        this->mVerticalForce = tempForce;
    } else {
        this->mVerticalForce = 0.0f;
    }

applyClamping:
    if (DAT_00e50fc8 != 0) {
        // Additional damping based on speeds vs target speeds
        float steeringSpeed = (float)(*(uint*)(this + 0xa8) & DAT_00e44680);
        float targetMin = steeringParams[0];
        float targetMax = steeringParams[1];
        float diff = targetMax - targetMin;
        if (diff > 0.0f) {
            float ratio = (steeringSpeed - targetMin * cOne) / (diff * cOne); // cOne is 1.0
            ratio = ratio * steeringParams[4];
            if (ratio < this->mSomeOtherThreshold) // offset 0x74
                this->mSomeOtherThreshold = ratio;
        }
        // Similar for vertical
        float verticalSpeed = (float)(*(uint*)(this + 0xac) & DAT_00e44680);
        float targetMinV = steeringParams[2];
        float targetMaxV = steeringParams[3];
        float diffV = targetMaxV - targetMinV;
        if (diffV > 0.0f) {
            float ratioV = (verticalSpeed - targetMinV * cOne) / (diffV * cOne);
            ratioV = ratioV * steeringParams[4];
            if (ratioV < this->mSomeOtherThresholdV) // offset 0x78
                this->mSomeOtherThresholdV = ratioV;
        }
    }
}
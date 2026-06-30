// FUNC_NAME: AICarBehavior::update

void __thiscall AICarBehavior::update(float dt) {
    Vehicle* vehicle = m_pVehicle; // this+0x78
    Entity* targetPtr = nullptr;   // from vehicle->m_pTargetPtr

    if (vehicle->m_pTargetHandle != 0) {
        targetPtr = vehicle->m_pTargetPtr;
    }

    if (targetPtr == nullptr) {
        FUN_004abdd0(0x20); // likely error / allocate? return early
        return;
    }

    // Copy target position
    m_targetPos[0] = targetPtr->x;
    m_targetPos[1] = targetPtr->y;
    m_targetPos[2] = targetPtr->z;

    float targetDist = vehicle->m_targetDistance; // +0xf8
    double d = (double)targetDist;

    // Compute heading direction (sin/cos of angle derived from distance)
    float sinAngle = SIN(d);   // FUN_00b99fcb -> sin
    float cosAngle = COS(d);  // FUN_00b99e20 -> cos

    m_headingVec[0] = sinAngle;
    m_headingVec[1] = 0.0f;
    m_headingVec[2] = cosAngle;

    // Normalize heading vector
    normalizeVector(&m_headingVec[0]); // FUN_0056afa0

    m_headingVec[0] = m_headingVec[0];
    m_headingVec[1] = 0.0f;
    m_headingVec[2] = m_headingVec[2];

    m_someOffset = DAT_00e44564 - m_headingVec[2]; // +0xb8
    m_headingVecCopy[0] = m_headingVec[0]; // +0xc0
    m_headingVecCopy[1] = m_headingVec[1]; // +0xbc

    // Get player position
    Player* player = GetPlayer(); // FUN_00471610
    m_relPos[0] = m_targetPos[0] - player->x; // +0x80
    m_relPos[1] = m_targetPos[1] - player->y; // +0x84
    m_relPos[2] = m_targetPos[2] - player->z; // +0x88

    // Get own velocity from AI controller
    Vector3 ownVelocity;
    m_pAIController->getVelocity(&ownVelocity); // vtable+0x4c

    float speed = length(ownVelocity); // sqrt sum squares

    // Compute distance to waypoint
    float dx = player->x - m_waypointX; // +0xc8
    float dz = player->z - m_waypointZ; // +0xd0
    float distToWaypoint = length(Vector2(dx, dz));

    float predictedDist = speed * dt + targetDist;

    float desiredSpeed = 0.0f;
    if (predictedDist <= distToWaypoint) {
        if (distToWaypoint < predictedDist + DAT_00d5780c) {
            desiredSpeed = (speed + targetDist) * DAT_00d5c458;
        }
    } else {
        desiredSpeed = speed + targetDist;
    }

    vehicle->m_desiredSpeed = desiredSpeed; // +0xb0

    // Save previous target pointer for comparison
    int prevTargetHandle = vehicle->m_targetHandle;
    int prevTargetPtr = vehicle->m_targetPtr;

    // AI state machine update
    AIStateMachineUpdateData updateData = { dt, 1, 0, &m_pAIController };
    m_aiState = FUN_00600210(updateData); // returns 1 or 3

    if (m_aiState == 1) {
        // Check if target changed
        int newTargetHandle = vehicle->m_targetHandle;
        int newTargetPtr = vehicle->m_targetPtr;

        if (newTargetPtr != prevTargetPtr) {
            if (rand() * DAT_00e44590 < DAT_00d5cf70) {
                m_flags |= 2;
            }

            char isValid = FUN_00762e60(vehicle, prevTargetPtr, m_aiState, newTargetPtr);
            if (isValid) {
                m_randomAngle = (float)FUN_00763130(); // +0xd4
            }

            FUN_007640a0(1, 0); // notify target change
            FUN_00763ff0();     // handle target update
        }
    } else if (m_aiState == 3) {
        FUN_005ff860(); // enter idle
    }

    // Update relative position copy
    GetPlayer(); // redundant? 
    m_prevRelPos[0] = m_relPos[0]; // +0x98
    m_prevRelPos[1] = m_relPos[1]; // +0x9c
    m_prevRelPos[2] = m_relPos[2]; // +0xa0

    FUN_00763880(); // path following update

    // Engine sound update
    float soundFactor = *(float*)(m_pAIController + 0x150);
    if (soundFactor <= DAT_00d5f18c && DAT_00d5f18c != soundFactor) {
        FUN_00601970(vehicle->m_targetDistance, (Vector3*)&ownVelocity);
        FUN_0046fe50((Vector3*)&ownVelocity, 0);
    }
}
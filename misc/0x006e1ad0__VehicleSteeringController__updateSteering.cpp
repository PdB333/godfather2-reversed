// FUNC_NAME: VehicleSteeringController::updateSteering
// Function address: 0x006e1ad0
// Role: Computes steering output (throttle and turn) for a vehicle or character controller,
// using a path-following / target tracking system with acceleration smoothing.
// Parameters: this (vehicle controller), inputForward (throttle), inputStrafe (steering),
// outTurnAngle (output steering angle), outForwardThrottle (output forward force).
// Internally uses a linked list of waypoints (node size 0x48) and player transform data.

char __thiscall VehicleSteeringController::updateSteering(
    VehicleSteeringController* thisX,
    float inputForward,
    float inputStrafe,
    float* outTurnAngle,
    float* outForwardThrottle
)
{
    int* pNode;         // piVar1
    float fVar2;
    double dVar3;
    float fVar4;
    int iVar8;
    unsigned int uVar12;
    float fVar13;
    float fVar14;
    float local_78;
    float local_70;
    float local_64;
    float local_60;
    float local_5c;
    float local_58;
    float local_bc;
    float local_b8;
    float local_b4;
    float local_d8;
    float local_c8;
    float local_a8;
    float local_7c;
    float local_94;
    float local_48;
    float local_38;
    float local_28;
    Vector3D local_9c;
    Vector3D local_84;
    Vector3D local_b0;
    Vector3D local_90;
    Vector3D local_78vec;
    Vector3D local_6c;
    Vector3D local_e0;
    Vector3D local_d0;
    Uint64 local_double;

    // Scale inputs by global time step
    if (DAT_0112a7a5 != '\0') {
        inputForward = inputForward * DAT_00d5ccf8;
    }
    if (DAT_0112a7a4 != '\0') {
        inputStrafe = inputStrafe * DAT_00d5ccf8;
    }

    // Get current player object from singleton
    if (*(int**)(DAT_012233a0 + 4) == 0) {
        iVar8 = 0;
    }
    else {
        iVar8 = *(int**)(DAT_012233a0 + 4) + -0x1f30;   // Player object offset
    }
    iVar8 = FUN_006e07b0(iVar8);   // Get some ID or flag

    pNode = (int*)(thisX + 0x1ec);   // Pointer to linked list head (waypoints)
    int* oldHead = *pNode;

    if (oldHead == 0) {
        iVar10 = 0;
    }
    else {
        iVar10 = oldHead + -0x48;   // Back to node structure
    }

    if (iVar10 != iVar8) {
        // Update linked list: remove old head, insert new node if exists
        if (iVar8 == 0) {
            iVar8 = 0;
        }
        else {
            iVar8 = iVar8 + 0x48;   // Node address
        }
        if (*pNode != iVar8) {
            if (*pNode != 0) {
                FUN_004daf90(pNode);   // Remove node from list
            }
            *pNode = iVar8;
            if (iVar8 != 0) {
                *(undefined4*)(thisX + 0x1f0) = *(undefined4*)(iVar8 + 4);
                *(int**)(iVar8 + 4) = pNode;   // Insert at head
            }
        }
        // Reset acceleration accumulators
        *(float*)(thisX + 0x1e8) = 0.0f;
        *(float*)(thisX + 0x1e4) = 0.0f;
    }

    if ((*pNode == 0) || (*pNode == 0x48)) {
        return '\0';
    }

    // Get player transform (position and orientation)
    Vector3D* playerPos = FUN_00424fb0(&local_e0, 0);
    local_9c = *playerPos;   // Position vector
    local_94 = *(float*)(playerPos + 1);   // Probably w component or fourth element

    // Initialize some constants
    local_44 = 0;
    local_34 = 0;
    local_24 = 0;
    local_14 = _DAT_00d5780c;   // Some constant

    // Get another transform (maybe forward vector)
    Vector3D* forwardVec = FUN_00425060(&local_6c, 0);
    dVar3 = *forwardVec;   // Might be double?
    local_d8 = *(float*)(forwardVec + 1);
    local_e0 = dVar3;
    // Convert to float components
    float ax = (float)(uint)(local_e0);
    float ay = (float)(uint)(local_e0 >> 0x20);
    FUN_0056b8a0(ay, ax, local_d8, &local_50);   // Probably normalize or convert

    // Extract various vectors from result
    local_b0 = local_40;   // Vector3D from temporary
    local_90 = local_30;
    local_7c = local_48;
    local_e0 = local_50;
    local_a8 = local_38;
    local_d8 = local_48;
    local_88 = local_28;
    local_d4 = 0;

    // Normalize vector
    FUN_0056afa0(&local_e0, &local_e0);
    local_84 = local_e0;   // Player forward direction
    local_7c = local_d8;

    // Compute right vector
    local_e0 = local_b0;
    local_d8 = local_a8;
    local_d4 = 0;
    FUN_0056afa0(&local_e0, &local_e0);
    local_b0 = local_e0;   // Player right direction
    local_a8 = local_d8;

    // Compute up vector
    local_e0 = local_90;
    local_d8 = local_88;
    local_d4 = 0;
    FUN_0056afa0(&local_e0, &local_e0);
    local_90 = local_e0;   // Player up direction
    local_88 = local_d8;

    // Get target position from current waypoint (index 4)
    int waypointBase = (*pNode == 0) ? 0 : *pNode - 0x48;
    char isValid = FUN_006c8620(&local_bc, waypointBase, 4);   // Read target point (Vec3 at index 4)
    uVar12 = DAT_00e44680;   // Some mask

    if (isValid != '\0') {
        // Check distance to target
        float dx = local_bc - (float)(local_9c);   // local_9c is player position
        float dy = local_b8 - local_9c._4_4_;   // player pos y
        float dz = local_b4 - local_94;          // player pos z
        float distSq = dx*dx + dy*dy + dz*dz;
        if (DAT_00e51280 < SQRT(distSq)) {   // If target is far enough
            // Apply acceleration in two axes (maybe steering and throttle?)
            if ((float)((uint)inputStrafe & uVar12) <= 0.0f) {
                if (0.0f < (float)(DAT_0112a958 & uVar12)) {
                    // Use a smoothing function for acceleration
                    float smoothed = FUN_006c89b0(*(float*)(thisX + 0x1e4), 0, DAT_0112a958);
                    *(float*)(thisX + 0x1e4) = smoothed;
                    uVar12 = DAT_00e44680;
                }
            }
            else {
                *(float*)(thisX + 0x1e4) = DAT_00e5127c * inputStrafe + *(float*)(thisX + 0x1e4);
            }

            if ((float)((uint)inputForward & uVar12) <= 0.0f) {
                if (0.0f < (float)(DAT_0112a954 & uVar12)) {
                    float smoothed = FUN_006c89b0(*(float*)(thisX + 0x1e8), 0, DAT_0112a954);
                    *(float*)(thisX + 0x1e8) = smoothed;
                }
            }
            else {
                *(float*)(thisX + 0x1e8) = DAT_00e51278 * inputForward + *(float*)(thisX + 0x1e8);
            }

            // Clamp accelerations
            float minAccel = DAT_00e44564;
            float maxAccel = DAT_00e5126c;
            float accelY = *(float*)(thisX + 0x1e4);   // lateral acceleration
            if (DAT_00e51274 < accelY && accelY < DAT_00e51270) {
                accelY = accelY;
            } else {
                accelY = (DAT_00e51274 > accelY) ? DAT_00e51274 : DAT_00e51270;
            }
            *(float*)(thisX + 0x1e4) = accelY;

            float accelX = *(float*)(thisX + 0x1e8);   // forward acceleration
            float range = maxAccel - minAccel;
            if (range < accelX) {
                accelX = range;
            } else {
                accelX = (accelX < maxAccel) ? accelX : maxAccel;
            }
            *(float*)(thisX + 0x1e8) = accelX;

            // Apply acceleration in forward direction
            local_d0 = local_84;
            local_c8 = local_7c;
            FUN_0043a210(&local_d0, &local_d0);   // Normalize or compute magnitude
            float fwdAcc = *(float*)(thisX + 0x1e8);
            local_bc += (float)local_d0 * fwdAcc;
            local_b8 += local_d0._4_4_ * fwdAcc;
            local_b4 += local_c8 * fwdAcc;

            // Apply acceleration in right direction
            local_d0 = local_b0;
            local_c8 = local_a8;
            FUN_0043a210(&local_d0, &local_d0);
            float rightAcc = *(float*)(thisX + 0x1e4);
            local_bc += (float)local_d0 * rightAcc;
            local_b8 += local_d0._4_4_ * rightAcc;
            local_b4 += local_c8 * rightAcc;

            // Compute error vector to target
            Vector3D error;
            error.x = local_bc - (float)(local_9c);
            error.y = local_b8 - local_9c._4_4_;
            error.z = local_b4 - local_94;
            local_78vec.x = error.x;
            local_70 = error.y;   // note: local_78vec.y likely
            local_6c.x = (uint)FUN_0043a210(&error, &error);   // magnitude

            // Compute turning output (likely using dot product with forward)
            float turnAngle = (float)(FUN_004a10f0(&DAT_00d5f714, &error, &DAT_00d5f708) * (float10)DAT_00d5ccf8);
            *outTurnAngle = turnAngle;   // param_4

            // Compute forward output (likely using dot product with right)
            float forwardForce = (float)(FUN_004a10f0(&error, &local_78vec, &local_84) * (float10)DAT_00d5ccf8);
            *outForwardThrottle = forwardForce;   // param_5

            // Additional adjustment: if player is facing away from target, add to forward force
            int someId = FUN_004262f0(0);   // Get some ID
            FUN_00424fb0(&local_9c, 0);     // Update player position again? Possibly redundant
            // Get player orientation (maybe from some global)
            Vector3D playerOrientation;
            playerOrientation = *(Vector3D*)(DAT_01129944 + 0x108);
            local_a8 = *(float*)(DAT_01129944 + 0x110);
            local_a4 = _DAT_00d5780c;
            // Convert orientation to world space
            FUN_0056b420(someId + 0x40, &playerOrientation, &local_60);
            Vector3D toTarget;
            toTarget.x = local_60 - (float)(local_9c);
            toTarget.y = local_5c - local_9c._4_4_;
            toTarget.z = local_58 - local_94;
            local_d0 = toTarget;
            local_c8 = toTarget.z;
            local_d4 = 0;
            FUN_0056afa0(&local_d0, &local_d0);
            // If player is behind target, add extra forward force
            if ((float10)0 < extraout_ST0) {
                float extraForce = (float)FUN_004a10f0(&local_90, &local_e0, &local_84);
                *outForwardThrottle = (float)(extraout_ST0_00 + (float10)*outForwardThrottle);
            }
            return isValid;
        }
    }
    return isValid;
}
// FUNC_NAME: PlayerVehicleController::smoothVelocityUpdate
bool __fastcall PlayerVehicleController::smoothVelocityUpdate(int thisPtr)
{
    // Check if player is controlling vehicle (probably a flag from GameState)
    if (!GameState::isPlayerControlling(0)) {
        return false;
    }
    // Check if cutscene or overlay is active
    if (CutsceneManager::isCutsceneActive()) {
        return false;
    }

    int vehiclePtr = VehicleManager::getPlayerVehicle();
    if (vehiclePtr == 0) {
        return false;
    }

    // Read vehicle's current position/velocity (likely doubles for smoothing)
    // Offsets: +0x30 = double (x,z?), +0x38 = float (y?)
    double vehiclePosDouble = *(double*)(vehiclePtr + 0x30);
    float vehiclePosY = *(float*)(vehiclePtr + 0x38);
    // Reading same double again for splitting
    double vehiclePosDouble2 = *(double*)(vehiclePtr + 0x30);
    float vehiclePosY2 = *(float*)(vehiclePtr + 0x38);

    // Extract components
    float vehiclePosX = (float)(uint32_t)(vehiclePosDouble);  // low part
    float vehiclePosZ = (float)(vehiclePosDouble >> 32);      // high part

    // Constants for smoothing (these are global floats)
    float smoothingFactor = 0.0f;  // will be set below
    // Global constant DAT_00e52828 likely blend factor
    float blendFactor = DAT_00e52828;  // e.g., 0.75
    // Global constant _DAT_00d5780c likely time delta or base speed
    float baseSpeed = _DAT_00d5780c;

    // Convert to local copy for interpolation
    Vector2 currentPos2D(vehiclePosX, vehiclePosZ);
    float currentPosY = vehiclePosY;
    Vector2 targetPos2D; // from local_e8
    float targetPosY;
    // ... (the code then calls some interpolation function)

    // Actually the code builds a vector and calls FUN_00542650 (likely VectorLerp)
    // Then FUN_009e5ed0 initializes something with a struct
    undefined local_60[92]; // buffer for some transform

    // Setup interpolation parameters
    float targetX = DAT_00e52830 + (float)(vehiclePosDouble >> 32);
    float targetZ = DAT_00e5282c - (float)vehiclePosDouble; // note sign
    // These DAT values are likely target position offsets

    Vector2 targetPos(targetX, targetZ);
    Vector2 lerpResult;
    Vector2Lerp(&lerpResult, &currentPos2D, &targetPos, DAT_00e52834, DAT_00e52838, 0, 0);

    // Prepare struct for FUN_009e5ed0
    struct SmoothingData {
        float unk0;   // local_b0
        float unk1;   // local_cc
        float *ptr;   // local_d0
        int flags;    // local_70, local_80
        // ...
    };

    SmoothingData data;
    data.ptr = &PTR_FUN_00e32a8c;  // some vtable/function table
    data.unk0 = _DAT_00d5780c;     // base speed
    data.unk1 = _DAT_00d5780c;     // same
    // Clear flags
    int flags1 = 0;
    int flags2 = 0;
    int ac = -1;
    int a0 = -1;

    // Call some initializer
    FUN_009e5ed0(local_60, &data);

    if (flags1 != 0) {
        // Apply smoothing with blend factor and time delta
        float blendedX = (targetPos.x - currentPos2D.x) * blendFactor + currentPos2D.x;
        float blendedZ = (targetPos.z - currentPos2D.z) * blendFactor + currentPos2D.z;
        float blendedY = (targetPosY - currentPosY) * blendFactor + currentPosY;

        // Scale by reciprocal of something
        float invTimeScale = baseSpeed / *(float*)(DAT_01223480 + 0x60); // +0x60 might be time delta

        // Compute final velocity
        double velocityXZ = (double)((blendedX - vehiclePosX) * invTimeScale);
        // Actually the code does ((target - current) * blend + current) - original
        // Then multiply by invTimeScale
        // The exact math is messy but we replicate

        // Store to thisPtr offsets
        *(double*)(thisPtr + 0x424) = velocityXZ;   // x and z packed as double
        *(float*)(thisPtr + 0x42c) = (blendedY - vehiclePosY) * invTimeScale;  // y velocity
        return true;
    }

    return false;
}
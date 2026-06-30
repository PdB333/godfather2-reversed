// FUNC_NAME: CameraShakeController::updateCameraShake

void CameraShakeController::updateCameraShake()
{
    // Global state variables (offsets derived from known addresses)
    // +0x01206720 : float g_shakeMagnitude
    // +0x012066f0 : int32 g_shakeActiveFlag
    // +0x0120670c : float g_shakeOffsetX
    // +0x01206718 : float g_shakeOffsetY
    // +0x01206710 : float g_shakeVelocityX
    // +0x01206714 : float g_shakeVelocityY
    // +0x0120671c : float g_shakeVelocityZ
    // +0x01206700,0x04,0x08 : float g_shakeTargetX/Y/Z
    // +0x01206730 : int32 g_savedShakeActive
    // +0x01206734..0x3c : float g_savedShakeValues[4]
    // +0x01206740..0x4c : float g_savedShakeTarget[4]
    // +0x01206750..0x5c : float g_savedShakeVelocity[4]
    // +0x00e2b1a4 : float g_shakeDampingThreshold
    // +0x00e2af44 : float g_shakeMinDisplacement
    // +0x00e2e780 : float g_shakeEpsilon
    // +0x012058d0 : int32 g_cameraMode
    // +0x00f15988 : int32 g_cameraModeMirror
    // +0x011f3a30,0x39f4,0x3a3c,0x3a38,0x3a14,0x3a44 : int32 g_cameraModeFlags[6]
    // +0x011f3910 : int32 g_shakeActive
    // +0x011f3914 : int32 g_shakePreviousActive
    // +0x01205750 : void* g_cameraInstance (pointer to camera object with vtable)
    // +0x012058a8 : uint32 g_cameraObjectId
    // +0x012054dc : void* g_gameState (with field +0x170 for camera Id)
    // +0x011a0f28 : byte[] g_cameraObjectStateArray (40-byte entries)

    int32 prevShakeActive = g_shakePreviousActive;

    // If no shake or zero displacement, clear saved active flag
    if (g_shakeMagnitude == 0.0f || g_shakeActiveFlag == 0 ||
        (g_shakeOffsetX < g_shakeMinDisplacement && g_shakeOffsetY < g_shakeMinDisplacement))
    {
        g_savedShakeActive = 0;
    }
    else
    {
        // Dampen shake if magnitude is below threshold (scale down the offsets?)
        if (g_shakeMagnitude < g_shakeDampingThreshold)
        {
            g_shakeOffsetX *= g_shakeMagnitude;
            g_shakeOffsetY *= g_shakeMagnitude;
        }

        // Check if any component of current state differs from saved state by more than epsilon
        bool stateChanged = (g_shakeActiveFlag != g_savedShakeActive) ||
            (fabs((float)((uint32)(g_shakeVelocityX - g_savedShakeVelocity[0]) & (uint32)g_shakeEpsilon)) > g_shakeEpsilon) ||
            (fabs((float)((uint32)(g_shakeVelocityY - g_savedShakeVelocity[1]) & (uint32)g_shakeEpsilon)) > g_shakeEpsilon) ||
            (fabs((float)((uint32)(g_shakeVelocityZ - g_savedShakeVelocity[2]) & (uint32)g_shakeEpsilon)) > g_shakeEpsilon) ||
            (fabs((float)((uint32)(g_shakeOffsetY - g_savedShakeVelocity[3]) & (uint32)g_shakeEpsilon)) > g_shakeEpsilon) ||
            (fabs((float)((uint32)(g_shakeTarget[0] - g_savedShakeTarget[0]) & (uint32)g_shakeEpsilon)) > g_shakeEpsilon) ||
            (fabs((float)((uint32)(g_shakeTarget[1] - g_savedShakeTarget[1]) & (uint32)g_shakeEpsilon)) > g_shakeEpsilon) ||
            (fabs((float)((uint32)(g_shakeTarget[2] - g_savedShakeTarget[2]) & (uint32)g_shakeEpsilon)) > g_shakeEpsilon) ||
            (fabs((float)((uint32)(g_shakeOffsetX - g_savedShakeTarget[3]) & (uint32)g_shakeEpsilon)) > g_shakeEpsilon);

        if (stateChanged)
        {
            // Copy current state into saved state
            g_savedShakeActive = g_shakeActiveFlag;
            g_savedShakeValues[0] = *(float*)(&g_shakeActiveFlag + 4); // next 4 floats
            g_savedShakeValues[1] = *(float*)((int*)&g_shakeActiveFlag + 2);
            g_savedShakeValues[2] = *(float*)((int*)&g_shakeActiveFlag + 3);
            g_savedShakeValues[3] = *(float*)((int*)&g_shakeActiveFlag + 4);
            g_savedShakeTarget[0] = g_shakeTarget[0];
            g_savedShakeTarget[1] = g_shakeTarget[1];
            g_savedShakeTarget[2] = g_shakeTarget[2];
            g_savedShakeTarget[3] = g_shakeOffsetX;
            g_savedShakeVelocity[0] = g_shakeVelocityX;
            g_savedShakeVelocity[1] = g_shakeVelocityY;
            g_savedShakeVelocity[2] = g_shakeVelocityZ;
            g_savedShakeVelocity[3] = g_shakeOffsetY;
        }
    }

    // Reset shake magnitude for next frame
    g_shakeMagnitude = 0.0f;

    // If shake is active and displacement is large enough, process transition
    if (g_savedShakeActive != 0 &&
        (g_shakeMinDisplacement <= g_savedShakeTarget[3] || g_shakeMinDisplacement <= g_savedShakeVelocity[3]))
    {
        bool previouslyActive = (g_shakeActive != 0);
        g_shakeActive = 0;
        g_shakePreviousActive = 0;

        if (previouslyActive || prevShakeActive != 0)
        {
            // Notify camera object that shake ended (virtual call at vtable+0x9c)
            (*(void (**)(void*, int))(*g_cameraInstance + 0x9c))(g_cameraInstance, 0);
        }

        // Set camera mode and flags (multiple assignments for different states)
        if (g_cameraMode < 0x16) g_cameraMode = 0x16;
        if (0x16 < g_cameraModeMirror) g_cameraModeMirror = 0x16;
        g_cameraModeFlags[0] = 1; // +0x011f3a30

        if (g_cameraMode < 7) g_cameraMode = 7;
        if (7 < g_cameraModeMirror) g_cameraModeMirror = 7;
        g_cameraModeFlags[1] = 0; // +0x011f39f4

        if (g_cameraMode < 0x19) g_cameraMode = 0x19;
        if (0x19 < g_cameraModeMirror) g_cameraModeMirror = 0x19;
        g_cameraModeFlags[2] = 5; // +0x011f3a3c

        if (g_cameraMode < 0x18) g_cameraMode = 0x18;
        if (0x18 < g_cameraModeMirror) g_cameraModeMirror = 0x18;
        g_cameraModeFlags[3] = 0; // +0x011f3a38

        if (g_cameraMode < 0xf) g_cameraMode = 0xf;
        if (0xf < g_cameraModeMirror) g_cameraModeMirror = 0xf;
        g_cameraModeFlags[4] = 0; // +0x011f3a14

        if (g_cameraMode < 0x1b) g_cameraMode = 0x1b;
        if (0x1a < g_cameraModeMirror) g_cameraModeMirror = 0x1b;
        g_cameraModeFlags[5] = 1; // +0x011f3a44

        // Call start/stop event with parameters (1,5,6)
        FUN_00417cf0(1, 5, 6);

        // Additional update functions
        FUN_005392b0();
        // Process camera object state for current ID
        uint32 cameraId = g_cameraObjectId;
        if (g_gameState != nullptr)
        {
            cameraId = *(uint32*)(g_gameState + 0x170);
        }
        if (cameraId != (uint32)-1 && cameraId < 0x1000)
        {
            int32 entryOffset = cameraId * 0x38;
            byte* stateBase = &g_cameraObjectStateArray[entryOffset];
            if (stateBase != nullptr && *stateBase < 4)
            {
                int32* ptr2 = (int32*)(stateBase + 0x1c); // +0x44 relative to base (0x28+0x1c=0x44)
                if (*ptr2 != 0)
                {
                    FUN_00606e60(*ptr2, 0x210000);
                }
                *(uint32*)(stateBase + 0x0c) = *(uint32*)(stateBase + 0x0c) & 0xfcad8fff | 0x210000;
                FUN_006189c0();
            }
        }

        // Run camera update chain
        FUN_0053a3d0();
        FUN_0053a320();
        FUN_0053a370();
        FUN_005388a0();

        // Allocate and fill a 5-element float buffer
        float* buffer = (float*)FUN_0060cd00(5, 4, 0, 1, 0);
        if (buffer != nullptr)
        {
            buffer[0] = g_shakeStartPoint;   // DAT_00e2eff4
            buffer[1] = g_shakeEndPoint;     // DAT_00e2eff4 (same?)
            buffer[2] = g_shakeDampingThreshold; // DAT_00e2b1a4
            buffer[3] = g_shakeEndPoint;
            buffer[4] = g_shakeEndPoint;
            buffer[5] = g_shakeDampingThreshold;
            buffer[6] = g_shakeDampingThreshold;
            buffer[7] = g_shakeDampingThreshold;
            FUN_0060cde0();
        }

        FUN_00539250();

        // Second set of mode assignments (different flags)
        if (g_cameraMode < 0x16) g_cameraMode = 0x16;
        if (0x16 < g_cameraModeMirror) g_cameraModeMirror = 0x16;
        g_cameraModeFlags[0] = 1;

        if (g_cameraMode < 7) g_cameraMode = 7;
        if (7 < g_cameraModeMirror) g_cameraModeMirror = 7;
        g_cameraModeFlags[1] = 1; // Changed from 0 to 1

        if (g_cameraMode < 0x19) g_cameraMode = 0x19;
        if (0x19 < g_cameraModeMirror) g_cameraModeMirror = 0x19;
        g_cameraModeFlags[2] = 7; // Changed from 5 to 7

        if (g_cameraMode < 0x18) g_cameraMode = 0x18;
        if (0x18 < g_cameraModeMirror) g_cameraModeMirror = 0x18;
        g_cameraModeFlags[3] = 0;

        if (g_cameraMode < 0xf) g_cameraMode = 0xf;
        if (0xf < g_cameraModeMirror) g_cameraModeMirror = 0xf;
        g_cameraModeFlags[4] = 0;

        if (g_cameraMode < 0x1b) g_cameraMode = 0x1b;
        if (0x1a < g_cameraModeMirror) g_cameraModeMirror = 0x1b;
        g_cameraModeFlags[5] = 0; // Changed from 1 to 0

        // Fire event again with same parameters
        FUN_00417cf0(1, 5, 6);

        // Save previous active IDs for next frame
        uint32 oldActive = g_shakeActive;
        uint32 oldPrev = g_shakePreviousActive;
        g_shakeActive = g_cameraObjectId;
        if (g_gameState != nullptr)
        {
            g_shakeActive = *(uint32*)(g_gameState + 0x170);
        }
        g_shakePreviousActive = 0;

        // Signal completion (type 4)
        FUN_00609340(4, oldActive, oldPrev);
    }
}
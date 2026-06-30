// FUNC_NAME: ChaseCamera::update
// Location: 0x006d5320
// This function updates the third-person chase camera each frame.
// It processes player input for camera rotation, applies damping and smoothing,
// handles camera collision and manages a timer for camera animations (e.g., shakes).

void __thiscall ChaseCamera::update(ChaseCamera* this, float deltaTime)
{
    // --- Global singletons / data ---
    // DAT_01129944 = some manager (e.g., PlayerManager) at +0x108 has camera origin?
    // DAT_01129914 = another manager (e.g., CameraManager) with flags at +0xd1
    // DAT_012233a0 = object manager, used for vtable check
    // DAT_0112a838 = input manager? +0x5c is an enable flag
    // DAT_0112a87c = game settings? +0x50 is bitfield for camera invert
    // DAT_0112a7a4, DAT_0112a7a5 = camera sensitivity flags

    int* pManager1 = (int*)DAT_01129944;          // e.g., player manager
    int* pManager2 = (int*)DAT_01129914;          // e.g., camera manager
    int* pObjMgr = (int*)DAT_012233a0;            // object manager
    float fCameraInitTimer = DAT_012233b4;        // initial timer for camera start?
    float fDeadZone = DAT_00d5c454;               // joystick dead zone
    float fSensitivityYaw = DAT_00d5ccf8;         // sensitivity for yaw
    float fSensitivityPitch = DAT_00d5ccf8;       // sensitivity for pitch (maybe separate)
    float fAccelFactor = DAT_00d5d934;            // acceleration factor? (used when sprinting)
    float fSmoothFactor;                          // from parent object
    float fYawInput, fPitchInput;                 // filtered input
    int parentObj;                                // parent sentient/player base object

    // Timer / cooldown for camera effect (e.g., shake or cinematic)
    if (*(int*)(this + 0xA0) == 0)
    {
        // --- Camera is in normal free mode ---
        int* vtable = **(int***)(pObjMgr[1]);
        if (vtable == 0 || vtable == (int*)0x1f30)
            goto LAB_006d5c8a;

        // Get the input device data (XInput controller state)
        int inputHandle = (**(code**)(*vtable + 8))();
        float* pInput = (float*)FUN_00410540(inputHandle);
        if (pInput == 0)
            goto LAB_006d5c8a;

        // Check if input is enabled (global flag)
        if (*(int*)(DAT_0112a838 + 0x5c) == 0)
        {
            // Determine camera attachment type
            int attachResult;
            if (*(int*)(this + 0xC0) == 0)
                attachResult = FUN_008a0410(this + 0xB0); // attach to shoulder
            else
                attachResult = FUN_008a0530(this + 0xB0); // attach to vehicle
            *(int*)(this + 0xA0) = attachResult;

            float fBaseFov = DAT_00e44634;
            float fZero = _DAT_00d5780c; // often 0.0

            if (attachResult == 0)
            {
                // --- Camera starts in default position ---
                // Compute a offset from the parent object
                float fOffsetX = DAT_00d5f414;
                float fOffsetY = fBaseFov;
                float fOffsetZ = DAT_00d5f414;
                *(ulonglong*)(pManager1 + 0x108) = (ulonglong)(uint)DAT_00d5f414 << 0x20;
                *(float*)(pManager1 + 0x110) = fBaseFov;

                float fDefaultPos[3]; // local_288 was used for something else
                // Get the parent object's facing direction
                FUN_0056b8a0(*(undefined4*)(this + 0x84), *(undefined4*)(this + 0x80),
                             *(undefined4*)(this + 0x88), (float*)afStack_1d0);

                // Compute a forward vector with some offset
                float fForward[4] = {0,0,0,0};
                FUN_0056b420((float*)afStack_1d0, &fForward[0], &fForward[0]);

                // Scale by a factor
                float fScale = DAT_00d5e288;
                fForward[0] *= fScale;
                fForward[1] *= fScale;
                fForward[2] *= fScale;
                fForward[3] *= fScale;

                // Compute the new camera position relative to parent
                float newPos[4];
                newPos[0] = fForward[0] + *(float*)(this + 0x20);
                newPos[1] = fForward[1] + *(float*)(this + 0x24);
                newPos[2] = fForward[2] + *(float*)(this + 0x28);
                newPos[3] = fForward[3] + *(float*)(this + 0x2c);
                FUN_0089e440((int*)(this + 0x20), newPos); // set new position

                // Check for camera shake trigger (flag & 0x400)
                if ((((uint)pInput[4] & 0x400) != 0) && ((*(ushort*)((int)pInput + 0x12) & 0x400) == 0)
                    && (*(char*)(pManager2 + 0xD1) != 0))
                {
                    FUN_0089fd30(); // start shake
                }

                // Create a camera effect (sound event)
                fCameraInitTimer = 0.0f;
                FUN_00540bc0(0x40106, 0x510001, &fCameraInitTimer, 0);

                // Store current position for later reference
                float currentPos[4];
                currentPos[0] = *(float*)(this + 0x20);
                currentPos[1] = *(float*)(this + 0x24);
                currentPos[2] = *(float*)(this + 0x28);
                currentPos[3] = *(float*)(this + 0x2c);

                // Call some debug/gameplay function
                FUN_00a64b00(_DAT_00d5c458);

                // Build a query structure for collision (raycast)
                float queryStart[6] = {_DAT_00d5780c, 0,0,0,0, _DAT_00d5780c};
                float queryEnd[4] = {currentPos[0], currentPos[1], currentPos[2], _DAT_00d5780c};
                queryEnd[1] = 0.0f; // actually the struct is weird, but it's a ray
                // ... (skipping details)

                // Perform a camera collision query
                FUN_00549b60((undefined4*)&uStack_220, (float*)afStack_c0, 0);
                int queryHandle = FUN_00540cc0((byte*)auStack_d4);

                // If the query returned a hit, adjust camera position
                if (iStack_160 != 0)
                {
                    FUN_0044c490((int*)(this + 0x20), &fForward[0], uStack_164, &currentPos[0]);

                    // Check for something (like a vehicle)
                    int someFlag = 0;
                    int obj = FUN_004afca0(uStack_158);
                    if (obj != 0)
                    {
                        someFlag = FUN_006c9470(obj, 0x383225a1);
                        if (someFlag != 0)
                        {
                            char c = FUN_007f47a0();
                            if (c != 0)
                                someFlag = 0;
                        }
                    }

                    // If camera is in a vehicle, maybe change behavior
                    if (((uint)pInput[4] & 0x800) != 0 && ((*(ushort*)((int)pInput + 0x12) & 0x800) == 0))
                    {
                        FUN_008a1060(&currentPos[0], someFlag);
                    }

                    char state = 0;
                    if (someFlag == 0)
                    {
                        if (*(char*)(pManager2 + 0xD1) != 0)
                            state = 2;
                    }
                    else
                    {
                        state = (*(char*)(pManager2 + 0xD1) != 0) * 2 + 1;
                    }

                    FUN_006d51d0(state); // set camera state
                }
            }
            else
            {
                // Attachment failed? Clear camera mode
                FUN_0089e200();
                FUN_0089e240();
                *(float*)(this + 0xA4) = fDeadZone;
            }
        }

        // If the camera timer is non-zero, it's in a forced animation
        if (*(int*)(this + 0xA0) != 0)
            goto LAB_006d5c8a;

        // --- Process player input for camera rotation ---
        // Check flags for camera control (input enabled)
        if ((uint)pInput[4] & 0x100)
        {
            if (*(int*)(this + 0xC0) != 1)
            {
                FUN_0089e240(); // enable camera?
                *(int*)(this + 0xC0) = 1;
            }
        }
        else
        {
            if (*(int*)(this + 0xC0) != 0)
            {
                FUN_0089e200(); // disable camera?
                *(int*)(this + 0xC0) = 0;
            }
        }

        // Read analog stick input (x = yaw, y = pitch)
        fYawInput = pInput[0];
        fPitchInput = pInput[1];

        // Apply dead zone filter
        float deadZone = fDeadZone;
        char isAiming = FUN_00410f30(); // check if aiming (disables input?)
        if (isAiming)
            deadZone = 0.0f;

        if ((float)((uint)fYawInput & DAT_00e44680) <= deadZone)
            fYawInput = 0.0f;
        if ((float)((uint)fPitchInput & DAT_00e44680) <= deadZone)
            fPitchInput = 0.0f;

        // Apply sensitivity and invert flags
        float sensitivityMult = 0.0f;
        if ((*(byte*)(DAT_0112a87c + 0x50) & 1) == 0) // check invert Y?
        {
            fPitchInput = pInput[2];
            if ((float)((uint)fPitchInput & DAT_00e44680) <= deadZone)
                fPitchInput = 0.0f;

            float pitchAccel = 0.0f;
            if (deadZone < (float)((uint)pInput[3] & DAT_00e44680))
                pitchAccel = pInput[3]; // acceleration from trigger?

            float invertMult = _DAT_00d5780c; // maybe 1.0
            if (DAT_0112a7a5 != 0)
                invertMult = DAT_00d5ccf8; // sensitivity

            fYawInput = invertMult * fYawInput;
            float pitchSens = DAT_00d5ccf8;
            if (DAT_0112a7a4 == 0)
                pitchSens = _DAT_00d5780c;
            pitchAccel = pitchSens * pitchAccel;

            // If aiming, reduce sensitivity
            char isAiming2 = FUN_00410eb0();
            if (isAiming2)
            {
                pitchAccel *= fAccelFactor;
                fYawInput *= fAccelFactor;
            }
        }

        // --- Update camera angular velocity ---
        // Parent object base (offset 0xc - 0x48)
        if (*(int*)(this + 0xC) == 0)
            parentObj = 0;
        else
            parentObj = *(int*)(this + 0xC) - 0x48;

        float fDamping = *(float*)(parentObj + 0xA0); // damping factor
        float fYawVelocity = *(float*)(this + 0x80);
        float fPitchVelocity = *(float*)(this + 0x84);

        // Apply input to velocity (with sensitivity and time)
        fYawVelocity += *(float*)(parentObj + 0xA4) * fYawInput * deltaTime;
        fPitchVelocity -= *(float*)(parentObj + 0xA4) * pitchAccel * deltaTime;

        // Clamp pitch velocity (based on parent constraints)
        float minPitch = *(float*)(parentObj + 0xA8);
        float maxPitch = *(float*)(parentObj + 0xAC);
        if (fYawVelocity < minPitch)
            fYawVelocity = minPitch;
        if (fYawVelocity > maxPitch)
            fYawVelocity = maxPitch;
        // Note: seems like yaw and pitch might be swapped in the decompile? We'll keep as is.

        // Apply damping over time
        FUN_0056b8a0(fPitchVelocity, fYawVelocity, *(undefined4*)(this + 0x88), (float*)afStack_1d0);
        // Compute velocity decay
        *(float*)(this + 0x68) -= (fStack_1a8 * fPitchInput + fStack_1c8 * fYawInput) * fDamping;
        *(float*)(this + 0x60) -= (fStack_1b0 * fPitchInput + afStack_1d0[0] * fYawInput) * fDamping;

        // Copy current state to global for interpolation
        int* pDest = &DAT_0112a890;
        int* pSrc = (int*)(this + 0x20);
        for (int i = 0; i < 16; i++)
            pDest[i] = pSrc[i];

        // --- Perform camera collision via world query ---
        float* pCurrentPos = (float*)(this + 0x20);
        float* pCurrentVelocity = (float*)(this + 0x60);
        // Build a query structure
        uStack_220 = *(undefined4*)(this + 0x20);
        uStack_210 = *(undefined4*)(this + 0x60);
        // ... (complex struct building)

        // Execute collision query
        FUN_009e5ed0(&uStack_220, &ppuStack_150);

        // If hit, interpolate camera position towards collision-avoided position
        if (iStack_f0 != 0)
        {
            float t = fStack_130 - DAT_00d58cbc;
            if (t < 0.0f || _DAT_00d5780c >= t)
                t = 0.0f;
            else
                t = _DAT_00d5780c; // clamp? Actually it's a lerp coefficient

            // Smoothly move camera to avoid collision
            float newPos2[4];
            newPos2[0] = (*(float*)(this + 0x60) - *(float*)(this + 0x20)) * t + *(float*)(this + 0x20);
            newPos2[1] = (*(float*)(this + 0x64) - *(float*)(this + 0x24)) * t + *(float*)(this + 0x24);
            newPos2[2] = (*(float*)(this + 0x68) - *(float*)(this + 0x28)) * t + *(float*)(this + 0x28);
            newPos2[3] = (*(float*)(this + 0x6C) - *(float*)(this + 0x2C)) * t + *(float*)(this + 0x2C);

            // Copy target to current for intermediate step?
            *(int*)(this + 0x64) = *(int*)(this + 0x24);
            *(float*)(this + 0x60) = newPos2[0];
            *(float*)(this + 0x68) = newPos2[2];
        }

        // Notify system of camera state
        FUN_009284a0(*(char*)(pManager2 + 0xD1) != 0);
        uVar15 = 0;
    }
    else
    {
        // --- Camera is in a timer-based animation (like a shake) ---
        float remaining = *(float*)(this + 0xA4) - deltaTime;
        *(float*)(this + 0xA4) = remaining;
        if (remaining > 0.0f)
        {
            // Copy target position to current position (snap)
            *(int*)(this + 0x60) = *(int*)(this + 0xB0);
            *(int*)(this + 0x64) = *(int*)(this + 0xB4);
            *(int*)(this + 0x68) = *(int*)(this + 0xB8);
            *(int*)(this + 0x6C) = *(int*)(this + 0xBC);
            goto LAB_006d5c8a;
        }

        // Timer expired – end effect
        FUN_0081ef50(0, 8);
        float fDuration = DAT_00d5c454; // possibly a default duration?
        *(float*)(this + 0xA4) = 0.0f;
        FUN_00424dc0(0, *(int*)(this + 0xA0), fDuration, 8, 0);
        *(int*)(this + 0xA0) = 0; // clear timer
        uVar15 = 1;
    }

    FUN_00928460(uVar15);

LAB_006d5c8a:
    // --- Final interpolation and smoothing across all camera properties ---
    // Parent object offset (again)
    if (*(int*)(this + 0xC) == 0)
        parentObj = 0;
    else
        parentObj = *(int*)(this + 0xC) - 0x48;

    float interpFactor = *(float*)(parentObj + 0xB0); // smoothing factor

    // Interpolate position
    *(float*)(this + 0x20) = (*(float*)(this + 0x60) - *(float*)(this + 0x20)) * interpFactor + *(float*)(this + 0x20);
    *(float*)(this + 0x24) = (*(float*)(this + 0x64) - *(float*)(this + 0x24)) * interpFactor + *(float*)(this + 0x24);
    *(float*)(this + 0x28) = (*(float*)(this + 0x68) - *(float*)(this + 0x28)) * interpFactor + *(float*)(this + 0x28);
    *(float*)(this + 0x2C) = (*(float*)(this + 0x6C) - *(float*)(this + 0x2C)) * interpFactor + *(float*)(this + 0x2C);

    // Interpolate look-at
    *(float*)(this + 0x40) = (*(float*)(this + 0x80) - *(float*)(this + 0x40)) * interpFactor + *(float*)(this + 0x40);
    *(float*)(this + 0x44) = (*(float*)(this + 0x84) - *(float*)(this + 0x44)) * interpFactor + *(float*)(this + 0x44);
    *(float*)(this + 0x48) = (*(float*)(this + 0x88) - *(float*)(this + 0x48)) * interpFactor + *(float*)(this + 0x48);
    *(float*)(this + 0x4C) = (*(float*)(this + 0x8C) - *(float*)(this + 0x4C)) * interpFactor + *(float*)(this + 0x4C);

    // If aiming, snap look-at to target immediately (no smoothing)
    char isAiming = FUN_00410eb0();
    if (isAiming)
    {
        *(int*)(this + 0x40) = *(int*)(this + 0x80);
        *(int*)(this + 0x44) = *(int*)(this + 0x84);
        *(int*)(this + 0x48) = *(int*)(this + 0x88);
        *(int*)(this + 0x4C) = *(int*)(this + 0x8C);
    }

    // Update camera position in the object manager (e.g., for debug display)
    int* pObjMgrVtable = **(int**)(pObjMgr[1]);
    if (pObjMgrVtable != 0)
    {
        int* vtableAdjusted = (int*)(pObjMgrVtable - 0x1f30);
        if (vtableAdjusted != 0)
        {
            float posForDebug[4];
            posForDebug[0] = *(float*)(this + 0x20);
            posForDebug[1] = *(float*)(this + 0x24);
            posForDebug[2] = *(float*)(this + 0x28);
            (**(code**)(*vtableAdjusted + 0x1c))(&posForDebug);
        }
    }

    return;
}
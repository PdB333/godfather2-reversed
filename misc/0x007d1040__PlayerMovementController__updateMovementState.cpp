//FUNC_NAME: PlayerMovementController::updateMovementState
void __thiscall PlayerMovementController::updateMovementState(int this, int gameTime, float deltaTime)
{
    // +0x8c: previous time, +0x88: current time
    *(int*)(this + 0x8c) = *(int*)(this + 0x88);
    float currentTime = FUN_00799230(); // getTime()
    *(float*)(this + 0x88) = currentTime;

    bool bIsCutscene = false;
    bool bIsBlocked = false;
    float speed = 0.0f;
    float inputMagnitude = 0.0f;
    float velocity[3] = {0.0f, 0.0f, 0.0f};

    // Check if cutscene is active
    if (FUN_00481620() == 0) // isCutsceneActive()
    {
        // Normal gameplay: get input vector and velocity
        FUN_007d0d40(&speed, &inputMagnitude); // getInputVector()
        if (FUN_00472510(&velocity[0]) != 0) // getVelocity()
        {
            float velMag = SQRT(velocity[0]*velocity[0] + velocity[1]*velocity[1] + velocity[2]*velocity[2]);
            // Check thresholds for blocking state
            if (gConfigBlockThresholdHigh < velMag ||
                (*(int*)(*(int*)(this + 0x58) + 0x8e4) < 0 && gConfigBlockThresholdMid < velMag))
            {
                bIsBlocked = true;
            }
            else if (gConfigBlockThresholdLow < velMag ||
                     ((*(uint*)(*(int*)(this + 0x58) + 0x8e4) >> 0x1e & 1) != 0 && gConfigBlockThresholdMin < velMag))
            {
                bIsCutscene = true; // Actually used as a flag for "blocked but not fully"
            }
        }
    }
    else
    {
        // Cutscene mode: use random noise for movement
        (*(code**)(**(int**)(this + 0x58) + 0x4c))(&velocity[0]); // getOrientation()
        float noise1 = FUN_0079eb40(0, 0); // getRandomFloat()
        speed = noise1;
        FUN_00425060(&velocity[0], *(undefined4*)(&DAT_00002494 + *(int*)(this + 0x58))); // getRotation()
        float noise2 = FUN_0079eb90(0, 0); // getRandomFloat2()
        inputMagnitude = (noise2 + velocity[0]) * gConfigCutsceneNoiseFactor;
        int playerIdx = FUN_00798f50(0); // getLocalPlayerIndex()
        if (FUN_0079e920(playerIdx) == 0) // isPlayerAlive()
        {
            if ((uint)(gameTime - *(int*)(this + 0xa0)) < gConfigCutsceneTimeout)
            {
                bIsCutscene = true;
            }
        }
        else
        {
            *(int*)(this + 0xa0) = gameTime;
            bIsCutscene = true;
        }
    }

    // Determine movement state based on speed threshold
    if (speed <= gConfigSpeedThreshold || speed == gConfigSpeedThreshold)
    {
        // Idle state
        *(int*)(this + 0x74) = 0; // +0x74: acceleration
        *(float*)(this + 0x90) += deltaTime; // +0x90: idle timer
        *(int*)(this + 0x7c) = 0; // +0x7c: angular velocity
    }
    else
    {
        // Moving state: compute acceleration and angular velocity
        float accel = (float)((uint)speed & gConfigAccelMask);
        speed = gConfigDefaultSpeed;
        float angularVel = 0.0f;
        if (accel <= gConfigDefaultSpeed)
        {
            if (0.0f <= accel)
                angularVel = accel;
            else
                angularVel = 0.0f;
        }
        else
        {
            angularVel = speed;
        }
        *(float*)(this + 0x80) = inputMagnitude; // +0x80: input magnitude
        *(float*)(this + 0x74) = angularVel; // +0x74: acceleration
        *(int*)(this + 0x90) = 0; // reset idle timer
        float angleDiff = inputMagnitude - *(float*)(this + 0x88);
        *(float*)(this + 0x7c) = FUN_006d6350(angleDiff); // +0x7c: angular velocity
    }

    // Debug/cheat: force reset if specific condition
    if (FUN_0079e970(0x466dc7de) != 0) // isCheatEnabled()
    {
        FUN_007cfdd0(gameTime); // resetMovement()
    }

    int newState = *(int*)(this + 0x94); // +0x94: current state
    if (*(float*)(this + 0x74) <= 0.0f)
    {
        // No acceleration: check idle timer
        float idleThreshold = gConfigIdleThresholdDefault;
        if (*(int*)(this + 0xc) != 4) // +0xc: movement type
        {
            idleThreshold = 0.0f;
            if (*(int*)(this + 0xc) == 5)
                idleThreshold = gConfigIdleThresholdAlt;
        }
        if (idleThreshold < *(float*)(this + 0x90))
        {
            newState = 0; // Idle state
            if (FUN_00481660() != 0) // isInputEnabled()
            {
                FUN_00472130(0); // lockInput(false)
            }
        }
    }
    else
    {
        // Has acceleration: determine state based on blocking
        if (FUN_007d0480(gameTime) != 0 || bIsBlocked) // isColliding()
        {
            newState = 3; // Blocked/stopped
        }
        else
        {
            newState = (bIsCutscene ? 1 : 0) + 1; // 1 or 2
        }
    }

    // Update state if changed
    if (newState != *(int*)(this + 0x94))
    {
        *(int*)(this + 0x98) = *(int*)(this + 0x94); // +0x98: previous state
        *(int*)(this + 0x94) = newState;
    }

    // Handle state-specific actions
    if (*(int*)(this + 0x94) != 0)
    {
        if (FUN_00481660() != 0 && FUN_00472820() == 0) // input enabled and not locked
        {
            FUN_00472130(1); // lockInput(true)
        }
        if (*(float*)(this + 0x74) == gConfigSpecialAccel)
        {
            *(float*)(this + 0x74) = gConfigSpecialAccelAlt;
        }
        if (*(int*)(this + 0x94) == 3)
        {
            // State 3: play blocked sounds
            FUN_007f63e0(0x3f); // playSound(kSoundBlocked1)
            FUN_007f6420(0x3e); // stopSound(kSoundBlocked2)
            FUN_007f6420(0x3d); // stopSound(kSoundBlocked3)
            *(int*)(this + 0xa0) = 0;
            return;
        }
        if (*(int*)(this + 0x94) == 2)
        {
            // State 2: play moving sounds
            FUN_007f6420(0x3f); // stopSound(kSoundBlocked1)
            FUN_007f63e0(0x3e); // playSound(kSoundBlocked2)
            FUN_007f6420(0x3d); // stopSound(kSoundBlocked3)
            return;
        }
        // State 1: check if should play idle sound
        if (FUN_007a5f40() != 2) // getMovementMode() != 2
        {
            FUN_007f6420(0x3f);
            FUN_007f6420(0x3e);
            FUN_007f63e0(0x3d); // playSound(kSoundBlocked3)
            return;
        }
    }
    // Default: stop all sounds
    FUN_007f6420(0x3f);
    FUN_007f6420(0x3e);
    FUN_007f6420(0x3d);
}
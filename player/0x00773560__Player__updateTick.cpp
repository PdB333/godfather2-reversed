// FUNC_NAME: Player::updateTick
void __fastcall Player::updateTick(Player *this)
{
    // this+0x74: m_pStateMachine (e.g., FSM)
    // this+0x9c: m_flags (bitfield)
    // this+0xa0: m_pFollowTarget or m_pCameraTarget (Entity*)
    // this+0xb0: m_pBehavior (e.g., AI behavior)

    int pPlayerData = 0;
    Entity *pFollowTarget = *(Entity **)(this + 0xa0);
    int behaviorPtr = *(int *)(this + 0xb0);

    if ((behaviorPtr != 0) && (behaviorPtr != 0x48)) {
        // Look up player-specific data via hash
        pPlayerData = findObjectByHash(0xb47bb605, 0);
    }

    bool bStateFlag = false;
    if (pPlayerData != 0) {
        if ((*(byte *)(pPlayerData + 0x1d0) & 1) != 0) {
            *(uint *)(pPlayerData + 0x1d0) &= 0xfffffffe; // clear bit 0
        }
        bStateFlag = (*(uint *)(pPlayerData + 0x1d0) >> 4) & 1; // bit 4
    }

    // Mark entity as needing update
    *(byte *)(pFollowTarget + 0xa20) = 1;

    // Check and handle cinematic state
    if (((*(byte *)(pFollowTarget + 0x8e6) & 1) != 0) &&
        (pFollowTarget != 0))
    {
        *(int *)(pFollowTarget + 0x1eb4) = DAT_01205224;
        if (getSingleton(DAT_0112a9fc) != 0) {
            resetAnimationSystem();
        }
    }

    // Push/render context?
    pushRenderContext(0x30);

    // Call virtual function at vtable+0x290 (e.g., setDrawMode)
    (*(void (__thiscall **)(Entity *, int, int))(*(int *)pFollowTarget + 0x290))(pFollowTarget, 1, 8);

    // Handle cursor lock flag
    if ((*(uint *)(this + 0x9c) >> 4 & 1) != 0) {
        setCursorState(0, 0, DAT_00d5ef90);
        *(uint *)(this + 0x9c) &= 0xffffffef; // clear bit 4
    }

    *(byte *)(pFollowTarget + 0xa20) = 1;

    // Set global input flag
    *(uint *)(DAT_011298f8 + 0x10) |= 2;

    // Check state machine conditions
    bool bSkipUpdate = true;
    int stateMachine = *(int *)(this + 0x74);
    if (stateMachine != 0) {
        uint stateFlags = *(uint *)(stateMachine + 0x24);
        if (bStateFlag == 0) {
            // Normal branch: check bits 0x3000/0x2000
            stateFlags &= 0x3000;
            if (stateFlags != 0x3000) {
                if (stateFlags != 0x2000) {
                    goto SkipCheck;
                }
                bSkipUpdate = false;
            }
        } else {
            // Alternative branch: check bits 0x600/0x400
            stateFlags &= 0x600;
            if (stateFlags != 0x600) {
                if (stateFlags != 0x400) {
                    goto SkipCheck;
                }
                bSkipUpdate = false;
            }
        }
        // If we reach here, state matched => bSkipUpdate becomes false
        bSkipUpdate = false;
    }
SkipCheck:
    // If bit 3 is set and we are not in a special state, call virtual function at vtable+0x27c
    if (((*(uint *)(this + 0x9c) >> 3 & 1) != 0) && (bSkipUpdate)) {
        (*(void (__thiscall **)(Entity *))(*(int *)pFollowTarget + 0x27c))(pFollowTarget);
    }

    int someState = *(int *)(pFollowTarget + 0x2124);
    bool bPaused = isGamePaused();
    if ((bPaused) && (someState != 0)) {
        setTimer(1);
    }

    updateCamera();
    updateAI(this);

    // Audio/event handling block
    if (((((pPlayerData != 0) &&
          ((*(uint *)(pPlayerData + 0x1d0) >> 0xb & 1) != 0)) &&
         (*(uint *)(pPlayerData + 0x1d0) &= 0xfffff7ff,
         pFollowTarget != 0)) &&
        ((pPlayerData = getSingleton(DAT_0112afb8), pPlayerData != 0 &&
         (int aiState = *(int *)(pPlayerData + 0x1c), aiState != 0)))) &&
       ((aiState != 0x3c &&
        (bPaused = isPlayerInVehicle(), f4 = DAT_00d5e288, bPaused == false)))) {

        float fStack_1c;
        Vector3 vAngle;

        getAngleToTarget(&vAngle, &fStack_1c); // gets relative angle/distance
        int followContext = *(int *)(pFollowTarget + 0x1f48);
        int stateValue = 0;
        if (followContext == 0) {
            stateValue = *(int *)(aiState + 0xe4);
        } else if (followContext == 1) {
            stateValue = *(int *)(aiState + 0xe0);
        } else if (followContext == 2) {
            stateValue = *(int *)(aiState + 0xe8);
        }

        fStack_1c = (f4 - DAT_00d5780c) - *(float *)(pPlayerData + 0x40);
        setAudioParameter(8);
        int zero = 0;
        int one = 1;
        float result = (float)atan2(stateValue, fStack_1c, 1, 0);
        applyAudioParameter(result, one, zero);

        // Play audio event if conditions met
        if (((someState != 0) &&
            (bPaused = isAudioBusy(), bPaused == false)) &&
           ((bPaused = checkGameState(*(int *)(pFollowTarget), 2), bPaused == false &&
            (bPaused = isSomethingEnabled(), bPaused != false)))) {
            int audioManager;
            if (**(int **)(DAT_012233a0 + 4) == 0) {
                audioManager = 0;
            } else {
                audioManager = **(int **)(DAT_012233a0 + 4) - 0x1f30;
            }
            int *vtable = (int *)getAudioManager(audioManager);
            (*(void (__thiscall **)(int, int, int, int))(vtable[0] + 0x28))(0x83f631c5, 0, -1, 0);
            int unknown = 0;
            int eventId = startAudioEvent(0, 0);
            setAudioVariable(0xf006f9c7, 0x4c, eventId, unknown);
            stopAudioEvent();
        }
    }
    return;
}
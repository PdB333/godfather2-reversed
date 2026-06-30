// FUNC_NAME: CharacterAimController::update
void CharacterAimController::update(float deltaTime) {
    // +0x2d4: pointer to animation update callback (virtual table with method at +0x0c)
    if (*(void**)(this + 0x2d4) != nullptr) {
        (*(void(__thiscall**)(void*, float))(*(int*)(this + 0x2d4) + 0x0c))(*(void**)(this + 0x2d4), deltaTime);
    }

    // +0x2d8: bitfield flags (bit2: enabled, bit7: smoothing toggle, bit0: trigger flag)
    // +0x214: state (0 = idle, 0x48 = maybe reload/cooldown)
    if (((*(uint32_t*)(this + 0x2d8) >> 2) & 1) == 0 || *(int*)(this + 0x214) == 0 || *(int*)(this + 0x214) == 0x48) {
        goto end;
    }

    // +0x161: boolean flag for timer usage
    // +0x528: timer (float countdown)
    if (*(char*)(this + 0x161) == 0) {
        *(float*)(this + 0x528) = 0.0f;
    } else {
        float timerValue = *(float*)(this + 0x528);
        if (timerValue > 0.0f) {
            timerValue -= deltaTime;
            *(float*)(this + 0x528) = timerValue;
            if (timerValue <= 0.0f) {
                // Timer expired - call a separate handler
                FUN_00701f40(); // probably "onTimerEnd" or start next phase
                *(float*)(this + 0x528) = 0.0f;
            }
        }
    }

    // Get global manager/input system
    int* globalMgr = (int*)FUN_007079a0(); // returns singleton pointer
    int currentPlayerId;
    if (globalMgr[0x1d3] == 0) {
        currentPlayerId = 0;
    } else {
        currentPlayerId = globalMgr[0x1d3] - 0x48; // adjust to get this object's ID
    }
    if (currentPlayerId != this) {
        goto end; // only update if this is the current player
    }

    // Delta time for this step
    float dTime = deltaTime;
    // +0x240: virtual method returning baseValue (e.g., from input)
    float baseValue = (*(float(__thiscall**)(int*))(globalMgr[0] + 0x240))(globalMgr);
    // Global constant (max smoothing factor)
    float maxSmooth = _DAT_00d5780c;

    // +0x23a >> 2 &1: flag for "underwater" or slow motion
    // FUN_006dfdb0: check if in state that overrides smoothing
    if (((globalMgr[0x23a] >> 2) & 1) != 0 && FUN_006dfdb0() != 0) {
        maxSmooth = *(float*)(this + 0x2f8); // custom smoothing factor
    }

    // +0x845: multiplier (e.g., sensitivity or speed)
    float acceleration = (float)globalMgr[0x845] * maxSmooth * dTime;
    // +0x244: set speed/value
    (*(void(__thiscall**)(int*, float))(globalMgr[0] + 0x244))(globalMgr, baseValue + acceleration);

    // Get current output value
    float currentValue = FUN_00702d70(); // get blended value

    // g_UseImmediateInput (bool at 0x0112aab0)
    if (DAT_0112aab0 != 0 && 
        ((globalMgr[0x23a] >> 2) & 1) == 0 || FUN_006dfdb0() == 0) {
        // Normal input smoothing path
        float inputMagnitude = FUN_0079eb40(0, 0); // returns 0..1 raw input magnitude
        if (inputMagnitude > 0.0f) {
            float clippedMagnitude = inputMagnitude;
            if (maxSmooth < inputMagnitude) {
                clippedMagnitude = maxSmooth;
            }
            // Subtract deadzone constant
            clippedMagnitude -= _DAT_00e516d4;
            if (clippedMagnitude <= _DAT_00d577a0) {
                // Smooth interpolation
                float mixerOut;
                FUN_00702bc0(&mixerOut, &clippedMagnitude, &acceleration);
                if (currentValue <= clippedMagnitude) {
                    // Clear bit7 (smoothing active flag)
                    *(uint32_t*)(this + 0x2d8) &= ~0x80;
                    float newValue = FUN_00702d70(); // re-read after clearing?
                    FUN_00702e90(currentValue - newValue);
                    // Restore base value
                    (*(void(__thiscall**)(int*))(globalMgr[0] + 0x240))(globalMgr);
                } else {
                    // Set bit7 – smoothing ongoing
                    *(uint32_t*)(this + 0x2d8) |= 0x80;
                }
            } else {
                // Large input (outside deadzone range)
                if ((*(uint32_t*)(this + 0x2d8) & 0x80) == 0) {
                    *(uint32_t*)(this + 0x2d8) |= 0x80;
                    float oldValue = FUN_00702d70();
                    FUN_00702e90(currentValue - oldValue);
                    float baseAfter = (*(float(__thiscall**)(int*))(globalMgr[0] + 0x240))(globalMgr);
                    float diff = baseAfter - baseValue;
                    if (diff < 0.0f) {
                        baseValue = 0.0f; // clamp? (unaff_ESI)
                        goto computeFinalBlend;
                    }
                }
                // else bit7 already set – skip to compute
computeFinalBlend:
                float blendFactor = (DAT_00e516d8 / (maxSmooth - _DAT_00e516d4)) * clippedMagnitude;
                if (blendFactor > 0.0f) {
                    if (maxSmooth < blendFactor) blendFactor = maxSmooth;
                } else {
                    blendFactor = 0.0f;
                }
                // Set acceleration again with blend
                (*(void(__thiscall**)(int*, float))(globalMgr[0] + 0x244))(globalMgr, baseValue);

                // Interpolate between two sets of parameters (offsets +0x31c,+0x320 and +0x30c,+0x310,+0x314,+0x318)
                float targetA = *(float*)(this + 0x320); // maybe desired yaw
                float currentA = *(float*)(this + 0x31c);
                float interpA = (targetA - currentA) * blendFactor + currentA;

                float targetB = *(float*)(this + 0x310);
                float currentB = *(float*)(this + 0x30c);
                float interpB = (targetB - currentB) * blendFactor + currentB;

                float targetC = *(float*)(this + 0x318);
                float currentC = *(float*)(this + 0x314);
                float interpC = (targetC - currentC) * blendFactor + currentC;

                float selected = interpC;
                if (interpA > currentValue) {
                    selected = interpB;
                }
                float scaledInput = selected * acceleration;
                bool isLessThanMax = interpA <= (scaledInput + currentValue);

                if (interpA <= currentValue) {
                    // Decrease case
                    if (!isLessThanMax) {
                        float diffVal = interpA - currentValue;
                        if (interpB < 0.0f && selected < 0.0f) {
                            interpC = (acceleration - diffVal / selected) * interpB;
                            goto applyFinal;
                        }
                    }
                } else {
                    // Increase case
                    if (isLessThanMax) {
                        float diffVal = interpA - currentValue;
                        if (interpC > 0.0f && selected > 0.0f) {
                            interpC = (acceleration - diffVal / selected) * interpC;
applyFinal:
                            float finalValue = interpC + (interpA - currentValue);
                            FUN_00702e90(finalValue);
                        }
                    }
                }
            }
        }
    }

    // Cooldown / rate-of-fire logic
    // +0x4f0: missile/attack count? +0x4f8: cooldown timer (ticks) +0x4f4: remaining shots
    // DAT_01205224: global frame count?
    if ((*(uint8_t*)(this + 0x2d8) & 1) != 0 && 
        *(int*)(this + 0x4f0) != 0 &&
        *(int*)(this + 0x4f8) == 0) {
        int* global2 = (int*)FUN_007079a0();
        if (*(uint32_t*)(this + 0x4f4) < (uint32_t)(DAT_01205224 - *(int*)(global2 + 0x1eb8))) {
            FUN_004df600(); // spawn projectile or attack
        }
    }

end:
    // Decrement cooldown timer if active
    if (*(int*)(this + 0x4f8) != 0) {
        *(int*)(this + 0x4f8) -= 1;
    }
}
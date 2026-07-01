// FUNC_NAME: AudioEnvironmentManager::updateTransition
// Address: 0x0085d290
// Role: Handles crossfade transition between two audio environments (e.g., interior/exterior).
// Updates per-channel gain values and master blend factor based on elapsed time and flags.

// Global state (likely static members of AudioEnvironmentManager or file-scope)
static float s_targetLeftDry;       // DAT_0112df98
static float s_targetLeftWet;       // DAT_0112df9c
static float s_targetRightDry;      // DAT_0112dfa0 (used as master blend target)
static float s_targetRightWet;      // DAT_0112dfa4? Not used directly, but pattern suggests
static float s_targetLeftDry2;      // DAT_0112dfa8 (second group left dry)
static float s_targetLeftWet2;      // DAT_0112dfac (second group left wet)
static float s_targetRightDry2;     // DAT_0112dfb0 (second group right dry)
static float s_fromLeftDry;         // DAT_0112df40
static float s_fromLeftWet;         // DAT_0112df44
static float s_fromRightDry;        // DAT_0112df48 (master blend from)
static float s_fromRightWet;        // DAT_0112df4c? Not used
static float s_fromLeftDry2;        // DAT_0112df50 (second group from left dry)
static float s_fromLeftWet2;        // DAT_0112df54 (second group from left wet)
static float s_volumeFactor;        // DAT_0112df58
static char s_transitionActive;     // DAT_0112df5c
static char s_transitionPending;    // DAT_0112df5d
static int s_transitionCounter;     // DAT_0112df60

// Constants (likely from config or other globals)
extern float g_thresholdEnter;      // DAT_00d75668
extern float g_thresholdExit;       // DAT_00d75664
extern float g_fadeRate;            // DAT_00d75660
extern float g_fadeSpeed;           // DAT_00d7566c
extern float g_timeOffset;          // DAT_00d75670
extern float g_minBlend;            // DAT_00d5780c
extern float g_floatConst;          // DAT_00e44578 (likely 0.0 or 1.0)
extern int g_someCounter;           // DAT_01205224

void __thiscall AudioEnvironmentManager::updateTransition(char lockFlag, char immediateFlag)
{
    float fVar1;
    char cVar2;
    int iVar3;
    int iVar4;
    uint uVar5;
    int *piVar6;
    uint uVar7;
    uint uVar8;
    float fVar9;
    float fVar10;
    float fVar11;
    float fVar12;
    float currentTime;

    // Get channel group object from this+4
    // +0x368: pointer to channel group
    iVar3 = *(int *)(*(int *)(this + 4) + 0x368);
    // uVar7 = total number of channels (from +0x20)
    uVar7 = (uint)*(char *)(iVar3 + 0x20);
    // uVar8 = dry channel count (difference between total and base at +0x98)
    uVar8 = uVar7 - (int)**(char **)(iVar3 + 0x98);
    piVar6 = (int *)0x0;
    currentTime = 0.0f;

    // If this+8 is non-zero and not 0x48, get the audio manager singleton
    if (((*(int *)(this + 8) != 0) && (*(int *)(this + 8) != 0x48)) &&
        (piVar6 = (int *)FUN_007ff880(), piVar6 != (int *)0x0))
    {
        // Call virtual function at vtable+0x1b0 to get current time
        fVar9 = (float)(**(code **)(*piVar6 + 0x1b0))();
        currentTime = (float)fVar9;
    }

    // If lockFlag is set, acquire mutex on the target data
    if ((lockFlag != '\0') && (piVar6 != (int *)0x0))
    {
        FUN_00875aa0(&DAT_0112df98); // likely EnterCriticalSection
    }

    fVar11 = g_minBlend; // store initial minBlend
    if (immediateFlag != '\0')
    {
        // Set target values directly from some other globals (DAT_0112df24 etc.)
        s_targetLeftDry = DAT_0112df24;
        s_targetRightDry = DAT_0112df2c;
        s_targetLeftDry2 = DAT_0112df34;
        s_targetRightDry2 = DAT_0112df3c;
    }

    // If volumeFactor is non-zero and we have a valid audio manager with a certain object
    if (((s_volumeFactor != 0.0f) && (piVar6 != (int *)0x0)) && (piVar6[0xd8] != 0))
    {
        iVar3 = *(int *)(piVar6[0xd8] + 0x1c); // get some object
        fVar10 = currentTime - g_timeOffset; // time since last update

        if ((lockFlag == '\0') || (fVar10 <= 0.0f))
        {
            // Normal fade (no immediate)
            fVar12 = s_volumeFactor;
            if ((g_someCounter < s_transitionCounter) &&
                ((iVar4 = piVar6[0x38f], iVar4 != 0 && (0.0f < fVar10))))
            {
                // Compute interpolated blend factor based on counter difference
                fVar12 = (float)(int)(s_transitionCounter - g_someCounter);
                if ((int)(s_transitionCounter - g_someCounter) < 0)
                {
                    fVar12 = fVar12 + g_floatConst;
                }
                fVar1 = (float)iVar4;
                if (iVar4 < 0)
                {
                    fVar1 = fVar1 + g_floatConst;
                }
                fVar1 = (fVar10 * g_fadeSpeed * fVar12) / fVar1;
                fVar12 = s_targetRightDry2;
                if (fVar1 < 1.0f)
                {
                    fVar12 = (s_targetRightDry2 - g_minBlend) * fVar1 + g_minBlend;
                }
                fVar12 = s_volumeFactor * fVar12;
            }
            // Write to object at offset 0x188 (likely volume/gain)
            *(float *)(iVar3 + 0x188) = fVar12;
        }
        else
        {
            // Immediate fade (lockFlag set and time > 0)
            fVar12 = s_targetRightDry2;
            if (fVar10 * g_fadeSpeed < g_minBlend)
            {
                fVar12 = (s_targetRightDry2 - g_minBlend) * fVar10 * g_fadeSpeed + g_minBlend;
            }
            *(float *)(iVar3 + 0x188) = s_volumeFactor * fVar12;
            s_transitionCounter = piVar6[0x38f] + g_someCounter;
        }
    }

    cVar2 = s_transitionActive;
    if ((lockFlag == '\0') && (immediateFlag == '\0'))
    {
        // No flags: check if transition is pending
        if (s_transitionPending != '\0')
        {
            if (s_transitionActive == '\0')
            {
                s_transitionActive = 1;
                s_transitionPending = cVar2;
                return;
            }
            goto LAB_0085d7fb; // handle active transition
        }
    }
    else
    {
        // Flags present: check if we should start a new transition
        if ((currentTime >= g_thresholdEnter) &&
            ((s_transitionPending == '\0' && (s_transitionActive == '\0'))))
        {
            // Start transition: fill dry channels with target values
            uVar5 = 0;
            if (3 < (int)uVar8)
            {
                iVar3 = 0;
                iVar4 = (uVar8 - 4 >> 2) + 1;
                uVar5 = iVar4 * 4;
                do
                {
                    // Write 8 floats per channel (4 pairs) with stride 0xa0 (160 bytes)
                    // Offsets: +0x10, +0xc, +0x38, +0x34, +0x60, +0x5c, +0x88, +0x84
                    *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x10 + iVar3) = s_targetLeftDry;
                    *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0xc + iVar3) = s_targetLeftDry2;
                    *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x38 + iVar3) = s_targetLeftDry;
                    *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x34 + iVar3) = s_targetLeftDry2;
                    *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x60 + iVar3) = s_targetLeftDry;
                    *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x5c + iVar3) = s_targetLeftDry2;
                    *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x88 + iVar3) = s_targetLeftDry;
                    *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x84 + iVar3) = s_targetLeftDry2;
                    iVar3 = iVar3 + 0xa0;
                    iVar4 = iVar4 + -1;
                } while (iVar4 != 0);
            }
            if (uVar5 < uVar8)
            {
                iVar3 = uVar5 * 0x28;
                iVar4 = uVar8 - uVar5;
                do
                {
                    // Write 2 floats per channel (stride 0x28)
                    *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x10 + iVar3) = s_targetLeftDry;
                    *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0xc + iVar3) = s_targetLeftDry2;
                    iVar3 = iVar3 + 0x28;
                    iVar4 = iVar4 + -1;
                } while (iVar4 != 0);
            }

            // Now fill wet channels (remaining channels) with wet target values
            if (3 < (int)(uVar7 - uVar8))
            {
                iVar3 = uVar8 * 0x28;
                iVar4 = ((uVar7 - uVar8) - 4 >> 2) + 1;
                uVar8 = uVar8 + iVar4 * 4;
                do
                {
                    *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x10 + iVar3) = s_targetLeftWet;
                    *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0xc + iVar3) = s_targetLeftWet2;
                    *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x38 + iVar3) = s_targetLeftWet;
                    *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x34 + iVar3) = s_targetLeftWet2;
                    *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x60 + iVar3) = s_targetLeftWet;
                    *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x5c + iVar3) = s_targetLeftWet2;
                    *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x88 + iVar3) = s_targetLeftWet;
                    *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x84 + iVar3) = s_targetLeftWet2;
                    iVar3 = iVar3 + 0xa0;
                    iVar4 = iVar4 + -1;
                } while (iVar4 != 0);
            }
            if (uVar8 < uVar7)
            {
                iVar3 = uVar8 * 0x28;
                iVar4 = uVar7 - uVar8;
                do
                {
                    *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x10 + iVar3) = s_targetLeftWet;
                    *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0xc + iVar3) = s_targetLeftWet2;
                    iVar3 = iVar3 + 0x28;
                    iVar4 = iVar4 + -1;
                } while (iVar4 != 0);
            }

            // Set master blend factor (at +0x38c + 0xc)
            *(float *)(*(int *)(*(int *)(this + 4) + 0x38c) + 0xc) = s_targetRightDry;
            s_transitionPending = 1;
            return;
        }

        // If no flags and time below threshold, go to check pending
        if (((lockFlag == '\0') && (immediateFlag == '\0')) || (currentTime < g_thresholdEnter))
            goto LAB_0085db36;
    }

    // If transition is not active, return
    if (s_transitionActive == '\0')
    {
        return;
    }

LAB_0085d7fb:
    // Transition is active: handle fade out or interpolation
    if (((lockFlag == '\0') && (immediateFlag == '\0')) || (currentTime <= g_thresholdExit))
    {
        // Time below exit threshold: deactivate transition
        s_transitionActive = '\0';
    }
    else if (s_transitionActive != '\0')
    {
        // Time above exit threshold: interpolate between from and target values
        fVar10 = (g_thresholdEnter - currentTime) * g_fadeRate;
        if (0.0f < fVar10)
        {
            if (fVar11 <= fVar10)
            {
                fVar10 = fVar11;
            }
        }
        else
        {
            fVar10 = 0.0f;
        }
        uVar5 = 0;
        fVar11 = fVar11 - fVar10; // remaining blend factor

        // Interpolate dry channels
        if (3 < (int)uVar8)
        {
            iVar3 = 0;
            iVar4 = (uVar8 - 4 >> 2) + 1;
            uVar5 = iVar4 * 4;
            do
            {
                *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x10 + iVar3) =
                    s_fromLeftDry * fVar10 + s_targetLeftDry * fVar11;
                *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0xc + iVar3) =
                    s_fromLeftDry2 * fVar10 + s_targetLeftDry2 * fVar11;
                // ... repeat for other pairs
                *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x38 + iVar3) =
                    s_fromLeftDry * fVar10 + s_targetLeftDry * fVar11;
                *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x34 + iVar3) =
                    s_fromLeftDry2 * fVar10 + s_targetLeftDry2 * fVar11;
                *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x60 + iVar3) =
                    s_fromLeftDry * fVar10 + s_targetLeftDry * fVar11;
                *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x5c + iVar3) =
                    s_fromLeftDry2 * fVar10 + s_targetLeftDry2 * fVar11;
                *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x88 + iVar3) =
                    s_fromLeftDry * fVar10 + s_targetLeftDry * fVar11;
                *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x84 + iVar3) =
                    s_fromLeftDry2 * fVar10 + s_targetLeftDry2 * fVar11;
                iVar3 = iVar3 + 0xa0;
                iVar4 = iVar4 + -1;
            } while (iVar4 != 0);
        }
        if (uVar5 < uVar8)
        {
            iVar3 = uVar5 * 0x28;
            iVar4 = uVar8 - uVar5;
            do
            {
                *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x10 + iVar3) =
                    s_fromLeftDry * fVar10 + s_targetLeftDry * fVar11;
                *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0xc + iVar3) =
                    s_fromLeftDry2 * fVar10 + s_targetLeftDry2 * fVar11;
                iVar3 = iVar3 + 0x28;
                iVar4 = iVar4 + -1;
            } while (iVar4 != 0);
        }

        // Interpolate wet channels
        if (3 < (int)(uVar7 - uVar8))
        {
            iVar3 = uVar8 * 0x28;
            iVar4 = ((uVar7 - uVar8) - 4 >> 2) + 1;
            uVar8 = uVar8 + iVar4 * 4;
            do
            {
                *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x10 + iVar3) =
                    s_fromLeftWet * fVar10 + s_targetLeftWet * fVar11;
                *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0xc + iVar3) =
                    s_fromLeftWet2 * fVar10 + s_targetLeftWet2 * fVar11;
                // ... repeat for other pairs
                *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x38 + iVar3) =
                    s_fromLeftWet * fVar10 + s_targetLeftWet * fVar11;
                *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x34 + iVar3) =
                    s_fromLeftWet2 * fVar10 + s_targetLeftWet2 * fVar11;
                *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x60 + iVar3) =
                    s_fromLeftWet * fVar10 + s_targetLeftWet * fVar11;
                *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x5c + iVar3) =
                    s_fromLeftWet2 * fVar10 + s_targetLeftWet2 * fVar11;
                *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x88 + iVar3) =
                    s_fromLeftWet * fVar10 + s_targetLeftWet * fVar11;
                *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x84 + iVar3) =
                    s_fromLeftWet2 * fVar10 + s_targetLeftWet2 * fVar11;
                iVar3 = iVar3 + 0xa0;
                iVar4 = iVar4 + -1;
            } while (iVar4 != 0);
        }
        if (uVar8 < uVar7)
        {
            iVar3 = uVar8 * 0x28;
            iVar4 = uVar7 - uVar8;
            do
            {
                *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x10 + iVar3) =
                    s_fromLeftWet * fVar10 + s_targetLeftWet * fVar11;
                *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0xc + iVar3) =
                    s_fromLeftWet2 * fVar10 + s_targetLeftWet2 * fVar11;
                iVar3 = iVar3 + 0x28;
                iVar4 = iVar4 + -1;
            } while (iVar4 != 0);
        }

        // Update master blend factor
        *(float *)(*(int *)(*(int *)(this + 4) + 0x38c) + 0xc) =
            s_fromRightDry * s_targetRightDry * fVar11 * fVar10;
        return;
    }

    // If transition active but time not above exit threshold, just set from values (no interpolation)
    uVar5 = 0;
    if (3 < (int)uVar8)
    {
        iVar3 = 0;
        iVar4 = (uVar8 - 4 >> 2) + 1;
        uVar5 = iVar4 * 4;
        do
        {
            *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x10 + iVar3) = s_fromLeftDry;
            *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0xc + iVar3) = s_fromLeftDry2;
            // ... repeat for other pairs
            *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x38 + iVar3) = s_fromLeftDry;
            *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x34 + iVar3) = s_fromLeftDry2;
            *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x60 + iVar3) = s_fromLeftDry;
            *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x5c + iVar3) = s_fromLeftDry2;
            *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x88 + iVar3) = s_fromLeftDry;
            *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x84 + iVar3) = s_fromLeftDry2;
            iVar3 = iVar3 + 0xa0;
            iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
    }
    if (uVar5 < uVar8)
    {
        iVar3 = uVar5 * 0x28;
        iVar4 = uVar8 - uVar5;
        do
        {
            *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x10 + iVar3) = s_fromLeftDry;
            *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0xc + iVar3) = s_fromLeftDry2;
            iVar3 = iVar3 + 0x28;
            iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
    }

    // Wet channels
    if (3 < (int)(uVar7 - uVar8))
    {
        iVar3 = uVar8 * 0x28;
        iVar4 = ((uVar7 - uVar8) - 4 >> 2) + 1;
        uVar8 = uVar8 + iVar4 * 4;
        do
        {
            *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x10 + iVar3) = s_fromLeftWet;
            *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0xc + iVar3) = s_fromLeftWet2;
            // ... repeat
            *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x38 + iVar3) = s_fromLeftWet;
            *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x34 + iVar3) = s_fromLeftWet2;
            *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x60 + iVar3) = s_fromLeftWet;
            *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x5c + iVar3) = s_fromLeftWet2;
            *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x88 + iVar3) = s_fromLeftWet;
            *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x84 + iVar3) = s_fromLeftWet2;
            iVar3 = iVar3 + 0xa0;
            iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
    }
    if (uVar8 < uVar7)
    {
        iVar3 = uVar8 * 0x28;
        iVar4 = uVar7 - uVar8;
        do
        {
            *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0x10 + iVar3) = s_fromLeftWet;
            *(float *)(*(int *)(*(int *)(*(int *)(this + 4) + 0x368) + 0x8c) + 0xc + iVar3) = s_fromLeftWet2;
            iVar3 = iVar3 + 0x28;
            iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
    }

    // Set master blend factor to from value
    *(float *)(*(int *)(*(int *)(this + 4) + 0x38c) + 0xc) = s_fromRightDry;
    return;
}
// FUNC_NAME: PlayerActionableTargetSM::processAction

undefined __thiscall PlayerActionableTargetSM::processAction(int thisPtr, int *actionOptions, float actionDuration)
{
    float fVar1;
    int iVar2;
    int *piVar3;
    char cVar4;
    int iVar5;
    int uVar6;
    int iVar7;
    int *piVar8;
    float10 fVar9;
    undefined1 retVal;
    int local_8;

    // Convert float duration to integer count
    iVar7 = (int)actionDuration;
    piVar3 = actionOptions;
    retVal = 0;

    // Navigate component chain: this->someComponent (offset +4) gives base offset of another object
    if (*(int *)(thisPtr + 4) == 0) {
        iVar5 = 0;
    }
    else {
        iVar5 = *(int *)(thisPtr + 4) + -0x48;  // +0x48 is size of something?
    }

    // Further navigation: component+0x200c points to sub-component, subtract 0x3c to get base
    if (*(int *)(iVar5 + 0x200c) == 0) {
        local_8 = 0;
    }
    else {
        local_8 = *(int *)(iVar5 + 0x200c) + -0x3c;  // +0x3c offset adjustment
    }

    // Check if action can begin
    cVar4 = canBeginAction(actionOptions, actionDuration);
    if (cVar4 != '\0') {
        actionDuration = *(float *)(local_8 + 0x44);   // Override duration from component field

        // Re-navigate to same sub-component (redundant but for safety)
        if (*(int *)(thisPtr + 4) == 0) {
            iVar5 = 0;
        }
        else {
            iVar5 = *(int *)(thisPtr + 4) + -0x48;
        }
        if (*(int *)(iVar5 + 0x200c) == 0) {
            iVar5 = 0;
        }
        else {
            iVar5 = *(int *)(iVar5 + 0x200c) + -0x3c;
        }

        // If state is 1-5 and special condition, override with another duration
        if ((*(int *)(iVar5 + 0x50) - 1U < 5) && (cVar4 = isSpecialState(actionOptions), cVar4 != '\0')) {
            actionDuration = *(float *)(local_8 + 0x48);  // +0x48 alternate duration
        }

        fVar1 = (float)iVar7;
        if (iVar7 < 0) {
            fVar1 = fVar1 + 0.5f;   // Round to nearest int (DAT_00e44578)
        }

        // Check actionOptions for valid actionType (offset 0x7b6 = 1974 dwords)
        if (((actionOptions != (int *)0x0) && (actionOptions[0x7b6] != 0)) && (actionOptions[0x7b6] != 0x48)) {
            if (*(int *)(local_8 + 0x50) == 9) {
                uVar6 = 5;       // Sound ID for state 9
            }
            else if (*(int *)(local_8 + 0x50) == 10) {
                uVar6 = 10;      // Sound ID for state 10
            }
            else {
                uVar6 = 9;       // Default sound ID
            }
            playSound(fVar1 * actionDuration, uVar6);  // Volume & sound ID
        }

        // Re-navigate again (common pattern)
        if (*(int *)(thisPtr + 4) == 0) {
            iVar5 = 0;
        }
        else {
            iVar5 = *(int *)(thisPtr + 4) + -0x48;
        }
        if (*(int *)(iVar5 + 0x200c) == 0) {
            iVar5 = 0;
        }
        else {
            iVar5 = *(int *)(iVar5 + 0x200c) + -0x3c;
        }

        // If state is 1-5, handle animation completion or start
        if (*(int *)(iVar5 + 0x50) - 1U < 5) {
            uVar6 = *(int *)(&DAT_00e517b8 + *(int *)(local_8 + 0x50) * 8);  // Lookup table for state
            cVar4 = checkAnimationCompletion(uVar6, *(undefined4 *)(local_8 + 0x4c));
            if (cVar4 == '\0') {
                iVar7 = updateAnimation(local_8 + 0x54, 0, 0, 0, 0);
                if (iVar7 == 0) {
                    return 0;
                }
                setAnimationState(*(undefined4 *)(local_8 + 0x4c));  // Trigger next animation
                if (*(int *)(local_8 + 0x4c) == 2) {
                    playSoundEffect(0xc5a3127d);   // Sound hash for state=2
                }
                uVar6 = getCurrentTime();
                cVar4 = isAnimationPaused(iVar7);
                if (cVar4 == '\0') {
                    pauseAnimation(iVar7, 1);   // Pause animation
                    showCharacter(0);          // Hide? 
                }
                stopTimer(uVar6);
                enablePhysics(1);               // Enable physics
                (**(code **)(*actionOptions + 0x248))(iVar7); // Perform action via vtable
                enablePhysics(0);               // Disable physics
                if (*(int *)(local_8 + 0x4c) != 0) {
                    playSoundEffect(0x3a04a052);
                }
                cameraShake(0x3d);              // Shake camera
            }
            else {
                iVar7 = getAnimationClip(uVar6);
                if (iVar7 == 0) {
                    return 0;
                }
                uVar6 = getCurrentTime();
                iVar5 = getAnimationStartTime();
                setAnimationElapsedTime(uVar6 - iVar5);  // Advance animation by elapsed time
            }
        }
        else {
            // States 6,7,8,9 (and maybe 10 via switch)
            switch(*(undefined4 *)(local_8 + 0x50)) {
            default:
                goto switchD_007203eb_caseD_0;
            case 6:
            case 7:
            case 8:
            case 9:
                if (iVar7 != 0) {   // Loop as many times as initial count
                    do {
                        if (*(int *)(local_8 + 0x50) == 9) {
                            playSoundEffect(0xdfa0bd45);
                        }
                        iVar5 = updateAnimation(local_8 + 0x54, 0, 0, 0, 0);
                        cVar4 = isAnimationPaused(iVar5);
                        if (cVar4 == '\0') {
                            pauseAnimation(iVar5, 1);
                            showCharacter(0);
                        }
                        updateGlobalState(DAT_01130fa0);  // Global state update
                        piVar8 = (int *)getPlayerComponent();  // Get player controller/component
                        if (((piVar8 != (int *)0x0) && (iVar5 != 0)) &&
                           ((*(int *)(local_8 + 0x50) == 9 && (*(char *)(iVar5 + 0x1ad) == '\x1d')))) {
                            // State 9 and specific animation flag
                            fVar9 = (float10)(**(code **)(*piVar8 + 0xc4))();  // Get position X
                            fVar1 = (float)fVar9;
                            fVar9 = (float10)(**(code **)(*piVar8 + 0xc0))();  // Get position Y
                            if (fVar9 < (float10)fVar1) {
                                iVar2 = *(int *)(iVar5 + 0x294);  // Some offset from animation data
                                fVar9 = (float10)(**(code **)(*piVar8 + 0xc0))();
                                fVar9 = fVar9 + (float10)iVar2;
                                actionOptions = (int *)(float)fVar9;
                                if ((float10)fVar1 < fVar9) {
                                    actionOptions = (int *)fVar1;
                                }
                                piVar8 = (int *)getTargetComponent(piVar8);
                                (**(code **)(*piVar8 + 0x3c))(actionOptions);  // Set target position
                            }
                        }
                        (**(code **)(*piVar3 + 0x300))(iVar5, 0);  // Apply animation to model
                        iVar7 = iVar7 + -1;   // Decrement loop count
                    } while (iVar7 != 0);
                }
            }
        }
        // Mark a flag in this object
        *(uint *)(thisPtr + 0x20) = *(uint *)(thisPtr + 0x20) | 4;
        retVal = 1;
    }
switchD_007203eb_caseD_0:
    return retVal;
}
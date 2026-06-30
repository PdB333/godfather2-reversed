// FUNC_NAME: AnimationController::advanceTime
// Address: 0x0051abd0
// Animates blending slots, handles state transitions, and manages animation playback.

void AnimationController::advanceTime(float deltaTime)
{
    uint32 flags = *(uint32*)(this + 0x0C);
    g_currentAnimation = this; // DAT_01205518

    // If flagged to stop and not paused, stop immediately
    if (((flags & 0x100000) != 0) && ((flags & 0x80000) == 0)) {
        stopAnimation(); // FUN_0051b120
        g_currentAnimation = 0;
        return;
    }

    // Check if animation is allowed to proceed based on some global flag and a counter
    if (((*(byte*)(*(int*)(this + 0x10) + 0x14) & 4) == 0) && (0x1d < *(short*)(this + 0x82))) {
        if ((flags & 1) == 0) {
            *(uint32*)(this + 0x0C) = flags | 0x210000;
            g_currentAnimation = 0;
            return;
        }
        if ((flags & 0x40000) == 0) {
            pauseAnimation(); // FUN_0051b1f0
        }
    }

    // If animation should be stopped due to priority condition
    if (((((*(byte*)(*(int*)(this + 0x10) + 0x14) & 4) == 0) &&
         ((*(uint32*)(this + 0x0C) & 0x80000) == 0)) &&
        ((int)*(uint32*)(this + 0x0C) < 0)) &&
       (0x1d < *(short*)(this + 0x82))) {
        g_currentAnimation = 0;
        return;
    }

    // Increment priority counter if within range and global flag is clear
    if ((*(short*)(this + 0x82) < 0x1e) && (g_someGlobalByte == '\0')) {
        *(short*)(this + 0x82) = *(short*)(this + 0x82) + 1;
    }

    // Reset global debug/state variables
    g_debugVar0 = 0;
    g_debugVar1 = 0;
    g_debugVar2 = 0;
    g_debugVar3 = g_someGlobalFloat; // DAT_00e2b1a4

    float newTime = *(float*)(this + 0x7C) + deltaTime;

    // If not stopped and has a callback pointer, call it
    if (((*(uint32*)(this + 0x0C) & 0x100000) == 0) && (*(int*)(this + 0xB0) != 0)) {
        (**(code**)(this + 0x78))(); // function pointer call
    }

    if ((*(uint32*)(this + 0x0C) & 0x10000) == 0) {
        bool anyActive = true; // bVar6
        if ((*(uint32*)(this + 0x0C) & 0x10000000) != 0) {
            clearSomeFlag(); // FUN_0051bc10
            *(uint32*)(this + 0x0C) &= 0xefffffff;
        }

        // Handle blended transform from a target if flagged
        if ((*(uint32*)(this + 0x0C) & 0x800000) != 0) {
            // Prepare blend source (possibly root transform)
            undefined4 blendSource[4]; // uStack_20
            if (*(int*)(this + 0xBC) == 0) {
                blendSource[0] = *(undefined4*)(this + 0x60);
                blendSource[1] = *(undefined4*)(this + 0x64);
                blendSource[2] = *(undefined4*)(this + 0x68);
                blendSource[3] = *(undefined4*)(this + 0x6C);
            } else {
                // Compute transform from motion
                computeBlendTransform(this + 0x30, *(int*)(this + 0xBC), blendSource); // FUN_0056b420
            }
            applyBlendTransform(); // FUN_004f39e0
        }

        short slotCount = *(short*)(this + 0x80);
        int slotIndex = 0;
        int sharedDataOffset = 0; // iStack_2c
        // Each slot has a 5-int struct starting at this+0xF4; shared block at this+0x10 has stride 0x24
        int* slot = (int*)(this + 0xF4); // piVar10
        while (slotIndex < slotCount) {
            g_currentSlotIndex = slotIndex; // DAT_01194a80

            if (slot[2] == 0) {
                // No animation assigned, mark as unused
                slot[-1] |= 0x10000000;
                slot[3] = 0;
            } else {
                int sharedBase = *(int*)(this + 0x10);
                // Determine if this slot can be activated based on blend weights
                if ((*slot != 0) || ((slot[-1] & 0x4000000U) == 0) ||
                    (((*(byte*)(sharedBase + 0x14) & 0x20) == 0 &&
                      ((((slot[-1] & 0x40000000U) == 0) ||
                        (*(float*)(this + 0x8C) < *(float*)(sharedBase + 0x48 + sharedDataOffset) ||
                         *(float*)(this + 0x8C) == *(float*)(sharedBase + 0x48 + sharedDataOffset))) ||
                       *(float*)(sharedBase + 0x50 + sharedDataOffset) <= *(float*)(this + 0x8C))))) {
                    // No special condition: check if animation has ended
                    float animEndTime = *(float*)(sharedBase + 0x34 + sharedDataOffset);
                    if ((newTime <= animEndTime) || (animEndTime < *(float*)(this + 0x7C))) {
                        goto LAB_0051ade6;
                    }
LAB_0051ae43:
                    bool shouldActivate = true; // bVar5
                } else {
                    float animEndTime = *(float*)(sharedBase + 0x34 + sharedDataOffset);
                    if (animEndTime <= newTime && newTime != animEndTime) {
                        goto LAB_0051ae43;
                    }
LAB_0051ade6:
                    bool shouldActivate = false;
                }

                uint32 slotFlags = slot[-1];
                uint* slotFlagsPtr = (uint*)(slot - 1);
                if (((slotFlags & 0x8000000) == 0) && shouldActivate) {
                    if (*slot == 0) {
                        // Need to create animation instance
                        if ((*(short*)(this + 0x82) < 0x1e) ||
                            ((*(uint32*)(sharedBase + 0x38 + sharedDataOffset) & 0x100) != 0)) {
                            // Priority or special flag allows creation
                            float blendWeight = *(float*)(this + 0x8C);
                            if ((blendWeight < *(float*)(sharedBase + 0x48 + sharedDataOffset) || blendWeight == *(float*)(sharedBase + 0x48 + sharedDataOffset)) ||
                                (*(float*)(sharedBase + 0x50 + sharedDataOffset) <= blendWeight)) {
                                *slotFlagsPtr = slotFlags | 0x64000000;
                            } else {
                                int* newAnim = createAnimationInstance(this, slotFlagsPtr, slotIndex); // FUN_00533e70
                                *slot = (int)newAnim;
                                if (newAnim != 0) {
                                    *slotFlagsPtr &= 0x9bffffff;
                                    (**(code**)(*newAnim + 0x40))(*(undefined4*)(this + 0xAC)); // initialize with channel
                                }
                            }
                        } else {
                            *slotFlagsPtr = slotFlags | 0x24000000;
                        }
                    } else {
                        // Update existing animation
                        (**(code**)(*(int*)*slot + 0x20))();
                    }
                    *slotFlagsPtr &= 0xefffffff;
                    slot[3] = 0;
LAB_0051aeb2:
                    int* currentAnim = (int*)*slot;
                    if ((currentAnim != 0) && ((anyActive = false, g_animationDeltaThreshold <= deltaTime))) {
                        updateAnimationTiming(); // FUN_00533fb0
                        (**(code**)(*currentAnim + 0x18))(deltaTime); // tick animation
                    }
                } else if (*slot != 0) {
                    // Animation exists but shouldn't be active
                    if ((*(short*)(this + 0x82) < 0x1e) ||
                        ((*(uint32*)(sharedBase + 0x38 + sharedDataOffset) & 0x100) != 0)) {
                        // Check if animation can be stopped with fade
                        if (((*(byte*)(*(int*)(**(int**)(UNUSED + 0x2C) + 8) + *(int*)(*slot + 0x10)) & 1) != 0) &&
                            ((((*(uint32*)(this + 0x0C) & 0x80000000) == 0 ||
                              ((*(uint32*)(sharedBase + 0x38 + *(int*)(this + 0x10)) & 0x200) != 0)) &&
                             (slot[3] == 0)))) {
                            slot[3] = 3; // fade count
                        }
                        if ((slot[3] < 1) || (int fadeCount = slot[3] - 1, slot[3] = fadeCount, 0 < fadeCount)) {
                            goto LAB_0051aeb2;
                        }
                        slotFlags = slotFlags | 0x10000000;
                    } else {
                        slotFlags = slotFlags | 0x34000000;
                    }
                    *slotFlagsPtr = slotFlags;
                    cleanupAnimation(); // FUN_005343f0
                    *slot = 0;
                }
            }

            slotIndex++;
            sharedDataOffset += 0x24; // stride of shared animation data
            slot += 5; // stride of slot struct (5 ints)
        }

        if (!anyActive) goto LAB_0051af64;

        // Check if all slots have finished playing
        short finalSlotCount = *(short*)(this + 0x80);
        if ((finalSlotCount != 0) && (newTime <= *(float*)(*(int*)(this + 0x10) + 0x34))) {
            anyActive = false;
        }

        // Mark as finished if no active slots and conditions met
        uint32 currentFlags = *(uint32*)(this + 0x0C);
        if ((((-1 < (int)currentFlags) && (anyActive)) &&
            ((*(uint32*)(this + 0x0C) = currentFlags | 0x10000, (currentFlags & 1) == 0 || ((currentFlags & 0x20000) != 0)))) &&
           (*(float*)(*(int*)(this + 0x10) + 0x18) <= 0.0)) {
            *(uint32*)(this + 0x0C) = currentFlags | 0x210000;
        }
    }

LAB_0051af64:
    *(float*)(this + 0x7C) = newTime;

    // Reset if animation has exceeded max time and looping is allowed
    if ((g_animationDeltaThreshold < *(float*)(*(int*)(this + 0x10) + 0x18)) &&
       (*(float*)(this + 0xE0) <= newTime && newTime != *(float*)(this + 0xE0))) {
        if (((*(byte*)(*(int*)(this + 0x10) + 0x14) & 2) == 0) ||
           ((*(uint32*)(this + 0x0C) & 0x80000) != 0)) {
            if ((*(uint32*)(this + 0x0C) & 0x10000) == 0) {
                stopAnimation(); // FUN_0051b120
            } else {
                *(uint32*)(this + 0x0C) |= 0x200000;
            }
        } else {
            transitionToNextAnimation(this); // FUN_0051b0b0
        }
    }

    // Restore global debug/state
    g_debugVar3 = g_someGlobalFloat;
    g_debugVar0 = 0;
    g_debugVar1 = 0;
    g_debugVar2 = 0;
    g_currentAnimation = 0;
    return;
}
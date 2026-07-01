// FUNC_NAME: PlayerSM::clearStateAndReset
void __fastcall PlayerSM::clearStateAndReset(int this)
{
    int *piVar1;
    char cVar2;
    int *piVar3;
    uint uVar4;
    int iVar5;
    int *piVar6;
    
    // Clear pending sound stops at +0x20e (sound slot 0xc) and +0x20d (slot 0xb)
    if (*(char *)(this + 0x20e) != '\0') {
        playSound(0xc);
        *(char *)(this + 0x20e) = 0;
    }
    if (*(char *)(this + 0x20d) != '\0') {
        playSound(0xb);
        *(char *)(this + 0x20d) = 0;
    }
    
    // Global update call
    updateGlobalState();
    
    // If bit 22 of state flags (+0x1d0) is set, call some function
    if ((*(uint *)(this + 0x1d0) >> 0x16 & 1) != 0) {
        handleActionFlag22();
    }
    
    piVar1 = *(int **)(this + 0x58); // Pointer to main state object
    
    // Stop sounds for actions 0x30, 0x32, 0x3c
    stopSound(0x30);
    stopSound(0x32);
    stopSound(0x3c);
    
    // Clear bit 11 (0x400) of flag at piVar1+0x928 (offset 0x24A0)
    piVar1[0x928] = piVar1[0x928] & 0xfffff7ff;
    // Set byte flag at piVar1+0x288 (first byte of that int)
    *(char *)(piVar1 + 0x288) = 1;
    // Set some global value
    piVar1[0x215] = externalGlobal_Var1;
    
    // Additional sound/state resets
    setAudioLobby(1);
    resetActiveAnimation();
    resetActionTimers(0);
    
    // Clear bit 11 in two flags (probably left/right weapon flags)
    piVar1[0x25c] = piVar1[0x25c] & 0xfffff7ff;
    piVar1[0x25d] = piVar1[0x25d] & 0xfffff7ff;
    
    // If both flags have bit 4 clear, call some function
    if ((((uint)piVar1[0x25c] >> 4 & 1) == 0) || (((uint)piVar1[0x25d] >> 4 & 1) == 0)) {
        resetWeaponState(1);
    }
    
    // Global check
    if (globalFlag_ResetNeeded != 0) {
        resetGlobalSystem();
    }
    
    piVar3 = (int *)getAnimPlayer(); // Singleton
    (**(code **)(*piVar3 + 4))(0x100); // Play animation 0x100
    
    // If bit 8 of state flags is set, handle a special action
    if ((*(uint *)(this + 0x1d0) >> 8 & 1) != 0) {
        callDebugPrint(globalDataPtr);
        resetCamera(0);
        *(uint *)(this + 0x1d0) = *(uint *)(this + 0x1d0) & 0xfffffeff; // Clear bit 8
    }
    
    piVar3 = (int *)getAnimPlayer();
    (**(code **)(*piVar3 + 4))(0x1bf); // Play animation 0x1bf
    
    // Check if action in progress (+0x80)
    if (*(char *)(this + 0x80) != '\0') {
        // Branch based on bit 4 of state flags
        if ((*(uint *)(this + 0x1d0) >> 4 & 1) == 0) {
            // Bit 4 not set: check if can continue action
            if (((*(int *)(this + 0x1c0) == 0) ||
                (uVar4 = *(uint *)(*(int *)(this + 0x1a0) * 0x2c +
                                   *(int *)(*(int *)(*(int *)(this + 0x1c0) + 0x10) + 4) + 0x24) & 0x3000,
                uVar4 == 0x3000)) || (uVar4 == 0x2000))
                goto LAB_007cd7c7; // Skip the virtual call
        } else {
            // Bit 4 set: check if a different condition holds
            if (((*(int **)(this + 0x1c0) != (int *)0x0) &&
                 (cVar2 = (**(code **)(**(int **)(this + 0x1c0) + 0x14))(), cVar2 != '\0')) &&
                ((uVar4 = *(uint *)(*(int *)(this + 0x1a0) * 0x2c +
                                    *(int *)(*(int *)(*(int *)(this + 0x1c0) + 0x10) + 4) + 0x24) & 0x600,
                uVar4 == 0x600 || (uVar4 == 0x400))))
                goto LAB_007cd7c7;
        }
        // If not skipped, call virtual function on main state object
        (**(code **)(*piVar1 + 0x27c))();
    }
    
LAB_007cd7c7:
    // Reset action camera
    resetActionCamera(0);
    
    piVar3 = (int *)(this + 0x1b4);
    // Check pointer at +0x1b4
    if ((*(int *)(this + 0x1b4) == 0) || (*(int *)(this + 0x1b4) == 0x48)) {
        *(uint *)(this + 0x1d0) = *(uint *)(this + 0x1d0) | 0x40; // Set bit 6
    } else {
        // Derive container object from the pointer (offset -0x48)
        if (*piVar3 == 0) {
            piVar6 = (int *)0x0;
        } else {
            piVar6 = (int *)(*piVar3 - 0x48);
        }
        handleStateTransition(); // +0xCB610
        
        // Clear bit 14 and stop sound 0x48 if set
        if ((*(uint *)(this + 0x1d0) >> 0xe & 1) != 0) {
            stopSound(0x48);
            *(uint *)(this + 0x1d0) = *(uint *)(this + 0x1d0) & 0xffffbfff;
        }
        // Clear bit 15 and call debug/camera if set
        if ((*(uint *)(this + 0x1d0) >> 0xf & 1) != 0) {
            if (piVar6 != (int *)0x0) {
                callDebugPrint(globalDataPtr);
            }
            resetCamera(0);
            *(uint *)(this + 0x1d0) = *(uint *)(this + 0x1d0) & 0xffff7fff;
        }
        // If bit 0 of byte at +0x1d2 is set, clear bit 2 in piVar6's flag and clear bit 16 in state
        if ((*(char *)(this + 0x1d2) & 1) != 0) {
            piVar6[0x208] = piVar6[0x208] & 0xfffffffb;
            *(uint *)(this + 0x1d0) = *(uint *)(this + 0x1d0) & 0xfffeffff;
        }
        // If there is an action object, call function on it
        if (*(int *)(this + 0x1c0) != 0) {
            handleActionObject(0);
        }
        
        cVar2 = checkTransitionCondition(piVar6, 2);
        if (cVar2 != '\0') {
            // Check bit 8 of piVar6+0x7e6 (offset 0x1F98)
            if ((((uint)piVar6[0x7e6] >> 8 & 1) == 0) &&
                (cVar2 = (**(code **)(*piVar6 + 0x1bc))(), cVar2 == '\0')) {
                // If state is 1 or 0, call function A
                if ((piVar6[0x841] == 1) || (piVar6[0x841] == 0)) {
                    handleTransitionCaseA();
                }
            } else {
                // Otherwise call function B with state index
                handleTransitionCaseB(piVar6[0x841], 0);
            }
        }
        
        // Additional state reset calls
        finishTransition();
        *(int *)(this + 0x1bc) = 0;
        resetAimingState();
        
        cVar2 = checkDisableFlag(0);
        if (cVar2 == '\0') {
            *(uint *)(this + 0x1d0) = *(uint *)(this + 0x1d0) & 0xffffffbf; // Clear bit 6
        } else {
            *(uint *)(this + 0x1d0) = *(uint *)(this + 0x1d0) | 0x40; // Set bit 6
        }
        
        // If bit 0 or bit 2 of state is set and a condition holds, call a function
        if ((((char)(*(uint *)(this + 0x1d0)) & 1) != 0) || ((*(uint *)(this + 0x1d0) >> 2 & 1) != 0)) {
            if (checkActionActive() != 0) {
                playFoleySound(0x10, 0);
            }
        }
        
        // Free the pointer at +0x1b4 if present
        if (*piVar3 != 0) {
            freeStateMemory(piVar3);
            *piVar3 = 0;
        }
        
        // Call function on piVar6 buffer
        handleBufferUpdate(piVar6 + 0x7f6);
        
        cVar2 = checkGlobalCondition();
        if (cVar2 == '\0') {
            piVar6[0x129] = piVar6[0x129] & 0xfffffffe; // Clear bit 0
        }
        
        // Set a global value in piVar1
        piVar1[0x7ad] = externalGlobal_Var2;
    }
    
    // Update global debug state
    iVar5 = debugStatePtr;
    if (*(char *)(debugStatePtr + 0x24) != '\0') {
        *(int *)(debugStatePtr + 0x40) = 0;
        *(int *)(debugStatePtr + 0x2c) = debugResetValue;
        *(int *)(debugStatePtr + 0x28) = 1;
        *(char *)(debugStatePtr + 0x25) = 0;
    }
    
    // If pointer at +0x1b0 is non-null, call exit function
    if (*(int *)(this + 0x1b0) != 0) {
        exitState(1);
    }
    
    // Free object at +0x1c8 if present
    if (*(int *)(this + 0x1c8) != 0) {
        freeActionObject(*(int *)(this + 0x1c8));
        *(int *)(this + 0x1c8) = 0;
    }
    
    cVar2 = checkNetworkSync();
    if ((cVar2 != '\0') && (cVar2 = checkGlobalCondition(), cVar2 == '\0')) {
        syncNetworkState();
    }
    
    // If bit 3 of state flags is set, stop animations via AnimPlayer
    if ((*(uint *)(this + 0x1d0) >> 3 & 1) != 0) {
        piVar3 = (int *)getAnimPlayer();
        (**(code **)(*piVar3 + 4))(8);
        (**(code **)(*piVar3 + 4))(2);
        (**(code **)(*piVar3 + 4))(0x20);
        *(uint *)(this + 0x1d0) = *(uint *)(this + 0x1d0) & 0xfffffff7; // Clear bit 3
    }
    
    // Clear multiple flags in state
    *(uint *)(this + 0x1d0) = *(uint *)(this + 0x1d0) & 0xff7ff9de;
    // Reset action and state variables
    *(int *)(this + 0x1c0) = 0;
    *(short *)(this + 0x1d6) = 0;
    
    // Additional cleanup calls
    cleanupActionState();
    finalizeStateReset();
    
    // Free memory at piVar1+0x71e if allocated
    if (piVar1[0x71e] != 0) {
        freeStateMemory(piVar1 + 0x71e);
        piVar1[0x71e] = 0;
    }
    
    return;
}
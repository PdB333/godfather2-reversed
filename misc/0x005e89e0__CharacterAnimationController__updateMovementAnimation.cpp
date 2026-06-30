// FUNC_NAME: CharacterAnimationController::updateMovementAnimation
void CharacterAnimationController::updateMovementAnimation(float ebx_arg) {
    // this = unaff_EDI
    int *vtable = (int*)DAT_01223510; // pointer to vtable base

    // +0x1c8 seems to be an animation handle/ID (float interpreted as int or handle)
    float animHandle = *(float*)(this + 0x1c8);
    if (*(int*)(this + 0x484) == 0) { // state check
        return;
    }
    if ((int)animHandle < 0) {
        return;
    }

    // vtable[0x94] - probably isAnimationValid(handle, &someCount)
    char valid = ((char(*)(float, int*))vtable[0x94])(animHandle, (int*)(this + 0x500));
    if (valid == 0) {
        return;
    }

    if (*(int*)(this + 0x500) < 1) {
        if (*(int*)(this + 0x484) == 3) { // state 3: maybe idle or not moving
            FUN_005e9520(); // reset animation state
        }
        return;
    }

    float fStack_1c = *(float*)(this + 0x25c); // some time or duration
    int local_18 = 0; // used as output for direction/vector

    if (*(char*)(this + 0x239) == 0) {
        // Branch A: No special direction override
        ((void(*)(float, int))vtable[0x78])(animHandle, 0); // setDirection? or stop?
        float vec[3] = {0.0f, 0.0f, 0.0f}; // local variables reconstructed
        // note: afStack_c is a 3-element array, fStack_10 and fStack_14 are also floats
        // The decompiler shows afStack_c[0], fStack_10, fStack_14 are used.
        // Actually afStack_c is [0]= afStack_c[0], fStack_10, fStack_14 are separate but likely part of a vector.
        // Let's assume a 3D vector: afStack_c[0] is x, fStack_14 is y? Wait from code:
        // afStack_c[0] = 0.0;
        // fStack_10 = 0.0;
        // Then call: FUN_005dcb60(...)
        // After call: unaff_EBX = afStack_c[0] * unaff_EBX; fStack_1c = fStack_10 * fStack_1c;
        // So the vector is {afStack_c[0], fStack_10, ?}, but fStack_14 is not used? Actually fStack_14 is not set in this branch.
        // Possibly a 2D vector in {afStack_c[0], fStack_10} and fStack_14 is unused.
        float dirX = 0.0f;
        float dirY = 0.0f;
        // call to get direction from manager
        char result = FUN_005dcb60(DAT_01223508, *(int*)(this + 0x24c));
        if (result != 0) {
            // Multiply original ebx_arg and fStack_1c by the direction components? This seems odd.
            // Probably the calls return direction in the global parameters? Actually FUN_005dcb60 modifies dirX and dirY? No, it takes pointers? The decompiler shows afStack_c[0] and fStack_10 as locals, but the call doesn't pass them? Wait:
            // The call is: FUN_005dcb60(DAT_01223508, *(undefined4 *)(unaff_EDI + 0x24c));
            // It doesn't pass the locals. So how do dirX and dirY get set? They were initialized to 0.0, but maybe FUN_005dcb60 writes to some global? That seems unlikely.
            // Actually, the decompiler might have misordered. Let's re-examine: after setting dirX=0, dirY=0, the call is made. Then after call, unaff_EBX = afStack_c[0] * unaff_EBX; fStack_1c = fStack_10 * fStack_1c; This means FUN_005dcb60 modifies afStack_c[0] and fStack_10? But they are not passed as pointers. So maybe Ghidra's decompilation is missing parameters. More likely, FUN_005dcb60 takes a pointer to a vector, and the call actually passes &afStack_c[0] or something. The decompiler doesn't show that because of calling convention or missing arguments.
            // Given the complexity, I'll assume FUN_005dcb60 fills in some global or returns a value that modifies those locals via some side effect? Unlikely.
            // For reconstruction, we'll assume the vector is updated via some global or passed implicitly. This is a weak point.
            // Better to leave as function calls with comments.
            // However, the pattern suggests that after the call, afStack_c[0] and fStack_10 are used.
            // Let's assume FUN_005dcb60 returns a boolean and updates some global state that is then used? No.
            // Looking at the code: afStack_c[0] = 0.0; fStack_10 = 0.0; then call FUN_005dcb60(DAT_01223508, 0x24c); then if (cVar2 != 0) { unaff_EBX = afStack_c[0] * unaff_EBX; fStack_1c = fStack_10 * fStack_1c; } So afStack_c[0] and fStack_10 must have been modified by the call, but they are not passed. Unless FUN_005dcb60 writes to them as global variables? No.
            // Possibly the decompiler omitted the pointer arguments. Let's assume the function actually takes a pointer to a 2D vector:
            // char FUN_005dcb60(void* manager, int id, float* outX, float* outY);
            // Then the call would be: cVar2 = FUN_005dcb60(DAT_01223508, unaff_EDI+0x24c, &afStack_c[0], &fStack_10);
            // But the decompiler shows only two arguments. However, the calling convention might pass some in registers. We'll reconstruct with assumed parameters.
        }
        // Then another call: FUN_005dcc40(DAT_01223508, &local_18); // local_18 is an output (maybe handle or something)
        FUN_005dcc40(DAT_01223508, &local_18);
    } else {
        // Branch B: Character has direction override (e.g., player input)
        float dirX = 0.0f;
        float dirY = 0.0f;
        float scalar = 1.0f; // from DAT_00e2b1a4
        // call FUN_005e5270 with several parameters: this+0x238 (some pointer), this+0x47c, &dirX, &dirY, &scalar, &local_18
        char result = FUN_005e5270(this + 0x238, this + 0x47c, &dirX, &dirY, &scalar, &local_18);
        float savedDirY = dirY;
        if (result != 0) {
            // vtable[0x78] - setAnimationSpeed? with multiplier from DAT_011274e8
            ((void(*)(float, float))vtable[0x78])(animHandle, DAT_011274e8 * dirY);
            fStack_1c = scalar * fStack_1c; // adjust time/duration
            ebx_arg = savedDirY; // update the EBX parameter (direction X?)
        }
    }

    // After direction logic: update state based on flags
    if (*(char*)(this + 0x285) == 0) {
        if (*(int*)(this + 0x484) == 3) {
            int currentTime = *(int*)(DAT_01223518 + 8); // global time
            int startTime = *(int*)(this + 0x204);
            int elapsed = currentTime - startTime;
            float limit = *(float*)(this + 0x1b8);
            // DAT_00e44598 is a threshold (maybe 0.0? or a small float)
            if (limit < DAT_00e44598 || (int)limit <= elapsed) {
                FUN_005e9520(); // reset
            } else {
                *(float*)(this + 0x1d8) = 1.0f - (float)elapsed / limit; // compute blend factor
            }
        }
    } else {
        // branch for state 0x285 != 0 && (0x1cc >= 0)
        if (*(int*)(this + 0x1cc) >= 0) {
            int durationFrames = (int)(*(float*)(this + 0x21c) * DAT_00e2e230);
            *(int*)(this + 0x1b8) = durationFrames; // store
            float One = 1.0f;
            if (durationFrames > 0) {
                if (*(char*)(this + 0x286) == 0) {
                    // Check if animation handle is valid
                    char valid2 = ((char(*)(int))vtable[0x90])(*(int*)(this + 0x1cc));
                    if (valid2 != 0) {
                        *(char*)(this + 0x286) = 1; // mark flag
                        *(int*)(this + 0x204) = *(int*)(DAT_01223518 + 8); // record start time
                    }
                    goto end_update;
                }
                int elapsed = *(int*)(DAT_01223518 + 8) - *(int*)(this + 0x204);
                if (elapsed < durationFrames && (float)durationFrames >= DAT_00e44598) {
                    *(float*)(this + 0x1d8) = (float)elapsed / (float)durationFrames;
                    goto end_update;
                }
            }
            // Not in range: reset flags
            *(float*)(this + 0x1d8) = 1.0f;
            *(float*)(this + 0x1dc) = One;
            *(char*)(this + 0x285) = 0;
            *(char*)(this + 0x286) = 0;
        }
    }

end_update:
    float blend = *(float*)(this + 0x1d8) * ebx_arg;
    // Clamp blend to [0,1]
    if (blend > 1.0f) blend = 1.0f;
    else if (blend < 0.0f) blend = 0.0f;

    // Call vtable functions: +0x6c might be some prepare, +0x84 set speed/weight
    ((void(*)(float))vtable[0x6c])(animHandle);
    ((void(*)(float, float))vtable[0x84])(animHandle, blend);

    // Determine ID for sound/effect? +0x24c is some ID, but if bit 4 in +0x250 is set, use alternative
    int id = *(int*)(this + 0x24c);
    if ((*(byte*)(this + 0x250) & 4) != 0) {
        id = DAT_012056c0; // alternative ID
    }

    // Call some function from manager with fStack_1c (adjusted time/duration)
    char result2 = FUN_005de7e0(DAT_01223508, id, &fStack_1c);
    if (result2 != 0 && *(float*)(this + 0x1e0) != fStack_1c) {
        *(float*)(this + 0x1e0) = fStack_1c;
        float rounded = (float)(int)fStack_1c;
        if (fStack_1c < 0.0f) {
            rounded += 0.5f; // DAT_00e44578
        }
        ((void(*)(float, float))vtable[0x88])(animHandle, rounded);
    }

    // Store the clamped blend
    *(float*)(this + 0x1ec) = blend;

    // Update integer parameters (maybe frame numbers)
    int newVal = (int)(animHandle * DAT_00e445e0); // seems to use animHandle as float? odd
    if (*(int*)(this + 0x1e4) != newVal) {
        char ok = ((char(*)(float, int))vtable[0x70])(animHandle, newVal);
        if (ok != 0) {
            *(int*)(this + 0x1e4) = newVal;
        }
    }

    int newVal2 = (int)(*(float*)(this + 0x260) * DAT_00e445e0);
    if (*(int*)(this + 0x1e8) != newVal2) {
        char ok = ((char(*)(float, int))vtable[0x74])(animHandle, newVal2);
        if (ok != 0) {
            *(int*)(this + 0x1e8) = newVal2;
        }
    }

    return;
}
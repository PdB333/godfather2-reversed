// FUNC_NAME: PlayerSM::transitionToAnimationState
void __fastcall PlayerSM::transitionToAnimationState(int param_1)
{
    // param_1 is offset 0x50 from the actual `this` pointer (base = param_1 - 0x50)
    // Fields relative to base:
    //   +0x88 (from param_1) = base + 0xD8: state (int)
    //   +0x2c = base + 0x7C: flags (uint)
    //   +0x4c = base + 0x9C: animationTimer (int)
    // Vtable at base+0 (base points to vtable pointer)

    int *globalPlayer;          // DAT_01223484 – global singleton Player pointer
    int animationId;            // iVar6
    code *vfuncStart;           // pcVar1
    bool canPlay;               // bVar2
    int *animData;              // puVar5 (string pointer or animation data)
    int stateField;             // iVar3 (actually same as globalPlayer)

    stateField = *(int *)(param_1 + 0x88);
    if (stateField == 0) {
        return; // inactive state, exit
    }

    // Determine if we can start a new animation based on current state and some global condition
    if ((stateField < 3) && (FUN_008a4380() != '\0')) {
        canPlay = true;
    } else {
        canPlay = false;
    }

    globalPlayer = DAT_01223484;

    if (canPlay) {
        if (globalPlayer == (int *)0x0) {
            goto LAB_008ae497;
        }
        // Check player flags: bit 4 (0x10) and bit 3 (0x08) in flags field at +0x37c
        if ((((*(uint *)(globalPlayer + 0x37c) >> 4) & 1) != 0) &&
            ((*(uint *)(globalPlayer + 0x37c) >> 3) & 1) != 0 &&
            (*(int *)(DAT_012234b8 + 0xc) != 0)) {
            // Get animation name string from global player at offset 0x384 (900 decimal)
            animData = *(code **)(globalPlayer + 900); // on 32-bit, pointer size 4 bytes, so offset 0x384
            if (animData == (code *)0x0) {
                animData = &DAT_0120546e; // default empty string
            }
            animationId = FUN_008acaf0(animData); // resolves string to animation ID
            goto LAB_008ae4d8;
        }
    }

    // If not triggering via condition, check if an animation is already queued
    if ((globalPlayer != (int *)0x0) &&
        (animationId = *(int *)(globalPlayer + 0x3b4), animationId != -1)) {
        // Fall through to set the animation
    } else {
        goto LAB_008ae497; // no animation to apply
    }

LAB_008ae4d8:
    // Set the animation ID in global player
    *(int *)(globalPlayer + 0x3b4) = animationId;
    // Set a flag in our state machine (bit 0x800)
    *(uint *)(param_1 + 0x2c) |= 0x800;

    // Call virtual function: likely “startAnimation” (vtable +0xB4)
    (**(code **)(*(int *)(param_1 - 0x50) + 0xb4))();

    // Get another virtual function pointer (vtable +0xE8)
    vfuncStart = *(code **)(*(int *)(param_1 - 0x50) + 0xe8);

    // Update state to 4 (e.g., “Animating”)
    *(int *)(param_1 + 0x88) = 4;
    *(int *)(param_1 + 0x4c) = 0; // Reset animation timer

    // Call the second virtual (probably “playAnimationNow”)
    (*vfuncStart)();

    // Clear the flag we set earlier
    *(uint *)(param_1 + 0x2c) &= 0xfffff7ff;
    return;

LAB_008ae497:
    // No animation change – call another virtual (vtable +0xB8) maybe “finishState”
    (**(code **)(*(int *)(param_1 - 0x50) + 0xb8))();

    if ((globalPlayer != (int *)0x0) && canPlay) {
        // Reset some systems
        FUN_008a2d40(0);
        FUN_008a4c30();
    }
    return;
}
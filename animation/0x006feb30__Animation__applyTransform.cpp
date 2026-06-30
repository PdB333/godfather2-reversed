// FUNC_NAME: Animation::applyTransform
void __fastcall Animation::applyTransform(int thisPtr)
{
    int iVar1;
    int local_18[2];
    undefined1 *local_10;
    int local_c;
    undefined1 *local_8;
    undefined1 **local_4;

    iVar1 = 0;
    // gAnimationManager is a global singleton
    // It has multiple bone/transform sets: primary (0x198), fallback1 (0x180), fallback2 (0x1d0, 0x1b8)
    if (*(int *)(gAnimationManager + 0x198) == 0) {
        iVar1 = gAnimationManager + 0x180;
    }
    else {
        if (*(int *)(gAnimationManager + 0x1d0) != 0) goto LAB_006feb67;
        iVar1 = gAnimationManager + 0x1b8;
    }
    if (iVar1 != 0) {
        // Increment reference count on the transform set
        *(int *)(iVar1 + 0x30) = *(int *)(iVar1 + 0x30) + 1;
    }
LAB_006feb67:
    // Push a scoped context onto the transform stack
    local_10 = &LAB_004747a0;  // Maybe vtable or function pointer for stack object
    local_8 = (undefined1 *)0x0;
    local_4 = gTransformStack;  // Global stack head
    if (gTransformStack != (undefined1 **)0x0) {
        gTransformStack[2] = (undefined1 *)&local_10;  // Link previous node
    }
    gTransformStack = &local_10;  // New node becomes top of stack

    // Copy transform data from animation object to the active transform set
    *(undefined4 *)(iVar1 + 0x20) = *(undefined4 *)(thisPtr + 0x14c);

    // Prepare a possible cleanup object
    local_18[0] = 0;
    local_18[1] = 0;
    local_c = thisPtr;

    // Call the actual transform application routine
    FUN_006fea40(thisPtr + 0x6c, &local_10, 0, 0, 0x3f800000);  // 1.0f as last arg

    // Free cleanup if needed
    if (local_18[0] != 0) {
        FUN_004daf90(local_18);
    }

    // Copy result back from transform set to animation object
    *(undefined4 *)(thisPtr + 0xe8) = *(undefined4 *)(iVar1 + 0x18);

    // Pop the scoped context from the transform stack
    if (local_8 != (undefined1 *)0x0) {
        *(undefined1 ***)(local_8 + 0xc) = local_4;
    }
    if (local_4 != (undefined1 **)0x0) {
        local_4[2] = local_8;
    }
    if (gTransformStack == &local_10) {
        gTransformStack = local_4;
    }
    return;
}
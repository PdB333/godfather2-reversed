// FUNC_NAME: OverlayManager::updateOverlayState
void OverlayManager::updateOverlayState(int param_1) // param_1 might be a step index
{
    float colorVal;
    float* colorArray;
    int iVar1;
    int* piVar2;
    int thisReg; // unaff_EDI stored here for clarity
    int fsOffset; // unaff_FS_OFFSET
    bool bVar3;
    int uVar4;

    // Access array of color values (stride 0x84 = 132 bytes)
    // DAT_01163850 and DAT_0116384c are arrays of float values
    colorArray = (float*)((int)&DAT_01163850 + thisReg * 0x84);
    colorVal = *colorArray;

    // Get pointer to global rendering context
    piVar2 = (int*)(DAT_012233a8 + 4);
    // Write two color values to the context at offsets +0x39f0 and +0x39f4
    *(int*)(*(int*)(DAT_012233a8 + 4) + 0x39f0) = *(int*)((int)&DAT_0116384c + thisReg * 0x84);
    *(int*)(*piVar2 + 0x39f4) = *(int*)colorArray;

    // Check global flag (night vision? fullscreen?)
    bVar3 = (DAT_0110aae7 == '\0');

    if (bVar3) {
        // Non-night-vision mode: set clear color to black transparent
        FUN_00609730(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f); // RGBA and something
        FUN_00609810(0x10); // set overlay layer 0x10
    } else {
        // Night vision: white full alpha
        FUN_00609730(1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f);
        FUN_00609810(0x11);
        // Then black transparent
        FUN_00609730(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
    }

    // Check pause flag
    if (DAT_0120535b == '\0') {
        // Not paused: update menu overlay
        FUN_0041fc90(param_1);
        // Check if overlay is visible (DAT_01163840 array, stride 0x210)
        if (*(int*)((int)&DAT_01163840 + thisReg * 0x210) != 0) {
            FUN_006096a0(); // clear or reset something
        }
    }

    // Choose alpha mode based on night vision flag
    if (DAT_0110aae7 == '\0') {
        uVar4 = 2;
    } else {
        uVar4 = 3;
    }
    FUN_00609890(uVar4); // set alpha blending mode

    // Access thread-local storage for some object
    iVar1 = **(int**)(fsOffset + 0x2c);
    *(int*)(iVar1 + 0x28) = 0;

    // If some state is zero, push a pointer to a global pointer list
    if (*(int*)(iVar1 + 0x34) == 0) {
        uVar4 = *(int*)((int)&DAT_01163820 + thisReg * 0x84 + param_1);
        piVar2 = (int*)(DAT_01206880 + 0x14);
        // Push address of global pointer array
        **(int**)(DAT_01206880 + 0x14) = &PTR_LAB_0110b708;
        *piVar2 = *piVar2 + 4;
        *(int*)*piVar2 = uVar4;
        *piVar2 = *piVar2 + 4;
    }

    // Reset global flag
    DAT_01163ccc = 0;
    return;
}
// FUNC_NAME: CameraManager::findActiveCamera
int* __fastcall CameraManager::findActiveCamera(int* cameraSlotArray)
{
    int* cameraObj;
    char isActive;
    int managerPtr;
    undefined4* vecPtr;
    undefined4 vec[4];
    int* resultCamera;
    int local_34;
    undefined4 uStack_30;
    undefined4 uStack_2c;
    undefined4 uStack_28;
    undefined4 uStack_24;
    undefined1* labelTable[5];
    undefined4 local_c;
    undefined1* local_8;
    undefined4 local_4;

    // Label table for debug strings or function pointers (not used directly in logic)
    labelTable[0] = &LAB_00898b50;
    labelTable[2] = &LAB_00898b70;
    labelTable[4] = &LAB_00898b40;
    local_8 = &LAB_00898b60;
    labelTable[1] = (undefined1*)0x0;
    labelTable[3] = (undefined1*)0x0;
    local_c = 0;
    local_4 = 0;

    // Get manager pointer from global
    if (**(int**)(DAT_012233a0 + 4) == 0) {
        managerPtr = 0;
    } else {
        managerPtr = **(int**)(DAT_012233a0 + 4) + -0x1f30;
    }

    local_34 = 0;
    if (managerPtr != 0) {
        undefined4 uVar4 = (**(code**)(*(int*)(managerPtr + 0x1f30) + 8))();
        local_34 = FUN_00410540(uVar4);
    }

    // Check game state (byte at global + 0x568)
    bool isNotSpecialState = *(char*)(DAT_012233b4 + 0x568) != 0x12;

    resultCamera = (int*)0x0;
    undefined1** ppuVar6 = labelTable + 1; // unused
    uint slotIndex = 0;

    do {
        // Get a vector (position/color) from some manager
        vecPtr = (undefined4*)FUN_004d94d0();
        vec[0] = *vecPtr;
        vec[1] = vecPtr[1];
        vec[2] = vecPtr[2];
        vec[3] = vecPtr[3];

        // Check if slot is active (first member non-null)
        if (*cameraSlotArray != 0) {
            // Get camera object pointer (slot stores pointer + 0x48 offset)
            cameraObj = (int*)(*cameraSlotArray - 0x48);
            if (cameraObj != (int*)0x0) {
                // Check slot flag (third member)
                if (cameraSlotArray[2] == 0) {
                    if (isNotSpecialState) {
                        isActive = (**(code**)(*cameraObj + 0x30))(); // virtual: isActive?
                        if (isActive == '\0') goto LAB_0089c9f0;
                        vecPtr = (undefined4*)(*(code*)ppuVar6[-1])(); // unused call
                    } else {
                        isActive = (**(code**)(*cameraObj + 0x30))();
                        if (isActive == '\0') {
LAB_0089c9f0:
                            vecPtr = (undefined4*)(DAT_0112a878 + 0x1d4); // debug string?
                        } else {
                            vecPtr = (undefined4*)(DAT_0112a878 + 0x1e4);
                        }
                    }
                    // Update vector from debug string
                    vec[0] = *vecPtr;
                    vec[1] = vecPtr[1];
                    vec[2] = vecPtr[2];
                    vec[3] = vecPtr[3];

                    // Check if this camera should be the result
                    if (((resultCamera == (int*)0x0) && 
                         (isActive = (**(code**)(*cameraObj + 0x30))(), isActive != '\0')) &&
                        (local_34 != 0) &&
                        ((*(uint*)((int)&DAT_00d785b8 + slotIndex) & (uint)*(ushort*)(local_34 + 0x10)) != 0 &&
                         ((*(uint*)((int)&DAT_00d785b8 + slotIndex) & (uint)*(ushort*)(local_34 + 0x12)) == 0))) {
                        resultCamera = cameraObj;
                    }
                }
                // Call virtual function at +0x34 with vector (e.g., setDebugColor)
                (**(code**)(*cameraObj + 0x34))(&vec);
                FUN_006cf840(); // render debug?
                if (isNotSpecialState) {
                    FUN_006cf960();
                } else {
                    FUN_006cfdc0(*(undefined4*)((int)&PTR_s__b_MPDC_CAMERA_1__00e543c0 + slotIndex));
                }
            }
        }
        slotIndex += 4;
        cameraSlotArray += 3;
        ppuVar6 += 2;
        if (0xf < slotIndex) {
            return resultCamera;
        }
    } while (true);
}
// FUNC_NAME: CameraManager::findFirstCameraControl
int* __fastcall findFirstCameraControl(int* pControlList) {
    // pControlList: pointer to an array of CameraControl structures (4 entries, each 12 bytes)
    // Each CameraControl: [0] = pointer to virtual object (e.g., ControllerDevice), [1..2] = unused here
    // Returns pointer to the first control that matches current controller hardware flags and game state

    int* pFoundDevice = 0;
    int* pLocalArray[4];
    pLocalArray[0] = (int*)&LAB_00898b50; // String or code references for camera names
    pLocalArray[1] = (int*)&LAB_00898b70;
    pLocalArray[2] = (int*)&LAB_00898b40;
    pLocalArray[3] = (int*)&LAB_00898b60;
    // These correspond to camera types: 1st person, 3rd person, chase, etc.

    int* pCurrentArrayEntry = &pLocalArray[0];
    uint slotIndex = 0;

    // Retrieve the current player's controller hardware ID
    int* pInputManager = *(int**)(gInputManagerSingleton + 4); // DAT_012233a0 + 4
    int iVar3;
    if (pInputManager == 0) {
        iVar3 = 0;
    } else {
        iVar3 = (int)pInputManager - 0x1f30; // Offset to get device manager from input manager
    }
    int local_38 = 0;
    if (iVar3 != 0) {
        // Call virtual function on device manager to get player's device ID
        int uVar4 = (**(code**)(*(int*)(iVar3 + 0x1f30) + 8))();
        local_38 = FUN_00410540(uVar4); // Convert to internal handle/type
    }

    // Check if game state is not in a specific mode (0x12 = e.g., STATE_PLAYING)
    bool bIsNotPlaying = *(char*)(gGameState + 0x568) != 0x12;

    // Iterate over 4 camera controls (likely fixed set)
    do {
        // Get current control's virtual object and check for active state
        int* pCameraDevice = (int*)FUN_004d94d0(); // Returns current input device data? Actually gets some state
        int localData[4];
        localData[0] = *pCameraDevice;
        localData[1] = pCameraDevice[1];
        localData[2] = pCameraDevice[2];
        localData[3] = pCameraDevice[3];

        int* pDevice = (int*)*pControlList;
        if (pDevice != 0) {
            // Check if the control is not already assigned (param_1[2] is some flag)
            if (pControlList[2] == 0) {
                bool bIsActive;
                if (bIsNotPlaying) {
                    bIsActive = (**(code**)(*pDevice + 0x10))() != 0; // Virtual: IsActive?
                    if (bIsActive) {
                        pCameraDevice = (int*)(*(code*)pCurrentArrayEntry[-1])(); // get camera name? Or function?
                    } else {
                        // fall through to default set
                    }
                } else {
                    bIsActive = (**(code**)(*pDevice + 0x10))() != 0;
                    if (bIsActive) {
                        pCameraDevice = (int*)(gLocal + 0x1e4); // DAT_0112a878 + 0x1e4 (some default constant)
                    } else {
                        pCameraDevice = (int*)(gLocal + 0x1d4); // DAT_0112a878 + 0x1d4
                    }
                }
                // Copy the chosen data back to local stack
                localData[0] = *pCameraDevice;
                localData[1] = pCameraDevice[1];
                localData[2] = pCameraDevice[2];
                localData[3] = pCameraDevice[3];
            }

            // Determine if this control matches the desired flags
            if ((pFoundDevice == 0) &&
                ((**(code**)(*pDevice + 0x10))() != 0) &&
                (local_38 != 0) &&
                ((*(uint*)((int)&gCameraFlagsTable + slotIndex) & (uint)*(ushort*)(local_38 + 0x10)) != 0) &&
                ((*(uint*)((int)&gCameraFlagsTable + slotIndex) & (uint)*(ushort*)(local_38 + 0x12)) == 0)) {
                pFoundDevice = pDevice;
            }

            // Update the control device with local data
            (**(code**)(*pDevice + 0x14))(&localData); // Virtual: Update(data)

            if (pDevice[4] != 0) {
                FUN_004df830(0); // Some cleanup/set function
            }
            if (bIsNotPlaying) {
                if (pDevice[4] != 0) {
                    FUN_004df6e0(); // Another cleanup
                }
            } else {
                // Not in playing state: call debug/log function with camera name
                FUN_0089e1b0(*(undefined4*)((int)&gCameraNames + slotIndex));
            }
        }

        // Move to next entry
        pCurrentArrayEntry += 2;
        slotIndex += 4;
        pControlList += 3;
        if (slotIndex > 0xf) {
            break;
        }
    } while (true);

    return pFoundDevice;
}
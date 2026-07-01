// FUNC_NAME: PlayerBehavior::updateBehavior

void __thiscall PlayerBehavior::updateBehavior(int thisPtr, int* context)
{
    // context[6] is likely deltaTime or some time value
    // thisPtr + 0x740 is a flag (byte)
    // _DAT_00d577a0 is a global float threshold
    if ((_DAT_00d577a0 < (float)context[6]) || (*(char*)(thisPtr + 0x740) != '\0')) {
        int* targetObj = (int*)context[0];
        int* somePtr = nullptr;
        if ((targetObj != nullptr) && (*(char*)(targetObj + 0x10) + targetObj != 0)) {
            // FUN_004af8c0 likely allocates or retrieves an object with type 0x2001
            FUN_004af8c0(&somePtr, 0x2001);
            if (somePtr == nullptr) {
                somePtr = nullptr;
            }
        }
        uint identifier = 0;
        if (somePtr != nullptr) {
            uint tempId = 0;
            char result = (**(code**)(*somePtr + 0x10))(0xa5975eb2, &tempId);
            identifier = (result != '\0') ? tempId : 0;
        }
        // Compare identifier with parent object (thisPtr - 0x2e0)
        if (identifier == thisPtr - 0x2e0U) {
            int* targetObj2 = (int*)context[1];
            if ((targetObj2 != nullptr) && (*(char*)(targetObj2 + 0x10) + targetObj2 != 0)) {
                FUN_004af8c0(&somePtr, 0x2001);
                if (somePtr != nullptr) {
                    uint tempId2 = 0;
                    char result2 = (**(code**)(*somePtr + 0x10))(0xa5975eb2, &tempId2);
                    if (result2 != '\0') {
                        identifier = tempId2;
                        goto LAB_0087cfcd;
                    }
                }
            }
        } else {
LAB_0087cfcd:
            uint uVar8 = identifier;
            if ((identifier != 0) &&
                ((*(uint*)(identifier + 0xc88) >> 2 & 1) != 0 ||
                 (_DAT_00d577a0 < (float)context[6]))) {
                if (thisPtr - 0x2e0U != identifier) {
                    // Check flags at thisPtr+0x9a8: bit 11 (0x800) and bit 2 (0x4)
                    if (((*(uint*)(identifier + 0xc88) >> 2 & 1) != 0) &&
                        ((*(uint*)(thisPtr + 0x9a8) >> 0xb & 1) != 0) &&
                        ((*(uint*)(thisPtr + 0x9a8) >> 2 & 1) == 0)) {
                        byte loopCounter = 0;
                        int count = FUN_00543330(); // get count of something
                        if (count != 0) {
                            uint index = 0;
                            do {
                                int* objPtr = nullptr;
                                // vtable +0x218: get object by index
                                (**(code**)(*(int*)(thisPtr - 0x2e0) + 0x218))(index, &objPtr);
                                int result3 = (**(code**)(*(int*)(thisPtr - 0x2e0) + 500))(auStack_a8); // vtable +500 (0x1f4)
                                if ((result3 != 0) && (result3 = FUN_006bc8d0(result3, 0x369ac561), result3 != 0)) {
                                    // Set flag at +0x1f58
                                    *(uint*)(result3 + 0x1f58) |= 4;
                                }
                                loopCounter++;
                                index = (uint)loopCounter;
                                count = FUN_00543330();
                                uVar8 = identifier;
                            } while (index < count);
                        }
                    }
                    int state = FUN_00544b70(); // get some state
                    if ((state == 2) &&
                        (((*(uint*)(uVar8 + 0xc88) >> 2 & 1) != 0) || (state = FUN_00544b70(), state == 1))) {
                        FUN_00544ae0(1); // set state to 1
                        *(int*)(thisPtr + 0x73c) = 100; // some timer or health
                        *(char*)(thisPtr + 0x740) = 1; // flag
                    }
                }
                // Check flag bit 2 at thisPtr+0x9a8
                if ((*(uint*)(thisPtr + 0x9a8) >> 2 & 1) == 0) {
                    if (*(float*)(thisPtr + 0x74c) <= 0.0f && *(float*)(thisPtr + 0x74c) != 0.0f) {
                        int timePtr = FUN_00471610(); // get time or position
                        // Copy 12 bytes (3 floats) from timePtr+0x30 to thisPtr+0x750
                        *(double*)(thisPtr + 0x750) = *(double*)(timePtr + 0x30);
                        *(float*)(thisPtr + 0x758) = *(float*)(timePtr + 0x38);
                    }
                    *(float*)(thisPtr + 0x74c) = _DAT_00d5779c; // set some float
                }
            }
        }
    }
    uint currentTime = FUN_00494d10(); // get current time
    // Check flag bit 4 at thisPtr+0x9a8
    if (((*(uint*)(thisPtr + 0x9a8) >> 4 & 1) != 0) && (100 < currentTime - _DAT_0112e014)) {
        float* vectorPtr = (float*)context[3]; // pointer to 3 floats
        // Build a matrix or transform from global constants and vectorPtr
        // _DAT_00d5780c is a float constant
        float matrixData[12]; // actually 12 floats? but we have 12 undefined4
        // Initialize matrixData with constants and vectorPtr
        matrixData[0] = _DAT_00d5780c; matrixData[1] = 0; matrixData[2] = 0; matrixData[3] = 0;
        matrixData[4] = 0; matrixData[5] = _DAT_00d5780c; matrixData[6] = 0; matrixData[7] = 0;
        matrixData[8] = 0; matrixData[9] = 0; matrixData[10] = _DAT_00d5780c; matrixData[11] = 0;
        // Actually the code sets uStack_60, uStack_5c, uStack_58 from vectorPtr[0..2]
        // and local_54 = _DAT_00d5780c, etc. It's a 4x4 matrix? Let's simplify.
        // The code calls FUN_0044b4e0(auStack_50, &uStack_90) which likely transforms something.
        // We'll skip detailed matrix reconstruction.
        // Instead, we'll note that it uses context[3] as a position vector.
        int* raycastResult = (int*)(thisPtr + 0x864);
        // Check if any of the four components at thisPtr+0x864..0x870 are non-zero
        bool hasRaycast1 = (*(int*)(thisPtr + 0x864) != 0) || (*(int*)(thisPtr + 0x868) != 0) ||
                           (*(int*)(thisPtr + 0x86c) != 0) || (*(int*)(thisPtr + 0x870) != 0);
        if (hasRaycast1 &&
            (*(float*)(thisPtr + 0x888) <= (float)(context[6] & _DAT_00e44680) &&
             (float)(context[6] & _DAT_00e44680) != *(float*)(thisPtr + 0x888))) {
            // Perform raycast
            int vtableResult = (**(code**)(*(int*)(thisPtr - 0x2e0) + 0x58))(0, 0, 0xffffffff, 0);
            uint raycastHandle = 0;
            FUN_004df330(&raycastHandle, raycastResult, matrixData, vtableResult);
            if (raycastHandle != 0) {
                *(int*)(raycastHandle + 8) = 0;
            }
        } else {
            // Check another set of components at thisPtr+0x854..0x860
            bool hasRaycast2 = (*(int*)(thisPtr + 0x854) != 0) || (*(int*)(thisPtr + 0x858) != 0) ||
                               (*(int*)(thisPtr + 0x85c) != 0) || (*(int*)(thisPtr + 0x860) != 0);
            if (hasRaycast2 &&
                (*(float*)(thisPtr + 0x884) <= (float)(context[6] & _DAT_00e44680) &&
                 (float)(context[6] & _DAT_00e44680) != *(float*)(thisPtr + 0x884))) {
                int vtableResult2 = (**(code**)(*(int*)(thisPtr - 0x2e0) + 0x58))(0, 0, 0xffffffff, 0);
                uint raycastHandle2 = 0;
                FUN_004df330(&raycastHandle2, thisPtr + 0x844, matrixData, vtableResult2);
                if (raycastHandle2 != 0) {
                    *(int*)(raycastHandle2 + 8) = 0;
                }
            } else {
                // Check third set at thisPtr+0x844..0x850
                bool hasRaycast3 = (*(int*)(thisPtr + 0x844) == 0) && (*(int*)(thisPtr + 0x848) == 0) &&
                                   (*(int*)(thisPtr + 0x84c) == 0) && (*(int*)(thisPtr + 0x850) == 0);
                if (!hasRaycast3 &&
                    ((float)(context[6] & _DAT_00e44680) >= *(float*)(thisPtr + 0x880) &&
                     (float)(context[6] & _DAT_00e44680) != *(float*)(thisPtr + 0x880))) {
                    int vtableResult3 = (**(code**)(*(int*)(thisPtr - 0x2e0) + 0x58))(0, 0, 0xffffffff, 0);
                    uint raycastHandle3 = 0;
                    FUN_004df330(&raycastHandle3, thisPtr + 0x844, matrixData, vtableResult3);
                    if (raycastHandle3 != 0) {
                        *(int*)(raycastHandle3 + 8) = 0;
                    }
                }
            }
        }
        _DAT_0112e014 = currentTime;
    }
LAB_0087d323:
    // Check byte flag at thisPtr+0x738 (bit 0)
    if ((*(byte*)(thisPtr + 0x738) & 1) == 0) {
        char shouldSkip = FUN_008773c0(context); // check if we should skip
        if (shouldSkip == '\0') {
            int* someInterface = (int*)(**(code**)(*(int*)(thisPtr - 0x2e0) + 0x1e4))();
            if (someInterface != nullptr) {
                uint checkId = 0;
                char result4 = (**(code**)(*someInterface + 0x10))(0xd80c71d2, &checkId);
                if ((result4 != '\0') && (checkId != 0)) {
                    if (*(int*)(thisPtr + 0x4e0) != 0) {
                        FUN_0085b4d0(context, _DAT_00d764b8); // set something with global float
                    }
                    if (_DAT_011299a8 != 0) {
                        FUN_008d1c00(); // some update
                    }
                    if (*(float*)(thisPtr + 0x888) * _DAT_00d5ca64 < (float)(context[6] & _DAT_00e44680)) {
                        FUN_0087b710(); // another update
                    }
                    goto LAB_0087d3ef;
                }
            }
            if (*(int*)(thisPtr + 0x4e0) != 0) {
                FUN_0085b4d0(context, 0x3f800000); // set something to 1.0f
            }
        }
    }
LAB_0087d3ef:
    FUN_00540410(0xd0); // end profiling scope
    return;
}
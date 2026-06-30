// FUNC_NAME: CombatPerception::evaluateTarget
undefined4 __thiscall CombatPerception::evaluateTarget(int this, undefined4 targetObject) {
    char isValid;
    int playerPtr;
    int *baseClassPtr;
    undefined4 outOrientation;
    int tempEAX;
    float deltaX1, deltaY1, deltaZ1;
    float deltaX2, deltaY2, deltaZ2;
    undefined4 retPosition[2]; // returned via hidden parameter (struct by value)
    undefined4 *stackRef;
    undefined4 coverTransformRaw[2];
    float coverPos1[3], coverPos2[3]; // positions from cover points
    int *outputStruct;
    float playerPosZ;

    // Initialize output struct
    outOrientation = 0;
    coverTransformRaw[0] = 0;

    // Get the base class pointer from the component (offset +0x54 points to a derived object, base at -0x48)
    if (*(int *)(this + 0x54) == 0) {
        baseClassPtr = (int *)0x0;
    } else {
        baseClassPtr = (int *)(*(int *)(this + 0x54) - 0x48);
    }

    // Store the address of the output transform for later use
    stackRef = coverTransformRaw;

    // Call a method on the base class (vtable index 0x1f0) with targetObject
    (*(code **)(*baseClassPtr + 0x1f0))(targetObject);

    // Check if the component at +0x54 is still valid
    if (*(int *)(this + 0x54) == 0) {
        playerPtr = 0;
    } else {
        playerPtr = *(int *)(this + 0x54) - 0x48;
    }

    isValid = FUN_00883670(&coverTransformRaw, *(undefined4 *)(this + 0x50), playerPtr);
    if (isValid == '\0') {
        isValid = FUN_008754e0(&coverTransformRaw);
        if (isValid != '\0') {
            // Reset the output struct
            outOrientation = 0;
            coverTransformRaw[0] = 0;

            // Get the component pointer again
            if (*(int *)(this + 0x54) == 0) {
                baseClassPtr = (int *)0x0;
            } else {
                baseClassPtr = (int *)(*(int *)(this + 0x54) - 0x48);
            }

            // Call vtable method at 0x1c8 to get a transform
            (*(code **)(*baseClassPtr + 0x1c8))(&coverTransformRaw, &outOrientation);

            // Re-validate the component
            if (*(int *)(this + 0x54) == 0) {
                playerPtr = 0;
            } else {
                playerPtr = *(int *)(this + 0x54) - 0x48;
            }

            isValid = FUN_00883670(&outOrientation, *(undefined4 *)(this + 0x50), playerPtr);
            if (isValid == '\0') {
                // Get the component pointer again for position retrieval
                if (*(int *)(this + 0x54) == 0) {
                    baseClassPtr = (int *)0x0;
                } else {
                    baseClassPtr = (int *)(*(int *)(this + 0x54) - 0x48);
                }

                // Get the first cover point position (vtable method 0xa4)
                (*(code **)(*baseClassPtr + 0xa4))(&coverPos1, &coverTransformRaw);

                // Get the component pointer again
                if (*(int *)(this + 0x54) == 0) {
                    baseClassPtr = (int *)0x0;
                } else {
                    baseClassPtr = (int *)(*(int *)(this + 0x54) - 0x48);
                }

                // Get the second cover point position
                (*(code **)(*baseClassPtr + 0xa4))(&coverPos2, &coverTransformRaw);

                // Get the player entity (presumably the local player)
                playerPtr = FUN_00471610();

                // Calculate vector from player to first cover point
                deltaX1 = *(float *)(playerPtr + 0x30) - coverPos1[0];
                deltaY1 = *(float *)(playerPtr + 0x34) - coverPos1[1];
                deltaZ1 = *(float *)(playerPtr + 0x38) - coverPos1[2];

                // Calculate vector from player to second cover point
                playerPtr = FUN_00471610();
                deltaX2 = *(float *)(playerPtr + 0x30) - coverPos2[0];
                deltaY2 = *(float *)(playerPtr + 0x34) - coverPos2[1];
                deltaZ2 = *(float *)(playerPtr + 0x38) - coverPos2[2];

                // Compare squared distances: choose the cover point that is closer
                if (deltaX2*deltaX2 + deltaY2*deltaY2 + deltaZ2*deltaZ2 <=
                    deltaX1*deltaX1 + deltaY1*deltaY1 + deltaZ1*deltaZ1) {
                    // Use the second cover point's transform (stored in coverTransformRaw)
                    retPosition[1] = outOrientation;
                    *retPosition = coverTransformRaw[0];
                    return 1;
                }
            }
        }
        // If the above condition failed, return the original transform from first cover point
        retPosition[1] = *(undefined4 *)&coverTransformRaw; // uStack_2c
        *retPosition = outOrientation;                       // unaff_EBX
        return 1;
    }

    // First validation path: check if the target is valid
    isValid = FUN_008754e0(&coverTransformRaw);
    if (isValid != '\0') {
        // Get the component pointer again
        if (*(int *)(this + 0x54) == 0) {
            baseClassPtr = (int *)0x0;
        } else {
            baseClassPtr = (int *)(*(int *)(this + 0x54) - 0x48);
        }

        // Call vtable method at 0x1c8 to get a transform (overwrites coverTransformRaw)
        (*(code **)(*baseClassPtr + 0x1c8))(&coverTransformRaw, &coverTransformRaw);

        // Re-validate the component
        if (*(int *)(this + 0x54) == 0) {
            playerPtr = 0;
        } else {
            playerPtr = *(int *)(this + 0x54) - 0x48;
        }

        isValid = FUN_00883670(&stackRef, *(undefined4 *)(this + 0x50), playerPtr);
        if (isValid == '\0') {
            // Output the transform
            *outputStruct = (int)stackRef;
            outputStruct[1] = tempEAX;
            return 1;
        }
    }

    // All checks failed
    return 0;
}
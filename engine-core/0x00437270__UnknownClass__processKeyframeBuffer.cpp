// FUNC_NAME: UnknownClass::processKeyframeBuffer

int UnknownClass::processKeyframeBuffer() {
    int* currentPtr = *(int**)(this + 0xC); // +0xC: current position in buffer
    int* endPtr = *(int**)(this + 0x8);     // +0x8: end of buffer

    if ((int*)endPtr <= currentPtr) return 0;
    if (currentPtr == nullptr) return 0;
    if (*currentPtr != 7 && *currentPtr != 2) return 0;

    currentPtr += 2; // skip 2 ints (8 bytes)
    if (endPtr <= currentPtr) return 0;
    if (currentPtr == nullptr) return 0;

    if (*currentPtr != 3) {
        if (*currentPtr != 4) return 0;
        int result = validateRotationType(&local_30); // FUN_00636850
        if (result == 0) return 0;
    }

    int* ptr1 = (int*)(*(int*)(this + 0xC) + 0x10);
    if (endPtr <= ptr1) return 0;
    if (ptr1 != nullptr) {
        if (*ptr1 != 3) {
            if (*ptr1 != 4) return 0;
            int result = validateRotationType(&local_30);
            if (result == 0) return 0;
        }

        int* ptr2 = (int*)(*(int*)(this + 0xC) + 0x18);
        if (endPtr <= ptr2) return 0;
        if (ptr2 != nullptr) {
            if (*ptr2 != 3) {
                if (*ptr2 != 4) return 0;
                int result = validateRotationType(&local_30);
                if (result == 0) return 0;
            }

            int* basePtr = *(int**)(this + 0xC);
            int handle;
            if (basePtr < endPtr && basePtr != nullptr) {
                if (*basePtr == 2) {
                    handle = basePtr[1];
                } else if (*basePtr == 7) {
                    handle = basePtr[1] + 0x10;
                } else {
                    handle = 0;
                }
            } else {
                handle = 0;
            }

            float roll = getFloatComponent(this, 2);  // FUN_006259b0(param_1,2)
            float pitch = getFloatComponent(this, 3); // FUN_006259b0(param_1,3)
            float yaw = getFloatComponent(this, 4);   // FUN_006259b0(param_1,4)

            int worldMatrix = 0;
            getWorldMatrix(&worldMatrix, 0); // FUN_005e73f0(&local_3c,0)
            if (worldMatrix != 0) {
                float baseVec[3];
                getMatrixTranslation(worldMatrix, baseVec); // FUN_005e7a40(local_3c, &local_20)

                float offsetVec[3];
                offsetVec[0] = 0.0f;
                offsetVec[1] = 0.0f;
                offsetVec[2] = yaw; // local_38

                float tempVec[3];
                transformVector(&tempVec, &offsetVec, &DAT_00e2e5f8, pitch * DAT_00e445c8); // FUN_004a0370
                transformVector(&offsetVec, &tempVec, &DAT_00e2e604, roll * DAT_00e445c8); // FUN_004a0370

                float finalPos[3];
                finalPos[0] = baseVec[0] + offsetVec[0];
                finalPos[1] = baseVec[1] + offsetVec[1];
                finalPos[2] = baseVec[2] + offsetVec[2];

                setPosition(handle, finalPos); // FUN_005e6580
            }
        }
    }
    return 0;
}
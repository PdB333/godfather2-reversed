// FUNC_NAME: GameObject::processMessage
void __thiscall GameObject::processMessage(void* thisPtr, int msgId, int extraData)
{
    // msgId constants (likely hashed strings)
    const int MSG_SET_VISIBILITY = 0xD444EA9D; // -0x2bbb2563
    const int MSG_PROCESS_EFFECTS = 0x2FF1B913;
    const int MSG_CLEAR_OBJECTS = 0x5A4FAEC5;

    // Recast this pointer to access fields
    GameObject* self = (GameObject*)thisPtr;

    if (msgId == MSG_SET_VISIBILITY)
    {
        // Direct visibility toggle (param=1 indicates on)
        setVisibility(self, 1);
        return;
    }

    if (msgId == MSG_PROCESS_EFFECTS)
    {
        // Main processing: iterates over child objects and triggers effects
        // Call virtual destroy? (+0x28)
        (*(void (__thiscall**)(GameObject*))(*((int*)self) + 0x28))(self);
        self->somePointer1 = 0; // +0x20

        uint32_t processedCount = 0;
        if (self->childCount != 0) // +0x1C
        {
            int childOffset = 0; // Each child has 0x70 bytes
            do
            {
                // Get pointer to current child data (at base + offset)
                int* childData = *(int**)(childOffset + 0x40 + self->childArray); // +0x40 within child data
                if (childData != 0 && (*(char*)(childData + 0xD8) == 0x07 || *(char*)(childData + 0xD8) == 0x06))
                {
                    // Some effect-related state detected
                    engineGetCameraAndTime(); // FUN_009f9620
                    engineGetDistanceAndAngle(&localDistance, &localAngle); // FUN_009f4860

                    if (localDistance <= g_globalDistanceThreshold) // DAT_00e44598
                    {
                        localDistance = g_minDistance; // DAT_00e2b1a4
                    }
                    if (g_minAngle < localAngle) // DAT_00e2b1a4
                    {
                        localAngle = g_maxAngle; // DAT_00e2eff4
                    }

                    if (localEffectPtr != 0 && localEffectPtr[3] == 0x0B) // +0x0C in effect data
                    {
                        uint32_t sourceHandle = *(uint32_t*)(childData + 0x180);
                        TlsGetValue(g_tlsIndex); // DAT_01139810
                        int newEffectId = allocateMemory(0x20, 0x27); // size, tag
                        *(uint16_t*)(newEffectId + 4) = 0x20;
                        localEffectPtr = (uint32_t*)duplicateObject(sourceHandle); // FUN_00a64b00
                    }

                    // Apply effect with distance
                    applyEffect(localEffectPtr, localDistance, &localData); // FUN_009e44f0
                    // Pack some data (likely a pointer index)
                    localData = ((self->childArray + childOffset) >> 2) | 0xC0000000;
                    localByte1 = 4;
                    localByte2 = 5;

                    TlsGetValue(g_tlsIndex);
                    int packetSize = allocateMemory(0x200, 0x2D);
                    *(uint16_t*)(packetSize + 4) = 0x200;
                    uint32_t* serializedData = (uint32_t*)encodeMessage(&localData); // FUN_009f4640

                    // Reference counting for old effect
                    if (localEffectPtr != 0 && *(short*)(localEffectPtr + 1) != 0)
                    {
                        *(short*)((int)localEffectPtr + 6) -= 1;
                        if (*(short*)((int)localEffectPtr + 6) == 0)
                        {
                            (*(void (__thiscall**)(uint32_t*))*localEffectPtr)(localEffectPtr + 0); // vtable destroy
                        }
                    }

                    // Reset child data
                    resetChildData(childData); // FUN_004b5800
                    *(uint16_t*)((int)serializedData + 0x96) = 0;

                    // Replace pointer in child array with serialized data
                    int childBase = self->childArray;
                    uint32_t* oldPtr = *(uint32_t**)(childBase + childOffset + 0x40);
                    if (oldPtr != serializedData)
                    {
                        if (oldPtr != 0 && *(short*)(oldPtr + 1) != 0)
                        {
                            *(short*)((int)oldPtr + 6) -= 1;
                            if (*(short*)((int)oldPtr + 6) == 0)
                            {
                                (*(void (__thiscall**)(uint32_t*))*oldPtr)(oldPtr);
                            }
                        }
                        *(uint32_t**)(childBase + childOffset + 0x40) = serializedData;
                        if (*(short*)(serializedData + 1) != 0)
                        {
                            *(short*)((int)serializedData + 6) += 1;
                        }
                    }

                    // Store first processed child if none stored yet
                    if (self->somePointer1 == 0)
                    {
                        self->somePointer1 = childBase + childOffset;
                    }

                    // Get engine pointer and register message
                    void* engineObj = (*(void* (__thiscall**)(int))(*(int*)(self->engineBase + 8) + 0x20))(); // FUN_004b7200 pattern
                    int audioSystem = (*(int (__thiscall**)(void*))(*(int*)engineObj + 0x1C))(engineObj);
                    (*(void (__thiscall**)(uint32_t*, int))(*(int*)*(int*)(audioSystem + 0x54) + 0x38))(serializedData, audioSystem);
                    engineFinishProcessing(); // FUN_009f01a0
                }
                else
                {
                    // Not in effect state, do nothing
                    engineSkipEffect(); // FUN_009f4240(4,1,0)
                }

                if (extraData != 0)
                {
                    self->extraPointer = extraData; // +0x24
                }

                childOffset += 0x70;
                processedCount++;
            } while (processedCount < self->childCount);
        }

        // Cleanup
        finalizeProcessing(self); // FUN_004a61b0
        (*(void (__thiscall**)(GameObject*))(*((int*)self) + 0x24))(self);
        return;
    }

    if (msgId == MSG_CLEAR_OBJECTS)
    {
        int offset = 0;
        processedCount = 0;
        if (self->childCount != 0)
        {
            do
            {
                if (*(int*)(offset + 0x40 + self->childArray) != 0)
                {
                    if (extraData != 0)
                    {
                        self->extraPointer = extraData;
                    }
                    if (self->extraPointer != 0)
                    {
                        processExtraPointer(self->extraPointer); // FUN_009f1f90
                        releaseExtraPointer(); // FUN_009f0190
                    }
                }
                processedCount++;
                offset += 0x70;
            } while (processedCount < self->childCount);
        }
    }
}
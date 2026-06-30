// FUNC_NAME: processAnimationInputs (global animation system function)
// Address: 0x00529050
// Role: Processes a list of animation input entries (e.g., damage/hit data) and updates global animation state

void processAnimationInputs(int inputSetPtr, int entryCount)
{
    float globalScale = DAT_00e35654;
    float threshold = DAT_00e2e780;
    bool bAnyAboveThreshold = false;
    bool bAllSameSecond = true;

    uint flagMaskNoBit0 = 0; // bitmask of entries with flags &1 ==0
    uint flagMaskBit1 = 0;   // bitmask of entries with flags &2 !=0

    uint index = 0;
    // Loop over each input entry (each entry is 0x20 bytes)
    // Entries begin at offset 0xC from inputSetPtr
    float* pEntryFloat = (float*)(inputSetPtr + 0xC);
    while (index < entryCount)
    {
        // Check if first float of entry >= threshold
        if (threshold <= pEntryFloat[0])
        {
            bAnyAboveThreshold = true;
        }

        // Check flags at pEntryFloat[2] (offset +8 within entry)
        uint flags = (uint)pEntryFloat[2];
        if ((flags & 1) == 0)
        {
            flagMaskNoBit0 |= (1 << index);
        }
        if ((flags & 2) != 0)
        {
            flagMaskBit1 |= (1 << index);
        }

        // Compare second float of entry with the second float of the first entry (inputSetPtr+0x10)
        if (pEntryFloat[1] != *(float*)(inputSetPtr + 0x10))
        {
            bAllSameSecond = false;
        }

        // Scale the base floats (first three floats of inputSetPtr) by entry's first float * globalScale
        float fVal = *pEntryFloat;
        float scaled = fVal * globalScale;
        // These operations are on the three floats before the current entry (base of inputSetPtr)
        *(pEntryFloat - 3) = scaled * *(pEntryFloat - 3); // base[0]
        *(pEntryFloat - 2) = scaled * *(pEntryFloat - 2); // base[1]
        *(pEntryFloat - 1) = scaled * *(pEntryFloat - 1); // base[2]

        // Set entry's first float based on its fourth float
        if (pEntryFloat[3] == 0.0f)
        {
            *pEntryFloat = 0.0f;
        }
        else
        {
            *pEntryFloat = scaled;
        }

        // Move to next entry (8 floats forward, i.e., 0x20 bytes)
        index++;
        pEntryFloat += 8;
    }

    if (bAnyAboveThreshold)
    {
        // --- Pad entries to 4 if less than 4 ---
        if (entryCount < 4)
        {
            int* pExtra = (int*)(inputSetPtr + entryCount * 0x20 + 0x10);
            int fillCount = 4 - entryCount;
            do {
                *(pExtra - 1) = 0;
                *pExtra = 0;
                *(pExtra + 1) = 1; // flags? Setting third word to 1
                pExtra += 8;
                fillCount--;
            } while (fillCount != 0);
        }

        // --- Process animation slot 0-4 (likely blend layers) ---
        int slotIdx = 0;
        uint animHandle = DAT_011f3910;
        do {
            if ((slotIdx == 4) && (animHandle != 0))
            {
                // Setup animation clip from handle
                uint clipDataOffset = animHandle * 0x38;
                bool8* clipData = (clipDataOffset < 0x1000) ? (&DAT_011a0f28 + clipDataOffset) : 0;
                setAnimationClip(animHandle, clipData); // FUN_00606830
                animHandle = DAT_011f3910; // reload
            }
            slotIdx++;
        } while (slotIdx < 5);

        // --- Set animation state IDs (DAT_012058d0 and DAT_00f15988) ---
        // These appear to be min/max constraints for animation clip indices
        forceMinGlobalAnimationID(&DAT_012058d0, 0x16);
        forceMaxGlobalAnimationID(&DAT_00f15988, 0x16);
        DAT_011f3a30 = 1;
        forceMinGlobalAnimationID(&DAT_012058d0, 7);
        forceMaxGlobalAnimationID(&DAT_00f15988, 7);
        DAT_011f39f4 = 0;
        forceMinGlobalAnimationID(&DAT_012058d0, 0xe);
        forceMaxGlobalAnimationID(&DAT_00f15988, 0xe);
        DAT_011f3a10 = 0;
        forceMinGlobalAnimationID(&DAT_012058d0, 0x19);
        forceMaxGlobalAnimationID(&DAT_00f15988, 0x19);
        DAT_011f3a3c = 5;
        forceMinGlobalAnimationID(&DAT_012058d0, 0x18);
        forceMaxGlobalAnimationID(&DAT_00f15988, 0x18);
        DAT_011f3a38 = 0;
        forceMinGlobalAnimationID(&DAT_012058d0, 0xf);
        forceMaxGlobalAnimationID(&DAT_00f15988, 0xf);
        DAT_011f3a14 = 0;
        forceMinGlobalAnimationID(&DAT_012058d0, 0x1b);
        forceMaxGlobalAnimationID(&DAT_00f15988, 0x1b);
        DAT_011f3a44 = 1;

        setAnimationState(1, 2, 1); // FUN_00417cf0

        // --- Process a list of something (slot 0-19) ---
        uint currentID = DAT_01218ea8;
        uint slot = 0;
        do {
            if (DAT_01218e50[slot*2] == currentID) {
                if (slot < 20) {
                    DAT_01218e54[slot*2] &= 0xFFFFFFFC;
                }
                break;
            }
            slot++;
        } while (slot < 20);

        int oldSlot = DAT_011f38f0;
        int oldVal = DAT_011f38f4;
        DAT_011f38f0 = currentID;
        DAT_011f38f4 = 0;
        switchAnimationSlot(0, oldSlot, oldVal); // FUN_00609340

        // --- Clear animation handles ---
        int oldHandle1 = DAT_011f3914;
        bool hadHandle = DAT_011f3910 != 0;
        DAT_011f3910 = 0;
        DAT_011f3914 = 0;
        if (hadHandle || (oldHandle1 != 0))
        {
            // Vtable call on some object at DAT_01205750 +0x9c
            (*(code**)(**DAT_01205750 + 0x9c))(DAT_01205750, 0);
        }

        setSomeColor(0,0,0,1.0f,1.0f); // FUN_0060db60

        // --- Check and modify some clip ---
        if ((DAT_01218ea0 != 0xFFFFFFFF) && (DAT_01218ea0 < 0x1000))
        {
            int clipIdx = DAT_01218ea0;
            bool8* clipData = &DAT_011a0f28 + clipIdx * 0x38;
            if (clipData && (clipData[0] < 4))
            {
                if (*(int*)(&DAT_011a0f44 + clipIdx * 0x38) != 0)
                {
                    modifyClipFlags(*(int*)(&DAT_011a0f44 + clipIdx * 0x38), 0x110000); // FUN_00606e60
                }
                *(uint*)(&DAT_011a0f34 + clipIdx * 0x38) = 
                    (*(uint*)(&DAT_011a0f34 + clipIdx * 0x38) & 0xFC9D8FFF) | 0x110000;
                updateClip(); // FUN_006189c0
            }
        }

        // --- Set some globals related to animation objects ---
        DAT_01125ba0 = DAT_01219908;
        DAT_01125d78 = -1;
        DAT_01125ba4 = DAT_01125d74;
        if (DAT_012058e8 == &PTR_PTR_01125b90)
        {
            releaseAnimationObject(DAT_01125d74); // FUN_0060a460
            releaseAnimationObject(DAT_01125ba0); // FUN_0060a460
        }
        updateAnimationSystem(); // FUN_00612a60

        if ((DAT_01125ba0 == DAT_01219908) && (DAT_01219928 != 0))
        {
            float zero[4] = {0.0f, 0.0f, 0.0f, 0.0f};
            attachAnimationToObject(DAT_01125ba0, DAT_01219928, zero); // FUN_0060add0
        }

        setupSomething(); // FUN_0053ce90

        // --- Send event (type 0xd) ---
        int* eventData = (int*)allocateEvent(0xd, 4, 0, 1, 0); // FUN_0060cd00
        int val1 = DAT_00e2eff4;
        int val2 = DAT_00e2b1a4;
        if (eventData)
        {
            eventData[0] = DAT_00e2eff4;
            eventData[1] = val1;
            eventData[2] = val2;
            eventData[3] = val1;
            eventData[4] = val2;
            eventData[5] = val2;
            eventData[6] = val1;
            eventData[7] = val2;
            submitEvent(); // FUN_0060cde0
        }

        if (DAT_01125c30 != 0)
        {
            uint idx = DAT_01125c30 & 0xFF;
            if (DAT_011eb8fc[DAT_01125ba4 * 16] != '\0')
                idx += 0x10;
            incrementCounter(idx); // FUN_00618d40
            DAT_011d912c[idx] = 0;
        }

        DAT_012058e8 = 0;
        DAT_012058f0 = 0;
        DAT_01125ba0 = 0;
        DAT_01125ba4 = 0;

        // --- Free animation slots 0-4 ---
        int slotIdx2 = 0;
        do {
            if ((slotIdx2 != 4))
            {
                uint handle = (&DAT_011f38f0)[slotIdx2 * 2];
                if (handle != 0)
                {
                    bool8* clipData = (handle < 0x1000) ? (&DAT_011a0f28 + handle * 0x38) : 0;
                    setAnimationClip(handle, clipData);
                }
            }
            slotIdx2++;
        } while (slotIdx2 < 5);

        // --- More animation ID clamping ---
        forceMinGlobalAnimationID(&DAT_012058d4, 0xa8);
        forceMaxGlobalAnimationID(&DAT_00f1598c, 0xa8);
        DAT_011f3c78 = 0xf;
        forceMinGlobalAnimationID(&DAT_012058d4, 0xbe);
        forceMaxGlobalAnimationID(&DAT_00f1598c, 0xbe);
        DAT_011f3cd0 = 0xf;

        // --- Process flag masks ---
        uint currentAnimHandle = DAT_01218ea8;
        if (flagMaskNoBit0 != 0)
        {
            setSomeColor(0,0,0,1.0f,1.0f);
            if ((currentAnimHandle != 0xFFFFFFFF) && (currentAnimHandle < 0x1000))
            {
                int clipIdx = currentAnimHandle;
                bool8* clipData = &DAT_011a0f28 + clipIdx * 0x38;
                if (clipData && (clipData[0] < 4))
                {
                    if (*(int*)(&DAT_011a0f44 + clipIdx * 0x38) != 0)
                    {
                        modifyClipFlags(*(int*)(&DAT_011a0f44 + clipIdx * 0x38), 0x100000);
                    }
                    *(uint*)(&DAT_011a0f34 + clipIdx * 0x38) = 
                        (*(uint*)(&DAT_011a0f34 + clipIdx * 0x38) & 0xFC9C8FFF) | 0x100000;
                    updateClip();
                }
            }
            processSpecialFlag(); // FUN_0053c6f0
            updateAnimationSystem();
            if (((DAT_0121bc20 == DAT_01219900) && (int h1 = DAT_01219924, h1 != 0)) ||
                ((DAT_0121bc20 == DAT_01198e74 && (int h2 = DAT_0121be80, h2 != 0))))
            {
                attachAnimationToObject(DAT_0121bc20, h1 ? h1 : h2, &DAT_011f6680);
            }
            if (*DAT_0121be7c != 0)
            {
                stopAnimation(); // FUN_006063b0
            }

            // Compute scaling factors from currentAnimHandle
            bool8* clipData = (currentAnimHandle < 0x1000) ? (&DAT_011a0f28 + currentAnimHandle * 0x38) : 0;
            float scaleX = DAT_00e2b198 / (float)*(ushort*)(clipData + 2);
            float scaleY = DAT_00e2b198 / (float)*(ushort*)(clipData + 4);
            float offsetY = DAT_00e44564 - scaleY;
            float offsetX = scaleX;
            if (DAT_0121be7c[7] != 0)
            {
                float params[4] = {scaleX, scaleY, offsetX, offsetY};
                attachAnimationToObject(DAT_0121bc24, DAT_0121be7c[7], params);
            }
            applyFlagMask(flagMaskNoBit0); // FUN_00417f50

            // Send event again (different data)
            eventData = (int*)allocateEvent(0xd, 4, 0, 1, 0);
            val1 = DAT_00e2eff4;
            val2 = DAT_00e2b1a4;
            if (eventData)
            {
                eventData[0] = DAT_00e2eff4;
                eventData[1] = val2;
                eventData[2] = 0;
                eventData[3] = 0;
                eventData[4] = val2;
                eventData[5] = val2;
                eventData[6] = val2;
                eventData[7] = 0;
                eventData[8] = val2;
                eventData[9] = val1;
                eventData[10] = val2;
                eventData[11] = val2;
                eventData[12] = val1;
                eventData[13] = val1;
                eventData[14] = 0;
                eventData[15] = val2;
                submitEvent();
            }

            if (DAT_0121bcb0 != 0)
            {
                uint idx = DAT_0121bcb0 & 0xFF;
                if (DAT_011eb8fc[DAT_0121bc24 * 16] != '\0')
                    idx += 0x10;
                incrementCounter(idx);
                DAT_011d912c[idx] = 0;
            }

            DAT_012058e8 = 0;
            DAT_012058f0 = 0;
            DAT_0121bc20 = 0;
            DAT_0121bc24 = 0;

            if (flagMaskBit1 != 0)
            {
                applyFlagMask(flagMaskBit1);
                setAnimationState(3, 2, 2);
                DAT_01219954 = DAT_012198fc;
                DAT_01219950 = DAT_01219900;
                DAT_01219a6c = 4;
                setupAnotherState(); // FUN_00530a60
                if ((currentAnimHandle != 0xFFFFFFFF) && (currentAnimHandle < 0x1000))
                {
                    int clipIdx = currentAnimHandle;
                    bool8* clipData = &DAT_011a0f28 + clipIdx * 0x38;
                    if (clipData && (clipData[0] < 4))
                    {
                        if (*(int*)(&DAT_011a0f44 + clipIdx * 0x38) != 0)
                        {
                            modifyClipFlags(*(int*)(&DAT_011a0f44 + clipIdx * 0x38), 0x110000);
                        }
                        *(uint*)(&DAT_011a0f34 + clipIdx * 0x38) = 
                            (*(uint*)(&DAT_011a0f34 + clipIdx * 0x38) & 0xFC9D8FFF) | 0x110000;
                        updateClip();
                    }
                }
                finalizeAnotherState(); // FUN_00530df0

                eventData = (int*)allocateEvent(0xd, 4, 0, 1, 0);
                if (eventData)
                {
                    eventData[0] = DAT_00e2eff4;
                    eventData[1] = val2;
                    eventData[2] = 0;
                    eventData[3] = 0;
                    eventData[4] = val2;
                    eventData[5] = val2;
                    eventData[6] = val2;
                    eventData[7] = 0;
                    eventData[8] = val2;
                    eventData[9] = val1;
                    eventData[10] = val2;
                    eventData[11] = val2;
                    eventData[12] = val1;
                    eventData[13] = val1;
                    eventData[14] = 0;
                    eventData[15] = val2;
                    submitEvent();
                }

                if (DAT_012199e0 != 0)
                {
                    uint idx = DAT_012199e0 & 0xFF;
                    if (DAT_011eb8fc[DAT_01219954 * 16] != '\0')
                        idx += 0x10;
                    incrementCounter(idx);
                    DAT_011d912c[idx] = 0;
                }

                DAT_01219950 = 0;
                DAT_01219954 = 0;
                DAT_012199e4 = 0;
                DAT_012199e8 = 0;
            }

            DAT_012058f0 = 0;
            DAT_012058e8 = 0;
            resetAnimationSystem(1); // FUN_00609890

            forceMinGlobalAnimationID(&DAT_012058d4, 0xa8);
            forceMaxGlobalAnimationID(&DAT_00f1598c, 0xa8);
            forceMinGlobalAnimationID(&DAT_012058d4, 0xbe);
            // Note: max not set here in original? It continues.
        }

        DAT_011f3cd0 = 0xf;
        DAT_011f3c78 = 0xf;

        // --- Update slot using current ID ---
        int currentID2 = DAT_012058a4;
        if (DAT_012054dc != 0)
        {
            currentID2 = *(int*)(DAT_012054dc + 0x16c);
        }

        uint slot2 = 0;
        do {
            if (DAT_01218e50[slot2*2] == currentID2) {
                if (slot2 < 20) {
                    DAT_01218e54[slot2*2] &= 0xFFFFFFFC;
                }
                break;
            }
            slot2++;
        } while (slot2 < 20);

        int oldSlot2 = DAT_011f38f0;
        int oldVal2 = DAT_011f38f4;
        DAT_011f38f4 = 0;
        DAT_011f38f0 = currentID2;
        switchAnimationSlot(0, oldSlot2, oldVal2);

        setSomeColor(0,0,0,1.0f,1.0f);

        if (DAT_012234d4 == '\0')
        {
            // --- Set animation state IDs again (different pattern) ---
            forceMinGlobalAnimationID(&DAT_012058d0, 0x16);
            forceMaxGlobalAnimationID(&DAT_00f15988, 0x16);
            DAT_011f3a30 = 1;
            forceMinGlobalAnimationID(&DAT_012058d0, 7);
            forceMaxGlobalAnimationID(&DAT_00f15988, 7);
            DAT_011f39f4 = 0;
            forceMinGlobalAnimationID(&DAT_012058d0, 0x19);
            forceMaxGlobalAnimationID(&DAT_00f15988, 0x19);
            DAT_011f3a3c = 5;
            forceMinGlobalAnimationID(&DAT_012058d0, 0x18);
            forceMaxGlobalAnimationID(&DAT_00f15988, 0x18);
            DAT_011f3a38 = 0;
            forceMinGlobalAnimationID(&DAT_012058d0, 0xf);
            forceMaxGlobalAnimationID(&DAT_00f15988, 0xf);
            DAT_011f3a14 = 0;
            forceMinGlobalAnimationID(&DAT_012058d0, 0x1b);
            forceMaxGlobalAnimationID(&DAT_00f15988, 0x1b);
            DAT_011f3a44 = 1;

            setAnimationState(1, 2, 6);

            DAT_01125ba0 = DAT_01219908;
            DAT_01125d78 = entryCount - 1;
            if ((bAllSameSecond) && (1 < entryCount))
            {
                DAT_01125d78 = entryCount + 2;
            }
            DAT_01125ba4 = DAT_01125c34[DAT_01125d78 * 0xb];

            if (DAT_012058e8 == &PTR_PTR_01125b90)
            {
                releaseAnimationObject(DAT_01125ba4);
                releaseAnimationObject(DAT_01125ba0);
            }
            updateAnimationSystem();
            if ((DAT_01125ba0 == DAT_01219908) && (DAT_01219928 != 0))
            {
                float zero[4] = {0.0f};
                attachAnimationToObject(DAT_01125ba0, DAT_01219928, zero);
            }

            // Modify clip using currentAnimHandle
            if ((currentAnimHandle != 0xFFFFFFFF) && (currentAnimHandle < 0x1000))
            {
                int clipIdx = currentAnimHandle;
                bool8* clipData = &DAT_011a0f28 + clipIdx * 0x38;
                if (clipData && (clipData[0] < 4))
                {
                    if (*(int*)(&DAT_011a0f44 + clipIdx * 0x38) != 0)
                    {
                        modifyClipFlags(*(int*)(&DAT_011a0f44 + clipIdx * 0x38), 0x100000);
                    }
                    *(uint*)(&DAT_011a0f34 + clipIdx * 0x38) = 
                        (*(uint*)(&DAT_011a0f34 + clipIdx * 0x38) & 0xFC9C8FFF) | 0x100000;
                    updateClip();
                }
            }

            setupAnotherState(); // FUN_0053cdc0

            // Process each entry again?
            int idx2 = 0;
            int clipDataPtr = getClipData(currentAnimHandle); // FUN_00606370
            int* pEntry = (int*)(inputSetPtr + 0xC);
            while (idx2 < entryCount)
            {
                if (DAT_01125c38[DAT_01125d78 * 0xb + idx2] != 0)
                {
                    attachAnimationToObject(DAT_01125ba4, DAT_01125c38[DAT_01125d78 * 0xb + idx2], pEntry);
                }
                // Compute scale
                float scaleX = *(float*)(inputSetPtr + 0x10) * DAT_00e2cd54 / (float)*(ushort*)(clipDataPtr + 2);
                float scaleY = *(float*)(inputSetPtr + 0x10) * DAT_00e2cd54 / (float)*(ushort*)(clipDataPtr + 4);
                float offsetY = DAT_00e44564 - scaleY;
                float offsetX = scaleX;
                if (DAT_01125c48[DAT_01125d78 * 0xb + idx2] != 0)
                {
                    float params[4] = {scaleX, scaleY, offsetX, offsetY};
                    attachAnimationToObject(DAT_01125ba4, DAT_01125c48[DAT_01125d78 * 0xb + idx2], params);
                }
                idx2++;
                pEntry += 8; // next entry (0x20 bytes)
            }

            // Send event
            eventData = (int*)allocateEvent(0xd, 4, 0, 1, 0);
            if (eventData)
            {
                eventData[0] = DAT_00e2eff4;
                eventData[1] = val1;
                eventData[2] = val2;
                eventData[3] = val1;
                eventData[4] = val2;
                eventData[5] = val2;
                eventData[6] = val1;
                eventData[7] = val2;
                submitEvent();
            }

            if (DAT_01125c30 != 0)
            {
                uint idx = DAT_01125c30 & 0xFF;
                if (DAT_011eb8fc[DAT_01125ba4 * 16] != '\0')
                    idx += 0x10;
                incrementCounter(idx);
                DAT_011d912c[idx] = 0;
            }

            DAT_012058e8 = 0;
            DAT_012058f0 = 0;
            DAT_01125ba0 = 0;
            DAT_01125ba4 = 0;
        }

        // --- Final animation state clamping ---
        forceMinGlobalAnimationID(&DAT_012058d0, 0x16);
        forceMaxGlobalAnimationID(&DAT_00f15988, 0x16);
        DAT_011f3a30 = 1;
        forceMinGlobalAnimationID(&DAT_012058d0, 7);
        forceMaxGlobalAnimationID(&DAT_00f15988, 7);
        DAT_011f39f4 = 1;
        forceMinGlobalAnimationID(&DAT_012058d0, 0xe);
        forceMaxGlobalAnimationID(&DAT_00f15988, 0xe);
        DAT_011f3a10 = 1;
        forceMinGlobalAnimationID(&DAT_012058d0, 0x19);
        forceMaxGlobalAnimationID(&DAT_00f15988, 0x19);
        DAT_011f3a3c = 7;
        forceMinGlobalAnimationID(&DAT_012058d0, 0x18);
        forceMaxGlobalAnimationID(&DAT_00f15988, 0x18);
        DAT_011f3a38 = 0;
        forceMinGlobalAnimationID(&DAT_012058d0, 0xf);
        forceMaxGlobalAnimationID(&DAT_00f15988, 0xf);
        DAT_011f3a14 = 0;
        forceMinGlobalAnimationID(&DAT_012058d0, 0x1b);
        forceMaxGlobalAnimationID(&DAT_00f15988, 0x1b);
        DAT_011f3a44 = 0;

        setAnimationState(1, 5, 6);
    }
}
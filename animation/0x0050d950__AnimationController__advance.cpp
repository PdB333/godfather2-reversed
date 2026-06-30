// FUNC_NAME: AnimationController::advance

#include <cstdint>

// Core animation update function
// Processes animation slots, advances timers, triggers animation events, handles finish conditions
bool AnimationController::advance(float deltaTime)
{
    // Thread-local pointer to global game state (via FS segment)
    int* pGlobalState = *(int**)(*(int*)(__readfsdword(0x2c)) + 0x2c);
    // Also: int* pGlobal = **(int**)(fs:0x2c);

    // Get animation data pointer
    int* pAnimData = *(int**)(this + 0x24);
    // Check for pause flag (0x10000000) – if set, force deltaTime to zero
    if (*(uint32_t*)(pAnimData + 0x10c) & 0x10000000)
        deltaTime = 0.0f;

    // Get something at this+0x10 (maybe base pointer for actor/object)
    int basePtr = *(int*)(this + 0x10);
    int* pBaseWithOffset = (int*)(pGlobalState[2] + basePtr); // pGlobalState[2] = *(int*)(pGlobalState+8)

    // Check flag at (pBaseWithOffset) bit 0x10 -> set flag 0x800
    if (*(uint8_t*)pBaseWithOffset & 0x10)
        *(uint32_t*)(this + 0x2c) |= 0x800;

    // Advance main timer at this+0x44
    float timer = *(float*)(this + 0x44) + deltaTime;
    *(float*)(this + 0x44) = timer;

    // Check threshold in anim data (offset 200)
    float threshold = *(float*)(pAnimData + 200);
    uint32_t flags = *(uint32_t*)(this + 0x2c);
    if ((threshold > 0.0f) && ((flags & 4) == 0) && ((flags & 0x800) == 0) && (threshold <= timer))
    {
        *(uint32_t*)(this + 0x2c) = flags | 0x800;
        *(float*)(this + 0x44) = threshold;
        char canPlay = FUN_005098a0(); // possibly check if animation can start
        if (canPlay)
        {
            uint32_t* pFlag = (uint32_t*)(pGlobalState[2] + basePtr);
            *pFlag |= 1;
        }
    }

    pAnimData = *(int**)(this + 0x24);
    // Secondary timeout check using offset 0x11c
    bool bTimedOut = false;
    if (*(float*)(pAnimData + 0x11c) > 0.0f && *(float*)(this + 0x44) >= *(float*)(pAnimData + 0x11c))
        bTimedOut = true;

    // Decay effect – this+0x94 (float) stored a value that decays to zero
    if (*(float*)(this + 0x94) != 0.0f)
    {
        if ((float)PTR_FUN_00e4462c < *(float*)(pAnimData + 0x180))
        {
            float decay = *(float*)(this + 0x94) - (deltaTime / *(float*)(pAnimData + 0x180)) * *(float*)(pAnimData + 0x17c);
            *(float*)(this + 0x94) = decay;
            if (*(float*)(pAnimData + 0x17c) <= 0.0f)
            {
                if (decay >= 0.0f) decay = 0.0f;
            }
            else
            {
                if (decay <= 0.0f) decay = 0.0f;
            }
            if (decay == 0.0f)
                *(uint32_t*)(this + 0x94) = 0;
        }
        *(float*)(this + 0x90) += *(float*)(this + 0x94) * deltaTime;
    }

    // Slot processing loop
    uint16_t slotsActive = *(uint16_t*)(this + 0x74); // number of active slots
    uint16_t slotIndex = *(uint16_t*)(this + 0x76);   // current slot index in circular buffer
    uint32_t slotCount = (uint32_t)slotsActive;
    uint32_t currentSlot = (uint32_t)slotIndex;
    int triggeredCount = 0;
    int savedSlotBase = 0;
    int savedSlotExtra = 0;
    uint32_t savedSlotOffset = 0;
    uint32_t wrappedIndex = currentSlot;

    if (slotCount != 0)
    {
        do
        {
            slotCount--;
            // Compute pointer to slot array entry (each entry is a pointer to a slot of size 0x50)
            int* pSlotEntry = (int*)(this + 0xb0 + ((currentSlot >> 3) * 8)); // array of 8-byte entries?
            uint32_t slotMask = currentSlot & 7;
            int slotOffset = slotMask * 0x50;

            // Pointer to slot data (float timer at slot base + slotMask*4)
            float* pSlotTimer = (float*)(*pSlotEntry + slotMask * 4 + pGlobalState[2]);
            // Pointer to slot info (additional data)
            int* pSlotInfo = (int*)(pGlobalState[2] + *pSlotEntry + slotOffset);

            // Check slot active flag (byte at offset 0x54, bit 2)
            if ((*(uint8_t*)(pSlotInfo + 0x54) & 2) == 0)
            {
                int* pAnimData2 = *(int**)(this + 0x24);
                float duration = *(float*)(pAnimData2 + 0xcc);
                if (*(uint8_t*)(pAnimData2 + 0x10c) & 2)
                {
                    // Complex duration calculation using multipliers
                    duration = (float)(int)(*(float*)(pAnimData2 + 0x178) * *(float*)(pAnimData2 + 0xcc)) + DAT_00e2b1a4;
                    duration *= *(float*)(*(int*)(this + 0x24) + 0x174);
                    if (*(uint32_t*)(*(int*)(this + 0x24) + 0x108) & 0x20000000)
                    {
                        duration += (*(float*)(pSlotInfo + 0x58) - DAT_00e2b1a4) * *(float*)(*(int*)(this + 0x28) + 0xc);
                    }
                    if (duration < 0.0f) duration = 0.0f;
                }

                // Check if slot should trigger
                if ((duration >= 0.0f && duration < *pSlotTimer + deltaTime) || bTimedOut)
                {
                    triggeredCount++;
                    FUN_0050c9a0(this, pSlotEntry); // trigger slot action
                    uint8_t* pFlag = (uint8_t*)(*pSlotEntry + slotOffset + 0x54 + pGlobalState[2]);
                    *pFlag |= 1;
                    char animState = *(char*)(this + 0x5b);
                    if (animState != 0 && animState != 3 && animState != 5)
                        FUN_0050fdc0(pSlotEntry); // maybe finish slot
                    *pSlotTimer = duration;
                    savedSlotBase = *pSlotEntry;
                    savedSlotExtra = pSlotEntry[1];
                    savedSlotOffset = slotMask;
                }
                else
                {
                    *pSlotTimer += deltaTime;
                    char animState = *(char*)(this + 0x5b);
                    if (animState != 0 && animState != 3 && animState != 5)
                    {
                        if ((*(uint8_t*)(*pSlotEntry + slotOffset + 0x54 + pGlobalState[2]) & 1) == 0)
                            FUN_00510110(this, pSlotEntry, slotMask, deltaTime); // update slot progress
                    }
                }
            }
            else
            {
                // Clear flag bit 2
                *(uint8_t*)(pSlotInfo + 0x54) &= 0xfd;
            }

            currentSlot++;
            if ((int)*(int16_t*)(this + 0x5c) <= (int)currentSlot)
                currentSlot -= (int)*(int16_t*)(this + 0x5c);
        } while (slotCount != 0);

        if (triggeredCount != 0)
        {
            uint32_t newSlotIndex = (uint32_t)(uint16_t)(slotIndex + triggeredCount);
            if (*(int16_t*)(this + 0x5c) <= (int)newSlotIndex)
                newSlotIndex -= *(int16_t*)(this + 0x5c);

            *(int*)(this + 0x54) += triggeredCount;
            slotsActive -= (uint16_t)triggeredCount;

            // Check if we need to build transformation matrix
            if ((*(uint8_t*)(pGlobalState[2] + basePtr) & 8) != 0)
            {
                pAnimData = *(int**)(this + 0x24);
                if (*(uint32_t*)(pAnimData + 0x10c) & 0x100)
                {
                    float bonePos = *(float*)(pGlobalState[2] + savedSlotOffset * 4 + savedSlotBase);
                    if (bonePos < 0.0f) bonePos = 0.0f;
                    uint32_t flags2 = 0;
                    float zero = DAT_00e2b1a4;
                    uint32_t counter = *(uint32_t*)(this + 0x54);
                    if ((*(uint32_t*)(pAnimData + 0x10c) & 0xc00) == 0)
                    {
                        FUN_0050a9d0(this, &savedSlotBase, local_40); // get bone transform
                        if ((*(uint32_t*)(pAnimData + 0x10c) & 0x400) == 0)
                            flags2 |= 2;
                        if ((*(uint32_t*)(pAnimData + 0x10c) & 0x800) == 0)
                            flags2 |= 4;
                    }
                    FUN_0051ab70(*(int*)(this + 4), local_50); // get world matrix
                    *(uint32_t*)(this + 0x54) = ((int)counter < 0) - 1 & counter;
                }
            }
        }
    }

    *(uint16_t*)(this + 0x76) = (uint16_t)currentSlot;
    *(uint16_t*)(this + 0x74) = slotsActive;

    // Special flag handling
    uint32_t animFlags = *(uint32_t*)(*(int*)(this + 0x24) + 0x10c);
    if (animFlags & 0x80000000)
    {
        FUN_0050d5e0();
        FUN_00533fb0();
    }

    animFlags = *(uint32_t*)(*(int*)(this + 0x24) + 0x10c);
    if ((animFlags & 0x18) && *(int*)(this + 0x70) != 0)
    {
        FUN_004eb6a0(*(int*)(this + 0x10) + 0x80 + pGlobalState[2], animFlags >> 4 & 0xffffff01);
        int* pSomething = (int*)(pGlobalState[2] + *(int*)(this + 0x10));
        FUN_0056b230(local_50, pSomething + 0x10, pSomething + 0x50, 3);
        pSomething[0x5c] = 0;
        pSomething[0x6c] = 0;
        pSomething[0x7c] = 0;
    }

    // Decrease internal timer
    *(float*)(this + 0x3c) -= deltaTime;

    if (deltaTime != 0.0f && (*(uint32_t*)(*(int*)(this + 4) + 0xc) & 0x20000) == 0 && !bTimedOut)
    {
        int splitCount = 2;
        float remainingDelta = deltaTime;
        if (deltaTime <= DAT_00e449ac)
            splitCount = 1;
        do
        {
            splitCount--;
            if (*(float*)(this + 0x3c) > 0.0f)
                break;
            // Attempt to subdivide using fun_0050d660
            FUN_0050d660(*(int16_t*)(this + 0x74), 0, &pSlotTimer);
            if (remainingDelta <= 0.0f)
                break;
        } while (splitCount > 0);
    }

    bool bFinished = false;
    if (*(int16_t*)(this + 0x74) == 0)
    {
        uint32_t flags3 = *(uint32_t*)(this + 0x2c);
        if ((flags3 & 0x10) || (*(uint32_t*)(*(int*)(this + 4) + 0xc) & 0x20000))
        {
            int16_t finishThreshold = *(int16_t*)(*(int*)(this + 0x24) + 0x118);
            if (finishThreshold < 0)
            {
                if ((*(uint8_t*)(*(int*)(this + 0x10) + pGlobalState[2]) & 2) && !bTimedOut)
                {
                    // Do nothing, go to end
                }
                else
                {
                    bFinished = true;
                    *(uint32_t*)(this + 0x2c) = flags3 | 8;
                }
            }
            else
            {
                bFinished = (int)finishThreshold <= *(int*)(this + 0x50);
                if (bFinished)
                    *(uint32_t*)(this + 0x2c) = flags3 | 8;
            }
        }
    }
    else
    {
        *(uint32_t*)(this + 0x2c) &= ~8;
    }

    // Additional flag logic
    uint32_t flags4 = *(uint32_t*)(this + 0x2c);
    if ((flags4 & 4) && (flags4 & 0x10))
        *(uint32_t*)(this + 0x2c) = flags4 | 0x800;

    if (*(uint32_t*)(this + 0x2c) & 8)
    {
        float threshold2 = *(float*)(*(int*)(this + 0x24) + 200);
        if (threshold2 <= 0.0f)
        {
            if (!(*(uint32_t*)(this + 0x2c) & 0x10))
                goto skipSetFlag;
        }
        else if (*(float*)(this + 0x44) < threshold2)
            goto skipSetFlag;
        // Set animation completion flag
        uint32_t* pFlag2 = (uint32_t*)(*(int*)(this + 0x10) + pGlobalState[2]);
        *pFlag2 |= 1;
    }
skipSetFlag:

    // Handle special zoom state (offset 0x108 bit 0x2000)
    if ((*(uint32_t*)(*(int*)(this + 0x24) + 0x108) & 0x2000) &&
        (*(int*)(*(int*)(this + 4) + 0xb0) == 4) &&
        (*(float*)(this + 0x98) < DAT_00e2b1a4))
    {
        int* pSomething2 = *(int**)(*(int*)(this + 4) + 0xc0);
        float acceleration = *(float*)(this + 0x9c) * deltaTime + *(float*)(this + 0x98);
        *(float*)(this + 0x98) = acceleration;
        if (DAT_00e2b1a4 < acceleration)
            *(float*)(this + 0x98) = DAT_00e2b1a4;
        int16_t limit = (int16_t)(int)(((float)(*(int16_t*)(pSomething2 + 2) - 1) + DAT_00e2e210) * *(float*)(this + 0x98));
        *(int16_t*)(this + 0x5e) = limit;
        if (*(int16_t*)(pSomething2 + 2) - 1 < (int)limit)
            *(int16_t*)(this + 0x5e) = *(int16_t*)(pSomething2 + 2) - 1;
    }

    // Copy world matrix from (this+0x10+0x80) to this+0x80
    int* sourceMatrix = (int*)(*(int*)(this + 0x10) + 0x80 + pGlobalState[2]);
    int m0 = sourceMatrix[0];
    int m1 = sourceMatrix[1];
    int m2 = sourceMatrix[2];
    int m3 = sourceMatrix[3];
    *(int*)(this + 0x80) = m0;
    *(int*)(this + 0x84) = m1;
    *(int*)(this + 0x88) = m2;
    *(int*)(this + 0x8c) = m3;

    *(float*)(this + 0x30) = deltaTime;

    return bFinished;
}
// FUNC_NAME: EffectPoolManager::acquireSlot
float * __thiscall EffectPoolManager::acquireSlot(int thisPtr, int ownerEntity)
{
    float *currentSlot;
    float *bestSlot;
    float *slotWithMaxDist;
    float *candidateSlot;
    int index;
    float baseValue;
    int tempInt;
    float maxDistance;
    float distance;
    float randomScale;

    baseValue = DAT_01205228; // some base constant (e.g., time or position)
    candidateSlot = (float *)0x0;
    float *slotArray = (float *)(thisPtr + 0xCC); // array of 8 slots (each 16 bytes), offset +0xCC
    index = 0;
    bestSlot = (float *)0x0;
    slotWithMaxDist = (float *)0x0;
    maxDistance = DAT_00d5ccf8; // initial smallest distance (maybe FLT_MAX)

    do {
        if (index > 7) {
            // All slots occupied; select the best candidate among used slots
            if (bestSlot == (float *)0x0) {
                bestSlot = slotWithMaxDist;
                if (slotWithMaxDist == (float *)0x0) {
                    bestSlot = candidateSlot;
                }
            }
            randomScale = _DAT_00d5c458;
            tempInt = FUN_0077dd80(); // some condition (e.g., mute or pause)
            if (tempInt != 0) {
                randomScale = 0.0f;
            }
            tempInt = _rand();
            // Initialize first field with a randomized value based on baseValue and randomScale
            *bestSlot = (float)tempInt * DAT_00e44590 * _DAT_00e51764 * randomScale + baseValue;
            bestSlot[1] = 0.0f; // second field set to zero
            currentSlot = bestSlot + 2; // pointer to third field (linked list node head)

            // Determine the owner's list head address; ownerEntity is a pointer,
            // the list head at offset 0x48 of owner is used.
            if (ownerEntity == 0) {
                baseValue = 0.0f;
            } else {
                baseValue = (float)(ownerEntity + 0x48); // reinterpret pointer as float (likely wrong)
            }

            // Remove from old list if already linked, then link into new list
            if (*currentSlot != baseValue) {
                if (*currentSlot != 0.0f) {
                    FUN_004daf90(currentSlot); // remove node from linked list
                }
                *currentSlot = baseValue;
                if (baseValue != 0.0f) {
                    // Insert into list: store old head in bestSlot[3], set head to currentSlot
                    bestSlot[3] = *(float *)((int)baseValue + 4);
                    *(float **)((int)baseValue + 4) = currentSlot;
                }
            }
            return bestSlot;
        }

        if (slotArray[index + 2] == 0.0f) { // third field is 0 -> slot is free
            tempInt = 0;
            goto checkCandidate;
        } else {
            // Slot is occupied; compute an identifier from the third field
            tempInt = (int)slotArray[index + 2] - 0x48;
            if ((tempInt == 0) || (slotArray[index + 1] == 0.0f)) {
                goto checkCandidate;
            }
        }
    compareSlot:
        candidateSlot = slotArray + index * 4; // current slot
        slotWithMaxDist = bestSlot;
        if ((tempInt != ownerEntity) &&
            (distance = (float)((uint)(DAT_01205228 - slotArray[index]) & DAT_00e44680),
             candidateSlot = bestSlot,
             maxDistance < distance)) {
            // This slot has a larger "distance" → better candidate for replacement
            candidateSlot = slotArray + index * 4;
            maxDistance = distance;
        }
        index++;
        slotArray += 4; // advance to next slot (16 bytes per slot)
        bestSlot = candidateSlot;
        slotWithMaxDist = slotWithMaxDist;
        if (candidateSlot != (float *)0x0) {
            // If a free slot was found, return it immediately
            return candidateSlot;
        }
    } while (true);
}
// FUNC_NAME: AudioManager::updateSoundSlots
bool __thiscall AudioManager::updateSoundSlots(int this, int soundBankIndex)
{
    bool bProcessed = false;
    bool bActive = false;
    int iManager;
    float* pfSlotField;
    int loopCount;
    float fDuration;
    int iSlotIndex;
    float afLocal18[2];
    float fStack_10;

    // Check if the sound manager is initialized and the bank index is valid.
    if ((*(int*)(this + 0x580) != 0) && (soundBankIndex >= 0) &&
        (*(int*)(this + soundBankIndex * 0x10 + 0x81c4) != 0))
    {
        iManager = FUN_005e9d10(); // likely get the audio system manager
        pfSlotField = (float*)(this + 0x8344); // points to array of slots (each 0x5c bytes)
        loopCount = 10; // There are 10 slot entries
        do {
            // Access slot fields via negative offsets relative to pfSlotField.
            // pfSlotField points to a field inside the slot struct (maybe at offset 0x58?).
            int field_state   = *(int*)(pfSlotField - 0x25);  // at -0x94 bytes from pfSlotField
            int field_bankId  = *(int*)(pfSlotField - 0x26);  // at -0x98 bytes
            int field_flags   = *(int*)(pfSlotField - 1);     // at -4 bytes
            float field_fade  = *(pfSlotField - 0xf);         // at -0x3c bytes
            float field_flag2 = *(pfSlotField - 0x24);        // at -0x90 bytes

            // Check if this slot is active, belongs to the given bank, and has no "stopped" flag.
            if ((field_state >= 0) && (field_bankId == soundBankIndex) && ((field_flags >> 1 & 1) == 0))
            {
                bActive = true;
                FUN_00ab4db0(&DAT_00e2aea0); // lock/mutex

                // If the slot has a fade factor and is in an initial state (flag2 == 1.4013e-45), transition.
                if ((field_fade != 0.0f) && (field_flag2 == 1.4013e-45f))
                {
                    FUN_00ac2810(); // some audio system call
                    *(float*)(pfSlotField - 0x24) = 2.8026e-45f; // new state value
                }

                // Check the slot's current time and if the manager is active.
                if ((*pfSlotField >= 0.0f) && (iManager != 0))
                {
                    fDuration = 0.0f;
                    FUN_00c9eac0(); // push audio context
                    FUN_00c9cd00(0, &fDuration); // get current audio time

                    if (*pfSlotField <= fDuration)
                    {
                        if (*pfSlotField == fDuration)
                        {
                            // Set a 3D position for the sound
                            FUN_00c9cbe0(*(int*)(this + 0x580), *(int*)(iManager + 0x10), 2, afLocal18);
                            afLocal18[0] = *pfSlotField;
                            FUN_00c9cd40(2, afLocal18); // set audio parameter

                            // Check for a sentinel value (likely "end of stream")
                            if (fStack_10 == DAT_00e2b05c)
                            {
                                *(int*)(pfSlotField - 1) = (int)((uint)*(int*)(pfSlotField - 1) | 2); // set stopped flag
                                bActive = false;
                                *(int*)(pfSlotField - 0x25) = -NAN; // reset state
                                FUN_00c9cd40(1, 0); // clear parameter
                            }
                        }
                    }
                    else
                    {
                        // Slot's time is behind current audio time, so sync and stop.
                        *(int*)(pfSlotField - 1) = (int)((uint)*(int*)(pfSlotField - 1) | 2); // set stopped flag
                        bActive = false;
                        *(int*)(pfSlotField - 0x25) = -NAN; // reset state
                        FUN_00c9cd40(1, 0); // clear parameter
                        *pfSlotField = fDuration; // update slot time
                    }
                    FUN_00c9eae0(); // pop audio context
                }

                if (bActive)
                {
                    // If still active (i.e., slot not stopped), decrement reference count and destroy slot.
                    if (*(int*)(pfSlotField - 0x26) >= 0) // bankID
                    {
                        int* pRefCount = (int*)(this + *(int*)(pfSlotField - 0x26) * 0x10 + 0x81bc);
                        LOCK();
                        *pRefCount = *pRefCount - 1;
                        UNLOCK();
                    }
                    FUN_005ea0d0(); // destroy the slot
                }

                FUN_00ab4e70(); // unlock
                bProcessed = true;
            }

            // Advance to the next slot (each slot is 0x5c bytes)
            pfSlotField = (float*)((int)pfSlotField + 0x5c);
            loopCount--;
        } while (loopCount != 0);
    }

    return bProcessed;
}
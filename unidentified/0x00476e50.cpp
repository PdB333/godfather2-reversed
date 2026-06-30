// FUN_00476e50: AudioChannel::handleEvent

void __thiscall AudioChannel::handleEvent(uint this, int* pEvent)
{
    int iVar1;
    bool bVar2;
    uint soundHandle;
    int iSoundId;
    int iVar4;
    int* pSlot;
    int local_c;
    int local_8;
    byte local_4;

    // gAudioEngine is a global pointer to the audio management system
    int* pAudioEngine = gAudioEngine;

    // Check if the event ID matches this channel's registered event ID
    if (*pEvent == *(int*)(this + 0x14))
    {
        // If sound index is not yet initialized, resolve from handle at +0x1c
        if (*(int*)(this + 0x20) == -1)
        {
            *(int*)(this + 0x20) = getSoundIndexFromHandle(*(int*)(this + 0x1c));
        }

        // If still uninitialized, assert and return
        if (*(int*)(this + 0x20) == -1)
        {
            debugAssert(-(uint)(this != 0x3c) & this); // conditional breakpoint
            return;
        }

        // Retrieve sound ID from the engine's lookup table using the sound index
        // gAudioEngine+0x24 points to a table of sound definitions (0x14 bytes each)
        iSoundId = *(int*)(*(int*)(pAudioEngine + 0x24) + 8 + *(int*)(this + 0x20) * 0x14);
        int eventParam = pEvent[1]; // secondary parameter from the event (e.g., volume modifier)

        // Iterate over the 32 sound slots (each 16 bytes, starting at +0x30)
        pSlot = (int*)(this + 0x30);
        bVar2 = true;
        if (pSlot != (int*)(this + 0xb0))
        {
            do
            {
                // Check if this slot's sound ID matches the one we need to play
                if (iSoundId == *pSlot)
                {
                    // Slot is active (non-zero flag at offset 4)
                    if (pSlot[1] != 0)
                    {
                        // If slot has a positive volume/fade duration (float at offset 12)
                        if (0.0 < (float)pSlot[3])
                        {
                            // Decide whether to apply a random modification (10% chance? trigger random function with parameter 0xC)
                            if ((eventParam == 0) || (iVar4 = randomFloat(0xc), iVar4 == 0))
                            {
                                soundHandle = 0;
                            }
                            else
                            {
                                soundHandle = generateSoundHandle();
                            }
                            // Play sound from this slot with its volume, using optional handle
                            playSound(pSlot + 1, 0, pSlot[3], soundHandle, 0);
                        }
                        else
                        {
                            // Negative or zero volume means stop the sound
                            local_4 = 0;
                            local_c = pSlot[1]; // maybe source ID
                            local_8 = eventParam;
                            stopSound(&local_c, 0);
                        }
                        bVar2 = false;
                    }
                }
                pSlot = pSlot + 4; // advance 16 bytes (4 ints)
            } while (pSlot != (int*)(this + 0xb0));
            if (!bVar2)
            {
                return;
            }
        }

        // Handle reserved sound at +0x24 (an additional sound instance)
        if (*(int*)(this + 0x24) != 0)
        {
            // If reserved sound's volume/timer is not positive, play immediately with no handle
            if (*(float*)(this + 0x2c) <= 0.0)
            {
                playSoundImmediate((int*)(this + 0x24), eventParam, 0);
                return;
            }
            // Otherwise, apply optional random handle as above
            if ((eventParam == 0) || (iVar5 = randomFloat(0xc), iVar5 == 0))
            {
                soundHandle = 0;
            }
            else
            {
                soundHandle = generateSoundHandle();
            }
            // Play the reserved sound with its volume and handle
            playSoundWithVolume((int*)(this + 0x24), *(float*)(this + 0x2c), soundHandle, 0);
        }
    }
    return;
}
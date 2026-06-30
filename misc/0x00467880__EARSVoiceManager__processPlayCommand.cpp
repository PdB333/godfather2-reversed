// FUNC_NAME: EARSVoiceManager::processPlayCommand
unsigned int EARSVoiceManager::processPlayCommand(EARSVoiceManager* thisPtr)
{
    // thisPtr offsets:
    // +0x08: pointer to current write position in command buffer
    // +0x0C: pointer to current read position in command buffer
    // Command buffer entry: 8 bytes { int type; float data; }

    int* readPos = *(int**)(thisPtr + 0x0C);
    int* writePos = *(int**)(thisPtr + 0x08);
    int resultValue = 0;

    // Base of global slot array (128 slots of 0x54 bytes each)
    // DAT_0122346c + 0x14 = gVoiceSlots
    char* slotArrayBase = (char*)(DAT_0122346c + 0x14);

    // Check if buffer has a command to process
    if (readPos != NULL && readPos < writePos)
    {
        int cmdType = *readPos;

        // Validate command type: only 3 (play) and 4 (replay?) are handled
        if (cmdType == 3)
        {
            // Type 3: proceed directly
        }
        else if (cmdType == 4)
        {
            // Type 4: additional validation required
            int validateResult = FUN_00636850(&thisPtr);
            if (validateResult == 0)
            {
                goto WRITE_OUTPUT;
            }
        }
        else
        {
            goto WRITE_OUTPUT;
        }

        // Extract slot index from command data (float rounded to int)
        float rawFloat = *(float*)(readPos + 1); // +4 bytes
        int slotIndex = (int)(rawFloat + 0.5f); // ROUND

        // Bounds check and verify slot owner matches this object
        if ((unsigned int)slotIndex < 128)
        {
            int* slotBase = (int*)(slotArrayBase + slotIndex * 0x54);
            if (*slotBase == (int)thisPtr) // +0x00: owner
            {
                char* slotFlag = (char*)(slotBase + 0x4D / 4); // +0x4D (byte offset)
                if (*slotFlag == 0)
                {
                    // Slot is free – acquire and start playback
                    int acquireResult = FUN_006257d0((int)thisPtr, 2);
                    if (acquireResult != 0)
                    {
                        FUN_006259b0((int)thisPtr, 2);
                        int currentTick = FUN_00b9a1c0();
                        slotBase[1] = currentTick; // +0x04: startTime1
                        slotBase[2] = currentTick; // +0x08: startTime2
                        resultValue = currentTick;
                    }
                }
                else
                {
                    // Slot is active – restart playback
                    *slotFlag = 0;
                    int acquireResult = FUN_006257d0((int)thisPtr, 2);
                    if (acquireResult != 0)
                    {
                        FUN_006259b0((int)thisPtr, 2);
                        unsigned int currentTick = FUN_00b9a1c0();
                        slotBase[1] = currentTick;
                        slotBase[2] = currentTick;
                        resultValue = currentTick;
                    }
                    // Global counter incremented each time a slot is restarted
                    _DAT_01205404++; // +0x01205404
                }
            }
        }
    }

WRITE_OUTPUT:
    // Write result command (type 3, data = resultValue) to output buffer
    int* outputPos = *(int**)(thisPtr + 0x08);
    *outputPos = 3;                      // command type
    *(float*)(outputPos + 1) = (float)resultValue; // data
    *(int**)(thisPtr + 0x08) = outputPos + 2; // advance write pointer by 8 bytes

    return 1;
}
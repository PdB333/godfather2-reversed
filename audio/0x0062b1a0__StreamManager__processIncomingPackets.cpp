// FUNC_NAME: StreamManager::processIncomingPackets
// This function parses a stream of incoming commands/packets from the network or local buffer.
// It reads a block size, a command ID, and a count, then processes each command.

bool StreamManager::processIncomingPackets(void* streamReader)
{
    int* currentReadPtr = *(int**)((char*)streamReader + 0x0C);        // +0x0C: current read pointer
    int* readEndPtr = *(int**)((char*)streamReader + 0x08);            // +0x08: end of readable data
    uint blockSize = 0;
    int commandID = 0;

    // First attempt to read block size from stream header
    if ((currentReadPtr < readEndPtr) && (currentReadPtr != nullptr))
    {
        if (*currentReadPtr == 4) // Tag for block size
        {
            blockSize = currentReadPtr[1] + 0x10;
        }
        else
        {
            int ret = readBlockSizeFromHeader(streamReader); // FUN_00633990
            if (ret != 0)
            {
                blockSize = currentReadPtr[1] + 0x10;
            }
            else
            {
                blockSize = 0;
            }

            // Overflow check (buffer metadata at +0x10)
            int* bufferMeta = *(int**)((char*)streamReader + 0x10); // +0x10: metadata pointer
            uint writeCount = *(uint*)((char*)bufferMeta + 0x20);   // +0x20: written count
            uint readCount = *(uint*)((char*)bufferMeta + 0x24);    // +0x24: read count
            if (writeCount <= readCount)
            {
                handleBufferOverflow(); // FUN_00627360
            }
        }

        if (blockSize != 0)
            goto readCommandPart;
    }

    // Fallback: set error and log
    blockSize = 1; // placeholder? Actually sets iVar3=1 for later use? No, blockSize is local_228.
    logError("string"); // FUN_00627ac0, probably error message

readCommandPart:
    // Read command ID from stream
    currentReadPtr = *(int**)((char*)streamReader + 0x0C);
    if ((currentReadPtr < readEndPtr) && (currentReadPtr != nullptr))
    {
        if (*currentReadPtr == 4)
        {
            commandID = *(int*)((char*)currentReadPtr[1] + 0x0C); // +0x0C offset for ID
        }
        else
        {
            int ret = readBlockSizeFromHeader(streamReader); // FUN_00633990
            if (ret != 0)
            {
                commandID = *(int*)((char*)currentReadPtr[1] + 0x0C);
            }
            else
            {
                commandID = 0;
            }
        }
    }
    else
    {
        commandID = 0;
    }

    // Read count (as float) for number of repetitions
    int* nextPtr = (int*)(*(int*)((char*)streamReader + 0x0C) + 8); // skip current header?
    if ((nextPtr >= readEndPtr) || (nextPtr == nullptr))
        goto fallbackCount;

    float countAsFloat;
    if (*nextPtr == 3) // Tag for direct float
    {
        countAsFloat = (float)nextPtr[1];
    }
    else if (*nextPtr == 4) // Tag for encoded float
    {
        int success = readFloatFromStream((char*)streamReader, &countAsFloat); // FUN_00636850
        if (success == 0)
            goto fallbackCount;
    }
    else
    {
        goto fallbackCount;
    }

    // If float equals sentinel (maybe -1.0?), skip to next block instead
    if (countAsFloat == SENTINEL_VALUE) // DAT_00e2b05c
    {
        while (true)
        {
            currentReadPtr = *(int**)((char*)streamReader + 0x0C);
            if ((currentReadPtr < readEndPtr) && (currentReadPtr != nullptr))
            {
                if (*currentReadPtr == 3)
                    break;
                if (*currentReadPtr == 4)
                {
                    int success = readFloatFromStream((char*)streamReader, &countAsFloat);
                    if (success != 0)
                        break;
                }
            }
            // If none, fallback
            blockSize = 2;
            logError("number"); // PTR_s_number_00e2a8a8
            goto fallbackCount;
        }
    }

    // All good, proceed to execute commands
    {
        char localBuffer[520]; // buffer for command processing? (stack allocated)
        char* bufferPtr = localBuffer;
        uint bufferSize = 0; // uStack_214
        int* streamRef = &streamReader; // iStack_210 = param_1

        int count = (int)countAsFloat;
        for (int i = 0; i < count; i++)
        {
            executeCommand(blockSize, commandID); // FUN_00628b20, processes one iteration
        }

        flushCommandBuffer(); // FUN_00628940
        resetStream(streamReader); // FUN_00626460
    }
    return true;

fallbackCount:
    countAsFloat = 0.0f;
    // Continue to loop below with count=0, so loop is skipped
    goto finish;

finish:
    // Original fallback path sets countAsFloat to 0 and goes to loop
    // But code flow is messy; this is simplified.
    return true; // original returns 1
}
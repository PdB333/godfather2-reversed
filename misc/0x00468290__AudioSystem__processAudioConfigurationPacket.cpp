// FUNC_NAME: AudioSystem::processAudioConfigurationPacket
undefined4 AudioSystem::processAudioConfigurationPacket(StreamReader* reader)
{
    int* currentReadPtr = *(int**)(reader + 0xc);          // +0x0C: current read position
    int* endPtr = *(int**)(reader + 0x8);                   // +0x08: buffer end

    if ((currentReadPtr < endPtr) && (currentReadPtr != nullptr))
    {
        int type = *currentReadPtr;
        if ((type == 4) || (type == 3))
        {
            int paramSize;
            if (type == 4)
            {
                paramSize = currentReadPtr[1] + 0x10;      // size embedded in stream
            }
            else // type 3
            {
                int isValid = checkStreamHasMoreData(reader); // FUN_00633990
                if (isValid == 0)
                {
                    paramSize = 0;
                }
                else
                {
                    paramSize = currentReadPtr[1] + 0x10;
                }
            }

            // Check buffer overflow condition on auxiliary object
            if (*(uint*)(*(int*)(reader + 0x10) + 0x20) <= *(uint*)(*(int*)(reader + 0x10) + 0x24))
            {
                reportBufferOverflow(); // FUN_00627360
            }
        }
        else
        {
            paramSize = 0;
        }

        allocateAudioParamBlock(paramSize); // FUN_004dafd0

        // Initialize global audio parameter structure with default values
        gAudioParams = (AudioParams*)DAT_01223470; // global pointer
        gAudioParams->field_0x08 = DAT_00e2eff4;   // +0x08
        gAudioParams->field_0x0C = DAT_00e2eff4;   // +0x0C
        gAudioParams->field_0x10 = DAT_00e2eff4;   // +0x10
        gAudioParams->field_0x14 = DAT_00e2b1a4;   // +0x14
        gAudioParams->field_0x18 = DAT_00e2b1a4;   // +0x18
        gAudioParams->field_0x1C = 0;              // +0x1C
        gAudioParams->field_0x20 = 0;              // +0x20
        gAudioParams->field_0x3C = 96000;          // +0x3C (sample rate)
        gAudioParams->field_0x24 = 1;              // +0x24
        gAudioParams->field_0x28 = 0xBADBADBA;     // +0x28 (magic)
        gAudioParams->field_0x2C = 0xBEEFBEEF;     // +0x2C (magic)
        gAudioParams->field_0x30 = 0xEAC15A55;     // +0x30 (magic)
        gAudioParams->field_0x34 = 0x91100911;     // +0x34 (magic)
        gAudioParams->field_0x38 = 0;              // +0x38

        // Read additional parameter values from stream (offsets +8, +0x10, +0x18, +0x20, +0x28)
        currentReadPtr = (int*)(*(int*)(reader + 0xc) + 8);
        if ((currentReadPtr < endPtr) && (currentReadPtr != nullptr))
        {
            if ((*currentReadPtr == 3) || ((*currentReadPtr == 4) && (readDoubleFromStream(&localDoubleVar) != 0))) // FUN_00636850
            {
                float val = readFloatFromStream(reader, 2); // FUN_006259b0
                gAudioParams->field_0x1C = val;             // +0x1C
                gAudioParams->field_0x20 = val;             // +0x20
            }
        }

        currentReadPtr = (int*)(*(int*)(reader + 0xc) + 0x10);
        if ((currentReadPtr < endPtr) && (currentReadPtr != nullptr))
        {
            if ((*currentReadPtr == 3) || ((*currentReadPtr == 4) && (readDoubleFromStream(&localDoubleVar) != 0)))
            {
                float val = readFloatFromStream(reader, 3);
                gAudioParams->field_0x14 = val;             // +0x14
            }
        }

        currentReadPtr = (int*)(*(int*)(reader + 0xc) + 0x18);
        if ((currentReadPtr < endPtr) && (currentReadPtr != nullptr))
        {
            if ((*currentReadPtr == 3) || ((*currentReadPtr == 4) && (readDoubleFromStream(&localDoubleVar) != 0)))
            {
                float val = readFloatFromStream(reader, 4);
                gAudioParams->field_0x18 = val;             // +0x18
            }
        }

        currentReadPtr = (int*)(*(int*)(reader + 0xc) + 0x20);
        if ((currentReadPtr < endPtr) && (currentReadPtr != nullptr))
        {
            if ((*currentReadPtr == 3) || ((*currentReadPtr == 4) && (readDoubleFromStream(&localDoubleVar) != 0)))
            {
                float val = readFloatFromStream(reader, 5);
                localDoubleVar = (longlong)roundFloat(val);
                gAudioParams->field_0x3C = (int)localDoubleVar; // +0x3C (overwrites sample rate)
            }
        }

        currentReadPtr = (int*)(*(int*)(reader + 0xc) + 0x28);
        if ((currentReadPtr < endPtr) && (currentReadPtr != nullptr))
        {
            if ((*currentReadPtr == 3) || ((*currentReadPtr == 4) && (readDoubleFromStream(&localDoubleVar) != 0)))
            {
                float val = readFloatFromStream(reader, 6);
                gAudioParams->field_0x10 = val;             // +0x10
            }
        }

        applyAudioParameters((void*)DAT_01223508); // FUN_005dc6e0
    }

    return 0;
}
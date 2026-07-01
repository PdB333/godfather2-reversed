// FUNC_NAME: DebugLogger::writeQueuedMessages
void __fastcall DebugLogger::writeQueuedMessages(void* thisPtr)
{
    // Check if any of the four queued message pointers are non-null
    if (*(int*)((int)thisPtr + 0x54) != 0 ||
        *(int*)((int)thisPtr + 0x58) != 0 ||
        *(int*)((int)thisPtr + 0x5c) != 0 ||
        *(int*)((int)thisPtr + 0x60) != 0)
    {
        // Get the stream/transport object (vtable +0x58 virtual function)
        int* stream = *(int**)((int)thisPtr + 0xC);

        // Get current timestamp (likely from system clock)
        unsigned int rawTimestamp = FUN_00471610();

        // Format timestamp into a string buffer
        char timestampBuffer[76] = {0};
        FUN_0044b4e0(timestampBuffer, rawTimestamp);

        // Prepare structure for virtual call and subsequent flush
        int resultStruct[2] = {0};                            // aiStack_64
        int unknownFlag = -1;                                  // local_58
        int zeroField = 0;                                     // local_54
        resultStruct[1] = 1;                                   // count/handle
        int* streamRef = stream;                               // local_5c

        // Call virtual function at offset 0x58 on stream object
        // Arguments: (0, pointer to resultStruct[1])
        int handle = (*(int(__thiscall**)(int, int, int*))(*(int*)stream + 0x58))(
            (int)stream, 0, &resultStruct[1]);

        // Flush the queued messages using the timestamp and handle
        FUN_004df270(resultStruct, (int)thisPtr + 0x54, timestampBuffer, handle);

        // Clear a potential error/state flag in the result structure
        if (resultStruct[0] != 0)
        {
            *(int*)(resultStruct[0] + 8) = 0;
        }
    }
}
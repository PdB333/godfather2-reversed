// FUNC_NAME: AudioManager::processAudioCommands
// Address: 0x0049e200
// Role: Processes a batch of audio commands (play, stop, fade, etc.) for a given channel/group.
// The class has arrays of byte counts at offsets +0x3e and +0x43 (indexed by param2),
// and a pointer to a pool of 32-byte command structures at +0x4c.
// Each command structure: +0x4 = arg1, +0x8 = objPtr, +0xC = commandType, +0x10 = arg2.

void __fastcall AudioManager::processAudioCommands(void* thisPtr, int channelIndex)
{
    byte* startCountPtr;
    byte* endCountPtr;
    int basePoolPtr;
    uint currentEntry;
    int objPtr;
    int arg1, arg2;
    int loopEnd;

    basePoolPtr = *(int*)((char*)thisPtr + 0x4c);          // pointer to command pool
    endCountPtr = (byte*)((char*)thisPtr + 0x43 + channelIndex); // byte: number of commands to process
    startCountPtr = (byte*)((char*)thisPtr + 0x3e + channelIndex); // byte: start index?

    // Loop from startCount * 0x20 to endCount * 0x20, stepping by 0x20 (32 bytes per command)
    currentEntry = (uint)(*startCountPtr) * 0x20 + basePoolPtr;
    loopEnd = (uint)(*endCountPtr) * 0x20 + basePoolPtr;

    while (currentEntry < loopEnd)
    {
        objPtr = *(int*)(currentEntry + 8);           // object handle or pointer
        if (objPtr != 0)
        {
            arg1 = *(int*)(currentEntry + 4);
            arg2 = *(int*)(currentEntry + 0x10);

            switch (*(byte*)(currentEntry + 0xc))     // command type
            {
                case 0: // Play sound
                    FUN_0060aa90(arg1, objPtr, arg2);
                    break;
                case 1: // Stop sound
                    FUN_0060ac80(arg1, objPtr, arg2);
                    break;
                case 2: // Set volume/fade in
                    FUN_0060ad20(arg1, objPtr, arg2);
                    break;
                case 3: // Fade out
                    FUN_0060add0(arg1, objPtr, arg2);
                    break;
                case 4: // Set parameter
                    FUN_0060b020(arg1, objPtr, arg2);
                    break;
                case 6: // Flush/reset
                    FUN_006063b0();
                    break;
                default:
                    break;
            }
        }
        currentEntry += 0x20;
    }
}
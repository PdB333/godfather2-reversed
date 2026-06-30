// FUNC_NAME: AudioChainManager::buildAudioChain
// Address: 0x005ee090
// Builds an audio processing chain (SndPlayer, Rechannel, Resample, LoPass, MatrixPanner, Sen0)
// and attaches it to the given audio source (thisPtr+0x580) and buffer (thisPtr+0x56c).
// Uses the singleton plugin chain manager (ST_PLUGINCHAIN). Returns 1 on success.

bool __thiscall AudioChainManager::buildAudioChain(void* thisPtr)
{
    // Get the plugin chain manager singleton
    int* pluginChain = (int*)FUN_004dafd0("ST_PLUGINCHAIN");
    // Store it for the caller (in_EAX)
    *in_EAX = pluginChain;

    // Copy the first field of the plugin chain into an array at offset 0x10
    int* arrStart = (int*)((char*)pluginChain + 0x10);
    for (int i = 0; i < 5; i++) {
        *arrStart = *pluginChain;
        arrStart = (int*)((char*)arrStart + 0xc);
    }

    // Iterate over slots starting from slot index 2 (offset 0x28)
    int* slotPtr = (int*)((char*)pluginChain + 0x28); // piVar6
    int slotCount = 5;
    bool built = false;

    do {
        // slotPtr[-5] is flag of slot 0 (offset -20 from slotPtr)
        // slotPtr[2] is the size field of the current slot
        if (slotPtr[-5] == 0 &&
            *(int*)((char*)thisPtr + 0x580) != 0 &&
            *(int*)((char*)thisPtr + 0x56c) != 0 &&
            slotPtr[2] == 0x10)
        {
            FUN_00c9eac0(); // possibly start profiling

            // Add SndPlayer node
            FUN_005e9ba0("SndPlayer");
            {
                int base = *slotPtr;
                int idx = slotPtr[1];
                int* nodeStart = (int*)(base + idx * 0xc);
                nodeStart[-2] = FUN_00c9cd50(0x536e5031); // hash for SndPlayer
                nodeStart[-3] = 0;
                *(char*)(nodeStart - 1) = 6;
            }

            // Add Rechannel node
            FUN_005e9ba0("Rechannel");
            {
                int base = *slotPtr;
                int idx = slotPtr[1];
                int* nodeStart = (int*)(base + idx * 0xc);
                nodeStart[-2] = FUN_00c9cd50(0x52636830); // hash for Rechannel
                nodeStart[-3] = 0;
                *(char*)(nodeStart - 1) = 1;
            }

            // Add Resample node
            FUN_005e9ba0("Resample");
            {
                int base = *slotPtr;
                int idx = slotPtr[1];
                int* nodeStart = (int*)(base + idx * 0xc);
                nodeStart[-2] = FUN_00c9cd50(0x52737030); // hash for Resample
                nodeStart[-3] = 0;
                *(char*)(nodeStart - 1) = 1;
            }

            // Add LoPass node
            FUN_005e9ba0("LoPass");
            {
                int base = *slotPtr;
                int idx = slotPtr[1];
                int* nodeStart = (int*)(base + idx * 0xc);
                nodeStart[-2] = FUN_00c9cd50(0x4c493230); // hash for LoPass
                nodeStart[-3] = 0;
                *(char*)(nodeStart - 1) = 1;
            }

            // Add MatrixPanner node
            FUN_005e9ba0("MatrixPanner");
            {
                int base = *slotPtr;
                int idx = slotPtr[1];
                int* nodeStart = (int*)(base + idx * 0xc);
                nodeStart[-2] = FUN_00c9cd50(0x4d745030); // hash for MatrixPanner
                nodeStart[-3] = 0;
                *(char*)(nodeStart - 1) = 6;
            }

            // Add Sen0 node (string from DAT_00e3f858)
            FUN_005e9ba0(&DAT_00e3f858); // "Sen0"
            {
                int base = *slotPtr;
                int idx = slotPtr[1];
                int* nodeStart = (int*)(base + idx * 0xc);
                nodeStart[-2] = FUN_00c9cd50(0x53656e30); // hash for Sen0
                nodeStart[-3] = 0;
                *(char*)(nodeStart - 1) = 6;
            }

            // Initialize the audio source with this chain
            int newHandle = FUN_00ca55a0(
                *(void**)((char*)thisPtr + 0x580), // audio source
                0,
                slotPtr[1],   // index
                *slotPtr,     // base array
                0
            );
            // Store handle in slot 0's flag and next field
            slotPtr[-5] = newHandle;
            slotPtr[-4] = newHandle + 0x50; // buffer offset
            built = true;

            FUN_00c9eae0(); // stop profiling
        }

        slotPtr = (int*)((char*)slotPtr + 0xc); // move to next slot
        slotCount--;
    } while (slotCount != 0);

    return built;
}
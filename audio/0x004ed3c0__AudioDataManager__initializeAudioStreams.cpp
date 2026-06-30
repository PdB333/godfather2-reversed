// FUNC_NAME: AudioDataManager::initializeAudioStreams

void AudioDataManager::initializeAudioStreams(uint32_t param_1, int param_2, int param_3)
{
    char flagByte;
    uint32_t valueFromGlobal;
    int iVar3;
    uint32_t* allocPtr;
    uint32_t* srcPtr;
    int threadLocalBase;

    // Stack locals: a small RAII object for streaming state
    int streamState;          // local_5c - initialized by constructor
    char isStreamingActive;   // local_58
    uint32_t copyBuffer[7];   // local_50, uStack_4c..uStack_34 (7 dwords)

    iVar3 = DAT_01205504;  // Pointer to some global audio configuration

    FUN_005334b0(&streamState, 0);  // Initialize stream state object to 0

    // Copy 4 dwords from config offset 0x10 to global audio state
    _DAT_01219b40 = *(uint32_t*)(iVar3 + 0x10);
    _DAT_01219b44 = *(uint32_t*)(iVar3 + 0x14);
    _DAT_01219b48 = *(uint32_t*)(iVar3 + 0x18);
    _DAT_01219b4c = *(uint32_t*)(iVar3 + 0x1c);

    // Check if conditional and then maybe load a stream
    if ((DAT_012058e8 == &DAT_01219a70) && (*(int*)(&DAT_01219cac + (uint)DAT_01219b20 * 0x30) != 0))
    {
        FUN_0060add0(DAT_01219a80, *(int*)(&DAT_01219cac + (uint)DAT_01219b20 * 0x30), iVar3 + 0x10);
    }

    // Enforce minimum and maximum thresholds for audio quality/volume
    if (DAT_012058d0 < 0xe) {
        DAT_012058d0 = 0xe;
    }
    if (0xe < DAT_00f15988) {
        DAT_00f15988 = 0xe;
    }

    _DAT_011f3a10 = 0;   // Reset some flag

    flagByte = *(char*)(*(int*)(iVar3 + 0x24) + 0x2e);  // Read a byte from config+0x24->0x2e

    if (DAT_012058d0 < 0x1b) {
        DAT_012058d0 = 0x1b;
    }
    if (0x1a < DAT_00f15988) {
        DAT_00f15988 = 0x1b;
    }

    _DAT_011f3a44 = (uint)(flagByte != '\x03');  // Set based on byte value

    FUN_004ec7a0();  // Some initialization

    streamState = DAT_00e2b1a4;  // Assign global audio stream handle
    if (flagByte == '\x01') {
        streamState = 0;
    }

    FUN_004eccc0(1);  // Set something to 1

    // Check thread-local data and possibly initialize something
    threadLocalBase = *(int*)(*(int*)(unaff_FS_OFFSET + 0x2c) + 8);
    if ((undefined*)(threadLocalBase + 0x50 + *(int*)(iVar3 + 8)) != &DAT_00e2cba0) {
        FUN_00417560();  // Log or create a resource
    }

    FUN_00535220();   // Update audio timing
    FUN_00534ff0(0);  // Set volume (0 = master?)

    if (isStreamingActive == '\0') {
        FUN_00535450(0, streamState);  // Start streaming on channel 0
        isStreamingActive = '\x01';
    }

    // Allocate memory for audio data blocks
    allocPtr = (uint32_t*)FUN_0060cd00(0xd, param_3, 0, 1, 0);
    valueFromGlobal = DAT_00e2b1a4;

    if (allocPtr != (uint32_t*)0)
    {
        // Initialize a local 7-dword structure (probably a buffer description)
        copyBuffer[0] = 0;  // uStack_4c = 0? Wait ordering: local_50, then uStack_4c..uStack_34
        // Actually the ordering from the decompiler: local_50 is first, then uStack_4c, uStack_48, uStack_44, local_40, uStack_3c, uStack_38, uStack_34
        // But the assignment order in the loop: uStack_4c=puVar5[-4]; uStack_48=puVar5[-3]; local_40=*puVar5; uStack_3c=puVar5[1];
        // So the structure is probably: [local_50] [uStack_4c] [uStack_48] [uStack_44] [local_40] [uStack_3c] [uStack_38] [uStack_34] -> 8 dwords but initialized to 0 later.
        // Actually the decompiler shows: uStack_48=0; uStack_4c=0; uStack_34=0; uStack_38=0; uStack_3c=0; local_40=0; uStack_44=DAT_00e2b1a4;
        // So we'll treat copyBuffer[0..6] accordingly.

        copyBuffer[0] = 0;           // local_50
        copyBuffer[1] = 0;           // uStack_4c (initially set to data from param_2)
        copyBuffer[2] = 0;           // uStack_48 (initially set)
        copyBuffer[3] = valueFromGlobal; // uStack_44
        copyBuffer[4] = 0;           // local_40 (initially set)
        copyBuffer[5] = 0;           // uStack_3c
        copyBuffer[6] = 0;           // uStack_38
        // uStack_34 is copyBuffer[7]? Actually there are 8 dwords: local_50, uStack_4c, uStack_48, uStack_44, local_40, uStack_3c, uStack_38, uStack_34
        // The initial zeros set uStack_34 as well? The decompiler sets uStack_34=0, so that's copyBuffer[7]. But we only have 7 slots in our array.
        // Let's adjust: We'll declare an array of 8:

        uint32_t bufferDesc[8];
        bufferDesc[0] = 0; // local_50
        bufferDesc[1] = 0; // uStack_4c
        bufferDesc[2] = 0; // uStack_48
        bufferDesc[3] = valueFromGlobal; // uStack_44
        bufferDesc[4] = 0; // local_40
        bufferDesc[5] = 0; // uStack_3c
        bufferDesc[6] = 0; // uStack_38
        bufferDesc[7] = 0; // uStack_34

        // Now iterate over param_3 records from param_2
        srcPtr = (uint32_t*)(param_2 + 0x10);
        for (int i = 0; i < param_3; i++)
        {
            // Each record is 6 dwords (24 bytes) starting at param_2+0x10
            bufferDesc[1] = srcPtr[-4]; // offset 0 from start? Actually srcPtr points to param_2+0x10, so srcPtr[-4] is at param_2+0x10 - 4*4 = param_2
            bufferDesc[2] = srcPtr[-3]; // param_2+4
            bufferDesc[4] = srcPtr[0];  // param_2+0x10 -> field
            bufferDesc[5] = srcPtr[1];  // param_2+0x14

            // Write data to allocated block (8 dwords per slot)
            allocPtr[0] = 0;                // unused?
            allocPtr[1] = bufferDesc[1];    // uStack_4c
            allocPtr[2] = bufferDesc[2];    // uStack_48
            allocPtr[3] = valueFromGlobal;  // uStack_44 (constant from global)
            allocPtr[4] = bufferDesc[4];    // local_40
            allocPtr[5] = bufferDesc[5];    // uStack_3c
            allocPtr[6] = 0;                // zero
            allocPtr[7] = 0;                // zero

            allocPtr += 8;
            srcPtr += 6;
        }

        // Finalize the data copy
        FUN_0060cde0();
    }

    // Cleanup the stream state object
    FUN_00533720(&streamState);

    return;
}
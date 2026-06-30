// Xbox PDB: EARS::Modules::FilteredNpcRequester::SpawnNpcsNow
// FUNC_NAME: AudioStreamFilter::processGenomeFilter
void __fastcall AudioStreamFilter::processGenomeFilter(int thisPtr)
{
    char isStreamPlaying;
    uint randomThresholdIndex;
    int streamState;
    int readyCheck;
    char isStreamActive;
    int paramA;
    int paramB;
    int filterBuffer[17]; // used for filter output when rateLimit active
    int* filterPtr;
    int sampleCount;
    uint64 randomThreshold;
    int streamBuffer;
    uint loopCount;
    int unused;

    // Check if sample counter (this+0x84) is below 100
    if (*(uint*)(thisPtr + 0x84) < 100) {
        // Pick a random threshold using DAT_010c2678 & DAT_012054b4 (a deterministic sequence?)
        randomThresholdIndex = DAT_010c2678 & DAT_012054b4;
        DAT_012054b4 = DAT_012054b4 + 1;
        // ROUND(randomFloat * DAT_00d5e288) -> likely a frequency multiplier
        randomThreshold = (uint64)FLOAT_ROUND(*(float*)(&DAT_010c2680 + randomThresholdIndex * 4) * DAT_00d5e288);
        // If sample counter is less than the random threshold, skip processing
        if (*(uint*)(thisPtr + 0x84) < (uint)randomThreshold) {
            return;
        }
    }

    randomThresholdIndex = 0;
    sampleCount = 0;
    streamBuffer = 0;
    loopCount = 0;
    unused = 0;
    filterPtr = nullptr;
    randomThreshold &= 0xFFFFFFFF00000000ULL; // keep only high 32 bits? Actually after assignment, it's truncated later.

    // Check if stream pointer (this+0x54) is null
    if (*(int*)(thisPtr + 0x54) == 0) {
        // No stream: create a "Busy" filter and get buffer count from (this+0x88, this+0x8c)
        filterPtr = (int*)createFilter(thisPtr + 0xa0, "Genome Filter (Busy)");
        sampleCount = calculateBufferSamples(*(undefined4*)(thisPtr + 0x88), *(undefined4*)(thisPtr + 0x8c));
    } else {
        // Stream exists: check its state
        streamState = getStreamState(*(int*)(thisPtr + 0x54));
        if ( (streamState != 0) &&
             (readyCheck = isStreamReady(), readyCheck == 0) &&
             (isStreamPlaying = isStreamPlaying(), isStreamPlaying != '\0') ) {
            // Stream is playing and ready: store stream's sample rate? (offset 0x40)
            randomThreshold = CONCAT44((uint)randomThreshold, *(undefined4*)(streamState + 0x40));
            isStreamActive = isStreamActive();
            if (isStreamActive == '\0') {
                // If idle: create "Idle" filter using (this+0x90, this+0x94)
                filterPtr = (int*)createFilter(thisPtr + 0xb0, "Genome Filter (Idle)");
                paramA = *(undefined4*)(thisPtr + 0x90);
                paramB = *(undefined4*)(thisPtr + 0x94);
            } else {
                // If busy: create "Busy" filter using (this+0x88, this+0x8c)
                filterPtr = (int*)createFilter(thisPtr + 0xa0, "Genome Filter (Busy)");
                paramA = *(undefined4*)(thisPtr + 0x88);
                paramB = *(undefined4*)(thisPtr + 0x8c);
            }
            sampleCount = calculateBufferSamples(paramA, paramB);
            // If (this+0x60) is non-null, read stream data into local buffers
            if (*(int*)(thisPtr + 0x60) != 0) {
                readStreamData(streamState, &streamBuffer, &sampleCount);
                // sampleCount updated; randomThresholdIndex becomes loopCount from readStreamData
                randomThresholdIndex = loopCount;
            }
        }
    }

    // Loop if randomThresholdIndex > 0 – appears to process samples/slots
    uint processed = 0;
    if (randomThresholdIndex != 0) {
        do {
            processSampleSlot(thisPtr, 0xffffffff);
            processed++;
        } while (processed < randomThresholdIndex);
    }

    // If filter was created and sampleCount > 0
    if ( (filterPtr != nullptr) && (sampleCount != 0) ) {
        // Check flag bit 1 at offset 0x80; if not set or randomThreshold == 0, submit directly
        if ( ((*(uint*)(thisPtr + 0x80) >> 1) & 1) == 0 || ((uint)randomThreshold == 0) ) {
            submitFilterOutput(filterPtr, sampleCount);
        } else {
            // Rate limiting: copy filterPtr data to local buffer; adjust header fields
            int* dst = filterBuffer;
            for (int i = 0x11; i != 0; i--) {
                *dst = *filterPtr;
                filterPtr++;
                dst++;
            }
            // Overwrite first 4 ints with rate limit parameters
            filterBuffer[0] = 4;       // likely a command/type
            filterBuffer[1] = 4;       // some sub-type
            filterBuffer[2] = (uint)randomThreshold; // rate limit sample count
            filterBuffer[3] = 0;       // padding
            submitFilterOutput(filterBuffer, sampleCount);
            flushFilter();
        }
    }

    // Free buffer if allocated
    if (streamBuffer != 0) {
        freeMemory(streamBuffer);
    }
}
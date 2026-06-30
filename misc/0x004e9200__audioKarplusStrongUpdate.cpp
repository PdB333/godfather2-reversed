// FUNC_NAME: audioKarplusStrongUpdate
// Address: 0x004e9200
// Implementation of a Karplus-Strong string synthesis step:
// Updates a delay line by adding a sample from position (index+2) to position (index-1),
// then advances the write pointer backwards by one step.
// Buffer size is 20, wrapped circularly.

static int sDelayIndex = 0;  // Index into the delay line (global @ 0x0119478c)
static int sDelayBuffer[20]; // Delay line buffer (global @ 0x01194790)

int audioKarplusStrongUpdate(void)
{
    int idxMinusOne = sDelayIndex - 1;  // Write position
    int idxPlusTwo  = sDelayIndex + 2;  // Read position (future sample)

    // Wrap indices modulo 20 (0x14)
    if (idxMinusOne < 0)
    {
        idxMinusOne = 19; // 0x13
    }
    else if (idxPlusTwo > 19)
    {
        idxPlusTwo = sDelayIndex - 18; // Wrap for positions >19 (e.g., 20->0, 21->1)
    }

    // Karplus-Strong combination: sum two delayed samples and store at write position
    sDelayBuffer[idxMinusOne] = sDelayBuffer[idxMinusOne] + sDelayBuffer[idxPlusTwo];

    // Update the index to the new write position
    sDelayIndex = idxMinusOne;

    // Return the new output sample
    return sDelayBuffer[idxMinusOne];
}
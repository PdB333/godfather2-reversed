// FUNC_NAME: ChunkReader::readNextByte

void __thiscall ChunkReader::readNextByte()
{
    int remaining;
    ChunkState *state;
    uint8_t *newData;
    uint8_t byteOut;
    int newSize;

    state = this->chunkState;                 // this+0x24
    remaining = state->remainingBytes;
    state->remainingBytes = remaining - 1;

    if (remaining == 0) {
        // Current chunk exhausted, fetch a new one
        newData = (uint8_t *)state->getNextChunk(0, state->userData, &newSize);
        if (newData == NULL || newSize == 0) {
            byteOut = 0xFF;                  // EOF marker (0xffffffff truncated)
        } else {
            state->dataPtr = newData;        // +0x04
            state->remainingBytes = newSize - 1;
            byteOut = *newData;
            state->dataPtr = newData + 1;
        }
    } else {
        byteOut = *state->dataPtr;
        state->dataPtr = state->dataPtr + 1;
    }

    this->currentByte = byteOut;              // this+0x00
    this->totalCharsRead++;                    // this+0x04

    if (this->totalCharsRead > 0x7FFFFFFD) {
        errorReport("too many %s (limit=%d)", "lines in a chunk", 0x7FFFFFFD);
    }
}
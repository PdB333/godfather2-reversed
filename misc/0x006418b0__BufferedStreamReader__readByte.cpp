// FUNC_NAME: BufferedStreamReader::readByte
uint BufferedStreamReader::readByte() {
    BufferState* state = *(BufferState**)((char*)this + 4);
    int remaining = state->remaining;
    state->remaining = remaining - 1;
    if (remaining == 0) {
        // Buffer exhausted, try to refill
        int newSize;
        byte* newBuffer = (byte*)state->refillFunc(0, state->refillParam, &newSize);
        if (newBuffer == nullptr || newSize == 0) {
            // Refill failed, signal error
            uint errorResult = FUN_00641890(); // error handling
            return errorResult;
        }
        state->data = newBuffer;
        state->remaining = newSize - 1;
        byte firstByte = *newBuffer;
        state->data = newBuffer + 1;
        return (uint)firstByte;
    } else {
        // Normal read from current position
        byte* currentData = state->data;
        byte b = *currentData;
        state->data = currentData + 1;
        return (uint)b;
    }
}
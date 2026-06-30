// FUNC_NAME: StreamBuffer::advanceState
// Address: 0x00642fc0
// This function appears to handle state transitions for a bit-stream buffer, likely used in networking (EARS engine packet handling).
// It manages a state machine (states 1, 4, and 0xb) and ensures the buffer position does not exceed a limit (0x200).
// The constant 0xfa (250) may represent a header size or alignment boundary.

int StreamBuffer::advanceState(StreamBuffer* thisStream, int* context) // context from ESI register, possible global or parameter
{
    // State machine loop (two passes in the original code, but logically a do-while)
    // Check if next data pointer equals end pointer (indicates empty/unused buffer)
    if (thisStream->nextDataPtr == thisStream->endDataPtr) {
        streamFlush(); // probably flush or reinitialize
        goto skipProcessing;
    }

    streamFlush();

    if (thisStream->state == 0xb) { // state 0xb likely "ready for new data"
        if (thisStream->nextDataPtr == thisStream->endDataPtr)
            goto skipProcessing;
        if (context[0x34 / 4] <= thisStream->bufferPosition) { // check if context capacity is less than position
            streamResize(thisStream->bufferPosition); // increase buffer
            goto skipProcessing;
        }
    }

    streamReset(); // reset stream to initial state for new data

skipProcessing:
    if (thisStream->state == 1) {
        // State 1: checking if buffer has space for at least 0xfa bytes more
        if (context[0x28 / 4] + 0xfa < 0x200) { // compare with context's max allowed size (512)
            int nextValue = streamGetNext(); // get next available slot or token
            thisStream->bufferPosition = nextValue;
            thisStream->state = 4; // transition to state 4
            return nextValue + 0xfa;
        }
    }
    else if (thisStream->state == 4) {
        if (thisStream->bufferPosition + 0xfa < 0x200) {
            return thisStream->bufferPosition + 0xfa;
        }
    }

    // Second pass: re-check conditions (maybe due to state changes from flush/resize)
    streamFlush();
    if (thisStream->state == 0xb) {
        int pos = thisStream->bufferPosition;
        if (thisStream->nextDataPtr == thisStream->endDataPtr) {
            return pos;
        }
        if (context[0x34 / 4] <= pos) {
            streamResize(pos);
            return thisStream->bufferPosition;
        }
    }

    streamReset();
    return thisStream->bufferPosition;
}
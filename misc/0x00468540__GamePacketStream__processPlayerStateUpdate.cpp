// FUNC_NAME: GamePacketStream::processPlayerStateUpdate
int GamePacketStream::processPlayerStateUpdate(int param_1) {
    int *readPtr = *(int **)(param_1 + 0xC); // offset +0xC: current read pointer
    int *endPtr = *(int **)(param_1 + 0x8);  // offset +0x8: end of buffer

    // Check if we have room for a packet header and the first token matches 4 or 3
    if (readPtr < endPtr && readPtr != nullptr &&
        (*readPtr == 4 || *readPtr == 3)) {

        readPtr += 2; // skip header (2 ints?)
        // Check second token equals 1
        if (readPtr < endPtr && readPtr != nullptr && *readPtr == 1) {
            int val1 = readStreamInt(param_1, 1);       // FUN_00625a70: read something from stream, 1 = mode?
            float val2 = streamBitsToFloat(val1);       // FUN_004dafd0: convert integer to float
            applyPlayerStateUpdate(val2);               // FUN_004564f0: apply the update
        }
    }
    return 0;
}
// FUNC_NAME: MultiTrackStream::processStopFlag
// Function at 0x008cac30: checks a flag (bit 1 at +0x5c) and if set, calls stopStream and clears the flag.
// This is likely part of a deferred stop request or cleanup. The called function (0x004b66a0) is named stopStream().
void MultiTrackStream::processStopFlag() {
    // +0x5c: flags byte (bit1 = stop pending?)
    if ((this->flags & 2) != 0) {
        stopStream();                // FUN_004b66a0 - perform actual stop/cleanup
        this->flags &= ~2;           // clear the pending flag
    }
}
// FUNC_NAME: NetConnection::setLastReceivedSeq  
// Address: 0x00704d20  
// Role: Updates the last received sequence number and adjusts the oldest received sequence number if the new sequence is lower (sliding window tracking).  
void __thiscall NetConnection::setLastReceivedSeq(uint32_t seq) {
    // +0xB0: mLastReceivedSeq (most recent received sequence number)
    // +0xAC: mOldestReceivedSeq (lowest received sequence number in the window)
    this->mLastReceivedSeq = seq;
    if (seq < this->mOldestReceivedSeq) {
        this->mOldestReceivedSeq = seq;
    }
}
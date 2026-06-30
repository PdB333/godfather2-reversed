// FUNC_NAME: SequenceNumberManager::getNextSequence
int SequenceNumberManager::getNextSequence(short previousResult) {
    // If previousResult != 0, decrement it and return; otherwise fetch stored sequence from internal structure.
    if (previousResult != 0) {
        return previousResult - 1;
    }
    // +0x24: pointer to a sub-structure containing sequence data
    // +0x26: offset within that sub-structure storing the current sequence number (short)
    return (int)*(short *)(*(int *)((char *)this + 0x24) + 0x26);
}
// FUNC_NAME: BufferIterator::getNextBlockPointer
int BufferIterator::getNextBlockPointer() // __thiscall with this = param_1
{
    // Check: mBuffer pointer must not be null
    if (mBuffer == nullptr) {
        assertionFail();
    }
    // Check: mCurrent pointer must not be at the end (end pointer stored at mBuffer->mEndOffset)
    if (mCurrent == *(int*)(mBuffer + 4)) {
        assertionFail();
    }
    // Return pointer to next block (advance by header size of 12 bytes)
    return mCurrent + 12;
}
// FUNC_NAME: Buffer::releaseBuffer
void __fastcall Buffer::releaseBuffer(int thisPtr)
{
    // local buffer for temporary purposes (likely unused/escaped from optimizer)
    undefined1 localTemp[8];

    // call internal helper to process buffer before release
    // arguments: localTemp, this, this->bufferPointer, this again, bufferPointer again
    internalReleaseHelper(localTemp, thisPtr, *(undefined4**)(thisPtr + 4), thisPtr, *(undefined4**)(thisPtr + 4));

    // free the allocated buffer
    deallocate(*(void**)(thisPtr + 4));  // +0x4: pointer to allocated memory

    // reset pointer and size to zero
    *(undefined4*)(thisPtr + 4) = 0;   // +0x4: buffer pointer
    *(undefined4*)(thisPtr + 8) = 0;   // +0x8: buffer size
}
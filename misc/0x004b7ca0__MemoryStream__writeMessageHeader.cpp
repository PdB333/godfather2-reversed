// FUNC_NAME: MemoryStream::writeMessageHeader
void __thiscall MemoryStream::writeMessageHeader(void *this, int arg0, int arg1)
{
    // this: pointer to MemoryStream object
    // Object layout: this points to a pointer to internal buffer (mBuffer)
    int *bufferPtr = *(int **)this; // dereference this to get mBuffer pointer
    // mBuffer+0x14: current write position pointer (mWriteCursor)
    // Write a fixed global constant as first value (likely a message type identifier)
    *(int **)(bufferPtr + 0x14) = (int *)&PTR_LAB_01124668; // write pointer to fixed global
    // Advance write cursor by 4 bytes
    bufferPtr = (int *)((int)bufferPtr + 0x14);
    *bufferPtr = (int)bufferPtr + 4; // increment mWriteCursor
    // Write second parameter
    *(int **)(bufferPtr + 0x14) = (int *)arg0;
    // Advance write cursor
    *(int *)(bufferPtr + 0x14) = *(int *)(bufferPtr + 0x14) + 4;
    // Write third parameter
    *(int **)(bufferPtr + 0x14) = (int *)arg1;
    // Advance write cursor
    *(int *)(bufferPtr + 0x14) = *(int *)(bufferPtr + 0x14) + 4;
}